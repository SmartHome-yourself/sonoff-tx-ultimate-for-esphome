#include "esphome/core/hal.h"
#include "esphome/core/helpers.h"
#include "esphome/core/log.h"
#include "tx_ultimate_touch.h"

namespace esphome
{
    namespace tx_ultimate_touch
    {
        static const char *const TAG = "tx_ultimate_touch";

        // Hex dump for debug logs ("AA 55 01 ..."); out needs 3 chars per byte + 1.
        static const char *format_frame(char *out, const uint8_t *data, int len)
        {
            out[0] = '\0';
            for (int i = 0; i < len; i++)
            {
                snprintf(out + i * 3, 4, "%02X ", data[i]);
            }
            return out;
        }

        void TxUltimateTouch::setup()
        {
            ESP_LOGI(TAG, "Tx Ultimate Touch is initialized");
        }

        void TxUltimateTouch::loop()
        {
            uint32_t now = millis();
            // Only an idle line makes a partial frame stale: bytes already waiting
            // in the UART buffer arrived in time, the loop was just late.
            if (this->frame_len_ > 0 && !this->available() && now - this->last_byte_ms_ > FRAME_TIMEOUT_MS)
            {
                ESP_LOGV(TAG, "Dropping incomplete frame (%d bytes)", this->frame_len_);
                this->frame_len_ = 0;
            }

            uint8_t byte;
            while (this->available() && this->read_byte(&byte))
            {
                this->last_byte_ms_ = now;
                this->feed_byte_(byte);
            }
        }

        void TxUltimateTouch::feed_byte_(uint8_t byte)
        {
            // Everything outside an AA 55 frame is skipped: line noise, and the
            // plain-text firmware banner the controller prints at power-on.
            if (this->frame_len_ == 0 && byte != FRAME_SYNC_1)
            {
                return;
            }
            if (this->frame_len_ == 1 && byte != FRAME_SYNC_2)
            {
                this->frame_len_ = byte == FRAME_SYNC_1 ? 1 : 0;
                return;
            }

            this->frame_[this->frame_len_++] = byte;

            if (this->frame_len_ < FRAME_HEADER_SIZE)
            {
                return;
            }
            int payload_len = this->frame_[4];
            if (payload_len > FRAME_MAX_PAYLOAD)
            {
                ESP_LOGV(TAG, "Dropping frame with payload length %d", payload_len);
                this->frame_len_ = 0;
                return;
            }
            // The length byte, not the next 0xAA, ends the frame: 0xAA can show
            // up inside the CRC.
            if (this->frame_len_ == FRAME_HEADER_SIZE + payload_len + FRAME_CRC_SIZE)
            {
                this->handle_frame_();
                this->frame_len_ = 0;
            }
        }

        void TxUltimateTouch::handle_frame_()
        {
            int crc_pos = this->frame_len_ - FRAME_CRC_SIZE;
            uint16_t expected = (this->frame_[crc_pos] << 8) | this->frame_[crc_pos + 1];
            uint16_t actual = crc16be(this->frame_ + 2, crc_pos - 2, 0xFFFF);
            if (actual != expected)
            {
                char hex[FRAME_SIZE * 3 + 1];
                ESP_LOGD(TAG, "Dropping frame with bad CRC: %s", format_frame(hex, this->frame_, this->frame_len_));
                return;
            }

            if (this->frame_[3] != FRAME_CMD_TOUCH)
            {
                // Command 07 with no payload is sent once at power-on.
                ESP_LOGD(TAG, "Ignoring frame with command 0x%02X", this->frame_[3]);
                return;
            }

            int bytes[FRAME_SIZE] = {};
            for (int i = 0; i < this->frame_len_; i++)
            {
                bytes[i] = this->frame_[i];
            }
            handle_touch(bytes);
        }

        void TxUltimateTouch::handle_touch(int bytes[])
        {
            char hex[FRAME_SIZE * 3 + 1];
            format_frame(hex, this->frame_, this->frame_len_);
            ESP_LOGV(TAG, "Touch frame: %s", hex);

            if (is_valid_data(bytes))
            {
                send_touch_(get_touch_point(bytes));
            }
            else
            {
                ESP_LOGD(TAG, "Unknown touch frame: %s", hex);
            }
        }

        void TxUltimateTouch::dump_config()
        {
            ESP_LOGCONFIG(TAG, "Tx Ultimate Touch");
        }

        void TxUltimateTouch::send_touch_(TouchPoint tp)
        {
            switch (tp.state)
            {
            case TOUCH_STATE_RELEASE:
                if (tp.x >= 17)
                {
                    tp.x = tp.x - 16;
                    ESP_LOGD(TAG, "Long Press Release (x=%d)", tp.x);
                    this->long_touch_release_trigger_.trigger(tp);
                }
                else
                {
                    ESP_LOGD(TAG, "Release (x=%d)", tp.x);
                    this->release_trigger_.trigger(tp);
                }
                break;

            case TOUCH_STATE_PRESS:
                ESP_LOGD(TAG, "Press (x=%d)", tp.x);
                this->touch_trigger_.trigger(tp);
                break;

            case TOUCH_STATE_SWIPE_LEFT:
                ESP_LOGD(TAG, "Swipe Left (x=%d)", tp.x);
                this->swipe_trigger_left_.trigger(tp);
                break;

            case TOUCH_STATE_SWIPE_RIGHT:
                ESP_LOGD(TAG, "Swipe Right (x=%d)", tp.x);
                this->swipe_trigger_right_.trigger(tp);
                break;

            case TOUCH_STATE_ALL_FIELDS:
                ESP_LOGD(TAG, "Full Touch Release");
                this->full_touch_release_trigger_.trigger(tp);
                break;

            default:
                break;
            }
        }

        bool TxUltimateTouch::is_valid_data(int bytes[])
        {
            if (!(bytes[0] == 170 && bytes[1] == 85 && bytes[2] == 1 && bytes[3] == 2))
            {
                return false;
            }

            int state = get_touch_state(bytes);
            if (state != TOUCH_STATE_PRESS &&
                state != TOUCH_STATE_RELEASE &&
                state != TOUCH_STATE_SWIPE_LEFT &&
                state != TOUCH_STATE_SWIPE_RIGHT &&
                state != TOUCH_STATE_ALL_FIELDS)
            {
                return false;
            }

            if (bytes[6] < 0 && state != TOUCH_STATE_ALL_FIELDS)
            {
                return false;
            }

            return true;
        }

        int TxUltimateTouch::get_x_touch_position(int bytes[])
        {
            int state = bytes[4];
            switch (state)
            {
            case TOUCH_STATE_RELEASE:
                return bytes[5];
                break;

            case TOUCH_STATE_ALL_FIELDS:
                return bytes[5];
                break;

            case TOUCH_STATE_SWIPE_LEFT:
                return bytes[5];
                break;

            case TOUCH_STATE_SWIPE_RIGHT:
                return bytes[5];
                break;

            default:
                return bytes[6];
                break;
            }
        }

        int TxUltimateTouch::get_touch_state(int bytes[])
        {
            int state = bytes[4];

            if (state == TOUCH_STATE_PRESS && bytes[5] != 0)
            {
                state = TOUCH_STATE_RELEASE;
            }

            if (state == TOUCH_STATE_RELEASE && bytes[5] == TOUCH_STATE_ALL_FIELDS)
            {
                state = TOUCH_STATE_ALL_FIELDS;
            }

            if (state == TOUCH_STATE_SWIPE)
            {
                if (bytes[5] == TOUCH_STATE_SWIPE_RIGHT)
                {
                    state = TOUCH_STATE_SWIPE_RIGHT;
                }
                else if (bytes[5] == TOUCH_STATE_SWIPE_LEFT)
                {
                    state = TOUCH_STATE_SWIPE_LEFT;
                }
            }

            return state;
        }

        TouchPoint TxUltimateTouch::get_touch_point(int bytes[])
        {
            TouchPoint tp;

            tp.x = get_x_touch_position(bytes);
            tp.state = get_touch_state(bytes);

            return tp;
        }

    } // namespace tx_ultimate_touch
} // namespace esphome

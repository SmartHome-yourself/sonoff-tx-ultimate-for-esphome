#pragma once

#include "esphome/core/automation.h"
#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/uart/uart_component.h"

namespace esphome
{
    namespace tx_ultimate_touch
    {
        const static uint8_t TOUCH_STATE_RELEASE = 1;
        const static uint8_t TOUCH_STATE_PRESS = 2;
        const static uint8_t TOUCH_STATE_SWIPE = 3;

        const static uint8_t TOUCH_STATE_ALL_FIELDS = 11;

        const static uint8_t TOUCH_STATE_SWIPE_RIGHT = 12;
        const static uint8_t TOUCH_STATE_SWIPE_LEFT = 13;

        // Frames from the touch controller:
        //   AA 55 | 01 | cmd | len | payload[len] | CRC-16/CCITT-FALSE (big endian)
        // The CRC covers everything after the AA 55 sync. Touch events use cmd 02.
        static constexpr uint8_t FRAME_SYNC_1 = 0xAA;
        static constexpr uint8_t FRAME_SYNC_2 = 0x55;
        static constexpr uint8_t FRAME_CMD_TOUCH = 0x02;
        static constexpr int FRAME_HEADER_SIZE = 5;
        static constexpr int FRAME_CRC_SIZE = 2;
        static constexpr int FRAME_MAX_PAYLOAD = 8;
        static constexpr int FRAME_SIZE = FRAME_HEADER_SIZE + FRAME_MAX_PAYLOAD + FRAME_CRC_SIZE;
        // A frame takes about 1 ms on the wire; a longer gap means bytes were lost.
        static constexpr uint32_t FRAME_TIMEOUT_MS = 50;

        struct TouchPoint
        {
            int8_t x = -1;
            int8_t state = -1;
        };

        class TxUltimateTouch : public uart::UARTDevice, public Component
        {
        public:
            Trigger<TouchPoint> *get_touch_trigger() { return &this->touch_trigger_; }
            Trigger<TouchPoint> *get_release_trigger() { return &this->release_trigger_; }
            Trigger<TouchPoint> *get_swipe_left_trigger() { return &this->swipe_trigger_left_; }
            Trigger<TouchPoint> *get_swipe_right_trigger() { return &this->swipe_trigger_right_; }
            Trigger<TouchPoint> *get_full_touch_release_trigger() { return &this->full_touch_release_trigger_; }
            Trigger<TouchPoint> *get_long_touch_release_trigger() { return &this->long_touch_release_trigger_; }

            void set_uart_component(esphome::uart::UARTComponent *uart_component)
            {
                this->set_uart_parent(uart_component);
            }

            void setup() override;
            void loop() override;
            void dump_config() override;

        protected:
            void feed_byte_(uint8_t byte);
            void handle_frame_();
            void send_touch_(TouchPoint tp);
            void handle_touch(int bytes[]);

            TouchPoint get_touch_point(int bytes[]);
            bool is_valid_data(int bytes[]);
            int get_x_touch_position(int bytes[]);
            int get_touch_state(int bytes[]);

            Trigger<TouchPoint> touch_trigger_;
            Trigger<TouchPoint> release_trigger_;
            Trigger<TouchPoint> swipe_trigger_left_;
            Trigger<TouchPoint> swipe_trigger_right_;
            Trigger<TouchPoint> full_touch_release_trigger_;
            Trigger<TouchPoint> long_touch_release_trigger_;

            uint8_t frame_[FRAME_SIZE];
            int frame_len_ = 0;
            uint32_t last_byte_ms_ = 0;

        }; // class TxUltimateTouch

    } // namespace tx_ultimate_touch
} // namespace esphome

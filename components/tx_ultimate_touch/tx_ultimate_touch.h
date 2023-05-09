#pragma once

#include "esphome/core/automation.h"
#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/uart/uart_component.h"
#include "esphome/components/text_sensor/text_sensor.h"

namespace esphome
{
    namespace tx_ultimate_touch
    {
        const static uint8_t TOUCH_STATE_RELEASE = 1;
        const static uint8_t TOUCH_STATE_PRESS = 2;
        const static uint8_t TOUCH_STATE_SWIPE = 3;

        const static uint8_t TOUCH_STATE_ALL_FIELDS = 11;

        const static uint8_t SWIPE_LEFT = 12;
        const static uint8_t SWIPE_RIGHT = 13;

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
            Trigger<TouchPoint> *get_swipe_trigger() { return &this->swipe_trigger_; }
            Trigger<TouchPoint> *get_full_touch_release_trigger() { return &this->full_touch_release_trigger_; }

            void set_status_sensor(text_sensor::TextSensor *text_sensor)
            {
                this->status_text_sensor_ = text_sensor;
            }

            void set_uart_component(esphome::uart::UARTComponent *uart_component)
            {
                this->set_uart_parent(uart_component);
            }

            void setup() override;
            void loop() override;
            void dump_config() override;

        protected:
            void send_touch_(TouchPoint tp);
            void handle_touch(int bytes[]);

            TouchPoint get_touch_point(int bytes[]);
            bool is_valid_data(int bytes[]);
            int get_x_touch_position(int bytes[]);
            int get_touch_state(int bytes[]);

            Trigger<TouchPoint> touch_trigger_;
            Trigger<TouchPoint> release_trigger_;
            Trigger<TouchPoint> swipe_trigger_;
            Trigger<TouchPoint> full_touch_release_trigger_;

            text_sensor::TextSensor *status_text_sensor_;
        }; // class TxUltimateTouch

    } // namespace tx_ultimate_touch
} // namespace esphome
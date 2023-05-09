# sonoff-tx-ultimate-for-esphome


```
substitutions:
  uart_tx_pin: GPIO09
  uart_rx_pin: GPIO10

esphome:
  name: sonoff-tx-ultimate
  friendly_name: sonoff_tx_ultimate

esp32:
  board: esp32dev
  framework:
    type: arduino

# Enable logging
logger:
  hardware_uart: UART2
  level: DEBUG

# Enable Home Assistant API
api:
  encryption:
    key: !secret ESPHOME_ENCRYPTION_KEY

ota:
  password: "24168c1d49d1e8e098ad837bf42730d6"

wifi:
  ssid: !secret wifi_ssid
  password: !secret wifi_password

  # Enable fallback hotspot (captive portal) in case wifi connection fails
  ap:
    ssid: "Sonoff-Tx-Ultimate"
    password: "btALNTuIIoPV"

captive_portal:


external_components:
  - source: /config/esphome/my_components


switch:
  - platform: gpio
    id: relay_1
    name: "L1"
    pin: GPIO18

  - platform: gpio
    id: relay_2
    pin: GPIO17
    name: "L2"

  - platform: gpio
    id: vibra
    pin: GPIO21
    name: "Vibration Motor"

#output:
#  - platform: ledc
#    id: vibra_out
#    pin: GPIO21


light:
  - platform: neopixelbus
    type: GRB
    variant: WS2811
    pin: GPIO13
    num_leds: 28
    name: "NeoPixel Light"
    id: leds
    default_transition_length: 0s
    effects:
      - addressable_rainbow:
          name: "Rainbow"
          speed: 10
          width: 20
      - pulse:
          name: "Pulse"
          transition_length: 1.4s
          update_interval: 1s

#  - platform: monochromatic
#    id: vibra
#    name: "Vibra"
#    output: vibra_out



uart:
  tx_pin: GPIO19
  rx_pin: GPIO22
  id: my_uart
  baud_rate: 115200
  data_bits: 8
  stop_bits: 1
  parity: NONE
#  debug:
#    direction: RX
#    dummy_receiver: false
#    after:
#      timeout: 2s
#      bytes: 2048
#    sequence:
#      - lambda: UARTDebug::log_hex(direction, bytes, ' ');


text_sensor:
  - platform: template
    id: touch_status

tx_ultimate_touch:
  id: tx_touch
  uart: my_uart
  status_sensor: touch_status

  on_press:
    - script.execute: 
        id: touch_led_marker
        pos: !lambda "return touch.x;"
        state: !lambda "return touch.state;"

    - lambda: >
        ESP_LOGD("tx_ultimate_touch", "Touch Position: %d / State: %d", touch.x, touch.state);

  on_release:
    - script.execute: 
        id: touch_led_marker
        pos: !lambda "return touch.x;"
        state: !lambda "return touch.state;"

    - lambda: >
        ESP_LOGD("tx_ultimate_touch", "Touch Position: %d / State: %d", touch.x, touch.state);

  on_swipe_release:
    - script.execute: 
        id: touch_led_marker
        pos: !lambda "return touch.x;"
        state: !lambda "return touch.state;"

    - lambda: >
        ESP_LOGD("tx_ultimate_touch", "Touch Position: %d / State: %d", touch.x, touch.state);

  on_full_touch_release:
    - script.execute: 
        id: touch_led_marker
        pos: !lambda "return touch.x;"
        state: !lambda "return touch.state;"

    - lambda: >
        ESP_LOGD("tx_ultimate_touch", "Touch Position: %d / State: %d", touch.x, touch.state);



script:
  - id: touch_led_marker
    mode: restart
    parameters:
      state: int
      pos: int
    then:
      - if:
          condition:
            lambda: "return state==1;"
          then:
            # RELEASE
            - light.turn_off: leds

          else:
            - if:
                condition:
                  lambda: "return state==2;"
                then:
                  # TOUCH
                  - light.turn_on:
                      id: leds
                      red: 1
                      green: 0
                      blue: 0
                  - delay: 1s
                  - light.turn_off: leds

                else:
                  - if:
                      condition:
                        lambda: "return state==11;"
                      then:
                        # FULL-TOUCH RELEASE
                        - light.turn_on:
                            id: leds
                            effect: "Rainbow"
                        - delay: 1s
                        - light.turn_off: leds

                      else:
                        # SWIPE
                        - if:
                            condition:
                              lambda: "return pos==12;"
                            then:
                              # SWIPE LEFT
                              - light.turn_on:
                                  id: leds
                                  red: 0
                                  green: 1
                                  blue: 0

                            else:
                              # SWIPE RIGHT
                              - light.turn_on:
                                  id: leds
                                  red: 0
                                  green: 0
                                  blue: 1
                        - delay: 1s
                        - light.turn_off: leds


```

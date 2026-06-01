#### Choose language:
[![en](https://img.shields.io/badge/lang-en-red.svg)](https://github.com/SmartHome-yourself/sonoff-tx-ultimate-for-esphome/blob/master/README.md) 
[![de](https://img.shields.io/badge/lang-de-blue.svg)](https://github.com/SmartHome-yourself/sonoff-tx-ultimate-for-esphome/blob/master/README.de.md)


# SONOFF TX Ultimate for ESPHome (Custom Component)

> **Existing installations:** Device configurations are not migrated automatically; running setups require a one-time adjustment.  
> 1. **`packages:`** YAML packages (relays, LEDs, Wi‑Fi, …) are hosted in **[shys-collection](https://github.com/SmartHome-yourself/shys-collection/tree/main/templates/esphome/setups/sonoff-tx-ultimate)**. Update the `packages:` URL in your ESPHome configuration to the new path (see [Installation](#installation)).  
> 2. **`external_components`:** The URL for the external component is unchanged and does not need to be modified — the custom component for touch handling remains in this repository (`sonoff-tx-ultimate-for-esphome`).

This is an ESPHome custom component for the SONOFF TX Ultimate Smart Switch.  
It gives you the ability to use your Switch with ESPHome, including the main features.
Thanks to the on_... actions, you can implement your own functions quickly and easily.  
Flashing via the web installer and then adopting the device in Home Assistant is sufficient to use the pure basic functionalities.

Detected touch events are visualized by short LED signals.  
A short touch on one of the touch surfaces switches the respective relay.
Swipe, long and multi-touch events can be implemented using the on_... actions, for example.
Alternatively, you can also react to swipe and multi-touch via the binary sensors in Home Assistant automations.  
  
&nbsp;  
  
## Detailed video on the TX Ultimate - Custom Component
[![SONOFF TX Ultimate - Custom Component](http://img.youtube.com/vi/naDLhX89enQ/0.jpg)](https://www.youtube.com/watch?v=naDLhX89enQ "SONOFF TX Ultimate - Custom Component")
  
&nbsp;  
  
## Purchase TX Ultimate
If you want to support my project, simply order your next SONOFF devices using the following affiliate link:  
http://itead.cc/product/sonoff-tx-ultimate-smart-touch-wall-switch/ref/85/?campaign=tx-comp  
  
Use the code **DANIELSCHSONOFF** to get an additional 10% off your order.  
  
&nbsp;  
  
## Home Assistant device
The screenshot shows an example of the device in Home Assistant after integration.  
![image](https://github.com/SmartHome-yourself/sonoff-tx-ultimate-for-esphome/assets/705724/86a6f88e-b453-492e-b9cf-ab50b69ad2e9)
  
&nbsp;    
  
# Installation

&nbsp;

## Device setups (YAML packages)

Full ESPHome configurations (standard, US, cover, local, …) with the short filenames (`tx_ult_*.yaml`) live in **[shys-collection](https://github.com/SmartHome-yourself/shys-collection/tree/main/templates/esphome/setups/sonoff-tx-ultimate)**.

Overview on the website: [ESPHome Setups – SONOFF TX Ultimate](https://www.smarthomeyourself.de/diy-collections/esphome/esphome-setups-sonoff-tx-ultimate)

See the [setup README](https://github.com/SmartHome-yourself/shys-collection/blob/main/templates/esphome/setups/sonoff-tx-ultimate/README.md) for package URLs, variants, and substitutions.

This repository contains only the **custom component** and a minimal [component_test.yaml](component_test.yaml) to validate builds.

&nbsp;

## Use the custom component (external)

```
external_components:
  - source:
      type: git
      url: https://github.com/SmartHome-yourself/sonoff-tx-ultimate-for-esphome
      ref: main
    components: [tx_ultimate_touch]
```

&nbsp;

## Local component copy

Copy the [tx_ultimate_touch folder](https://github.com/SmartHome-yourself/sonoff-tx-ultimate-for-esphome/tree/main/components/) into your ESPHome directory and point `external_components` to that path.

&nbsp;

# Configuration (substitutions reference)
All substitutions are optional, but I recommend specifying at least name, friendly_name, and relay_count.  
The pins are already specified by the hardware and therefore do not actually have to be changed.  
  
## Standard Configuration (tx_ultimate.yaml / tx_ult_local.yaml)
```
substitutions:
  name: "shys-tx-ultimate"
  friendly_name: "TX Ultimate"

  relay_count: "2"

  toggle_relay_1_on_touch: "true"
  toggle_relay_2_on_touch: "true"
  toggle_relay_3_on_touch: "true"

  vibra_time: 150ms
  button_on_time: 500ms

  button_brightness: "0.7"
  button_color: "{0,0,100}"

  nightlight: "on"
  nightlight_brightness: "0.2"
  nightlight_color: "{80,70,0}"

  latitude: "50.123456°"
  longitude: "5.654321°"

  touch_brightness: "1"
  touch_color: "{0,100,100}"
  touch_effect: "Scan"

  long_press_brightness: "1"
  long_press_color: "{100,0,0}"
  long_press_effect: ""

  multi_touch_brightness: "1"
  multi_touch_color: "{0,0,0}"
  multi_touch_effect: "Rainbow"

  swipe_left_brightness: "1"
  swipe_left_color: "{0,100,0}"
  swipe_left_effect: ""

  swipe_right_brightness: "1"
  swipe_right_color: "{100,0,70}"
  swipe_right_effect: ""

  relay_1_pin: GPIO18
  relay_2_pin: GPIO17
  relay_3_pin: GPIO27
  relay_4_pin: GPIO23

  vibra_motor_pin: GPIO21
  pa_power_pin: GPIO26

  led_pin: GPIO13
  status_led_pin: GPIO33

  uart_tx_pin: GPIO19
  uart_rx_pin: GPIO22

  audio_lrclk_pin: GPIO4
  audio_bclk_pin: GPIO2
  audio_sdata_pin: GPIO15

  touchpanel_power_pin: GPIO5

```
  
  
## Cover Configuration (tx_ult_cover.yaml)
Parameters differ slightly for blinds.

```
substitutions:
  name: "shys-txult-cover"
  friendly_name: "TX Ultimate Cover"

  relay_count: "3"

  # only used on 3-way switch (relay_count = 3)
  toggle_relay_3_on_touch: "true"

  cover_name: "My Cover"
  cover_open_duration: 25s
  cover_close_duration: 25s

  vibra_time: 150ms
  button_on_time: 500ms

  button_brightness: "0.7"
  button_color: "{0,0,100}"

  nightlight: "on"
  nightlight_brightness: "0.2"
  nightlight_color: "{80,70,0}"

  cover_brightness: "0.7"
  cover_color1: "{255,0,0}"
  cover_color2: "{0,255,0}"

  latitude: "51.132241°"
  longitude: "7.178795°"

  touch_brightness: "1"
  touch_color: "{0,100,100}"
  touch_effect: "Scan"

  boot_brightness: "0.7"
  boot_color1: "{100,0,0}"
  boot_color2: "{100,100,0}"
  boot_effect: "Scan"

  long_press_brightness: "1"
  long_press_color: "{100,0,0}"
  long_press_effect: ""

  multi_touch_brightness: "1"
  multi_touch_color: "{0,0,0}"
  multi_touch_effect: "Rainbow"

  swipe_left_brightness: "1"
  swipe_left_color: "{0,100,0}"
  swipe_left_effect: "Pulse"

  swipe_right_brightness: "1"
  swipe_right_color: "{100,0,70}"
  swipe_right_effect: "Pulse"

  relay_1_pin: GPIO18
  relay_2_pin: GPIO17
  relay_3_pin: GPIO27
  relay_4_pin: GPIO23

  vibra_motor_pin: GPIO21
  pa_power_pin: GPIO26

  led_pin: GPIO13
  status_led_pin: GPIO33

  uart_tx_pin: GPIO19
  uart_rx_pin: GPIO22

  audio_lrclk_pin: GPIO4
  audio_bclk_pin: GPIO2
  audio_sdata_pin: GPIO15

  touchpanel_power_pin: GPIO5
```
  
&nbsp;  
  
**name** _(Default: sonoff-tx-ultimate)_   
The hostname of the device.  
  
**friendly_name** _(Default: TX Ultimate)_   
The name that is displayed in the Frontend.  
  
**relay_count** _(Default: 2)_   
Indicates whether it is the 1, 2 or 3 relay variant.  
The blind configuration only supports the variants with 2 or 3 relays.  
_Possible Values (Integer 1-3)_  
  
**vibra_time** _(Default: 100ms)_  
Specifies the duration of the vibration signal on touch.  
  
**button_on_time** _(Default: 200ms)_  
Specifies how long the binary sensors should remain active as a signal for a touch input.  
  
**toggle_relay_1_on_touch** _(Default: "true")_  
Specifies whether relay 1 should be permanently linked to touchfield 1.  
If set to true, the relay will be triggered every time touchfield 1 is pressed.  
If set to false, only the touch event will be transmitted, but the relay will not be triggered.  
Not available in the blind variant, as relays 1 and 2 are required for motor control.  
  
**toggle_relay_2_on_touch** _(Default: "true")_  
Specifies whether relay 2 should be permanently linked to touchfield 2.  
If set to true, the relay will be triggered every time touchfield 2 is pressed.  
If set to false, only the touch event will be transmitted, but the relay will not be triggered.  
Not available in the blind variant, as relays 1 and 2 are required for motor control.  
  
**toggle_relay_3_on_touch** _(Default: "true")_  
Specifies whether relay 3 should be permanently linked to touchfield 3.  
If set to true, the relay will be triggered every time touchfield 3 is pressed.  
If set to false, only the touch event will be transmitted, but the relay will not be triggered.  
  
**button_brightness** _(Default: "0.7")_  
Sets the brightness level for indicating a relay is turned on.  
  
**button_color** _(Default: "{0,0,100}")_  
Sets the color to display under the button when a relay is turned on.  
The color is specified as an RGB value using an array of 3 integers from 0-100.  
  
**nightlight** _(Default: "on")_  
Specifies whether the nightlight should automatically turn on after sunset.  
To enable automatic on/off functionality, you need to specify your location using latitude and longitude coordinates.  
  
**nightlight_brightness** _(Default: "0.2")_  
Sets the brightness level for the nightlight.  
  
**nightlight_color** _(Default: "{80,70,0}")_  
Sets the color in which the nightlight should glow.  
The color is specified as an RGB value using an array of 3 integers from 0-100.  
  
**latitude** _(Default: "50.123456°")_  
Sets the latitude of your location to determine sunrise and sunset times.  
  
**longitude** _(Default: "5.654321°")_  
Sets the longitude of your location to determine sunrise and sunset times.  
  
**touch_brightness** _(Default: "1")_  
Sets the brightness level for the LEDs used in touch visualization. (Valid values: 0.0 - 1.0)  
  
**touch_color** _(Default: "{0,100,100}")_  
Sets the color for the LEDs used in touch visualization.  
The color is specified as an RGB value using an array of 3 integers from 0-100.  
  
**touch_effect** _(Default: "Scan")_  
Sets the effect for the LEDs used in touch visualization.  
Possible effects:  
- Rainbow  
- Scan  
  
**long_press_brightness** _(Default: "1")_  
Sets the brightness level for the LEDs used in long-press visualization. (Valid values: 0.0 - 1.0)  
  
**long_press_color** _(Default: "{100,0,0}")_  
Sets the color for the LEDs used in long-press visualization.  
The color is specified as an RGB value using an array of 3 integers from 0-100.  
  
**long_press_effect** _(Default: "")_  
Sets the effect for the LEDs used in long-press visualization.  
Possible effects:  
- Rainbow  
- Scan  
  
**multi_touch_brightness** _(Default: "1")_  
Sets the brightness level for the LEDs used in multi-touch visualization. (Valid values: 0.0 - 1.0)  
  
**multi_touch_color** _(Default: "{0,0,0}")_  
Sets the color for the LEDs used in multi-touch visualization.  
The color is specified as an RGB value using an array of 3 integers from 0-100.  
  
**multi_touch_effect** _(Default: "Rainbow")_  
Sets the effect for the LEDs used in multi-touch visualization.  
Possible effects:  
- Rainbow  
- Scan  
  
**swipe_left_brightness** _(Default: "1")_ (Valid values: 0.0 - 1.0)  
Sets the brightness level for the LEDs used in left swipe visualization. (Valid values: 0.0 - 1.0)  
  
**swipe_left_color** _(Default: "{0,100,0}")_  
Sets the color for the LEDs used in left swipe visualization.  
The color is specified as an RGB value using an array of 3 integers from 0-100.  
  
**swipe_left_effect** _(Default: "")_  
Sets the effect for the LEDs used in left swipe visualization.  
Possible effects:  
- Rainbow  
- Scan  
  
**swipe_right_brightness** _(Default: "1")_ (Valid values: 0.0 - 1.0)  
Sets the brightness level for the LEDs used in right swipe visualization. (Valid values: 0.0 - 1.0)  
  
**swipe_right_color** _(Default: "{100,0,70}")_  
Sets the color for the LEDs used in right swipe visualization.  
The color is specified as an RGB value using an array of 3 integers from 0-100.  
  
**swipe_right_effect** _(Default: "")_  
Sets the effect for the LEDs used in right swipe visualization.  
Possible effects:  
- Rainbow  
- Scan  
  
**relay_1_pin** _(Default: GPIO18)_  
Set the GPIO pin for the first relay.  
  
**relay_2_pin** _(Default: GPIO17)_  
Set the GPIO pin for the second relay.  
  
**relay_3_pin** _(Default: GPIO27)_  
Set the GPIO pin for the third relay.  
  
**relay_4_pin** _(Default: GPIO23)_  
Set the GPIO pin for the fourth relay.  
(So far I haven't seen a 4-relay variant. However, it was in the documentation. So here it is.)  
  
**vibra_motor_pin** _(Default: GPIO21)_  
Set the GPIO pin for the vibration motor.  
  
**pa_power_pin** _(Default: GPIO26)_  
Set the GPIO pin for the power amplifier.  
  
**led_pin** _(Default: GPIO13)_  
Set the GPIO pin for RGBIC LED signal.  
  
**uart_tx_pin** _(Default: GPIO19)_  
Set the GPIO pin for UART TX to RX of the touch controller.  
  
**uart_rx_pin** _(Default: GPIO22)_  
Set the GPIO pin for UART RX to TX of the touch controller.  
  
**audio_lrclk_pin** _(Default: GPIO4)_  
Set the GPIO pin for the I2S audio bus Word Select.  
  
**audio_bclk_pin** _(Default: GPIO2)_  
Set the GPIO pin for the I2S audio bus clock.  
  
**audio_sdata_pin** _(Default: GPIO15)_  
Set the GPIO pin for the I2S data.  
  
**cover_name** _(Default: GPIO15)_  
Name of the cover component.  
  
**cover_open_duration** _(Default: 25s)_  
The time it takes for the blind to open.  
  
**cover_close_duration** _(Default: 25s)_  
The time it takes for the blind to close.
  
**cover_brightness** _(Default: 0.7)_  
Brightness of the position indicator for the cover (right side).  
Automatically dims to "nightlight_brightness" when the nightlight mode is activated.  
  
**cover_color1** _(Default: {255,0,0})_  
Color 1 for the position indicator of the cover component.  
  
**cover_color2** _(Default: {0,255,0})_  
Color 2 for the position indicator of the cover component.  
  
&nbsp;  
  
# Actions
All actions are used to react to touch events and to be able to carry out your own actions on touch/swipe.  
The position where the touch surface was touched is available in all actions via Lambda as touch.x.  
The value in touch.x can be an integer 1 (left) - 10 (right).
  
### on_press
Is triggered as soon as a finger touches the surface.  
  
### on_release
Is triggered, if the finger releases the surface.  
The on_release action only fires, when the release event occurs at the same position as the previous press event and if it's not a multi-touch or long-touch event!  
  
### on_swipe_left
Is triggered, if you swipe from right to left side of the surface.  
  
### on_swipe_right
Is triggered, if you swipe from left to right side of the surface.  
  
### on_full_touch_release
Is triggered, if you touch more than one point on the surface.  
  
### on_long_touch_release
Is triggered, if you touch a point on the surface longer than 5 seconds.  
  
&nbsp;  
  
# Example Code
This is an example of a custom touch action.  
It extends the main functionalities of the Sonoff TX Ultimate switch by adding a custom log output when the touch surface is pressed.  
  
Feel free to customize the actions according to your needs.  

```
tx_ultimate_touch:
  id: tx_touch
  uart: my_uart

  on_press:
    - lambda: >
        ESP_LOGD("tx_ultimate_touch.on_press", "My Event: Position: %d / State: %d", touch.x, touch.state);
```  
  
  
# Components

### relay
Depending on the switch variant, the TX has 1-3 relays installed. Therefore there are 3 switches for the relays.  
According to the documentation, there is also a GPIO for a 4th relay, but I am not aware of any 4-way variant.  

### Touchsurface
The touch surface communicate over uart with the esp. 
It send information for the following events:
- touch press
- touch release
- swipe left (release)
- swipe right (release)
- touch on more than one sensor-point (release)
- long press (5 seconds)
  
### Binary sensors
I've added one binary sensor for each type of touch event, except the long press.  
So you can handle all events easy in Home Assistant.  
The long press event is only usable by using the on_long_touch_release action at the moment.  
  
### LEDs
There are 28 addressable LEDs on board (32 on US variants), driven via `esp32_rmt_led_strip` with predefined effects.

**Effects:**
- Rainbow
- Pulse

### Audio / speaker
An external I²S DAC is configured via `i2s_audio` + `speaker` (ID `media_out`). Quality is still experimental; the PA power switch (`pa_power`) must be on for the amplifier.
  
### Vibration motor  
  
## Component IDs
You can use all components based on their ID.  
  
### Binary Sensors
**Touchfield 1:** touchfield_1  
**Touchfield 2:** touchfield_2  
**Touchfield 3:** touchfield_3  
**Swipe left:** swipe_left  
**Swipe right:** swipe_right  
**Multi-touch:** multi_touch  
**Long-touch:** long_press  
  
### Switches
**Relay 1:** relay_1  
**Relay 2:** relay_2  
**Relay 3:** relay_3  
**Vibration motor:** vibra  
**Nightlight** nightlight_active  
  
### Touch Input
**tx_ultimate_touch:** tx_touch  
**uart:** my_uart  
  
### LED Lights
**28 RGBIC LEDs:** leds  

### Audio
**speaker:** media_out  
**i2s_audio:** audio_i2s  

### Example code to use the components based on their IDs
This is a simple example to turn the LEDs on and off, which are defined in the package. 
*Remember, that this is just an example for ID usage. The on_release is not always triggered. (If you release on another point on the surface as you press). Then the LEDs won't turn off.*
```
  on_press:
    - light.turn_on: leds
	
  on_release:
    - light.turn_off: leds
```


#### Choose language:
[![en](https://img.shields.io/badge/lang-en-red.svg)](https://github.com/SmartHome-yourself/sonoff-tx-ultimate-for-esphome/blob/master/README.md) 
[![de](https://img.shields.io/badge/lang-de-blue.svg)](https://github.com/SmartHome-yourself/sonoff-tx-ultimate-for-esphome/blob/master/README.de.md)


# SONOFF TX Ultimate for ESPHome (Custom Component)
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
  
## Minimal code
This is the needed code to use the tx ultimate with this component. 
You can use this as base to implement your own features or leave it as it is and go with the main features (switch relay on touch).  
```
substitutions:
  name: "shys-tx-ultimate"
  friendly_name: "SHYS TX Ultimate"
  relay_count: "2"

packages:
  smarthomeyourself.tx-ultimate: github://SmartHome-yourself/sonoff-tx-ultimate-for-esphome/tx_ultimate.yaml@main
  
esphome:
  name: ${name}
  name_add_mac_suffix: false

api:
ota:

wifi:
  ssid: !secret wifi_ssid
  password: !secret wifi_password
  
  ap:
    ssid: ${friendly_name} AP
    password: "top_secret"
```  
  
&nbsp;  
  
## Local use in ESPHome
You can create your Project yourself without usage of my package by copy the [tx_ultimate_local.yaml](https://github.com/SmartHome-yourself/sonoff-tx-ultimate-for-esphome/blob/main/tx_ultimate_local.yaml) into your project.  
If you want to use the custom component localy, you can copy the [tx_ultimate_touch folder](https://github.com/SmartHome-yourself/sonoff-tx-ultimate-for-esphome/tree/main/components/) into your esphome directory or some subfolder and include it local.
Then you only have to change the source of the external_components entry.

**Example for local custom component**
```
external_components:
  - source: /config/esphome/my_components
    components: [tx_ultimate_touch]
```  
  
&nbsp;  
  
# Configuration
All substitutions are optional, but I recommend specifying at least name, friendly_name, and relay_count.  
The pins are already specified by the hardware and therefore do not actually have to be changed.  

```
substitutions:
  name: "sonoff-tx-ultimate"
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

**name** _(Default: sonoff-tx-ultimate)_   
The hostname of the device.  
  
**friendly_name** _(Default: TX Ultimate)_   
The name that is displayed in the Frontend.  
  
**relay_count** _(Default: 2)_   
Indicates whether it is the 1, 2 or 3 relay variant.  
_Possible Values (Integer 1-3)_  
  
**vibra_time** _(Default: 100ms)_  
Specifies the duration of the vibration signal on touch.  
  
**button_on_time** _(Default: 200ms)_  
Specifies how long the binary sensors should remain active as a signal for a touch input.  
  
**toggle_relay_1_on_touch** _(Default: "true")_  
Specifies whether relay 1 should be permanently linked to touchfield 1.  
If set to true, the relay will be triggered every time touchfield 1 is pressed.  
If set to false, only the touch event will be transmitted, but the relay will not be triggered.  
  
**toggle_relay_2_on_touch** _(Default: "true")_  
Specifies whether relay 2 should be permanently linked to touchfield 2.  
If set to true, the relay will be triggered every time touchfield 2 is pressed.  
If set to false, only the touch event will be transmitted, but the relay will not be triggered.  
  
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
There are 28 addressable LEDs on board. They are implemented as neopixel platform with 2 predefined effects.

**Effects:**
- Rainbow
- Pulse

### Media player
I've added the media_player component in the package. But currently it is not really usable.
It only produce a lot of noise. I'll update the package if I get it to work propperly.
  
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
**media_player:** media_out  
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


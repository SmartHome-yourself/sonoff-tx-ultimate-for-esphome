# sonoff-tx-ultimate-for-esphome

# Konfiguration

```
substitutions:
  name: "sonoff-tx-ultimate"
  friendly_name: "TX Ultimate"

  relay_count: "2"

  vibra_time: 100ms
  button_on_time: 200ms

  relais_1_pin: GPIO18
  relais_2_pin: GPIO17
  relais_3_pin: GPIO27
  relais_4_pin: GPIO23

  vibra_motor_pin: GPIO21
  pa_power_pin: GPIO26

  led_pin: GPIO13

  uart_tx_pin: GPIO09
  uart_rx_pin: GPIO10

  audio_lrclk_pin: GPIO4
  audio_bclk_pin: GPIO2
  audio_sdata_pin: GPIO15
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

**relais_1_pin** _(Default: GPIO18)_  
Set the GPIO pin for the first relay.

**relais_2_pin** _(Default: GPIO17)_  
Set the GPIO pin for the second relay.

**relais_3_pin** _(Default: GPIO27)_  
Set the GPIO pin for the third relay.

**relais_4_pin** _(Default: GPIO23)_  
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
Here is a small example for a sonoff tx ultimate configuration with own action-events based on the full package to use the default main functionality.

```
substitutions:
  name: "sonoff-tx-ultimate"
  friendly_name: "TX Ultimate"
  relay_count: "2"

packages:
  smarthomeyourself.tx-ultimate: github://SmartHome-yourself/sonoff-tx-ultimate-for-esphome/tx_ultimate.yaml@main
 
api:
ota:

wifi:
  ssid: !secret wifi_ssid
  password: !secret wifi_password

  ap:
    ssid: ${friendly_name} AP
    password: "top_secret"

tx_ultimate_touch:
  id: tx_touch
  uart: my_uart

  on_press:
    - lambda: >
        ESP_LOGD("tx_ultimate_touch.on_press", "My Event: Position: %d / State: %d", touch.x, touch.state);

```

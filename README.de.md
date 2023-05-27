#### Sprachauswahl:
[![en](https://img.shields.io/badge/lang-en-red.svg)](https://github.com/SmartHome-yourself/sonoff-tx-ultimate-for-esphome/blob/master/README.md) 
[![de](https://img.shields.io/badge/lang-de-blue.svg)](https://github.com/SmartHome-yourself/sonoff-tx-ultimate-for-esphome/blob/master/README.de.md)


# SONOFF TX Ultimate für ESPHome (Benutzerdefinierte Komponente)
Dies ist eine benutzerdefinierte ESPHome-Komponente für den SONOFF TX Ultimate Smart Switch.  
Sie ermöglicht Ihnen die Verwendung Ihres Schalters mit ESPHome und umfasst die wichtigsten Funktionen.
Dank der on_... Aktionen können Sie schnell und einfach eigene Funktionen implementieren.  
Das Flashen über den Web-Installer und die Integration des Geräts in Home Assistant genügen, um die grundlegenden Funktionen zu nutzen.

Erkannte Touch-Ereignisse werden durch kurze LED-Signale visualisiert.  
Eine kurze Berührung einer der Touch-Oberflächen schaltet das entsprechende Relais um.
Swipe-, Lang- und Mehrfach-Touch-Ereignisse können mithilfe der on_... Aktionen implementiert werden.
Alternativ können Sie auch auf Swipe- und Mehrfach-Touch-Ereignisse über die binären Sensoren in Home Assistant-Automatisierungen reagieren.
  
&nbsp;  
  
## Home Assistant-Gerät
Der Screenshot zeigt ein Beispiel für das Gerät in Home Assistant nach der Integration.  
![image](https://github.com/SmartHome-yourself/sonoff-tx-ultimate-for-esphome/assets/705724/8a4d817c-1850-43bd-be6a-648699c38a05)  
  
&nbsp;  
    
# Installation 
## Web-Installer 
Sie finden den Webinstaller auf der Projektseite:  
[https://smarthomeyourself.de/sonoff-tx](https://smarthomeyourself.de/sonoff-tx)
  
&nbsp;  
  
## Verwendung in ESPHome ohne Webinstaller
Sie können Ihr Projekt selbst erstellen, ohne meine Pakete zu verwenden, indem Sie die [tx_ultimate_local.yaml](https://github.com/SmartHome-yourself/sonoff-tx-ultimate-for-esphome/blob/main/tx_ultimate_local.yaml) in Ihr Projekt kopieren.  
Wenn Sie die benutzerdefinierte Komponente lokal verwenden möchten, können Sie den [tx_ultimate_touch-Ordner](https://github.com/SmartHome-yourself/sonoff-tx-ultimate-for-esphome/tree/main/components/) in Ihr ESPHome-Verzeichnis oder einen Unterordner kopieren und lokal einbinden.
Dann müssen Sie nur noch die Quelle des external_components-Eintrags ändern.

**Beispiel für lokale benutzerdefinierte Komponente**
```
external_components:
  - source: /config/esphome/my_components
    components: [tx_ultimate_touch]
```  
  
&nbsp;  
    
# Minimal Konfiguration
Dies ist der benötigte Code, um das tx ultimate mit dieser Komponente zu verwenden.  
Sie können dies als Basis verwenden, um Ihre eigenen Funktionen zu implementieren oder es so lassen und die Hauptfunktionen nutzen (Relais bei Berührung schalten).  
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
  
# Konfiguration
Alle Ersetzungen sind optional, aber ich empfehle, mindestens `name`, `friendly_name` und `relay_count` anzugeben.  
Die Pins sind bereits in der Hardware angegeben und müssen daher nicht geändert werden.  

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
  
  touchpanel_power_pin: GPIO5
```

**name** _(Standard: sonoff-tx-ultimate)_   
Der Hostname des Geräts.  
  
**friendly_name** _(Standard: TX Ultimate)_   
Der Name, der im Frontend angezeigt wird.  
  
**relay_count** _(Standard: 2)_   
Gibt an, ob es sich um die 1-, 2- oder 3-Relais-Variante handelt.  
_Mögliche Werte (ganze Zahl von 1 bis 3)_  
  
**vibra_time** _(Standard: 100ms)_  
Gibt die Dauer des Vibrationszeichens bei Berührung an.  
  
**button_on_time** _(Standard: 200ms)_  
Gibt an, wie lange die binären Sensoren als Signal für eine Berührung aktiv bleiben sollen.  
  
**relais_1_pin** _(Standard: GPIO18)_  
Legen Sie den GPIO-Pin für das erste Relais fest.
  
**relais_2_pin** _(Standard: GPIO17)_  
Legen Sie den GPIO-Pin für das zweite Relais fest.  
  
**relais_3_pin** _(Standard: GPIO27)_  
Legen Sie den GPIO-Pin für das dritte Relais fest.  
  
**relais_4_pin** _(Standard: GPIO23)_  
Legen Sie den GPIO-Pin für das vierte Relais fest.  
(Bisher habe ich keine 4-Relais-Variante gesehen. Es wurde jedoch in der Dokumentation erwähnt, also ist es hier aufgeführt.)  
  
**vibra_motor_pin** _(Standard: GPIO21)_  
Legen Sie den GPIO-Pin für den Vibrationsmotor fest.  
  
**pa_power_pin** _(Standard: GPIO26)_  
Legen Sie den GPIO-Pin für den Leistungsverstärker fest.  
  
**led_pin** _(Standard: GPIO13)_  
Legen Sie den GPIO-Pin für das RGBIC-LED-Signal fest.  
  
**uart_tx_pin** _(Standard: GPIO19)_  
Legen Sie den GPIO-Pin für UART TX auf RX des Touch-Controllers fest.  
  
**uart_rx_pin** _(Standard: GPIO22)_  
Legen Sie den GPIO-Pin für UART RX auf TX des Touch-Controllers fest.  
  
**audio_lrclk_pin** _(Standard: GPIO4)_  
Legen Sie den GPIO-Pin für die I2S-Audio-Bus-Word-Select-Leitung fest.  
  
**audio_bclk_pin** _(Standard: GPIO2)_  
Legen Sie den GPIO-Pin für die I2S-Audio-Bus-Taktleitung fest.  
  
**audio_sdata_pin** _(Standard: GPIO15)_  
Legen Sie den GPIO-Pin für die I2S-Datenleitung fest.  
  
&nbsp;  
  
# Aktionen
Alle Aktionen werden verwendet, um auf Touch-Ereignisse zu reagieren und eigene Aktionen bei Berührung/Swipe durchzuführen.  
Die Position, an der die Touch-Oberfläche berührt wurde, steht in allen Aktionen über Lambda als touch.x zur Verfügung.  
Der Wert in touch.x kann eine ganze Zahl von 1 (links) bis 10 (rechts) sein.
  
### on_press
Wird ausgelöst, sobald ein Finger die Oberfläche berührt.  
  
### on_release
Wird ausgelöst, wenn der Finger die Oberfläche loslässt.  
Die on_release-Aktion wird nur ausgelöst, wenn das Loslassen-Ereignis an derselben Position wie das vorherige Druckereignis erfolgt und es sich nicht um ein Mehrfach-Touch- oder Langzeit-Touch-Ereignis handelt!  
  
### on_swipe_left
Wird ausgelöst, wenn Sie von der rechten Seite zur linken Seite der Oberfläche wischen.  
  
### on_swipe_right
Wird ausgelöst, wenn Sie von der linken Seite zur rechten Seite der Oberfläche wischen.  
  
### on_full_touch_release
Wird ausgelöst, wenn Sie mehr als einen Punkt auf der Oberfläche berühren.  
  
### on_long_touch_release
Wird ausgelöst, wenn Sie einen Punkt auf der Oberfläche länger als 5 Sekunden berühren.  
  
&nbsp;  
  
# Beispielcode
Dies ist ein Beispiel für eine eigenen Touch Aktion.  
Es erweitert die Hauptfunktionen des Sonoff TX Ultimate-Schalters um eine eigenen Log-Ausgabe beim Druck auf die Touch-Fläche.  
  
Es steht Ihnen natürlich vollkommen frei, was Sie in den Ereignissen ausführen.  

```
tx_ultimate_touch:
  id: tx_touch
  uart: my_uart

  on_press:
    - lambda: >
        ESP_LOGD("tx_ultimate_touch.on_press", "My Event: Position: %d / State: %d", touch.x, touch.state);
```


# Komponenten

### Relais
Je nach Schaltervariante enthält der TX 1-3 Relais. Daher gibt es 3 Schalter für die Relais im Code.  
Laut Dokumentation gibt es auch einen GPIO für ein 4. Relais, aber mir ist keine 4-Wege-Variante bekannt. Daher habe ich darauf verzichtet, diese zu berücksichtigen.  

### Touch-Oberfläche
Die Touch-Oberfläche kommuniziert über UART mit dem ESP.  
Sie sendet Informationen für die folgenden Ereignisse:  
- Touch-Druck
- Touch-Loslassen
- Wischen nach links (Loslassen)
- Wischen nach rechts (Loslassen)
- Berührung von mehr als einem Sensorenpunkt (Loslassen)
- Langzeitdruck (5 Sekunden)
  
### Binäre Sensoren
Ich habe einen binären Sensor für jeden Typ von Touch-Ereignis hinzugefügt, außer für den Langzeitdruck.  
So können Sie alle Ereignisse einfach in Home Assistant verarbeiten.  
Das Langzeitdruck-Ereignis kann derzeit nur über die on_long_touch_release-Aktion verwendet werden.  
  
### LEDs
Auf der Platine befinden sich 28 adressierbare LEDs. Sie sind als Neopixel-Plattform mit 2 vordefinierten Effekten implementiert.  
  
**Effekte:**
- Rainbow (Regenbogen)
- Pulse (Pulsieren)

### Media Player
Ich habe den Media-Player-Komponenten im Paket hinzugefügt. Derzeit ist er jedoch nicht wirklich verwendbar.  
Er erzeugt nur viel Lärm. Ich werde das Paket aktualisieren, wenn ich es ordnungsgemäß zum Funktionieren bringe.  
  
### Vibrationsmotor  
  
## Komponenten-IDs
Sie können alle Komponenten anhand ihrer ID verwenden.  
  
### Binäre Sensoren
**Touchfeld 1:** touchfield_1  
**Touchfeld 2:** touchfield_2  
**Touchfeld 3:** touchfield_3  
**Wischen nach links:** swipe_left  
**Wischen nach rechts:** swipe_right  
**Mehrfach-Touch:** multi_touch  
  
### Schalter
**Relais 1:** relay_1  
**Relais 2:** relay_2  
**Relais 3:** relay_3  
**Vibrationsmotor:** vibra  
**Leistungsverstärker:** pa_power  
  
### Touch-Eingabe
**tx_ultimate_touch:** tx_touch  
**uart:** my_uart  
  
### LED-Leuchten
**28 RGBIC LEDs:** leds  
  
### Audio
**media_player:** media_out  
**i2s_audio:** audio_i2s  
  
### Beispielcode zur Verwendung der Komponenten anhand ihrer IDs
Dies ist ein einfaches Beispiel, um die in der Konfiguration definierten LEDs ein- und auszuschalten.  
*Bitte beachten Sie, dass dies nur ein Beispiel für die Verwendung von IDs ist. Das Ereignis `on_release` wird nicht immer ausgelöst, wenn Sie an einer anderen Stelle auf der Oberfläche loslassen, als Sie gedrückt haben. In diesem Fall werden die LEDs nicht ausgeschaltet.*  
```
  on_press:
    - light.turn_on: leds

  on_release:
    - light.turn_off: leds
```  
  

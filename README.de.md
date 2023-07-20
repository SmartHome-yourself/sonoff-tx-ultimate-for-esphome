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

## Ausführliches Video zur TX Ultimate - Custom Component
[![SONOFF TX Ultimate - Custom Component](http://img.youtube.com/vi/naDLhX89enQ/0.jpg)](https://www.youtube.com/watch?v=naDLhX89enQ "SONOFF TX Ultimate - Custom Component")

&nbsp;  
  
## TX Ultimate kaufen
Wenn Ihr mein Projekt unterstützen wollt, bestellt einfach eure nächsten SONOFF Geräte über den folgenden Affiliate Link:  
http://itead.cc/product/sonoff-tx-ultimate-smart-touch-wall-switch/ref/85/?campaign=tx-comp  
  
Mit dem Code **DANIELSCHSONOFF** erhaltet Ihr sogar noch einmal 10% auf eure Bestellung.  
  
&nbsp;  
  
## Home Assistant-Gerät
Der Screenshot zeigt ein Beispiel für das Gerät in Home Assistant nach der Integration.  
![image](https://github.com/SmartHome-yourself/sonoff-tx-ultimate-for-esphome/assets/705724/86a6f88e-b453-492e-b9cf-ab50b69ad2e9)
  
&nbsp;  
    
# Installation 

&nbsp;  
    
## Minimal Konfiguration
Dies ist der benötigte Code, um das tx ultimate mit dieser Komponente zu verwenden.  
Sie können dies als Basis verwenden, um Ihre eigenen Funktionen zu implementieren oder es so lassen und einfach die Hauptfunktionen nutzen (Relais bei Berührung schalten).  
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
  
## Lokale Verwendung in ESPHome
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
  
## Alternative Jalousie-Steuerung
Wer den Schalter zum steuern von Jalousien einsetzen möchte, benötigt eine etwas abweichende Konfiguration.  
Vor allem müssen die zwei Relais für den Motor gegeneinander gesperrt werden (interlock).   
Natürlich funktioniert das nur mit der 2- und 3-Relais-Variante. In beiden Fällen wird für die Motorsteuerung Relais 1 und 2 verwendet, da ich das interlock nicht dynamisch konfigurieren konnte.  
Bei Schaltern mit 3 Relais ist bei der Cover-Konfiguration daher der mittlere Taster mit dem dritten Relais belegt. Öffnen und schließen steuert man also immer mit den Tasten links und rechts.  
  
### Minimal Konfiguration für Jalousie-Steuerung
Grundsätzlich unterscheidet sich die mindestens notwendige Konfiguration für Jalousien nur in der Package-URL.
Die Zeitangaben für cover_open_duration und cover_close_duration sollten so genau wie möglich angegeben werden. Lieber aber eine Sekunde zu viel, als zu wenig.

```
substitutions:
  name: "shys-tx-ultimate"
  friendly_name: "SHYS TX Ultimate"
  relay_count: "2"
  
  cover_open_duration: 25s
  cover_close_duration: 25s
  
packages:
  smarthomeyourself.tx-ultimate: github://SmartHome-yourself/sonoff-tx-ultimate-for-esphome/tx_ultimate_cover.yaml@main
  
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

## Standard-Konfiguration (tx_ultimate.yaml / tx_ultimate_local.yaml)
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
  
  
## Cover-Konfiguration (tx_ultimate_cover.yaml)
Bei der Jalousie weichen die Parameter etwas ab.

```
substitutions:
  name: "shys-tx-ultimate-cover"
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
  
**name** _(Standard: sonoff-tx-ultimate)_   
Der Hostname des Geräts.  
  
**friendly_name** _(Standard: TX Ultimate)_   
Der Name, der im Frontend angezeigt wird.  
  
**relay_count** _(Standard: 2)_   
Gibt an, ob es sich um die 1-, 2- oder 3-Relais-Variante handelt.  
Die Jalousie-Konfiguration unterstützt nur die Varianten mit 2 oder 3 Relais.
_Mögliche Werte (ganze Zahl von 1 bis 3)_  
  
**vibra_time** _(Standard: 100ms)_  
Gibt die Dauer des Vibrationszeichens bei Berührung an.  
  
**button_on_time** _(Standard: 200ms)_  
Gibt an, wie lange die binären Sensoren als Signal für eine Berührung aktiv bleiben sollen.  
  
**toggle_relay_1_on_touch** _(Standard: "true")_  
Legt fest, ob das Relais 1 fest an das Touchfeld 1 gekoppelt sein soll.  
Bei true wird das Relais bei jedem Druck auf Touchfeld 1 geschaltet.  
Bei false wird nur das Touch-Event übermittelt aber das Relais nicht geschaltet.  
Existiert in der Jalousie-Variante nicht, da Relais 1 und 2 zwingend für den Motor benötigt werden.  
  
**toggle_relay_2_on_touch** _(Standard: "true")_  
Legt fest, ob das Relais 2 fest an das Touchfeld 2 gekoppelt sein soll.  
Bei true wird das Relais bei jedem Druck auf Touchfeld 2 geschaltet.  
Bei false wird nur das Touch-Event übermittelt aber das Relais nicht geschaltet.  
Existiert in der Jalousie-Variante nicht, da Relais 1 und 2 zwingend für den Motor benötigt werden.  

**toggle_relay_3_on_touch** _(Standard: "true")_  
Legt fest, ob das Relais 3 fest an das Touchfeld 3 gekoppelt sein soll.  
Bei true wird das Relais bei jedem Druck auf Touchfeld 3 geschaltet.  
Bei false wird nur das Touch-Event übermittelt aber das Relais nicht geschaltet.  
  
**button_brightness** _(Standard: "0.7")_  
Legt die Helligkeit fest, mit der angezeigt wird, dass ein Relais eingeschaltet ist. (Gültige Werte: 0.0 - 1.0)  
  
**button_color** _(Standard: "{0,0,100}")_  
Legt die Farbe fest, in der unter der Schaltfläche angezeigt werden soll, dass das Relais eingeschaltet ist.  
Die Farbe wird als RGB-Wert durch ein Array von 3 Ganzzahlen von 0-100 angegeben.  
  
**nightlight** _(Standard: "on")_  
Gibt an, ob das Nachtlicht nach Sonnenuntergang automatisch eingeschaltet werden soll.  
Damit die automatische an/abschaltung funktioniert, muss der eigene Standort über Längen- und Breitengrad mit latitude und longitude angegeben werden!
  
**nightlight_brightness** _(Standard: "0.2")_  
Legt die Helligkeit fest, mit der das Nachtlicht leuchten soll. (Gültige Werte: 0.0 - 1.0)  
  
**nightlight_color** _(Standard: "{80,70,0}")_  
Legt die Farbe fest, in der das Nachtlicht leuchten soll.  
Die Farbe wird als RGB-Wert durch ein Array von 3 Ganzzahlen von 0-100 angegeben.  
  
**latitude** _(Standard: "50.123456°")_  
Legt den Breitengrad des eigenen Standorts fest, um Sonnenauf- und untergang zu ermitteln  

**longitude** _(Standard: "5.654321°")_  
Legt den Längengrad des eigenen Standorts fest, um Sonnenauf- und untergang zu ermitteln  
  
**touch_brightness**  _(Standard: "1")_  
Legt die Helligkeit der LEDs für die Touch Visualisierung fest. (Gültige Werte 0.0 - 1.0)  
  
**touch_color**  _(Standard: "{0,100,100}")_  
Legt die Farbe der LEDs für die Touch Visualisierung fest.  
Die Farbe wird als RGB-Wert durch ein Array von 3 Ganzzahlen von 0-100 angegeben.  
  
**touch_effect**  _(Standard: "Scan")_  
Legt den Effekt der LEDs für die Touch Visualisierung fest.  
Mögliche Effekte:  
- Rainbow  
- Scan  
  
**long_press_brightness**  _(Standard: "1")_  
Legt die Helligkeit der LEDs für die Long-Press Visualisierung fest. (Gültige Werte 0.0 - 1.0)  
  
**long_press_color**  _(Standard: "{100,0,0}")_  
Legt die Farbe der LEDs für die Long-Press Visualisierung fest.  
Die Farbe wird als RGB-Wert durch ein Array von 3 Ganzzahlen von 0-100 angegeben.  
  
**long_press_effect**  _(Standard: "")_  
Legt den Effekt der LEDs für die Long-Press Visualisierung fest.  
Mögliche Effekte:  
- Rainbow  
- Scan  
  
**multi_touch_brightness**  _(Standard: "1")_  
Legt die Helligkeit der LEDs für die Multi-Touch Visualisierung fest. (Gültige Werte 0.0 - 1.0)  
  
**multi_touch_color**  _(Standard: "{0,0,0}")_  
Legt die Farbe der LEDs für die Multi-Touch Visualisierung fest.  
Die Farbe wird als RGB-Wert durch ein Array von 3 Ganzzahlen von 0-100 angegeben.  
  
**multi_touch_effect**  _(Standard: "Rainbow")_  
Legt den Effekt der LEDs für die Multi-Touch Visualisierung fest.  
Mögliche Effekte:  
- Rainbow  
- Scan  
  
**swipe_left_brightness**  _(Standard: "1")_ (Gültige Werte: 0.0 - 1.0)  
Legt die Helligkeit der LEDs für die Visualisierung des wischen nach links fest. (Gültige Werte 0.0 - 1.0)  
  
**swipe_left_color**  _(Standard: "{0,100,0}")_  
Legt die Farbe der LEDs für die Visualisierung des wischen nach links fest.  
Die Farbe wird als RGB-Wert durch ein Array von 3 Ganzzahlen von 0-100 angegeben.  
  
**swipe_left_effect**  _(Standard: "")_  
Legt den Effekt der LEDs für die Visualisierung des wischen nach links fest.  
Mögliche Effekte:  
- Rainbow  
- Scan  
  
**swipe_right_brightness**  _(Standard: "1")_ (Gültige Werte: 0.0 - 1.0)  
Legt die Helligkeit der LEDs für die Visualisierung des wischen nach rechts fest. (Gültige Werte 0.0 - 1.0)  
  
**swipe_right_color**  _(Standard: "{100,0,70}")_  
Legt die Farbe der LEDs für die Visualisierung des wischen nach rechts fest.  
Die Farbe wird als RGB-Wert durch ein Array von 3 Ganzzahlen von 0-100 angegeben.  
  
**swipe_right_effect**  _(Standard: "")_  
Legt den Effekt der LEDs für die Visualisierung des wischen nach rechts fest.  
Mögliche Effekte:  
- Rainbow  
- Scan  
  
**relay_1_pin** _(Standard: GPIO18)_  
Legen Sie den GPIO-Pin für das erste Relais fest.  
  
**relay_2_pin** _(Standard: GPIO17)_  
Legen Sie den GPIO-Pin für das zweite Relais fest.  
  
**relay_3_pin** _(Standard: GPIO27)_  
Legen Sie den GPIO-Pin für das dritte Relais fest.  
  
**relay_4_pin** _(Standard: GPIO23)_  
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
  
**cover_name** _(Standard: GPIO15)_  
Name der Cover-Komponente  
  
**cover_open_duration** _(Standard: 25s)_  
Die Zeit, die die Jalousie zum öffnen benötigt.  
  
**cover_close_duration** _(Standard: 25s)_  
Die Zeit, die die Jalousie zum schließen benötigt.  
  
**cover_brightness** _(Standard: 0.7)_  
Helligkeit der Positionsanzeige fürs Cover (Rechte Seite)  
Dimmt automatisch auf "nightlight_brightness", wenn der Nachtlicht-Modus aktiv wird.  
  
**cover_color1** _(Standard: {255,0,0})_  
Farbe 1 für die Positionsanzeige der Cover-Komponente.  
  
**cover_color2** _(Standard: {0,255,0})_  
Farbe 2 für die Positionsanzeige der Cover-Komponente.  
  
  
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
**Langer-Touch:** long_press  
  
### Schalter
**Relais 1:** relay_1  
**Relais 2:** relay_2  
**Relais 3:** relay_3  
**Vibrationsmotor:** vibra  
**Nachtlicht** nightlight_active  
  
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
  

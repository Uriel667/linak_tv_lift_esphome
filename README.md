# Linak TV Lift Controller (ESPHome)

This is a custom ESPHome component for controlling **Linak Bluetooth TV Lifts** (and desk controllers) that use the generic Linak `99FA` service.

It is a modernized fork of the original Idasen Desk Controller, updated for **ESPHome 2025.11+** with specific support for TV Lifts.

**Key Features:**
* **Fixed for 2025:** Resolves `cover_schema` and `gattc_write_char` breaking changes.
* **TV Lift Support:** Uses the full 128-bit UUIDs required for Linak TV Lifts.
* **Instant Control:** Bypasses the "deep sleep" connection delay found in other integrations.
* **Assumed State:** Permanently enables Up/Down buttons, fixing the "Greyed out button" issue.

## Credits & Attribution
This project is based on the excellent work of **[j5lien](https://github.com/j5lien/esphome-idasen-desk-controller)** and their `esphome-idasen-desk-controller` component. It has been adapted here to support generic Linak hardware and newer ESPHome versions.

## Installation

### Step 1: Create your YAML
Create a new device in ESPHome and use the below configuration.

### Step 2: Pairing
Flash the ESP32 using ESPHome
Put your Linak Lift into Pairing Mode (hold the Bluetooth button for 3-5 seconds until the blue light flashes or plug out the bluetooth stick for 10 seconds and plug it back in).
Power on the ESP32. It will connect automatically.

```yaml
esphome:
  name: tv-lift
  friendly_name: TV Lift

esp32:
  board: esp32dev
  framework:
    type: arduino

api:
ota:
  - platform: esphome

wifi:
  ssid: "YOUR_WIFI_SSID"
  password: "YOUR_WIFI_PASSWORD"

esp32_ble_tracker:

ble_client:
  - mac_address: XX:XX:XX:XX:XX:XX  # <--- Replace with your Linak MAC Address
    id: lift_ble_client

# Pull the component from GitHub
external_components:
  - source:
      type: git
      url: [https://github.com/YOUR_GITHUB_USERNAME/linak_tv_lift_esphome](https://github.com/YOUR_GITHUB_USERNAME/linak_tv_lift_esphome)
      ref: main
    components: [ linak_tv_lift ]

# Configure the Controller
linak_tv_lift:
  id: my_lift
  ble_client_id: lift_ble_client

# Create the Cover (Buttons)
cover:
  - platform: linak_tv_lift
    id: lift_cover
    name: "TV Lift"

# REQUIRED: Dummy sensor to force library linking
sensor:
  - platform: template
    name: "Force Build Sensor"
    lambda: 'return 0;'
    internal: true
  - platform: linak_tv_lift
    name: "TV Lift Height"

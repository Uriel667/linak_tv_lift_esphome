# Linak TV Lift Controller (ESPHome)

This is a custom ESPHome component for controlling **Linak Bluetooth TV Lifts** (and desk controllers) that use the `99FA` service. 

It is designed to work with **ESPHome 2025.11+** and fixes several issues found in older libraries:
1.  **Updated for 2025:** Fixes the `cover_schema` and `gattc_write_char` breaking changes.
2.  **Linak UUIDs:** Uses the full 128-bit UUIDs required for TV Lifts (instead of just Idasen desks).
3.  **Assumed State:** Enables "Up/Down" buttons permanently, fixing the "Greyed out button" issue for devices that don't report position accurately.
4.  **Instant Connection:** Bypasses deep-sleep delays.

## Hardware Required
* An **ESP32** board (Generic ESP32-WROOM-32 recommended).
* A **Linak Bluetooth-enabled** TV Lift or Desk.

## Installation

You do NOT need to download files manually. You can point ESPHome directly to this repository.

### Step 1: Create your YAML
Create a new device in ESPHome and use the following configuration:

```yaml
esphome:
  name: tv-lift
  friendly_name: TV Lift

esp32:
  board: esp32dev
  framework:
    type: arduino

# Enable Home Assistant API
api:

ota:
  - platform: esphome

wifi:
  ssid: "YOUR_WIFI_SSID"
  password: "YOUR_WIFI_PASSWORD"

# REQUIRED: Bluetooth Tracker
esp32_ble_tracker:

ble_client:
  - mac_address: XX:XX:XX:XX:XX:XX  # <--- Replace with your Linak MAC Address
    id: desk_ble_client

# Pull the component from GitHub
external_components:
  - source:
      type: git
      url: [https://github.com/YOUR_USERNAME/linak_tv_lift_esphome](https://github.com/YOUR_USERNAME/linak_tv_lift_esphome)
      ref: main
    components: [ idasen_desk_controller ]

# Configure the Controller
idasen_desk_controller:
  id: my_desk
  ble_client_id: desk_ble_client

# Create the Cover (Buttons)
cover:
  - platform: idasen_desk_controller
    id: desk_cover
    name: "TV Lift"

# REQUIRED: Dummy sensor to force library linking
sensor:
  - platform: template
    name: "Force Build Sensor"
    lambda: 'return 0;'
    internal: true
  - platform: idasen_desk_controller
    name: "TV Lift Height"

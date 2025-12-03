#pragma once

#include "esphome/core/component.h"
#include "esphome/components/ble_client/ble_client.h"
#include "esphome/components/esp32_ble_tracker/esp32_ble_tracker.h"
#include "esphome/components/cover/cover.h"
#include "esphome/components/sensor/sensor.h"

namespace esphome {
namespace linak_tv_lift {

// Standard Linak 128-bit UUIDs for TV Lifts and DPG controllers
static const esp32_ble::ESPBTUUID CONTROL_SERVICE_UUID = esp32_ble::ESPBTUUID::from_raw("99FA0001-338A-1024-8A49-009C0215F78A");
static const esp32_ble::ESPBTUUID CONTROL_CHARACTERISTIC_UUID = esp32_ble::ESPBTUUID::from_raw("99FA0002-338A-1024-8A49-009C0215F78A");

class LinakTvLift : public Component, public ble_client::BLEClientNode {
 public:
  void setup() override;
  void loop() override;
  void dump_config() override;
  void gattc_event_handler(esp_gattc_cb_event_t event, esp_gatt_if_t gattc_if, esp_ble_gattc_cb_param_t *param) override;
  void set_ble_client_parent(ble_client::BLEClient *parent) { parent_ = parent; }
  void set_height_sensor(sensor::Sensor *sensor) { height_sensor_ = sensor; }

  void move_up();
  void move_down();
  void stop_move();

 protected:
  ble_client::BLEClient *parent_;
  sensor::Sensor *height_sensor_{nullptr};
  uint16_t char_handle_{0};
};

class LinakTvLiftCover : public cover::Cover, public Component {
 public:
  void setup() override;
  void loop() override;
  void dump_config() override;
  void set_linak_tv_lift(LinakTvLift *controller) { controller_ = controller; }
  cover::CoverTraits get_traits() override;

 protected:
  void control(const cover::CoverCall &call) override;
  LinakTvLift *controller_;
};

}  // namespace linak_tv_lift
}  // namespace esphome

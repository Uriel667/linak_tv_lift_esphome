#include "linak_tv_lift.h"
#include "esphome/core/log.h"

namespace esphome {
namespace linak_tv_lift {

static const char *TAG = "linak_tv_lift";

void LinakTvLift::setup() {
  if (this->parent_ != nullptr) {
    this->parent_->register_ble_node(this);
  }
}

void LinakTvLift::loop() {}

void LinakTvLift::dump_config() {
  ESP_LOGCONFIG(TAG, "Linak TV Lift:");
  LOG_SENSOR("  ", "Height", this->height_sensor_);
}

void LinakTvLift::gattc_event_handler(esp_gattc_cb_event_t event, esp_gatt_if_t gattc_if, esp_ble_gattc_cb_param_t *param) {
  switch (event) {
    case ESP_GATTC_OPEN_EVT: {
      if (param->open.status == ESP_GATT_OK) {
        ESP_LOGI(TAG, "Connected successfully to Lift!");
      }
      break;
    }
    case ESP_GATTC_SEARCH_CMPL_EVT: {
      ESP_LOGI(TAG, "Service search complete. Looking for Control Handle...");
      auto *char_desc = this->parent_->get_characteristic(CONTROL_SERVICE_UUID, CONTROL_CHARACTERISTIC_UUID);
      if (char_desc == nullptr) {
        ESP_LOGE(TAG, "CRITICAL: No control characteristic found at UUID 0x%s", CONTROL_CHARACTERISTIC_UUID.to_string().c_str());
        break;
      }
      this->char_handle_ = char_desc->handle;
      ESP_LOGI(TAG, "Success! Found Control Handle: 0x%x", this->char_handle_);
      break;
    }
    default:
      break;
  }
}

void LinakTvLift::move_up() {
  if (this->char_handle_ == 0) {
    ESP_LOGW(TAG, "Cannot move UP: No connection to desk handle.");
    return;
  }
  uint8_t cmd[] = {0x47, 0x00};
  esp_ble_gattc_write_char(this->parent_->get_gattc_if(), this->parent_->get_conn_id(), this->char_handle_, sizeof(cmd), cmd, ESP_GATT_WRITE_TYPE_NO_RSP, ESP_GATT_AUTH_REQ_NONE);
}

void LinakTvLift::move_down() {
  if (this->char_handle_ == 0) {
    ESP_LOGW(TAG, "Cannot move DOWN: No connection to desk handle.");
    return;
  }
  uint8_t cmd[] = {0x46, 0x00};
  esp_ble_gattc_write_char(this->parent_->get_gattc_if(), this->parent_->get_conn_id(), this->char_handle_, sizeof(cmd), cmd, ESP_GATT_WRITE_TYPE_NO_RSP, ESP_GATT_AUTH_REQ_NONE);
}

void LinakTvLift::stop_move() {
  if (this->char_handle_ == 0) return;
  uint8_t cmd[] = {0xFF, 0x00};
  esp_ble_gattc_write_char(this->parent_->get_gattc_if(), this->parent_->get_conn_id(), this->char_handle_, sizeof(cmd), cmd, ESP_GATT_WRITE_TYPE_NO_RSP, ESP_GATT_AUTH_REQ_NONE);
}

void LinakTvLiftCover::setup() {}
void LinakTvLiftCover::loop() {}
void LinakTvLiftCover::dump_config() { LOG_COVER("", "Linak TV Lift Cover", this); }

cover::CoverTraits LinakTvLiftCover::get_traits() {
  auto traits = cover::CoverTraits();
  traits.set_supports_position(false);
  traits.set_supports_tilt(false);
  traits.set_is_assumed_state(true); // Fix greyed out buttons
  return traits;
}

void LinakTvLiftCover::control(const cover::CoverCall &call) {
  if (call.get_position().has_value()) {
    float pos = *call.get_position();
    if (pos == 1.0f) {
      this->controller_->move_up();
    } else if (pos == 0.0f) {
      this->controller_->move_down();
    } else {
      this->controller_->stop_move();
    }
  }
  if (call.get_stop()) {
    this->controller_->stop_move();
  }
}

}  // namespace linak_tv_lift
}  // namespace esphome

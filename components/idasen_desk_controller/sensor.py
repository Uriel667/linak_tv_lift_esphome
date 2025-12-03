import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.const import CONF_ID, UNIT_CENTIMETER, ICON_ARROW_EXPAND_VERTICAL
from . import IdasenDeskController

CONFIG_SCHEMA = sensor.sensor_schema(
    unit_of_measurement=UNIT_CENTIMETER,
    icon=ICON_ARROW_EXPAND_VERTICAL,
    accuracy_decimals=0
).extend({
    cv.GenerateID('idasen_desk_controller_id'): cv.use_id(IdasenDeskController),
})

def to_code(config):
    parent = yield cg.get_variable(config['idasen_desk_controller_id'])
    var = yield sensor.new_sensor(config)
    cg.add(parent.set_height_sensor(var))

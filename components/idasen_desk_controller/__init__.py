import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import ble_client
from esphome.const import CONF_ID

# Force dependencies
DEPENDENCIES = ['ble_client', 'sensor']

linak_tv_lift_ns = cg.esphome_ns.namespace('linak_tv_lift')
LinakTvLift = linak_tv_lift_ns.class_('LinakTvLift', cg.Component, ble_client.BLEClientNode)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(LinakTvLift),
    cv.Required('ble_client_id'): cv.use_id(ble_client.BLEClient),
}).extend(cv.COMPONENT_SCHEMA)

def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)
    client = yield cg.get_variable(config['ble_client_id'])
    cg.add(var.set_ble_client_parent(client))

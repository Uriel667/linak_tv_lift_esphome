import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import cover
from esphome.const import CONF_ID
from . import IdasenDeskController, idasen_desk_controller_ns

IdasenDeskControllerCover = idasen_desk_controller_ns.class_('IdasenDeskControllerCover', cover.Cover, cg.Component)

# 2025 Fix: Call cover_schema function before extending
CONFIG_SCHEMA = cover.cover_schema(IdasenDeskControllerCover).extend({
    cv.GenerateID(): cv.declare_id(IdasenDeskControllerCover),
    cv.GenerateID('idasen_desk_controller_id'): cv.use_id(IdasenDeskController),
})

def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)
    yield cover.register_cover(var, config)
    parent = yield cg.get_variable(config['idasen_desk_controller_id'])
    cg.add(var.set_idasen_desk_controller(parent))

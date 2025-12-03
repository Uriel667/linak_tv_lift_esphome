import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import cover
from esphome.const import CONF_ID
from . import LinakTvLift, linak_tv_lift_ns

LinakTvLiftCover = linak_tv_lift_ns.class_('LinakTvLiftCover', cover.Cover, cg.Component)

CONFIG_SCHEMA = cover.cover_schema(LinakTvLiftCover).extend({
    cv.GenerateID(): cv.declare_id(LinakTvLiftCover),
    cv.GenerateID('linak_tv_lift_id'): cv.use_id(LinakTvLift),
})

def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)
    yield cover.register_cover(var, config)
    parent = yield cg.get_variable(config['linak_tv_lift_id'])
    cg.add(var.set_linak_tv_lift(parent))

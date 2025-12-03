#### File 2: `components/idasen_desk_controller/__init__.py`
*Note: You must create the folder structure `components/idasen_desk_controller/` in your repo.*

```python
import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import ble_client
from esphome.const import CONF_ID

# Force dependencies to link correct libraries
DEPENDENCIES = ['ble_client', 'sensor']

idasen_desk_controller_ns = cg.esphome_ns.namespace('idasen_desk_controller')
IdasenDeskController = idasen_desk_controller_ns.class_('IdasenDeskController', cg.Component, ble_client.BLEClientNode)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(IdasenDeskController),
    cv.Required('ble_client_id'): cv.use_id(ble_client.BLEClient),
}).extend(cv.COMPONENT_SCHEMA)

def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)
    client = yield cg.get_variable(config['ble_client_id'])
    cg.add(var.set_ble_client_parent(client))

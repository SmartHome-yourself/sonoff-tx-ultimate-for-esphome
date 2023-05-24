import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart
from esphome.const import (
    CONF_ID,
)

from esphome import automation

CODEOWNERS = ["@SmartHome-yourself"]
DEPENDENCIES = ['uart']

# CONFIG-IDs
CONF_TX_ULTIMATE_TOUCH = "tx_ultimate_touch"

CONF_UART = "uart"

CONF_ON_PRESS = "on_press"
CONF_ON_RELEASE = "on_release"

CONF_ON_SWIPE_LEFT = "on_swipe_left"
CONF_ON_SWIPE_RIGHT = "on_swipe_right"

CONF_ON_FULL_TOUCH_RELEASE = "on_full_touch_release"
CONF_ON_LONG_TOUCH_RELEASE = "on_long_touch_release"

# ------------------------------
# ------------------------------

tx_ultimate_touch_ns = cg.esphome_ns.namespace('tx_ultimate_touch')
TouchPoint = tx_ultimate_touch_ns.struct("TouchPoint")

#TouchListener = tx_ultimate_touch_ns.class_("TouchListener")

TxUltimateTouch = tx_ultimate_touch_ns.class_(
    'TxUltimateTouch', cg.Component, uart.UARTDevice)


# ------------------------------
#  Parameter Config
# ------------------------------
CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(TxUltimateTouch),

    cv.Required(CONF_UART): cv.use_id(uart),

    cv.Optional(CONF_ON_PRESS): automation.validate_automation(single=True),
    cv.Optional(CONF_ON_RELEASE): automation.validate_automation(single=True),
    cv.Optional(CONF_ON_SWIPE_LEFT): automation.validate_automation(single=True),
    cv.Optional(CONF_ON_SWIPE_RIGHT): automation.validate_automation(single=True),
    cv.Optional(CONF_ON_FULL_TOUCH_RELEASE): automation.validate_automation(single=True),
    cv.Optional(CONF_ON_LONG_TOUCH_RELEASE): automation.validate_automation(single=True),

}).extend(cv.COMPONENT_SCHEMA).extend(uart.UART_DEVICE_SCHEMA)


# ------------------------------
#  Actions
# ------------------------------
async def register_tx_ultimate_touch(var, config):
    uart_component = await cg.get_variable(config[CONF_UART])
    cg.add(var.set_uart_component(uart_component))

    if CONF_ON_PRESS in config:
        await automation.build_automation(
            var.get_touch_trigger(),
            [(TouchPoint, "touch")],
            config[CONF_ON_PRESS],
        )

    if CONF_ON_RELEASE in config:
        await automation.build_automation(
            var.get_release_trigger(),
            [(TouchPoint, "touch")],
            config[CONF_ON_RELEASE],
        )

    if CONF_ON_SWIPE_LEFT in config:
        await automation.build_automation(
            var.get_swipe_left_trigger(),
            [(TouchPoint, "touch")],
            config[CONF_ON_SWIPE_LEFT],
        )

    if CONF_ON_SWIPE_RIGHT in config:
        await automation.build_automation(
            var.get_swipe_right_trigger(),
            [(TouchPoint, "touch")],
            config[CONF_ON_SWIPE_RIGHT],
        )

    if CONF_ON_FULL_TOUCH_RELEASE in config:
        await automation.build_automation(
            var.get_full_touch_release_trigger(),
            [(TouchPoint, "touch")],
            config[CONF_ON_FULL_TOUCH_RELEASE],
        )

    if CONF_ON_LONG_TOUCH_RELEASE in config:
        await automation.build_automation(
            var.get_long_touch_release_trigger(),
            [(TouchPoint, "touch")],
            config[CONF_ON_LONG_TOUCH_RELEASE],
        )


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)

    await register_tx_ultimate_touch(var, config)

#include <zephyr/device.h>
#include <zephyr/drivers/led_strip.h>

#include <zmk/event_manager.h>
#include <zmk/events/battery_state_changed.h>

static const struct device *const strip = DEVICE_DT_GET(DT_NODELABEL(ws2812));

static int battery_led_listener(const zmk_event_t *eh) {
  const struct zmk_battery_state_changed *ev = as_zmk_battery_state_changed(eh);
  if (!ev || !device_is_ready(strip)) {
    return 0;
  }

  if (ev->state_of_charge <= 10) {
    struct led_rgb color = {.r = 0xFF, .g = 0x00, .b = 0x00};
    led_strip_update_rgb(strip, &color, 1);
  }

  return 0;
}

ZMK_LISTENER(battery_led_listener, battery_led_listener);
ZMK_SUBSCRIPTION(battery_led_listener, zmk_battery_state_changed);

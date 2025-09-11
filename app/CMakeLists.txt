if(CONFIG_WS2812_STRIP)
  target_sources(app PRIVATE src/battery_led.c)
endif()

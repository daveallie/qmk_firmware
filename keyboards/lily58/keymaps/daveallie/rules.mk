# Build Options
#   change to "no" to disable the options, or define them in the Makefile in
#   the appropriate keymap folder that will get included automatically
#
EXTRAKEY_ENABLE = yes        # Audio control and System control
CONSOLE_ENABLE = no          # Console for debug
OLED_DRIVER_ENABLE = yes     # OLED display
ENCODER_ENABLE = yes
MOUSEKEY_ENABLE = yes
RAW_ENABLE = yes

# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no    # Breathing sleep LED during USB suspend

OPT_DEFS += -DCUSTOM_SERIAL_DATA_ENABLE -DCUSTOM_SERIAL_M2S_BYTES=4 -DCUSTOM_SERIAL_S2M_BYTES=0

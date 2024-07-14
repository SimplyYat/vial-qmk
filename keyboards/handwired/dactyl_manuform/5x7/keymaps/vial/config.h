/* SPDX-License-Identifier: GPL-2.0-or-later */

#pragma once

#define VIAL_KEYBOARD_UID {0xA7, 0x50, 0xDA, 0x3E, 0x6C, 0x63, 0x01, 0x38}

#define VIAL_UNLOCK_COMBO_ROWS { 0, 5 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 5 }

#define USE_SERIAL
#define MASTER_LEFT

// Using Serial instead of I2C
#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_USART_TX_PIN GP24
#define SERIAL_USART_RX_PIN GP25
#define SERIAL_PIO_USE_PIO0
#define SERIAL_USART_TIMEOUT     100  // USART driver timeout. default 100
#define SERIAL_USART_SPEED 921600

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 200U
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED_MASK 0U

#define MATRIX_COL_PINS { GP22, GP3, GP4, GP5, GP6, GP7, GP8 }
#define MATRIX_ROW_PINS { GP9, GP10, GP11, GP12, GP13, GP14, GP15 }
#define MATRIX_ROW_PINS_RIGHT { GP9, GP10, GP16, GP17, GP13, GP14, GP15 }

#define SPLIT_WATCHDOG_ENABLE
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_LED_STATE_ENABLE
#define SPLIT_MODS_ENABLE
#define RGB_TRIGGER_ON_KEYDOWN      // Triggers RGB keypress events on key down. This makes RGB control feel more responsive. This may cause RGB to not function properly on some boards

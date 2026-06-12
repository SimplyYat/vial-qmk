![SofleKeyboard default keymap](https://i.imgur.com/MZxVvm9.png)
![SofleKeyboard adjust layer](https://i.imgur.com/f5sKy0I.png)


# Custom Vial Keymap for Sofle Pico Keyboard

This is a highly customized keymap for the Sofle Pico, adapted from the classic Sofle Keyboard by Josef Adamcik, featuring advanced dynamic per-key RGB backlighting and full Vial support.

## Key Features

### 1. Dynamic Layer-Based Lighting
To help with visibility and layer navigation, the lighting matches your active key configurations:
- **Base Layer (Layer 0)**: All keys light up using their designated key category colors.
- **Active Layers (Layers 1+)**: Only keys that are **active** (i.e. set to non-transparent/non-empty keycodes on the current layer) will light up. Empty and transparent keys (`KC_TRNS`, `KC_NO`) remain dark/off.

### 2. Live EEPROM Parsing
The firmware reads configuration changes in real-time from the keyboard's EEPROM. Any changes you make to your keymap or layers in the **Vial GUI** are instantly detected, and the per-key LED colors update automatically without needing a firmware re-compile.

### 3. Split Synchronization
Per-key LED colors are computed on the master half and synchronized to the slave half via custom packed 5-bit transactions (RPC). This guarantees consistent color representation across both halves regardless of which side is connected to USB.

---

## Key Color Reference

The keymap classifies keycodes into distinct groups, each mapped to a harmonious color scheme:

| Key Category | Color | RGB Value | Notes / Description |
| :--- | :--- | :--- | :--- |
| **Normal Alphabet** | Sky Blue | `(0, 140, 255)` | Standard letters (a-z) |
| **Caps Lock / Caps Word** | Vibrant Orange | `(255, 50, 0)` | Letters when Caps Lock or Caps Word is active |
| **Number** | Green | `(0, 255, 0)` | Number row and keypad numbers |
| **Symbol** | Purple | `(191, 0, 255)` | Punctuation, brackets, math operators, etc. |
| **Modifier** | Violet | `(127, 0, 255)` | `Shift`, `Ctrl`, `Alt`, `Gui`, etc. |
| **Layer Key** | Indigo | `(75, 0, 130)` | Momentary layer switches or toggles |
| **Delete / Backspace** | Red | `(255, 0, 0)` | `KC_DEL` and `KC_BSPC` |
| **Enter** | Gold / Amber | `(255, 90, 0)` | Enter keys (adjusted for green hardware LED bias) |
| **Arrow, Space, Tab** | Pure White | `(255, 255, 255)` | Directional arrows, space bar, and tab key |
| **Other** | Lavender | `(200, 160, 255)` | Any other keys / fallback |

### Special Keys (Hold-Tap, Tap-Dance, and Blends)

To distinguish dual-function keys, the keymap uses special colors and color blending:

* **Hold-Tap / Mod-Tap (`LT`, `MT`)**:
  - **Standard**: Light Pink `(255, 0, 127)`
  - **Blended**: If the primary tap action is a letter, number, or symbol, the color blends **75%** of the tap character's color with **25%** of the Hold-Tap pink.
* **Tap-Dance**:
  - **Standard**: Magenta `(255, 0, 255)`
  - **Blended**: If the primary tap action is a letter, number, or symbol, the color blends **75%** of the tap character's color with **25%** of the Tap-Dance magenta.

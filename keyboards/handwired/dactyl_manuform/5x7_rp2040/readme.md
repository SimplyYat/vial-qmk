# handwired/dactyl_manuform/5x7_rp2040

A 5x7 Dactyl Manuform using 2 x RP2040 controllers (1 for each half).

* Keyboard Maintainer: [SimplyYat](https://github.com/SimplyYat)
* Hardware Supported: This keyboard should support with most versions of RP2040. You can handwire the diodes directly to keyswitches, use individual key PCBs like [Amoeba Royale](https://github.com/climent/keyboard-pcbs/tree/master/amoeba-royale), or [Amoeba King](https://github.com/climent/keyboard-pcbs/tree/king_v1.2/amoeba-king), or use flexible PCBs like [this one from BastardKB](https://github.com/Bastardkb/Dactyl-Manuform-PCB-Plate) or [this one](https://oshwlab.com/simplyyat/dm-5-row-smt). There might be a lot more options available on various ecommerce websites.
* Hardware Availability: I built mine with a generic Purple RP2040 from Aliexpress, but you can choose whichever one you prefer.

## Building the firmware

> These commands will need to be run in QMK MSYS terminal, not in a Windows Powershell terminal.
> See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

Make the firmware with Vial support:

    make handwired/dactyl_manuform/5x7_rp2040:vial

Make example for this keyboard with default layout:

    make handwired/dactyl_manuform/5x7_rp2040:default

Flashing example for this keyboard:

    make handwired/dactyl_manuform/5x7_rp2040:default:flash

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

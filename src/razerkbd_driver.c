/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
 *
 * Should you need to contact me, the author, you can do so by
 * e-mail - mail your message to Terry Cain <terry@terrys-home.co.uk>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "razerkbd_driver.h"
#include "razerchromacommon.h"
#include "razercommon.h"

struct razer_report razer_send_payload(IOUSBDeviceInterface **dev, struct razer_report *request_report);

bool is_blade_laptop(IOUSBDeviceInterface **usb_dev) {
    UInt16 product = -1;
    (*usb_dev)->GetDeviceProduct(usb_dev, &product);

    switch (product) {
        case USB_DEVICE_ID_RAZER_BLADE_STEALTH:
        case USB_DEVICE_ID_RAZER_BLADE_STEALTH_LATE_2016:
        case USB_DEVICE_ID_RAZER_BLADE_PRO_LATE_2016:
        case USB_DEVICE_ID_RAZER_BLADE_2018:
        case USB_DEVICE_ID_RAZER_BLADE_2018_MERCURY:
        case USB_DEVICE_ID_RAZER_BLADE_2018_BASE:
        case USB_DEVICE_ID_RAZER_BLADE_2019_ADV:
        case USB_DEVICE_ID_RAZER_BLADE_MID_2019_MERCURY:
        case USB_DEVICE_ID_RAZER_BLADE_STUDIO_EDITION_2019:
        case USB_DEVICE_ID_RAZER_BLADE_QHD:
        case USB_DEVICE_ID_RAZER_BLADE_LATE_2016:
        case USB_DEVICE_ID_RAZER_BLADE_STEALTH_MID_2017:
        case USB_DEVICE_ID_RAZER_BLADE_STEALTH_LATE_2017:
        case USB_DEVICE_ID_RAZER_BLADE_STEALTH_2019:
        case USB_DEVICE_ID_RAZER_BLADE_PRO_2017:
        case USB_DEVICE_ID_RAZER_BLADE_PRO_2017_FULLHD:
        case USB_DEVICE_ID_RAZER_BLADE_2019_BASE:
        case USB_DEVICE_ID_RAZER_BLADE_STEALTH_LATE_2019:
        case USB_DEVICE_ID_RAZER_BLADE_PRO_2019:
        case USB_DEVICE_ID_RAZER_BLADE_PRO_LATE_2019:
        case USB_DEVICE_ID_RAZER_BLADE_STEALTH_EARLY_2020:
        case USB_DEVICE_ID_RAZER_BLADE_STEALTH_LATE_2020:
        case USB_DEVICE_ID_RAZER_BOOK_2020:
        case USB_DEVICE_ID_RAZER_BLADE_15_ADV_2020:
        case USB_DEVICE_ID_RAZER_BLADE_EARLY_2020_BASE:
        case USB_DEVICE_ID_RAZER_BLADE_15_ADV_2021:
            return true;
    }

    return false;
}

/**
 * Read device file "device_type"
 *
 * Returns friendly string of device type
 */
int razer_attr_read_device_type(IOUSBDeviceInterface **usb_dev, char *buf) {
    UInt16 product = -1;
    (*usb_dev)->GetDeviceProduct(usb_dev, &product);

    char *device_type = "";

    switch (product)
    {
        case USB_DEVICE_ID_RAZER_NOSTROMO:
            device_type = "Razer Nostromo\n";
            break;

        case USB_DEVICE_ID_RAZER_ORBWEAVER:
            device_type = "Razer Orbweaver\n";
            break;

        case USB_DEVICE_ID_RAZER_ORBWEAVER_CHROMA:
            device_type = "Razer Orbweaver Chroma\n";
            break;

        case USB_DEVICE_ID_RAZER_BLACKWIDOW_STEALTH:
            device_type = "Razer BlackWidow Stealth\n";
            break;

        case USB_DEVICE_ID_RAZER_BLACKWIDOW_STEALTH_EDITION:
            device_type = "Razer BlackWidow Stealth Edition\n";
            break;

        case USB_DEVICE_ID_RAZER_BLACKWIDOW_ULTIMATE_2012:
            device_type = "Razer BlackWidow Ultimate 2012\n";
            break;

        case USB_DEVICE_ID_RAZER_BLACKWIDOW_ULTIMATE_2013:
            device_type = "Razer BlackWidow Ultimate 2013\n";
            break;

        case USB_DEVICE_ID_RAZER_BLACKWIDOW_ULTIMATE_2016:
            device_type = "Razer BlackWidow Ultimate 2016\n";
            break;

        case USB_DEVICE_ID_RAZER_BLACKWIDOW_X_ULTIMATE:
            device_type = "Razer BlackWidow X Ultimate\n";
            break;

        case USB_DEVICE_ID_RAZER_BLADE_STEALTH:
            device_type = "Razer Blade Stealth\n";
            break;

        case USB_DEVICE_ID_RAZER_BLADE_STEALTH_LATE_2019:
            device_type = "Razer Blade Stealth (Late 2019)\n";
            break;

        case USB_DEVICE_ID_RAZER_BLADE_STEALTH_EARLY_2020:
            device_type = "Razer Blade Stealth (Early 2020)\n";
            break;

        case USB_DEVICE_ID_RAZER_BLADE_STEALTH_LATE_2020:
            device_type = "Razer Blade Stealth (Late 2020)\n";
            break;

        case USB_DEVICE_ID_RAZER_BOOK_2020:
            device_type = "Razer Book 13 (2020)\n";
            break;

        case USB_DEVICE_ID_RAZER_BLADE_STEALTH_LATE_2016:
            device_type = "Razer Blade Stealth (Late 2016)\n";
            break;

        case USB_DEVICE_ID_RAZER_BLADE_STEALTH_MID_2017:
            device_type = "Razer Blade Stealth (Mid 2017)\n";
            break;

        case USB_DEVICE_ID_RAZER_BLADE_QHD:
            device_type = "Razer Blade Stealth (QHD)\n";
            break;

        case USB_DEVICE_ID_RAZER_BLADE_PRO_LATE_2016:
            device_type = "Razer Blade Pro (Late 2016)\n";
            break;

        case USB_DEVICE_ID_RAZER_BLADE_2018:
            device_type = "Razer Blade 15 (2018)\n";
            break;

        case USB_DEVICE_ID_RAZER_BLADE_2018_MERCURY:
            device_type = "Razer Blade 15 (2018) Mercury\n";
            break;

        case USB_DEVICE_ID_RAZER_BLADE_2018_BASE:
            device_type = "Razer Blade 15 (2018) Base Model\n";
            break;

        case USB_DEVICE_ID_RAZER_BLADE_2019_ADV:
            device_type = "Razer Blade 15 (2019) Advanced\n";
            break;

        case USB_DEVICE_ID_RAZER_BLADE_2019_BASE:
            device_type = "Razer Blade 15 (2019) Base Model\n";
            break;

        case USB_DEVICE_ID_RAZER_BLADE_EARLY_2020_BASE:
            device_type = "Razer Blade 15 Base (Early 2020)\n";
            break;

        case USB_DEVICE_ID_RAZER_BLADE_MID_2019_MERCURY:
            device_type = "Razer Blade 15 (Mid 2019) Mercury White\n";
            break;

        case USB_DEVICE_ID_RAZER_BLADE_STUDIO_EDITION_2019:
            device_type = "Razer Blade 15 Studio Edition (2019)\n";
            break;

        case USB_DEVICE_ID_RAZER_BLADE_LATE_2016:
            device_type = "Razer Blade (Late 2016)\n";
            break;

        case USB_DEVICE_ID_RAZER_BLADE_PRO_2017:
            device_type = "Razer Blade Pro (2017)\n";
            break;
        case USB_DEVICE_ID_RAZER_BLADE_PRO_2017_FULLHD:
            device_type = "Razer Blade Pro FullHD (2017)\n";
            break;

        case USB_DEVICE_ID_RAZER_BLADE_PRO_2019:
            device_type = "Razer Blade Pro (2019)\n";
            break;

        case USB_DEVICE_ID_RAZER_BLADE_PRO_LATE_2019:
            device_type = "Razer Blade Pro (Late 2019)\n";
            break;

        case USB_DEVICE_ID_RAZER_BLADE_STEALTH_LATE_2017:
            device_type = "Razer Blade Stealth (Late 2017)\n";
            break;

        case USB_DEVICE_ID_RAZER_BLADE_STEALTH_2019:
            device_type = "Razer Blade Stealth (2019)\n";
            break;

        case USB_DEVICE_ID_RAZER_BLADE_15_ADV_2020:
            device_type = "Razer Blade 15 Advanced (2020)\n";
            break;

        case USB_DEVICE_ID_RAZER_BLADE_15_ADV_2021:
            device_type = "Razer Blade 15 Advanced (2021)\n";
            break;

        case USB_DEVICE_ID_RAZER_TARTARUS:
            device_type = "Razer Tartarus\n";
            break;

        case USB_DEVICE_ID_RAZER_TARTARUS_CHROMA:
            device_type = "Razer Tartarus Chroma\n";
            break;

        case USB_DEVICE_ID_RAZER_TARTARUS_V2:
            device_type = "Razer Tartarus V2\n";
            break;

        case USB_DEVICE_ID_RAZER_BLACKWIDOW_OVERWATCH:
            device_type = "Razer BlackWidow Chroma (Overwatch)\n";
            break;

        case USB_DEVICE_ID_RAZER_BLACKWIDOW_CHROMA:
            device_type = "Razer BlackWidow Chroma\n";
            break;

        case USB_DEVICE_ID_RAZER_DEATHSTALKER_EXPERT:
            device_type = "Razer Deathstalker Expert\n";
            break;

        case USB_DEVICE_ID_RAZER_DEATHSTALKER_CHROMA:
            device_type = "Razer DeathStalker Chroma\n";
            break;

        case USB_DEVICE_ID_RAZER_BLACKWIDOW_CHROMA_TE:
            device_type = "Razer BlackWidow Chroma Tournament Edition\n";
            break;

        case USB_DEVICE_ID_RAZER_BLACKWIDOW_X_CHROMA:
            device_type = "Razer BlackWidow X Chroma\n";
            break;

        case USB_DEVICE_ID_RAZER_BLACKWIDOW_X_CHROMA_TE:
            device_type = "Razer BlackWidow X Chroma Tournament Edition\n";
            break;

        case USB_DEVICE_ID_RAZER_BLACKWIDOW_LITE:
            device_type = "Razer BlackWidow Lite\n";
            break;

        case USB_DEVICE_ID_RAZER_BLACKWIDOW_2019:
            device_type = "Razer BlackWidow 2019\n";
            break;

        case USB_DEVICE_ID_RAZER_BLACKWIDOW_ESSENTIAL:
            device_type = "Razer BlackWidow Essential\n";
            break;

        case USB_DEVICE_ID_RAZER_ORNATA:
            device_type = "Razer Ornata\n";
            break;

        case USB_DEVICE_ID_RAZER_ORNATA_CHROMA:
            device_type = "Razer Ornata Chroma\n";
            break;

        case USB_DEVICE_ID_RAZER_ORNATA_CHROMA_V2:
            device_type = "Razer Ornata Chroma V2\n";
            break;

        case USB_DEVICE_ID_RAZER_HUNTSMAN_ELITE:
            device_type = "Razer Huntsman Elite\n";
            break;

        case USB_DEVICE_ID_RAZER_HUNTSMAN_TE:
            device_type = "Razer Huntsman Tournament Edition\n";
            break;

        case USB_DEVICE_ID_RAZER_BLACKWIDOW_ELITE:
            device_type = "Razer BlackWidow Elite\n";
            break;

        case USB_DEVICE_ID_RAZER_HUNTSMAN:
            device_type = "Razer Huntsman\n";
            break;

        case USB_DEVICE_ID_RAZER_CYNOSA_CHROMA:
            device_type = "Razer Cynosa Chroma\n";
            break;

        case USB_DEVICE_ID_RAZER_CYNOSA_CHROMA_PRO:
            device_type = "Razer Cynosa Chroma Pro\n";
            break;

        case USB_DEVICE_ID_RAZER_CYNOSA_LITE:
            device_type = "Razer Cynosa Lite\n";
            break;

        case USB_DEVICE_ID_RAZER_BLACKWIDOW_CHROMA_V2:
            device_type = "Razer BlackWidow Chroma V2\n";
            break;

        case USB_DEVICE_ID_RAZER_ANANSI:
            device_type = "Razer Anansi\n";
            break;

        case USB_DEVICE_ID_RAZER_CYNOSA_V2:
            device_type = "Razer Cynosa V2\n";
            break;

        case USB_DEVICE_ID_RAZER_HUNTSMAN_MINI:
            device_type = "Razer Huntsman Mini\n";
            break;

        default:
            device_type = "Unknown Device\n";
    }

    return sprintf(buf, "%s", device_type);
}

/**
 * Read device file "game_mode"
 *
 * Returns a string
 */
int razer_attr_read_mode_game(IOUSBDeviceInterface **usb_dev, char *buf) {
    struct razer_report report = razer_chroma_standard_get_led_state(VARSTORE, GAME_LED);
    struct razer_report response;

    response = razer_send_payload(usb_dev, &report);
    return sprintf(buf, "%d\n", response.arguments[2]);
}

/**
 * Write device file "mode_macro"
 *
 * When 1 is written (as a character, 0x31) Macro mode will be enabled, if 0 is written (0x30)
 * then game mode will be disabled
 */
int razer_attr_write_mode_macro(IOUSBDeviceInterface **usb_dev, const char *buf, int count) {
    unsigned char enabled = (unsigned char)strtol(buf, NULL, 10);
    struct razer_report report = razer_chroma_standard_set_led_state(VARSTORE, MACRO_LED, enabled);

    razer_send_payload(usb_dev, &report);

    return count;
}

/**
 * Write device file "mode_macro_effect"
 *
 * When 1 is written the LED will blink, 0 will static
 */
int razer_attr_write_mode_macro_effect(IOUSBDeviceInterface **usb_dev, const char *buf, int count) {
    struct razer_report report;
    unsigned char enabled = (unsigned char)strtol(buf, NULL, 10);
    report = razer_chroma_standard_set_led_effect(VARSTORE, MACRO_LED, enabled);
    razer_send_payload(usb_dev, &report);

    return count;
}

/**
 * Read device file "macro_mode_effect"
 *
 * Returns a string
 */
int razer_attr_read_mode_macro_effect(IOUSBDeviceInterface **usb_dev, char *buf) {
    struct razer_report report = razer_chroma_standard_get_led_effect(VARSTORE, MACRO_LED);
    struct razer_report response = razer_send_payload(usb_dev, &report);

    return sprintf(buf, "%d\n", response.arguments[2]);
}

/**
 * Write device file "mode_pulsate"
 *
 * The brightness oscillates between fully on and fully off generating a pulsing effect
 */
int razer_attr_write_mode_pulsate(IOUSBDeviceInterface **usb_dev, const char *buf, int count) {
    struct razer_report report = razer_chroma_standard_set_led_effect(VARSTORE, BACKLIGHT_LED, 0x02);
    razer_send_payload(usb_dev, &report);

    return count;
}

/**
 * Read device file "mode_pulsate"
 *
 * Returns a string
 */
int razer_attr_read_mode_pulsate(IOUSBDeviceInterface **usb_dev, char *buf) {
    struct razer_report report = razer_chroma_standard_get_led_effect(VARSTORE, LOGO_LED);
    struct razer_report response = razer_send_payload(usb_dev, &report);

    return sprintf(buf, "%d\n", response.arguments[2]);
}

/**
 * Read device file "profile_led_red"
 *
 * Actually a Yellow LED
 *
 * Returns a string
 */
int razer_attr_read_tartarus_profile_led_red(IOUSBDeviceInterface **usb_dev, char *buf) {
    struct razer_report report = razer_chroma_standard_get_led_state(VARSTORE, RED_PROFILE_LED);
    struct razer_report response = razer_send_payload(usb_dev, &report);

    return sprintf(buf, "%d\n", response.arguments[2]);
}

/**
 * Read device file "profile_led_green"
 *
 * Returns a string
 */
int razer_attr_read_tartarus_profile_led_green(IOUSBDeviceInterface **usb_dev, char *buf) {
    struct razer_report report = razer_chroma_standard_get_led_state(VARSTORE, GREEN_PROFILE_LED);
    struct razer_report response = razer_send_payload(usb_dev, &report);

    return sprintf(buf, "%d\n", response.arguments[2]);
}

/**
 * Read device file "profile_led_blue"
 *
 * Returns a string
 */
int razer_attr_read_tartarus_profile_led_blue(IOUSBDeviceInterface **usb_dev, char *buf) {
    struct razer_report report = razer_chroma_standard_get_led_state(VARSTORE, BLUE_PROFILE_LED);
    struct razer_report response = razer_send_payload(usb_dev, &report);

    return sprintf(buf, "%d\n", response.arguments[2]);
}

/**
 * Read device file "get_firmware_version"
 *
 * Returns a string
 */
int razer_attr_read_get_firmware_version(IOUSBDeviceInterface **usb_dev, char *buf) {
    struct razer_report report = razer_chroma_standard_get_firmware_version();
    struct razer_report response_report = razer_send_payload(usb_dev, &report);

     return sprintf(buf, "v%d.%d\n", response_report.arguments[0], response_report.arguments[1]);
 }


/**
 * Write device file "mode_none"
 *
 * No keyboard effect is activated whenever this file is written to
 */
int razer_attr_write_mode_none(IOUSBDeviceInterface **usb_dev, const char *buf, int count) {
    struct razer_report report;
    razer_chroma_standard_matrix_effect_none(VARSTORE, BACKLIGHT_LED);

    razer_send_payload(usb_dev, &report);

    return count;
}

/**
 * Write device file "mode_wave"
 *
 * When 1 is written (as a character, 0x31) the wave effect is displayed moving left across the keyboard
 * if 2 is written (0x32) then the wave effect goes right
 *
 * For the extended its 0x00 and 0x01
 */
int razer_attr_write_mode_wave(IOUSBDeviceInterface **usb_dev, const char *buf, int count) {
    unsigned char direction = (unsigned char)strtol(buf, NULL, 10);
    struct razer_report report;
    report = razer_chroma_standard_matrix_effect_wave(VARSTORE, BACKLIGHT_LED, direction);

    razer_send_payload(usb_dev, &report);

    return count;
}

/**
 * Write device file "mode_spectrum"
 *
 * Specrum effect mode is activated whenever the file is written to
 */
int razer_attr_write_mode_spectrum(IOUSBDeviceInterface **usb_dev, const char *buf, int count) {
    struct razer_report report;
    report = razer_chroma_standard_matrix_effect_spectrum(VARSTORE, BACKLIGHT_LED);
    razer_send_payload(usb_dev, &report);

    return count;
}

/**
 * Write device file "mode_reactive"
 *
 * Sets reactive mode when this file is written to. A speed byte and 3 RGB bytes should be written
 */
int razer_attr_write_mode_reactive(IOUSBDeviceInterface **usb_dev, const char *buf, int count) {
    struct razer_report report;

    if(count == 4) {
        unsigned char speed = (unsigned char)buf[0];
        report = razer_chroma_standard_matrix_effect_reactive(VARSTORE, BACKLIGHT_LED, speed, (struct razer_rgb*)&buf[1]);
        razer_send_payload(usb_dev, &report);
    } else {
        printf("razerkbd: Reactive only accepts Speed, RGB (4byte)");
    }

    return count;
}

/**
 * Write device file "mode_static"
 *
 * Set the keyboard to mode when 3 RGB bytes are written
 */
int razer_attr_write_mode_static(IOUSBDeviceInterface **usb_dev, const char *buf, int count) {
    struct razer_report report;

    if(count == 3) {
        report = razer_chroma_standard_matrix_effect_static(VARSTORE, BACKLIGHT_LED, (struct razer_rgb*)&buf[0]);
        razer_send_payload(usb_dev, &report);
    } else {
        printf("razerkbd: mode only accepts RGB (3byte)");
    }

    return count;
}

/**
* Write device file "mode_starlight"
*
* Starlight keyboard effect is activated whenever this file is written to (for bw2016)
*
* Or if an Ornata
* 7 bytes, speed, rgb, rgb
* 4 bytes, speed, rgb
* 1 byte, speed
*/
int razer_attr_write_mode_starlight(IOUSBDeviceInterface **usb_dev, const char *buf, int count) {
    struct razer_report report;
    report = razer_chroma_standard_matrix_effect_starlight_single(VARSTORE, BACKLIGHT_LED, buf[0], (struct razer_rgb*)&buf[1]);
    razer_send_payload(usb_dev, &report);

    return count;
}

/**
 * Write device file "mode_breath"
 */
int razer_attr_write_mode_breath(IOUSBDeviceInterface **usb_dev, const char *buf, int count) {
    struct razer_report report;

    switch(count) {
        case 1: // "Random" colour mode
            report = razer_chroma_standard_matrix_effect_breathing_random(VARSTORE, BACKLIGHT_LED);
            razer_send_payload(usb_dev, &report);
            break;
        case 3: // Single colour mode
            report = razer_chroma_standard_matrix_effect_breathing_single(VARSTORE, BACKLIGHT_LED, (struct razer_rgb*)&buf[0]);
            razer_send_payload(usb_dev, &report);
            break;
        case 6: // Dual colour mode
            report = razer_chroma_standard_matrix_effect_breathing_dual(VARSTORE, BACKLIGHT_LED, (struct razer_rgb*)&buf[0], (struct razer_rgb*)&buf[3]);
            razer_send_payload(usb_dev, &report);
            break;
        default:
            printf("Unsupported breath mode.");
            break;
    }

    return count;
}


int has_inverted_led_state(IOUSBDeviceInterface **usb_dev) {
    UInt16 product = -1;
    (*usb_dev)->GetDeviceProduct(usb_dev, &product);

    switch(product) {
        case USB_DEVICE_ID_RAZER_BLADE_STEALTH_LATE_2016:
        case USB_DEVICE_ID_RAZER_BLADE_PRO_LATE_2016:
        case USB_DEVICE_ID_RAZER_BLADE_QHD:
        case USB_DEVICE_ID_RAZER_BLADE_LATE_2016:
            return 1;
        default:
            return 0;
    }
}

/**
 * Read device file "set_logo"
 *
 * Sets the logo lighting state to the ASCII number written to this file.
 */
int razer_attr_read_set_logo(IOUSBDeviceInterface **usb_dev, char *buf, int count) {
    struct razer_report report = razer_chroma_standard_get_led_effect(VARSTORE, LOGO_LED);
    struct razer_report response = get_empty_razer_report();
    int state;

    // Blade laptops don't use effect for logo on/off, and mode 2 ("blink") is technically unsupported.
    if (is_blade_laptop(usb_dev)) {
        report = razer_chroma_standard_get_led_state(VARSTORE, LOGO_LED);
    }

    response = razer_send_payload(usb_dev, &report);
    state = response.arguments[2];

    if (has_inverted_led_state(usb_dev) && (state == 0 || state == 1)) {
        state = !state;
    }

    return sprintf(buf, "%d\n", state);
}


/**
 * Write device file "set_logo"
 *
 * Sets the logo lighting state to the ASCII number written to this file.
 */
int razer_attr_write_set_logo(IOUSBDeviceInterface **usb_dev, const char *buf, int count) {
    unsigned char state = (unsigned char)strtol(buf, NULL, 10);
    struct razer_report report = {0};

    if (has_inverted_led_state(usb_dev) && (state == 0 || state == 1)) {
        state = !state;
    }

    // Blade laptops are... different. They use state instead of effect.
    // Note: This does allow setting of mode 2 ("blink"), but this is an undocumented feature.
    if (is_blade_laptop(usb_dev) && (state == 0 || state == 1)) {
        report = razer_chroma_standard_set_led_state(VARSTORE, LOGO_LED, state);
    } else {
        report = razer_chroma_standard_set_led_effect(VARSTORE, LOGO_LED, state);
    }

    razer_send_payload(usb_dev, &report);

    return count;
}


/**
 * Write device file "mode_custom"
 *
 * Sets the keyboard to custom mode whenever the file is written to
 */
int razer_attr_write_mode_custom(IOUSBDeviceInterface **usb_dev, const char *buf, int count) {
    struct razer_report report;

    report = razer_chroma_standard_matrix_effect_custom_frame(VARSTORE); // Possibly could use VARSTORE
    razer_send_payload(usb_dev, &report);
    return count;
}

/**
 * Write device file "set_fn_toggle"
 *
 * Sets the logo lighting state to the ASCII number written to this file.
 */
int razer_attr_write_set_fn_toggle(IOUSBDeviceInterface **usb_dev, const char *buf, int count) {
    unsigned char state = (unsigned char)strtol(buf, NULL, 10);
    struct razer_report report = razer_chroma_misc_fn_key_toggle(state);
    razer_send_payload(usb_dev, &report);

    return count;
}

/**
 * Write device file "set_brightness"
 *
 * Sets the brightness to the ASCII number written to this file.
 */
int razer_attr_write_set_brightness(IOUSBDeviceInterface **usb_dev, const char *buf, int count) {
    unsigned char brightness = (unsigned char)strtol(buf, NULL, 10);
    struct razer_report report;


    report = razer_chroma_misc_set_blade_brightness(brightness);
    razer_send_payload(usb_dev, &report);

    return count;
}

/**
 * Read device file "macro_mode"
 *
 * Returns a string
 */
int razer_attr_read_set_brightness(IOUSBDeviceInterface **usb_dev, char *buf) {
    unsigned char brightness = 0;
    struct razer_report report;
    struct razer_report response;
    report = razer_chroma_misc_get_blade_brightness();

    response = razer_send_payload(usb_dev, &report);

    // Brightness is stored elsewhere for the stealth cmds
    brightness = response.arguments[1];

    return sprintf(buf, "%d\n", brightness);
}

/**
 * Write device file "matrix_custom_frame"
 *
 * Format
 * ROW_ID START_COL STOP_COL RGB...
 */
int razer_attr_write_matrix_custom_frame(IOUSBDeviceInterface **usb_dev, const char *buf, int count) {
    struct razer_report report;
    int offset = 0;
    unsigned char row_id;
    unsigned char start_col;
    unsigned char stop_col;
    unsigned char row_length;

    //printk(KERN_ALERT "razerkbd: Total count: %d\n", (unsigned char)count);

    while(offset < count)
    {
        if(offset + 3 > count)
        {
            printf("razerkbd: Wrong Amount of data provided: Should be ROW_ID, START_COL, STOP_COL, N_RGB\n");
            break;
        }

        row_id = buf[offset++];
        start_col = buf[offset++];
        stop_col = buf[offset++];
        row_length = ((stop_col+1) - start_col) * 3;

        // printk(KERN_ALERT "razerkbd: Row ID: %d, Start: %d, Stop: %d, row length: %d\n", row_id, start_col, stop_col, row_length);

        if(start_col > stop_col)
        {
            printf("razerkbd: Start column is greater than end column\n");
            break;
        }

        if(offset + row_length > count)
        {
            printf("razerkbd: Not enough RGB to fill row\n");
            break;
        }

        // Offset now at beginning of RGB data
        report.transaction_id.id = 0x80; // Fall into the 2016/blade/blade2016 to set device id
        razer_send_payload(usb_dev, &report);

        // *3 as its 3 bytes per col (RGB)
        offset += row_length;
    }


    return count;
}

/**
 * Send report to the keyboard
 */
int razer_get_report(IOUSBDeviceInterface **usb_dev, struct razer_report *request_report, struct razer_report *response_report) {
    UInt16 product = -1;
    (*usb_dev)->GetDeviceProduct(usb_dev, &product);

    uint report_index;
    uint response_index;

    switch (product) {
        case USB_DEVICE_ID_RAZER_ANANSI:
            report_index = 0x02;
            response_index = 0x02;
            break;
        default:
            report_index = 0x01;
            response_index = 0x01;
            break;
    }

    return razer_get_usb_response(usb_dev, report_index, request_report, response_index, response_report, RAZER_BLACKWIDOW_CHROMA_WAIT_MIN_US);
}

/**
 * Function to send to device, get response, and actually check the response
 */
struct razer_report razer_send_payload(IOUSBDeviceInterface **dev, struct razer_report *request_report) {
    IOReturn retval = -1;

    struct razer_report response_report = {0};
    request_report->crc = razer_calculate_crc(request_report);

    retval = razer_get_report(dev, request_report, &response_report);

    if (retval == kIOReturnSuccess) {
        // Check the packet number, class and command are the same
        if(response_report.remaining_packets != request_report->remaining_packets ||
           response_report.command_class != request_report->command_class ||
           response_report.command_id.id != request_report->command_id.id) {
            printf("Response doesnt match request\n");
//        } else if (response_report.status == RAZER_CMD_BUSY) {
//            printf("Device is busy\n");
        } else if (response_report.status == RAZER_CMD_FAILURE) {
            printf("Command failed\n");
        } else if (response_report.status == RAZER_CMD_NOT_SUPPORTED) {
            printf("Command not supported\n");
        } else if (response_report.status == RAZER_CMD_TIMEOUT) {
            printf("Command timed out\n");
        }
    } else {
        printf("Invalid Report Length");
    }

    return response_report;
}

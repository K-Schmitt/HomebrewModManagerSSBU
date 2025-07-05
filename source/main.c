#include <switch.h>
#include <stdio.h>
#include "mod_manager.h"

int main(int argc, char **argv) {
    consoleInit(NULL);

    PadState pad;
    padConfigureInput(1, HidNpadStyleSet_NpadStandard);
    padInitializeDefault(&pad);

    ModManager manager;
    mod_manager_init(&manager);
    mod_manager_scan_mods(&manager);
    mod_manager_draw(&manager);

    while (appletMainLoop()) {
        padUpdate(&pad);
        u64 kDown = padGetButtonsDown(&pad);

        if (kDown & HidNpadButton_Plus) {
            break;
        }

        if (kDown & HidNpadButton_Up) {
            if (manager.selected > 0) {
                manager.selected--;
                mod_manager_adjust_scroll(&manager);
                mod_manager_draw(&manager);
            }
        }

        if (kDown & HidNpadButton_Down) {
            if (manager.selected < manager.count - 1) {
                manager.selected++;
                mod_manager_adjust_scroll(&manager);
                mod_manager_draw(&manager);
            }
        }

        if (kDown & HidNpadButton_A) {
            if (manager.count > 0) {
                mod_manager_toggle_mod(&manager, manager.selected);
                mod_manager_draw(&manager);
            }
        }

        if (kDown & HidNpadButton_X) {
            mod_manager_scan_mods(&manager);
            if (manager.selected >= manager.count) {
                manager.selected = manager.count > 0 ? manager.count - 1 : 0;
            }
            mod_manager_adjust_scroll(&manager);
            mod_manager_draw(&manager);
        }

        if (kDown & HidNpadButton_Y) {
            manager.current_language = cycle_language(manager.current_language);
            mod_manager_draw(&manager);
        }

        if (kDown & HidNpadButton_L || kDown & HidNpadButton_R) {
            mod_manager_cycle_sort(&manager);
            if (manager.selected >= manager.count) {
                manager.selected = manager.count > 0 ? manager.count - 1 : 0;
            }
            mod_manager_adjust_scroll(&manager);
            mod_manager_draw(&manager);
        }

        if (kDown & HidNpadButton_ZL) {
            if (manager.count > 0) {
                mod_manager_enable_all(&manager);
                mod_manager_draw(&manager);
            }
        }

        if (kDown & HidNpadButton_ZR) {
            if (manager.count > 0) {
                mod_manager_disable_all(&manager);
                mod_manager_draw(&manager);
            }
        }

        consoleUpdate(NULL);
    }

    consoleExit(NULL);
    return 0;
}

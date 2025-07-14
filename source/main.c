#include <switch.h>
#include <stdio.h>
#include "mod_manager.h"

#define STICK_THRESHOLD 0.5f

int main(int argc, char **argv) {
    consoleInit(NULL);

    PadState pad;
    padConfigureInput(1, HidNpadStyleSet_NpadStandard);
    padInitializeDefault(&pad);

    ModManager manager;
    mod_manager_init(&manager);
    mod_manager_scan_mods(&manager);
    mod_manager_draw(&manager);

    u64 lastStickInput = 0;

    while (appletMainLoop()) {
        padUpdate(&pad);
        u64 kDown = padGetButtonsDown(&pad);

        HidAnalogStickState leftStick = padGetStickPos(&pad, 0);
        float stickY = (float)leftStick.y / 32767.0f;

        if (kDown & HidNpadButton_Plus) {
            break;
        }

        if (kDown & HidNpadButton_Up) {
            if (manager.count > 0) {
                if (manager.selected > 0) {
                    manager.selected--;
                } else {
                    manager.selected = manager.count - 1;
                }
                mod_manager_adjust_scroll(&manager);
                mod_manager_draw(&manager);
            }
        }

        if (kDown & HidNpadButton_Down) {
            if (manager.count > 0) {
                if (manager.selected < manager.count - 1) {
                    manager.selected++;
                } else {
                    manager.selected = 0;
                }
                mod_manager_adjust_scroll(&manager);
                mod_manager_draw(&manager);
            }
        }

        u64 currentTick = armGetSystemTick();
        if (manager.count > 0 && (currentTick - lastStickInput) > 1000000) {
            if (stickY > STICK_THRESHOLD) {
                int newSelected = manager.selected - 1;
                if (newSelected < 0) {
                    newSelected = 0;
                }
                if (newSelected != manager.selected) {
                    manager.selected = newSelected;
                    mod_manager_adjust_scroll(&manager);
                    mod_manager_draw(&manager);
                    lastStickInput = currentTick;
                }
            } else if (stickY < -STICK_THRESHOLD) {
                int newSelected = manager.selected + 1;
                if (newSelected >= manager.count) {
                    newSelected = manager.count - 1;
                }
                if (newSelected != manager.selected) {
                    manager.selected = newSelected;
                    mod_manager_adjust_scroll(&manager);
                    mod_manager_draw(&manager);
                    lastStickInput = currentTick;
                }
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

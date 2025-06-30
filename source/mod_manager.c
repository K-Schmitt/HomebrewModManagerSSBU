#include "mod_manager.h"

void mod_manager_init(ModManager* manager) {
    manager->count = 0;
    manager->selected = 0;
    memset(manager->mods, 0, sizeof(manager->mods));
    create_mods_directories();
}

void create_mods_directories() {
    mkdir("sdmc:/ultimate", 0777);
    mkdir("sdmc:/ultimate/mods", 0777);
    mkdir("sdmc:/ultimate/mods_disabled", 0777);
}

bool file_exists(const char* path) {
    struct stat st;
    return stat(path, &st) == 0;
}

bool move_file_or_directory(const char* src, const char* dest) {
    return rename(src, dest) == 0;
}

void mod_enable(const char* mod_name) {
    char src_path[MAX_PATH_LENGTH];
    char dest_path[MAX_PATH_LENGTH];

    snprintf(src_path, sizeof(src_path), "%s%s", MODS_DISABLED_PATH, mod_name);
    snprintf(dest_path, sizeof(dest_path), "%s%s", MODS_PATH, mod_name);

    move_file_or_directory(src_path, dest_path);
}

void mod_disable(const char* mod_name) {
    char src_path[MAX_PATH_LENGTH];
    char dest_path[MAX_PATH_LENGTH];

    snprintf(src_path, sizeof(src_path), "%s%s", MODS_PATH, mod_name);
    snprintf(dest_path, sizeof(dest_path), "%s%s", MODS_DISABLED_PATH, mod_name);

    move_file_or_directory(src_path, dest_path);
}

void scan_directory(ModManager* manager, const char* dir_path, bool enabled) {
    DIR* dir = opendir(dir_path);
    if (!dir) {
        return;
    }

    struct dirent* entry;

    while ((entry = readdir(dir)) != NULL && manager->count < MAX_MODS) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        if (entry->d_name[0] == '.' || strstr(entry->d_name, ".tmp")) {
            continue;
        }

        Mod* mod = &manager->mods[manager->count];
        strncpy(mod->name, entry->d_name, MAX_NAME_LENGTH - 1);
        mod->name[MAX_NAME_LENGTH - 1] = '\0';

        snprintf(mod->path, sizeof(mod->path), "%s%s", dir_path, entry->d_name);

        mod->is_directory = (entry->d_type == DT_DIR);
        mod->enabled = enabled;

        manager->count++;
    }

    closedir(dir);
}

void mod_manager_scan_mods(ModManager* manager) {
    manager->count = 0;

    scan_directory(manager, MODS_PATH, true);

    scan_directory(manager, MODS_DISABLED_PATH, false);
}

void mod_manager_toggle_mod(ModManager* manager, int index) {
    if (index < 0 || index >= manager->count) {
        return;
    }

    Mod* mod = &manager->mods[index];

    if (mod->enabled) {
        mod_disable(mod->name);
    } else {
        mod_enable(mod->name);
    }

    mod_manager_scan_mods(manager);

    if (manager->selected >= manager->count) {
        manager->selected = manager->count > 0 ? manager->count - 1 : 0;
    }
}

void mod_manager_draw(ModManager* manager) {
    consoleClear();

    printf("\x1b[2;1H");
    printf("=== Manager de Mods SSBU ===\n\n");

    if (manager->count == 0) {
        printf("Aucun mod trouve.\n");
        printf("Placez vos mods dans:\n");
        printf("- %s (mods actifs)\n", MODS_PATH);
        printf("- %s (mods desactives)\n\n", MODS_DISABLED_PATH);
    } else {
        printf("Mods trouves: %d\n\n", manager->count);

        int active_count = 0, disabled_count = 0;
        for (int i = 0; i < manager->count; i++) {
            if (manager->mods[i].enabled) active_count++;
            else disabled_count++;
        }

        printf("\x1b[32mActifs: %d\x1b[37m | \x1b[31mDesactives: %d\x1b[37m\n\n", active_count, disabled_count);

        for (int i = 0; i < manager->count; i++) {
            Mod* mod = &manager->mods[i];

            if (i == manager->selected) {
                printf("\x1b[32m> ");
            } else {
                printf("  ");
            }

            if (mod->enabled) {
                printf("\x1b[32m[ON] ");
            } else {
                printf("\x1b[31m[OFF]");
            }

            printf("\x1b[37m %s", mod->name);

            if (mod->is_directory) {
                printf(" \x1b[36m(Dossier)\x1b[37m");
            }

            printf("\n");
        }
    }

    printf("\n\x1b[33m");
    printf("Controles:\n");
    printf("↑/↓: Naviguer\n");
    printf("A: Activer/Desactiver le mod\n");
    printf("X: Actualiser la liste\n");
    printf("+: Quitter\n");
    printf("\x1b[37m");

    consoleUpdate(NULL);
}
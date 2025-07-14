#include "mod_manager.h"
#include <string.h>
#include <stdlib.h>

static int sort_by_name(const Mod* a, const Mod* b, bool reverse) {
    int result = strcasecmp(a->name, b->name);
    return reverse ? -result : result;
}

static int compare_alphabetical(const void* a, const void* b) {
    return sort_by_name((const Mod*)a, (const Mod*)b, false);
}

static int compare_alphabetical_reverse(const void* a, const void* b) {
    return sort_by_name((const Mod*)a, (const Mod*)b, true);
}

static int compare_status_on_first(const void* a, const void* b) {
    const Mod* mod_a = (const Mod*)a;
    const Mod* mod_b = (const Mod*)b;

    if (mod_a->enabled != mod_b->enabled) {
        return mod_b->enabled - mod_a->enabled;
    }
    return sort_by_name(mod_a, mod_b, false);
}

static int compare_status_off_first(const void* a, const void* b) {
    const Mod* mod_a = (const Mod*)a;
    const Mod* mod_b = (const Mod*)b;

    if (mod_a->enabled != mod_b->enabled) {
        return mod_a->enabled - mod_b->enabled;
    }
    return sort_by_name(mod_a, mod_b, false);
}

static int compare_type_folders_first(const void* a, const void* b) {
    const Mod* mod_a = (const Mod*)a;
    const Mod* mod_b = (const Mod*)b;

    if (mod_a->is_directory != mod_b->is_directory) {
        return mod_b->is_directory - mod_a->is_directory;
    }
    return sort_by_name(mod_a, mod_b, false);
}

static void apply_sort(ModManager* manager) {
    if (manager->count <= 1) return;

    static int (*const sort_functions[])(const void*, const void*) = {
        [SORT_ALPHABETICAL] = compare_alphabetical,
        [SORT_ALPHABETICAL_REVERSE] = compare_alphabetical_reverse,
        [SORT_STATUS_ON_FIRST] = compare_status_on_first,
        [SORT_STATUS_OFF_FIRST] = compare_status_off_first,
        [SORT_TYPE_FOLDERS_FIRST] = compare_type_folders_first
    };

    if (manager->current_sort < SORT_COUNT) {
        qsort(manager->mods, manager->count, sizeof(Mod), sort_functions[manager->current_sort]);
    }
}

void mod_manager_init(ModManager* manager) {
    manager->count = 0;
    manager->selected = 0;
    manager->scroll_offset = 0;
    manager->current_language = detect_system_language();
    manager->current_sort = SORT_ALPHABETICAL;
    memset(manager->mods, 0, sizeof(manager->mods));
    create_mods_directories();
}

void create_mods_directories(void) {
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

static void scan_directory(ModManager* manager, const char* dir_path, bool enabled) {
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
        size_t name_len = strlen(entry->d_name);
        if (name_len >= MAX_NAME_LENGTH) {
            strncpy(mod->name, entry->d_name, MAX_NAME_LENGTH - 1);
            mod->name[MAX_NAME_LENGTH - 1] = '\0';
        } else {
            strcpy(mod->name, entry->d_name);
        }

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
    apply_sort(manager);
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

void mod_manager_cycle_sort(ModManager* manager) {
    manager->current_sort = (SortOrder)((manager->current_sort + 1) % SORT_COUNT);
    mod_manager_scan_mods(manager);
}

static void adjust_scroll(ModManager* manager) {
    if (manager->selected < manager->scroll_offset) {
        manager->scroll_offset = manager->selected;
    }
    else if (manager->selected >= manager->scroll_offset + MAX_VISIBLE_MODS) {
        manager->scroll_offset = manager->selected - MAX_VISIBLE_MODS + 1;
    }
}

void mod_manager_adjust_scroll(ModManager* manager) {
    adjust_scroll(manager);
}

void mod_manager_enable_all(ModManager* manager) {
    for (int i = 0; i < manager->count; i++) {
        if (!manager->mods[i].enabled) {
            mod_enable(manager->mods[i].name);
        }
    }
    mod_manager_scan_mods(manager);
    mod_manager_adjust_scroll(manager);
}

void mod_manager_disable_all(ModManager* manager) {
    for (int i = 0; i < manager->count; i++) {
        if (manager->mods[i].enabled) {
            mod_disable(manager->mods[i].name);
        }
    }
    mod_manager_scan_mods(manager);
    mod_manager_adjust_scroll(manager);
}

const char* get_sort_name(SortOrder sort, Language lang) {
    const LocalizedStrings* strings = get_localized_strings(lang);

    switch (sort) {
        case SORT_ALPHABETICAL:
            return strings->sort_alphabetical;
        case SORT_ALPHABETICAL_REVERSE:
            return strings->sort_alphabetical_reverse;
        case SORT_STATUS_ON_FIRST:
            return strings->sort_status_on_first;
        case SORT_STATUS_OFF_FIRST:
            return strings->sort_status_off_first;
        case SORT_TYPE_FOLDERS_FIRST:
            return strings->sort_type_folders_first;
        default:
            return strings->sort_alphabetical;
    }
}

void mod_manager_draw(ModManager* manager) {
    consoleClear();

    const LocalizedStrings* strings = get_localized_strings(manager->current_language);

    printf("\x1b[2;1H");
    printf("%s\n\n", strings->title);

    if (manager->count == 0) {
        printf("%s\n", strings->no_mods_found);
        printf("%s\n", strings->place_mods_in);
        printf("- %s (%s)\n", MODS_PATH, strings->active_mods);
        printf("- %s (%s)\n\n", MODS_DISABLED_PATH, strings->disabled_mods);
    } else {
        printf("%s: %d\n\n", strings->mods_found, manager->count);

        int active_count = 0, disabled_count = 0;
        for (int i = 0; i < manager->count; i++) {
            if (manager->mods[i].enabled) active_count++;
            else disabled_count++;
        }

        printf("\x1b[32m%s: %d\x1b[37m | \x1b[31m%s: %d\x1b[37m\n", 
               strings->active, active_count, strings->disabled, disabled_count);

        printf("\x1b[36m%s: %s\x1b[37m\n",
               strings->current_sort, get_sort_name(manager->current_sort, manager->current_language));

        printf("\n");

        int start_index = manager->scroll_offset;
        int end_index = start_index + MAX_VISIBLE_MODS;
        if (end_index > manager->count) {
            end_index = manager->count;
        }

        for (int i = start_index; i < end_index; i++) {
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
                printf(" \x1b[36m(%s)\x1b[37m", strings->folder);
            }

            printf("\n");
        }

        if (manager->count > MAX_VISIBLE_MODS) {
            printf("\n\x1b[33m");
            if (manager->scroll_offset > 0) {
                printf("%s", strings->mods_above);
            }
            if (end_index < manager->count) {
                if (manager->scroll_offset > 0) printf(" | ");
                printf("%s", strings->mods_below);
            }
            printf("\x1b[37m\n");
        }
    }

    printf("\n\x1b[33m");
    printf("%s\n", strings->controls);
    printf("^/v: %s\n", strings->navigate);
    printf("A: %s\n", strings->toggle_mod);
    printf("X: %s\n", strings->refresh_list);
    printf("Y: %s\n", strings->change_language);
    printf("L/R: %s\n", strings->change_sort);
    printf("ZL: %s\n", strings->enable_all);
    printf("ZR: %s\n", strings->disable_all);
    printf("+: %s\n", strings->quit);
    printf("\x1b[37m");

    consoleUpdate(NULL);
}
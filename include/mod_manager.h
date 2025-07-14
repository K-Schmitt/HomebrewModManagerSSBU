#pragma once
#include <switch.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include "localization.h"

#define MAX_MODS 500
#define MAX_PATH_LENGTH 256
#define MAX_NAME_LENGTH 64
#define MODS_PATH "sdmc:/ultimate/mods/"
#define MODS_DISABLED_PATH "sdmc:/ultimate/mods_disabled/"
#define MAX_VISIBLE_MODS 24

typedef enum {
    SORT_ALPHABETICAL = 0,
    SORT_ALPHABETICAL_REVERSE,
    SORT_STATUS_ON_FIRST,
    SORT_STATUS_OFF_FIRST,
    SORT_TYPE_FOLDERS_FIRST,
    SORT_COUNT
} SortOrder;

typedef struct {
    char name[MAX_NAME_LENGTH];
    char path[MAX_PATH_LENGTH];
    bool enabled;
    bool is_directory;
} Mod;

typedef struct {
    Mod mods[MAX_MODS];
    int count;
    int selected;
    int scroll_offset;
    Language current_language;
    SortOrder current_sort;
} ModManager;

void mod_manager_init(ModManager* manager);
void mod_manager_scan_mods(ModManager* manager);
void mod_manager_toggle_mod(ModManager* manager, int index);
void mod_manager_draw(ModManager* manager);
void mod_manager_adjust_scroll(ModManager* manager);
void mod_manager_enable_all(ModManager* manager);
void mod_manager_disable_all(ModManager* manager);

void mod_enable(const char* mod_name);
void mod_disable(const char* mod_name);
void create_mods_directories(void);
bool file_exists(const char* path);
bool move_file_or_directory(const char* src, const char* dest);
void mod_manager_cycle_sort(ModManager* manager);
const char* get_sort_name(SortOrder sort, Language lang);
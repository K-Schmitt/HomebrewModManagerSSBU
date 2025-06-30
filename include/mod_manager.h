#pragma once
#include <switch.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

#define MAX_MODS 100
#define MAX_PATH_LENGTH 256
#define MAX_NAME_LENGTH 64
#define MODS_PATH "sdmc:/ultimate/mods/"
#define MODS_DISABLED_PATH "sdmc:/ultimate/mods_disabled/"

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
} ModManager;

void mod_manager_init(ModManager* manager);
void mod_manager_scan_mods(ModManager* manager);
void mod_manager_toggle_mod(ModManager* manager, int index);
void mod_manager_draw(ModManager* manager);
void mod_enable(const char* mod_name);
void mod_disable(const char* mod_name);

void create_mods_directories();
bool file_exists(const char* path);
bool move_file_or_directory(const char* src, const char* dest);
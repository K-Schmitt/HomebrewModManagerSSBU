#pragma once
#include <switch.h>

typedef enum {
    LANG_ENGLISH = 0,
    LANG_FRENCH,
    LANG_GERMAN,
    LANG_SPANISH,
    LANG_ITALIAN,
    LANG_COUNT
} Language;

typedef struct {
    const char* title;
    const char* no_mods_found;
    const char* place_mods_in;
    const char* active_mods;
    const char* disabled_mods;
    const char* mods_found;
    const char* active;
    const char* disabled;
    const char* folder;
    const char* controls;
    const char* navigate;
    const char* toggle_mod;
    const char* refresh_list;
    const char* quit;
    const char* change_language;
    const char* change_sort;
    const char* sort_alphabetical;
    const char* sort_alphabetical_reverse;
    const char* sort_status_on_first;
    const char* sort_status_off_first;
    const char* sort_type_folders_first;
    const char* current_sort;
} LocalizedStrings;

Language detect_system_language(void);
const LocalizedStrings* get_localized_strings(Language lang);
Language cycle_language(Language current_lang);
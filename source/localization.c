#include "localization.h"

static const LocalizedStrings english_strings = {
    .title = "=== SSBU Mod Manager ===",
    .no_mods_found = "No mods found.",
    .place_mods_in = "Place your mods in:",
    .active_mods = "active mods",
    .disabled_mods = "disabled mods",
    .mods_found = "Mods found",
    .active = "Active",
    .disabled = "Disabled",
    .folder = "Folder",
    .controls = "Controls:",
    .navigate = "Navigate",
    .toggle_mod = "Enable/Disable mod",
    .refresh_list = "Refresh list",
    .quit = "Quit",
    .change_language = "Change language",
    .change_sort = "Change sort order",
    .sort_alphabetical = "Alphabetical (A-Z)",
    .sort_alphabetical_reverse = "Alphabetical (Z-A)",
    .sort_status_on_first = "Status (ON first)",
    .sort_status_off_first = "Status (OFF first)",
    .sort_type_folders_first = "Type (Folders first)",
    .current_sort = "Sort"
};

static const LocalizedStrings french_strings = {
    .title = "=== Manager de Mods SSBU ===",
    .no_mods_found = "Aucun mod trouve.",
    .place_mods_in = "Placez vos mods dans:",
    .active_mods = "mods actifs",
    .disabled_mods = "mods desactives",
    .mods_found = "Mods trouves",
    .active = "Actifs",
    .disabled = "Desactives",
    .folder = "Dossier",
    .controls = "Controles:",
    .navigate = "Naviguer",
    .toggle_mod = "Activer/Desactiver le mod",
    .refresh_list = "Actualiser la liste",
    .quit = "Quitter",
    .change_language = "Changer de langue",
    .change_sort = "Changer l'ordre de tri",
    .sort_alphabetical = "Alphabetique (A-Z)",
    .sort_alphabetical_reverse = "Alphabetique (Z-A)",
    .sort_status_on_first = "Statut (ON en premier)",
    .sort_status_off_first = "Statut (OFF en premier)",
    .sort_type_folders_first = "Type (Dossiers en premier)",
    .current_sort = "Tri"
};

static const LocalizedStrings german_strings = {
    .title = "=== SSBU Mod Manager ===",
    .no_mods_found = "Keine Mods gefunden.",
    .place_mods_in = "Platzieren Sie Ihre Mods in:",
    .active_mods = "aktive Mods",
    .disabled_mods = "deaktivierte Mods",
    .mods_found = "Mods gefunden",
    .active = "Aktiv",
    .disabled = "Deaktiviert",
    .folder = "Ordner",
    .controls = "Steuerung:",
    .navigate = "Navigieren",
    .toggle_mod = "Mod aktivieren/deaktivieren",
    .refresh_list = "Liste aktualisieren",
    .quit = "Beenden",
    .change_language = "Sprache wechseln",
    .change_sort = "Sortierung ändern",
    .sort_alphabetical = "Alphabetisch (A-Z)",
    .sort_alphabetical_reverse = "Alphabetisch (Z-A)",
    .sort_status_on_first = "Status (AN zuerst)",
    .sort_status_off_first = "Status (AUS zuerst)",
    .sort_type_folders_first = "Typ (Ordner zuerst)",
    .current_sort = "Sortierung"
};

static const LocalizedStrings spanish_strings = {
    .title = "=== Gestor de Mods SSBU ===",
    .no_mods_found = "No se encontraron mods.",
    .place_mods_in = "Coloca tus mods en:",
    .active_mods = "mods activos",
    .disabled_mods = "mods desactivados",
    .mods_found = "Mods encontrados",
    .active = "Activos",
    .disabled = "Desactivados",
    .folder = "Carpeta",
    .controls = "Controles:",
    .navigate = "Navegar",
    .toggle_mod = "Activar/Desactivar mod",
    .refresh_list = "Actualizar lista",
    .quit = "Salir",
    .change_language = "Cambiar idioma",
    .change_sort = "Cambiar orden",
    .sort_alphabetical = "Alfabético (A-Z)",
    .sort_alphabetical_reverse = "Alfabético (Z-A)",
    .sort_status_on_first = "Estado (ON primero)",
    .sort_status_off_first = "Estado (OFF primero)",
    .sort_type_folders_first = "Tipo (Carpetas primero)",
    .current_sort = "Orden"
};

static const LocalizedStrings italian_strings = {
    .title = "=== Gestore Mod SSBU ===",
    .no_mods_found = "Nessun mod trovato.",
    .place_mods_in = "Posiziona i tuoi mod in:",
    .active_mods = "mod attivi",
    .disabled_mods = "mod disattivati",
    .mods_found = "Mod trovati",
    .active = "Attivi",
    .disabled = "Disattivati",
    .folder = "Cartella",
    .controls = "Controlli:",
    .navigate = "Navigare",
    .toggle_mod = "Attivare/Disattivare mod",
    .refresh_list = "Aggiornare lista",
    .quit = "Uscire",
    .change_language = "Cambiare lingua",
    .change_sort = "Cambiare ordine",
    .sort_alphabetical = "Alfabetico (A-Z)",
    .sort_alphabetical_reverse = "Alfabetico (Z-A)",
    .sort_status_on_first = "Stato (ON prima)",
    .sort_status_off_first = "Stato (OFF prima)",
    .sort_type_folders_first = "Tipo (Cartelle prima)",
    .current_sort = "Ordine"
};

Language detect_system_language(void) {
    u64 languageCode = 0;
    SetLanguage language = SetLanguage_ENUS;

    Result rc = setGetSystemLanguage(&languageCode);
    if (R_SUCCEEDED(rc)) {
        rc = setMakeLanguage(languageCode, &language);
    }

    if (R_FAILED(rc)) {
        return LANG_ENGLISH;
    }

    switch (language) {
        case SetLanguage_ENUS:
        case SetLanguage_ENGB:
            return LANG_ENGLISH;
        case SetLanguage_FR:
        case SetLanguage_FRCA:
            return LANG_FRENCH;
        case SetLanguage_DE:
            return LANG_GERMAN;
        case SetLanguage_ES:
        case SetLanguage_ES419:
            return LANG_SPANISH;
        case SetLanguage_IT:
            return LANG_ITALIAN;
        default:
            return LANG_ENGLISH;
    }
}

Language cycle_language(Language current_lang) {
    Language next_lang = (Language)((current_lang + 1) % LANG_COUNT);
    return next_lang;
}

const LocalizedStrings* get_localized_strings(Language lang) {
    switch (lang) {
        case LANG_ENGLISH:
            return &english_strings;
        case LANG_FRENCH:
            return &french_strings;
        case LANG_GERMAN:
            return &german_strings;
        case LANG_SPANISH:
            return &spanish_strings;
        case LANG_ITALIAN:
            return &italian_strings;
        default:
            return &english_strings;
    }
}
# HomebrewModManagerSSBU

A simple and efficient mod manager for Super Smash Bros Ultimate on Nintendo Switch.

## 📋 Description

HomebrewModManagerSSBU is a homebrew application that allows you to easily manage your SSBU mods directly from your Nintendo Switch. The application provides an intuitive console interface for enabling/disabling your mods with multilingual support and multiple sorting options.

## ✨ Features

- 🎮 Intuitive console interface with D-Pad navigation
- ✅ One-click mod activation/deactivation
- ⚡ **Bulk operations**: Enable/disable all mods at once
- 📄 **Smart pagination**: Handle large mod collections (100+ mods)
- 📁 Support for both file and folder mods
- 🔄 Automatic mod list refresh
- 📊 Active/disabled mod counters with pagination info
- 🎯 Smooth navigation with visual selection and auto-scroll
- 🌍 **Multilingual support** (5 languages)
- 🔀 **Multiple sorting options** (5 modes)
- 🎨 Colorful interface with ANSI codes

## 🌍 Supported Languages

- 🇬🇧 English
- 🇫🇷 French
- 🇩🇪 German
- 🇪🇸 Spanish
- 🇮🇹 Italian

## 🔀 Sorting Options

1. **Alphabetical (A-Z)** - Classic alphabetical sorting
2. **Alphabetical (Z-A)** - Reverse alphabetical sorting
3. **Status (ON first)** - Active mods at top, then disabled
4. **Status (OFF first)** - Disabled mods at top, then active
5. **Type (Folders first)** - Folders first, then files

## 📦 Prerequisites

- Nintendo Switch with Custom Firmware (CFW)
- Functional Homebrew Launcher
- Super Smash Bros Ultimate installed
- `ultimate` folder created on your SD card

## 🚀 Installation

### Option 1: Direct download
1. Download the `ssbu-mod-manager.nro` file from [Releases](../../releases)
2. Copy the file to the `/switch/` folder on your SD card
3. Launch the application via the Homebrew Launcher

### Option 2: Build from source

#### Development prerequisites
- [devkitPro](https://devkitpro.org/wiki/Getting_Started) installed
- devkitA64 and libnx configured
- Git to clone the repository

#### Build steps
```bash
# Clone the repository
git clone https://github.com/your-username/HomebrewModManagerSSBU.git
cd HomebrewModManagerSSBU

# Build
make clean
make

# The ssbu-mod-manager.nro file will be generated in the root folder
```

## 📁 Folder structure

The application uses the following folder structure on your SD card:

```
sdmc:/
└── ultimate/
    ├── mods/           # Active mods (loaded by the game)
    └── mods_disabled/  # Disabled mods (not loaded)
```

## 🎮 Usage

1. **Launch**: Open the application from the Homebrew Launcher
2. **Navigation**: Use ↑/↓ to navigate through the mod list
3. **Toggle**: Press A to toggle a mod's state
4. **Bulk operations**: Use ZL/ZR to enable/disable all mods at once
5. **Refresh**: Press X to refresh the list (useful after adding new mods)
6. **Exit**: Press + to close the application

### Controls
| Button | Action |
|--------|--------|
| ↑/↓ (^/v) | Navigate through the list |
| A | Enable/Disable selected mod |
| X | Refresh mod list |
| Y | Change language |
| L/R | Change sorting order |
| **ZL** | **Enable all mods** |
| **ZR** | **Disable all mods** |
| + | Exit application |

### Smart Pagination
- The interface displays up to 20 mods at once for optimal readability
- When you have more mods, pagination indicators show:
  - Current page number (e.g., "Page 2/5")
  - "^ More mods above" when there are mods above the current view
  - "v More mods below" when there are mods below the current view
- Navigation automatically scrolls the view to keep the selected mod visible

## 📝 Adding mods

1. Place your mods in the `sdmc:/ultimate/mods/` folder (they will be active by default)
2. Or in `sdmc:/ultimate/mods_disabled/` (they will be disabled by default)
3. Launch the manager and press X to refresh the list
4. Use A to enable/disable individual mods, or ZL/ZR for bulk operations

## ⚠️ Important notes

- **Backup**: Always backup your save data before using mods
- **Compatibility**: Check mod compatibility with your SSBU version
- **Performance**: Too many active mods may affect performance
- **Updates**: Disable all mods before game updates
- **Large collections**: The manager can handle 100+ mods efficiently with pagination

## 🔧 Development

### Project structure
```
HomebrewModManagerSSBU/
├── include/
│   ├── localization.h      # Localization types and functions
│   └── mod_manager.h       # Core types and functions
├── source/
│   ├── localization.c      # Localization implementation + translations
│   ├── mod_manager.c       # Mod manager business logic
│   └── main.c              # Entry point and main loop
└── ...
```

### Technical features
- Secure memory management with defined limits (max 100 mods)
- Recursive mod folder scanning with file type detection
- Atomic file operations for safe mod state changes
- Console interface with ANSI color codes
- Smart pagination system for large mod collections
- Auto-scrolling navigation system
- Bulk operations with progress handling

## 🤝 Contributing

Contributions are welcome! To contribute:

1. Fork the project
2. Create a feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## 📄 License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## 🙏 Acknowledgments

- [devkitPro](https://devkitpro.org/) for Nintendo Switch development tools
- The Nintendo Switch homebrew community
- SSBU mod developers

## ⚡ Support

If you encounter issues:
1. Check that your CFW is up to date
2. Make sure the required folders exist
3. Verify that your SD card has enough free space
4. For large mod collections, ensure mods are properly named (no special characters)
5. Open an [issue](../../issues) with details about your problem

---

**Disclaimer**: This application is intended for educational and legal modding purposes. Respect Nintendo's terms of service and the laws of your country.
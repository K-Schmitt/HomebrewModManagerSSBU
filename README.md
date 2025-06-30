# HomebrewModManagerSSBU

A simple and efficient mod manager for Super Smash Bros Ultimate on Nintendo Switch.

## 📋 Description

HomebrewModManagerSSBU is a homebrew application that allows you to easily manage your SSBU mods directly from your Nintendo Switch. The application provides an intuitive console interface for enabling/disabling your mods with multilingual support and multiple sorting options.

## ✨ Features

- 🎮 Intuitive console interface with D-Pad navigation
- ✅ One-click mod activation/deactivation
- 📁 Support for both file and folder mods
- 🔄 Automatic mod list refresh
- 📊 Active/disabled mod counters
- 🎯 Smooth navigation with visual selection
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
1. Download the `manager-ssbu.nro` file from [Releases](../../releases)
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

# The manager-ssbu.nro file will be generated in the root folder
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
4. **Refresh**: Press X to refresh the list (useful after adding new mods)
5. **Exit**: Press + to close the application

### Controls
| Button | Action |
|--------|--------|
| ↑/↓ | Navigate through the list |
| A | Enable/Disable selected mod |
| X | Refresh mod list |
| Y | Change language |
| L/R | Change sorting order |
| + | Exit application |

## 📝 Adding mods

1. Place your mods in the `sdmc:/ultimate/mods/` folder (they will be active by default)
2. Or in `sdmc:/ultimate/mods_disabled/` (they will be disabled by default)
3. Launch the manager and press X to refresh the list
4. Use A to enable/disable as needed

## ⚠️ Important notes

- **Backup**: Always backup your save data before using mods
- **Compatibility**: Check mod compatibility with your SSBU version
- **Performance**: Too many active mods may affect performance
- **Updates**: Disable all mods before game updates

## 🔧 Development

### Project structure
```
HomebrewModManagerSSBU/
├── include/
│   ├── localization.h      # Types et fonctions de localisation
│   └── mod_manager.h       # Types et fonctions principales
├── source/
│   ├── localization.c      # Implémentation localisation + traductions
│   ├── mod_manager.c       # Logique métier du gestionnaire
│   └── main.c              # Point d'entrée et boucle principale
└── ...
```

### Technical features
- Secure memory management with defined limits
- Recursive mod folder scanning
- Atomic file operations
- Console interface with ANSI color codes

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
3. Open an [issue](../../issues) with details about your problem

---

**Disclaimer**: This application is intended for educational and legal modding purposes. Respect Nintendo's terms of service and the laws of your country.
# HomebrewModManagerSSBU

A simple and efficient mod manager for Super Smash Bros Ultimate on Nintendo Switch.

## 📋 Description

HomebrewModManagerSSBU is a homebrew application that allows you to easily manage your SSBU mods directly from your Nintendo Switch. The application provides a simple console interface to enable/disable your mods without having to manually manipulate files.

## ✨ Features

- 🎮 Intuitive console interface with D-Pad navigation
- ✅ One-click mod activation/deactivation
- 📁 Support for mods as files and folders
- 🔄 Automatic mod list refresh
- 📊 Active/disabled mod counters
- 🎯 Smooth navigation with visual selection

## 🎯 Screenshots

The interface displays:
- List of mods with their status (ON/OFF)
- Visual indication for folders
- Active and disabled mod counters
- Detailed controls

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
│   └── mod_manager.h    # Function and structure declarations
├── source/
│   ├── main.c           # Entry point and main loop
│   └── mod_manager.c    # Mod management logic
├── Makefile             # Build configuration
└── README.md            # This file
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
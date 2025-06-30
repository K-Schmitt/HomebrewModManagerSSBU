# Contributing Guide

Thank you for your interest in contributing to HomebrewModManagerSSBU! This guide will help you understand how to participate in the project development.

## 🚀 How to contribute

### Reporting bugs

If you find a bug:
1. First check that the bug hasn't already been reported in [Issues](../../issues)
2. Create a new issue with:
   - A descriptive title
   - A detailed description of the problem
   - Steps to reproduce the bug
   - Your environment (CFW version, SSBU version, etc.)

### Suggesting improvements

To propose a new feature:
1. Open an issue with the "enhancement" label
2. Clearly describe the desired feature
3. Explain why this feature would be useful

### Submitting code

1. **Fork** the repository
2. **Clone** your fork locally
3. **Create** a new branch for your feature:
   ```bash
   git checkout -b feature/your-feature-name
   ```
4. **Develop** your feature
5. **Test** your changes on real hardware if possible
6. **Commit** with clear messages
7. **Push** to your fork
8. **Open** a Pull Request

## 🔧 Development setup

### Prerequisites
- [devkitPro](https://devkitpro.org/wiki/Getting_Started) installed
- devkitA64 and libnx configured
- Git
- A code editor (VS Code recommended)

### Installation
```bash
git clone https://github.com/your-username/HomebrewModManagerSSBU.git
cd HomebrewModManagerSSBU
make clean
make
```

## 📝 Code standards

### Code style
- Use descriptive variable and function names
- Indent with 4 spaces (no tabs)
- Comment complex code
- Respect the existing structure

### Naming conventions
- Variables: `snake_case`
- Functions: `snake_case`
- Constants: `UPPER_CASE`
- Structures: `PascalCase`

### Well-formatted code example:
```c
typedef struct {
    char name[MAX_NAME_LENGTH];
    bool enabled;
} Mod;

void mod_manager_toggle_mod(ModManager* manager, int index) {
    if (index < 0 || index >= manager->count) {
        return; // Bounds checking
    }
    
    Mod* mod = &manager->mods[index];
    // Toggle logic...
}
```

## 🧪 Testing

Before submitting your code:
1. **Compile** without errors or warnings
2. **Test** on real hardware if possible
3. **Verify** the interface remains responsive
4. **Test** with different types of mods (files/folders)

## 📋 Pull Request checklist

- [ ] Code compiles without errors
- [ ] New features are documented
- [ ] Changes are tested
- [ ] Code style is respected
- [ ] Commit messages are clear
- [ ] PR has a detailed description

## 🎯 Priority improvement areas

- User interface (better navigation, colors)
- More robust error handling
- Support for more mod formats
- Performance optimizations
- Documentation and translations

## ❓ Questions

If you have questions:
- Open an issue with the "question" label
- Check existing documentation
- Look at closed issues for similar answers

## 📄 License

By contributing to this project, you agree that your contributions will be licensed under the MIT license, like the rest of the project.

---

Thank you for making HomebrewModManagerSSBU better for the entire community! 🎮
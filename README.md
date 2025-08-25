# NetEmul-NG

This is a fork of the original NetEmul network simulation software, focused on fixing implementation flaws.

## Compilation Instructions for Linux

### Prerequisites

NetEmul requires Qt4 development libraries. Install the required packages:

**Arch Linux / Manjaro:**
```bash
sudo pacman -S qt4
```

**Ubuntu / Debian:**
```bash
sudo apt-get install libqt4-dev qt4-qmake
```

**CentOS / RHEL / Fedora:**
```bash
sudo yum install qt-devel qt4-devel
# or for newer versions:
sudo dnf install qt-devel qt4-devel
```

### Building

1. Clone this repository:
```bash
git clone <repository-url>
cd netemul-ng
```

2. Generate Makefile using Qt4 qmake:
```bash
qmake-qt4
# or if qmake-qt4 is not available, try:
# qmake
```

3. Build the project:
```bash
make
```

4. The executable `netemul-ng` will be created in the project directory.

### Running

```bash
./netemul-ng
```

### Installation (Optional)

```bash
sudo make install
```

This will install NetEmul-NG to `/usr/local/bin/` by default.

### Troubleshooting

**Build Issues:**
- Ensure you're using Qt4 qmake, not Qt5/Qt6
- The ipedit designer plugin may fail to build (this is non-essential)
- If you get header errors, verify Qt4 development packages are installed

**Qt Version Check:**
```bash
qmake --version
# Should show Qt version 4.x.x
```

## Testing

NetEmul includes both unit tests and integration tests:

### Unit Tests
```bash
cd test
qmake
make
./pusk  # Runs all unit tests
```

### Integration Tests
JavaScript-based acceptance tests are available in the `scripts/` directory and can be run via the application's test menu.

## Development

See `CLAUDE.md` for development guidance and architecture information.

## License

NetEmul is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version.

See `GPL-2` file for the complete license text.

## Acknowledgments

**Original Authors:**
- **Semenov Pavel** - Original developer and architect
- **Omilaeva Anastasia** - Original developer

This is a fork/continuation of the original NetEmul project, created for educational and research purposes. All credit for the original design and implementation goes to Semenov Pavel and Omilaeva Anastasia.

**Original NetEmul Distribution:**
The original NetEmul source code and releases are available at: https://sourceforge.net/projects/netemul/

The original NetEmul was developed as a network simulation tool for educational institutions and network engineering students.

---

*This fork includes modernization efforts and build fixes for contemporary Linux systems while preserving the original functionality and design.*
# NetEmul-NG

This is a fork of the original NetEmul network simulation software, focused on fixing implementation flaws and updated to use Qt5.

## Compilation Instructions for Linux

### Prerequisites

NetEmul requires **Qt5** development libraries. **Important**: This project has been updated from Qt4 to Qt5 and is no longer compatible with Qt4.

### Platform Support

- **Modern Linux**: Qt5 packages widely available (Ubuntu 18.04+, Fedora 28+, etc.)
- **Windows**: Qt5 installer from Qt.io or compile from source
- **macOS**: Qt5 via Homebrew or official Qt installer

Install the required packages:

**Arch Linux / Manjaro:**

```bash
sudo pacman -S qt5-base qt5-script qt5-tools
```

**Ubuntu / Debian:**

```bash
sudo apt-get install qt5-qmake qtbase5-dev qtscript5-dev qt5-printsupport qttools5-dev
```

**CentOS / RHEL / Fedora:**

```bash
sudo dnf install qt5-qtbase-devel qt5-qtscript-devel qt5-qttools-devel
```

### Building

1. Clone this repository:

```bash
git clone <repository-url>
cd netemul-ng
```

2. Generate Makefile using Qt5 qmake:

```bash
qmake
# or on systems with multiple Qt versions:
# qmake-qt5
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

**Common Build Issues:**

- **Qt Version**: Ensure you're using Qt5 qmake
- **Header Errors**: Verify Qt5 development packages are installed
- **Missing Modules**: Ensure qt5-widgets, qt5-script, and qt5-printsupport are installed
- **Plugin Build**: The ipedit designer plugin may fail to build (this is non-essential)

**Qt Version Check:**

```bash
qmake --version
# Should show Qt version 5.x.x
```

## Testing

NetEmul includes both unit tests and integration tests:

### Unit Tests

```bash
cd test
qmake  # Use Qt5 qmake
make
./pusk  # Runs all unit tests
```

**Test Results**: 6 test suites, 31 total tests covering MAC addresses, IP addresses, frames, packets, chips, and routing models.

### Integration Tests

JavaScript-based acceptance tests are available in the `scripts/` directory and can be run via the application's test menu.

## Development

See `CLAUDE.md` for development guidance and architecture information.

## License

NetEmul is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version.

See `GPL-2` file for the complete license text.

## Acknowledgments

**Original Authors:**

- **Semenov Pavel** - Original project admin and developer
- **Omilaeva Anastasia** - Original project developer

This is a fork/continuation of the original NetEmul project, created for educational and research purposes. All credit for the original design and implementation goes to Semenov Pavel and Omilaeva Anastasia.

**Original NetEmul Distribution:**
The original NetEmul source code and releases are available at: https://sourceforge.net/projects/netemul/

The original NetEmul was developed as a network simulation tool for educational institutions and network engineering students.

---

_This fork includes build fixes, comprehensive testing, and Qt5 modernization while preserving the original functionality and design._

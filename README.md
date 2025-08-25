# NetEmul-NG

This is a fork of the original NetEmul network simulation software, focused on fixing implementation flaws.

## Compilation Instructions for Linux

### Prerequisites

NetEmul requires **Qt4** development libraries. **Important**: This project is not compatible with Qt5/Qt6.

### Platform Support
- **Legacy Linux**: Ubuntu 18.04 LTS and earlier, CentOS 7, Debian 9 and earlier
- **Modern Linux**: Qt4 packages removed from Ubuntu 20.04+, Fedora 30+ - requires manual compilation
- **Windows/macOS**: Requires Qt4 from archives or manual compilation

Install the required packages:

**Arch Linux / Manjaro:**
```bash
sudo pacman -S qt4
```

**Ubuntu / Debian (18.04 and earlier):**
```bash
sudo apt-get install libqt4-dev qt4-qmake qt4-dev-tools libqt4-opengl-dev
```

**Note**: Qt4 packages were removed from Ubuntu 20.04+. For modern systems, consider using a container with Ubuntu 18.04 or compiling Qt4 from source.

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

**Common Build Issues:**
- **Qt Version**: Ensure you're using Qt4 qmake, not Qt5/Qt6
- **Header Errors**: Verify Qt4 development packages are installed
- **Plugin Build**: The ipedit designer plugin may fail to build (this is non-essential)
- **Modern Systems**: Qt4 incompatible with recent compilers - use legacy system or container

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
qmake-qt4  # Use Qt4 qmake
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
- **Semenov Pavel** - Original developer and architect
- **Omilaeva Anastasia** - Original developer

This is a fork/continuation of the original NetEmul project, created for educational and research purposes. All credit for the original design and implementation goes to Semenov Pavel and Omilaeva Anastasia.

**Original NetEmul Distribution:**
The original NetEmul source code and releases are available at: https://sourceforge.net/projects/netemul/

The original NetEmul was developed as a network simulation tool for educational institutions and network engineering students.

---

*This fork includes build fixes and comprehensive testing while preserving Qt4 compatibility and the original functionality and design.*

## Legacy Software Notice

**Qt4 End-of-Life**: Qt4 reached end-of-life in 2015 and is not supported on modern systems. This software is maintained for:
- Educational purposes and network simulation learning
- Legacy system compatibility  
- Historical preservation of the original NetEmul design

**Modern Alternative**: Consider migrating to Qt5/Qt6-based network simulation tools for production use on contemporary systems.
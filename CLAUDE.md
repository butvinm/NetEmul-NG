# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

NetEmul-NG is a network simulation program built with **Qt5** and C++. It allows users to visually design and simulate computer networks with various devices (computers, routers, switches, hubs) and test network protocols and configurations.

**Important**: This project has been updated to use Qt5. It is no longer compatible with Qt4 due to modernized includes and API usage.

## Build System

This project uses **qmake** (.pro files) as its build system.

### Build Requirements
- **Qt5 development libraries** (qt5-base-dev, qt5-script, qt5-tools)
- **Qt5 Widgets module** (qt5-widgets)
- **Qt5 OpenGL support** (qt5-opengl-dev) 
- **Qt5 Print Support module** (qt5-printsupport)
- **Qt5 Script support** (for JavaScript test integration)
- **C++ compiler** (g++, build-essential)

### Build Commands
- `qmake` - Generate Makefiles from .pro files  
- `make -j8` - Build the project with parallel compilation (8 threads)
- `make clean` - Clean intermediate build files (object files, MOC files)
- `make distclean-all` - Clean all build artifacts including executables

**Note**: On systems with multiple Qt versions, use `qmake` (Qt5 default) or `qmake-qt5` explicitly.

### Platform Compatibility
- **Modern Linux distributions**: Qt5 packages are widely available (Ubuntu 18.04+, Fedora 28+, etc.)
- **Windows**: Qt5 installer from Qt.io or compile from source  
- **macOS**: Qt5 via Homebrew or official Qt installer

**Important**: This project now uses Qt5 and is compatible with modern development environments.

### Build Structure
- Main project file: `netemul.pro` (builds `netemul-ng` executable)
- Build artifacts go to: `build/` directory
- Modular .pri includes organize source code by component

## Testing

The project implements a **dual testing approach**:

### Unit Tests
Located in `test/` directory with individual test programs using **Qt Test framework**:
- **Build tests**: `cd test && qmake && make`
- **Run all tests**: `cd test && ./pusk` (bash script runs all tests with `-silent` flag)
- **Individual tests**: `cd <test_dir> && ./<test_name>` for detailed output
- **Test components**: 
  - `mac/` - MAC address functionality
  - `ipaddress/` - IP address handling
  - `frame/` - Network frame operations  
  - `boxchip/` - Device port/chip logic
  - `ippacket/` - IP packet processing
  - `routemodel/` - Routing table model
  - `ripprogramm/` - RIP routing protocol

### Integration/Acceptance Tests  
JavaScript-based tests in `scripts/` directory using **Qt Script engine**:
- **Files**: `arp.js`, `dhcp.js`, `hub.js`, `checknet.js`, `big.js`
- **Execution**: Via application's test menu (testdialog.cpp)
- **Capabilities**:
  - Programmatic network topology creation
  - Device configuration (IP addresses, routing)
  - Packet transmission simulation  
  - Result validation through packet counters
  - Scene manipulation and saving

### Testing Infrastructure
- Special `__TESTING__` define for test builds
- Qt Script integration for device interaction
- Automated test execution via shell scripts
- Silent mode support for batch testing

## Architecture

### Core Components
- **Main Application**: `mainwindow.h/cpp`, `mycanvas.h/cpp` - GUI and main scene
- **Devices** (`src/devices/`): Network devices (computer, router, switch, hub, sharebus)
- **Graphics** (`src/graphics/`): Visual representation and scene items  
- **Packets** (`src/packets/`): Network protocols (IP, TCP, UDP, ARP, DHCP)
- **Programs** (`src/programms/`): Device software (DHCP client/server, RIP)
- **Dialogs** (`src/dialogs/`): Property windows and configuration dialogs

### Device Hierarchy
- `smartdevice` - Base for intelligent network devices
- `computer` - End-user devices with network stacks
- `routerdevice` - Layer 3 routing devices
- `switchdevice` - Layer 2 switching devices  
- `hubdevice` - Physical layer repeaters

### Script Integration
Uses Qt Script engine for automation and testing. JavaScript files can:
- Create network topologies programmatically
- Configure device properties (IP addresses, routing tables)
- Send test packets and verify network behavior

## Release Management

### Binary Naming Convention
When creating releases, always name binaries with architecture specification:

**Format**: `netemul-ng-{platform}-{architecture}[.extension]`

**Examples**:
- `netemul-ng-linux-x86_64` - Linux 64-bit
- `netemul-ng-linux-aarch64` - Linux ARM 64-bit  
- `netemul-ng-windows-x86_64.exe` - Windows 64-bit
- `netemul-ng-macos-x86_64` - macOS Intel
- `netemul-ng-macos-arm64` - macOS Apple Silicon

This ensures users can easily identify the correct binary for their system.

### Version Management
**Application Version Policy**: The application version (set via `QCoreApplication::setApplicationVersion()` in `src/mainwindow.cpp`) should ONLY be modified when incompatible changes to the binary format are introduced. This includes:
- Changes to scene file format that break compatibility with older versions
- Modifications to save/load mechanisms that render old files unreadable
- Protocol changes that affect network simulation data persistence

Minor features, bug fixes, or UI changes should NOT trigger application version increments. The application version is specifically used for file format compatibility checking.

### Release Process
**Publishing Releases**: Follow these steps to publish a new release:

1. **Prerequisites**: Ensure version has been bumped in `netemul.pro` via PR (e.g., 1.2 → 1.2.1 for patch)
2. **Build & Test**: Run `qmake && make -j8` to build and `cd test && ./pusk` to run tests
3. **GitHub Release**: Use `gh release create` with binary asset (creates tag automatically):
   ```bash
   gh release create vX.Y.Z --title "NetEmul-NG vX.Y.Z" --notes "Release notes" netemul-ng-linux-x86_64
   ```

**Release Notes Guidelines**: Focus only on new features and significant changes. Omit internal refactoring, documentation updates, or version management changes unless they directly impact users.

## Development Notes

- Russian comments and documentation throughout codebase
- Uses Qt's signal/slot mechanism extensively  
- Graphics based on QGraphicsScene/QGraphicsView framework
- Modular architecture with .pri files for each component
- Cross-platform support (Linux/Windows/macOS) via Qt5
- **Qt5 Compatibility**: Uses Qt5 includes and APIs with widgets module support
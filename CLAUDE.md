# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

NetEmul-NG is a network simulation program built with **Qt4** and C++. It allows users to visually design and simulate computer networks with various devices (computers, routers, switches, hubs) and test network protocols and configurations.

**Important**: This project requires Qt4 and is not compatible with Qt5/Qt6 due to API changes in GUI components and includes.

## Build System

This project uses **qmake** (.pro files) as its build system.

### Build Requirements
- **Qt4 development libraries** (libqt4-dev, qt4-qmake, qt4-dev-tools)
- **Qt4 OpenGL support** (libqt4-opengl-dev) 
- **Qt4 Script support** (for JavaScript test integration)
- **C++ compiler** (g++, build-essential)

### Build Commands
- `qmake` or `qmake-qt4` - Generate Makefiles from .pro files  
- `make` - Build the project
- `make clean` - Clean intermediate build files (object files, MOC files)
- `make distclean-all` - Clean all build artifacts including executables

**Note**: On systems with multiple Qt versions, use `qmake-qt4` explicitly.

### Platform Compatibility
- **Modern Linux distributions**: Qt4 packages may not be available (removed from Ubuntu 20.04+, Fedora 30+)
- **Legacy Linux systems**: Ubuntu 18.04 LTS and earlier, CentOS 7, Debian 9 and earlier
- **Windows**: Qt4 installer from Qt archives or compile from source  
- **macOS**: Homebrew Qt4 (deprecated) or compile from source

**Important**: Qt4 reached end-of-life in 2015. For modern systems, consider porting to Qt5/Qt6.

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

## Development Notes

- Russian comments and documentation throughout codebase
- Uses Qt's signal/slot mechanism extensively  
- Graphics based on QGraphicsScene/QGraphicsView framework
- Modular architecture with .pri files for each component
- Cross-platform support (Linux/Windows/macOS) via Qt4
- **Qt4 Compatibility**: Uses Qt4-style includes and APIs that are not compatible with Qt5/Qt6
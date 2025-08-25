# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

NetEmul-NG is a network simulation program built with Qt4/Qt5 and C++. It allows users to visually design and simulate computer networks with various devices (computers, routers, switches, hubs) and test network protocols and configurations.

## Build System

This project uses **qmake** (.pro files) as its build system.

### Build Commands
- `qmake` - Generate Makefiles from .pro files
- `make` - Build the project
- `make clean` - Clean build artifacts

### Build Structure
- Main project file: `netemul.pro` (builds `netemul-ng` executable)
- Build artifacts go to: `build/` directory
- Modular .pri includes organize source code by component

## Testing

### Unit Tests
Located in `test/` directory with individual test programs:
- Run all tests: `cd test && ./pusk` (script that runs all test programs)
- Build tests: `cd test && qmake && make`
- Individual test directories: `boxchip/`, `frame/`, `ipaddress/`, etc.

### Integration Tests  
JavaScript-based acceptance tests in `scripts/` directory:
- `arp.js`, `dhcp.js`, `hub.js`, `checknet.js`, `big.js`
- Run via application's test menu

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

## Development Notes

- Russian comments and documentation throughout codebase
- Uses Qt's signal/slot mechanism extensively  
- Graphics based on QGraphicsScene/QGraphicsView framework
- Modular architecture with .pri files for each component
- Cross-platform support (Linux/Windows/macOS) via Qt
# RC_Control

## Introduction

This project aims to control an RC airplane (based on an ESP32) from a laptop using a HOTAS (flight joystick).  
The goal is to develop the ground-to-air communication and the aircraft's onboard intelligence from scratch, using minimal off-the-shelf hardware.

## Requirements

- `cmake`
- A compiler (e.g., gcc or clang)
- Arduino IDE

## Project Structure

- `src`: All C source files  
- `includes`: All header files  
- `libs`: External libraries used by the project  
- `Arduino`: All Arduino IDE-compatible programs, including `ESP32_Code`, which runs on the ESP32

## Installation

1. Clone the repository  
2. Build the `SimpleBLE` library  
3. Build the main program using `cmake`  
4. Upload the ESP32 code using the Arduino IDE

## Roadmap

Currently, I’m focused on controlling engine speed using HOTAS inputs:

- HOTAS inputs are successfully read  
- BLE connection with the ESP32 is established

### TODO:

- Transmit input data over BLE  
- Control the engine via the ESP32 and an ESC  

### Upcoming Features:

- Control of servomotors for various flight axes  
- Integration of onboard intelligence such as autopilot or INS-like behavior

## Plugins / Libraries

For the BLE server, I’m using [SimpleBLE](https://github.com/simpleble/simpleble/discussions?discussions_q=is%3Aopen+)

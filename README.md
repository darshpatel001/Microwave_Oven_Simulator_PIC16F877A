# Microwave Oven Simulator Using PIC16F877A

## Overview

The Microwave Oven Simulator is an embedded systems project developed using the PIC16F877A microcontroller. The project simulates the operation of a modern microwave oven with multiple cooking modes, timer management, temperature control, and user interaction through a keypad and CLCD display.

The system provides a realistic microwave user interface and demonstrates real-time embedded firmware design using state machines, timers, and peripheral control.

---

## Features

* Micro Mode
* Grill Mode
* Convection Mode
* Cooking Timer
* Start / Pause Functionality
* Temperature Selection
* Fan Control
* Buzzer Notification
* CLCD User Interface
* Matrix Keypad Input
* Menu Driven Navigation
* Real-Time Countdown

---

## Development Environment

### Software

| Tool            | Purpose                   |
| --------------- | ------------------------- |
| MPLAB X IDE     | Project Development       |
| XC8 Compiler    | Embedded C Compilation    |
| PICSimLab       | Hardware Simulation       |
| PICGenios Board | Virtual Development Board |

### Target Platform

```text
PIC16F877A Microcontroller
PICSimLab Simulator
PICGenios Development Board
```

---

## Hardware Platform

This project was developed and tested using the **PICGenios Development Board** available in **PICSimLab**.

Peripherals used:

* PIC16F877A MCU
* Character LCD (20x4 CLCD)
* Matrix Keypad
* Buzzer
* Cooling Fan
* Timer2
* Virtual Input Controls

---

## Technologies Used

* Embedded C
* MPLAB X IDE
* XC8 Compiler
* State Machine Design
* Timer Interrupts
* Matrix Keypad Interfacing
* CLCD Interfacing
* Real-Time Embedded Systems

---

## Project Structure

```text
.
├── main.c
├── main.h
├── microwave_oven.c
├── microwave_oven.h
├── clcd.c
├── clcd.h
├── matrix_keypad.c
├── matrix_keypad.h
├── timers.c
├── timers.h
├── uart.c
├── uart.h
├── global.h
├── Makefile
└── README.md
```

---

## System Architecture

```text
                  +----------------+
                  | Matrix Keypad  |
                  +----------------+
                           |
                           v

                  +----------------+
                  | PIC16F877A MCU |
                  +----------------+
                     |         |
                     |         |
                     v         v

              +---------+   +---------+
              |  CLCD   |   | Buzzer  |
              +---------+   +---------+
                     |
                     |
                     v

                +---------+
                |  Fan    |
                +---------+

                     ^
                     |
              +-------------+
              | Timer Engine|
              +-------------+
```

---
# Microwave Oven Simulator Using PIC16F877A

## Project Demo

[🎥 Watch Demo Video](./Screencast from 2026-06-23 10-22-00.mp4)
---

## Working Principle

### Main Menu

The user selects one of the available cooking modes:

```text
1. Micro Mode
2. Grill Mode
3. Convection Mode
4. Start Cooking
```

---

### Micro Mode

Provides microwave cooking operation.

```text
Power = 900W
MICRO MODE
```

---

### Grill Mode

Provides grilling functionality.

```text
Power = 900W
GRILL MODE
```

---

### Convection Mode

Allows temperature-controlled cooking.

User can select:

```text
180°C
200°C
220°C
250°C
```

before starting the cooking cycle.

---

### Cooking Operation

When cooking starts:

* Countdown timer begins
* Fan activates
* Remaining time displayed
* Pause and Resume supported

Example:

```text
MODE : MICRO

TIME : 00:58
TEMP : 180C
```

---

### Completion

When timer reaches zero:

* Fan stops
* Buzzer activates
* Completion message displayed

```text
COOKING COMPLETE
```

---

## Functional Modules

### Menu Module

#### menu_screen()

* Displays available cooking modes.
* Handles user selection.

---

### Micro Mode Module

#### micro_menu_mode()

* Handles microwave cooking mode.

---

### Grill Mode Module

#### grill_mode()

* Controls grill operation.

---

### Convection Module

#### convection_mode()

* Handles temperature selection.
* Controls convection cooking.

---

### Countdown Module

#### update_countdown()

* Updates cooking timer.
* Decrements remaining seconds.

---

### Timer Module

#### init_timer2()

* Configures Timer2.

#### timer_isr()

* Generates periodic interrupts.

---

### Keypad Module

#### read_matrix_keypad()

* Reads keypad inputs.
* Supports menu navigation.

---

### Display Module

#### clcd_print()

* Displays text on CLCD.

#### clear_screen()

* Clears display.

---

## Program Flow

```text
1. System Initialization
2. Display Welcome Screen
3. Show Main Menu
4. Select Cooking Mode
5. Configure Parameters
6. Start Cooking
7. Countdown Execution
8. Cooking Complete
9. Sound Buzzer
10. Return to Menu
```

---

## Build Instructions

### Open Project

```text
MPLAB X IDE
```

### Compiler

```text
XC8 Compiler
```

### Build

```text
Clean and Build Project
```

### Program Device

```text
PIC16F877A
```

---

## Simulation Setup

### Simulator

```text
PICSimLab
```

### Development Board

```text
PICGenios
```

### Microcontroller

```text
PIC16F877A
```

---

## Sample Execution

### Welcome Screen

```text
MICROWAVE OVEN
SIMULATOR
```

### Mode Selection

```text
1.MICRO
2.GRILL
3.CONVECTION
```

### Cooking Screen

```text
MODE : MICRO
TIME : 00:58
TEMP : 180C
```

### Completion Screen

```text
COOKING COMPLETE
```

---

## Screenshots

Add screenshots of:

* PICSimLab PICGenios Board
* Welcome Screen
* Main Menu
* Micro Mode
* Grill Mode
* Convection Mode
* Cooking Screen
* Completion Screen

---

## Demo Video

```markdown
## Demo Video

[Watch Demo](Videos/microwave_oven_demo.mp4)
```

or upload to YouTube and add the link.

---

## Concepts Demonstrated

* Embedded C
* State Machines
* Timer Interrupts
* Keypad Scanning
* CLCD Interfacing
* Real-Time Systems
* Event Driven Programming
* Firmware Architecture

---

## Applications

* Smart Kitchen Appliances
* Home Automation Systems
* Embedded User Interfaces
* Consumer Electronics
* Appliance Control Systems

---

## Future Improvements

* RTC Integration
* EEPROM Recipe Storage
* Touch Screen Interface
* Voice Commands
* Wi-Fi Connectivity
* Mobile App Control
* IoT Monitoring

---

## Learning Outcomes

Through this project, I gained practical experience in:

* PIC16F877A Programming
* Embedded Firmware Design
* State Machine Implementation
* Timer Management
* User Interface Design
* Real-Time Embedded Systems
* PICSimLab Development

---

## Author

**Darsh Patel**

Electronics & Communication Engineer

Firmware Engineer | Embedded Systems | IoT Developer

GitHub: https://github.com/darshpatel001

---

## License

This project is licensed under the MIT License.

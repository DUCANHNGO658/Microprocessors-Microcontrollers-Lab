# Lab 3: Buttons and Switches - Traffic Light Controller

A 4-mode traffic light intersection controller implemented on **STM32F103C6** and simulated in **Proteus 8 Professional**.

---

## 📁 Project Structure

```text
.
├── Core/
│   ├── Inc/
│   │   ├── input_processing.h    # FSM state declarations & mode definitions
│   │   ├── input_reading.h       # Button debounce & 1s hold detection
│   │   ├── led_display.h         # 7-segment display & 2Hz blinking drivers
│   │   ├── main.h                # Hardware pin definitions
│   │   └── timer.h               # Software timer service (10ms tick)
│   └── Src/
│       ├── input_processing.c    # Mode switching & traffic light cycle logic
│       ├── input_reading.c       # Debounce filtering algorithms
│       ├── led_display.c         # 7-segment multiplexing & LED drivers
│       ├── main.c                # System initialization & main loop
│       └── timer.c               # Hardware timer callback & counters
├── Drivers/                      # STM32 HAL and CMSIS libraries
├── 3.1.hex                       # Pre-compiled binary for Proteus
├── 3.1.ioc                       # STM32CubeMX configuration file
├── 3.1.pdsprj                    # Proteus schematic & simulation file
├── STM32F103C6UX_FLASH.ld        # Linker script
└── README.md

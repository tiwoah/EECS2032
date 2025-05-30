#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL43Z4.h"
#include "fsl_debug_console.h"

/*
 * @brief Main entry point of the program.
 * This program toggles the green LED every 0.25 seconds using the SysTick timer, without interrupts.
 */
int main(void) {

    // Initialize default board hardware (clocks, pins, peripherals, etc.)
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();

#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    // Initialize the debug console so we can print to the serial monitor
    BOARD_InitDebugConsole();
#endif

    PRINTF("Hello World\r\n"); // Print message to serial monitor

    // Enable clock for PORTD (Bit 12 = PORTD)
    SIM->SCGC5 |= (1 << 12); 

    // Configure Port D pin 5 (PTD5) as GPIO (LED green pin)
    // 0x100 sets MUX to 001 (GPIO function)
    PORTD->PCR[5] = 0x100;  

    // Set PTD5 as output (LED needs output to control it)
    PTD->PDDR |= (1 << 5); 

    // Turn ON the green LED initially (LEDs on KL43Z are active-low)
    PTD->PCOR |= (1 << 5); 

    // Setup SysTick Timer:
    // - Bit 0: ENABLE = 1 (turn on timer)
    // - Bit 2: CLKSOURCE = 1 (use system clock, 48 MHz)
    // - Bit 1 (TICKINT) = 0 (do NOT use interrupt — we're polling)
    SysTick->CTRL |= (1 << 0) | (1 << 2); 

    // Set reload value for 0.25s delay:
    // (48 million ticks/sec) * 0.25 sec = 12,000,000 ticks - 1 = 0xB71BFF
    SysTick->LOAD = 0xB71BFF; 

    // Infinite loop
    while (1) {
        // Wait for the COUNTFLAG (bit 16) to become 1
        // This means SysTick timer has counted down to 0
        while ((SysTick->CTRL & 0x10000) == 0) {
            // Do nothing, just wait (polling)
        }

        // Toggle the green LED (PTD5)
        PTD->PTOR |= (1 << 5); 
    }

    // This NOP (no operation) instruction allows stepping in debugger
    __asm volatile ("nop");

    return 0;
}
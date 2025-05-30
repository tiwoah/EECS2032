#include <stdio.h>                // Standard I/O header (not used in this code, but often included by default)
#include "board.h"                // Board-specific hardware initialization
#include "peripherals.h"          // Peripheral device initialization
#include "pin_mux.h"              // Pin multiplexing configuration
#include "clock_config.h"         // Clock system setup
#include "MKL43Z4.h"              // MCU register definitions for MKL43Z4 microcontroller
#include "fsl_debug_console.h"    // Debug console initialization

// You could include more headers if your project needs them.

/*
 * Simple delay function: makes the CPU "do nothing" for a while,
 * acting as a pause or wait.
 */
void delay () {
    // 'for' loop runs 800,000 times. Each time, a "nop" (no operation) is executed.
    // This keeps the processor busy and creates a time delay.
    for (int i = 0; i < 800000; i++) {
        __asm("nop"); // 'nop' = "no operation" - just wastes time
    }
}

int main(void) {

    // -----------------------------
    // 1. Initialize the board hardware
    // These functions set up pins, clocks, and peripherals as needed.
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();

    // If the debug console peripheral wasn't already initialized, do it now.
    #ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
        BOARD_InitDebugConsole();
    #endif

    // -----------------------------
    // 2. Enable clock to GPIO port modules.
    // SIM->SCGC5 is the register that controls clock gating for peripherals.
    // We set the bits for ports A, C, D, and E so we can use them.
    SIM->SCGC5 |= (1 << 9)  // Enable clock for PORTA (bit 9)
                | (1 << 11) // Enable clock for PORTC (bit 11)
                | (1 << 12) // Enable clock for PORTD (bit 12)
                | (1 << 13);// Enable clock for PORTE (bit 13)

    // -----------------------------
    // 3. Configure pin control registers (PCR)
    // Set up which pins will be used as GPIO.
    // 0x103 = GPIO mode, enable pull-up resistor, and enable input.
    PORTA->PCR[4] = 0x103;  // PTA4 as GPIO input with pull-up
    PORTC->PCR[3] = 0x103;  // PTC3 as GPIO input with pull-up

    // 0x100 = GPIO mode, no pull-up/down
    PORTD->PCR[5] = 0x100;  // PTD5 as GPIO output
    PORTE->PCR[31] = 0x100; // PTE31 as GPIO output

    // -----------------------------
    // 4. Configure direction for GPIO pins (input or output)
    // PDDR = Port Data Direction Register (0 = input, 1 = output)
    PTA->PDDR &= ~(1 << 4);  // PTA4 as input (clear bit 4)
    PTC->PDDR &= ~(1 << 3);  // PTC3 as input (clear bit 3)

    PTD->PDDR |= (1 << 5);   // PTD5 as output (set bit 5)
    PTE->PDDR |= (1 << 31);  // PTE31 as output (set bit 31)

    // -----------------------------
    // 5. Main loop: runs forever, checking button inputs and controlling outputs
    while (1) {
        int buttonA, buttonC; // These will read the state of PTA4 and PTC3

        // Read input pins: if pressed, bit will be 0 (because of pull-up resistors)
        buttonA = PTA->PDIR & (1 << 4); // Read PTA4
        buttonC = PTC->PDIR & (1 << 3); // Read PTC3

        /*
         * Four cases, depending on if buttons are pressed (logic LOW) or not (logic HIGH):
         * - If both buttons are pressed, both bits will be 0.
         * - If neither is pressed, both bits will be nonzero.
         * - If only one is pressed, you'll get one bit zero, one bit nonzero.
         *
         * But since the pull-up means a pressed button is '0', you might want to invert logic!
         * For a complete beginner, it can help to comment this inversion logic.
         */

        // BUTTON PRESSED means bit is 0
        int pressedA = !buttonA; // true if PTA4 is LOW
        int pressedC = !buttonC; // true if PTC3 is LOW

        if (pressedA && pressedC) {
            // Both buttons pressed
            PTD->PDOR = (1 << 5);    // Turn ON output on PTD5
            PTE->PDOR = 0;           // Turn OFF output on PTE31
        } else if (!pressedA && pressedC) {
            // Only C pressed
            PTD->PDOR = 0;           // Turn OFF output on PTD5
            PTE->PDOR = 0;           // Turn OFF output on PTE31
            delay();
            PTE->PDOR = (1 << 31);   // Turn ON output on PTE31
            delay();
        } else if (pressedA && !pressedC) {
            // Only A pressed
            PTD->PDOR = (1 << 5);    // Turn ON output on PTD5
            PTE->PDOR = 0;           // Turn OFF output on PTE31
            delay();
            PTE->PDOR = (1 << 31);   // Turn ON output on PTE31
            delay();
        } else {
            // Neither button pressed
            PTE->PDOR = (1 << 31);   // Turn ON output on PTE31
            PTD->PDOR = (1 << 5);    // Turn ON output on PTD5
            PTD->PDOR = 0;           // Turn OFF output on PTD5
            delay();
            PTD->PDOR = (1 << 5);    // Turn ON output on PTD5
            PTE->PDOR = 0;           // Turn OFF output on PTE31
            delay();
        }
    }
    // main never reaches here because of the infinite loop
    // return 0;
}

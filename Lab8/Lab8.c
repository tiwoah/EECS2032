#include <stdio.h>                        // Standard I/O library (not really used here, but included by default)
#include "board.h"                        // Board-specific setup (pin mappings, etc.)
#include "peripherals.h"                  // Peripheral initialization
#include "pin_mux.h"                      // Pin multiplexer configuration
#include "clock_config.h"                 // System clock configuration
#include "MKL43Z4.h"                      // Device-specific definitions for the MKL43Z4 microcontroller
#include "fsl_debug_console.h"           // For debugging output (e.g. printf)


// Creates a short delay by executing "do nothing" instructions in a loop
void delay (){
    for (int i=0; i<800000; i++) {
        __asm ("nop");  // "No Operation" - takes up time without doing anything
    }
}

int Sw1;  // Global variable to store the state of a pushbutton (on PTA4)


// Main function: entry point of the program
int main(void) {

    // === STEP 1: INITIALIZE THE BOARD ===
    BOARD_InitBootPins();               // Initialize pins (as configured in your project)
    BOARD_InitBootClocks();            // Set up system clocks
    BOARD_InitBootPeripherals();       // Initialize peripherals (e.g., ADC, UART, etc.)

#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    BOARD_InitDebugConsole();          // Set up the debug console (enables printf)
#endif

    // === STEP 2: DISABLE INTERRUPTS TEMPORARILY ===
    __disable_irq();                   // Globally disable all interrupts (so setup can happen safely)
    NVIC_DisableIRQ(PORTC_PORTD_IRQn); // Disable the interrupt specifically for Port C/D

    // === STEP 3: ENABLE CLOCKS TO GPIO PORTS A, C, AND D ===
    SIM->SCGC5 |= (1<<9) | (1<<12);    // Enable clock to Port A and Port D
    SIM->SCGC5 |= 0x800;               // Enable clock to Port C (bit 11 = 0x800)

    // === STEP 4: CONFIGURE PINS ===
    PORTA->PCR[4] = 0x103;             // PTA4: Enable pull-up resistor, select GPIO mode
    PORTC->PCR[3] = 0x103;             // PTC3: Enable pull-up resistor, select GPIO mode
    PORTD->PCR[5] = 0x100;             // PTD5: GPIO mode (for LED output)

    // === STEP 5: SET PIN DIRECTIONS ===
    PTA->PDDR &= (1 << 4);             // PTA4 as input (button 1)
    PTC->PDDR &= ~(0x08);              // PTC3 as input (button 2)

    PTD->PDDR |= (1<<5);               // PTD5 as output (e.g., for LED)

    // === STEP 6: CONFIGURE INTERRUPT FOR PTC3 ===
    PORTC->PCR[3] &= ~0xF0000;         // Clear bits for interrupt configuration (IRQC)
    PORTC->PCR[3] |= 0xA0000;          // Set IRQC = 0b1010 = interrupt on falling edge

    // === STEP 7: ENABLE THE INTERRUPT ===
    NVIC_SetPriority(PORTC_PORTD_IRQn, 192);   // Set interrupt priority (lower = higher priority)
    NVIC_ClearPendingIRQ(PORTC_PORTD_IRQn);    // Clear any pending interrupt flags
    NVIC_EnableIRQ(PORTC_PORTD_IRQn);          // Enable the PORTC/PORTD interrupt
    __enable_irq();                            // Re-enable global interrupts

    // === STEP 8: MAIN LOOP ===
    volatile static int i = 0;                 // Volatile to prevent compiler optimization (used below)

    while(1) {                                 // Infinite loop
        i++;                                   // Just incrementing a counter (not really used)

        // Read the state of the button on PTA4
        // If button is not pressed, Sw1 = 1 (due to pull-up resistor)
        // If button is pressed, Sw1 = 0 (pin is pulled low)
        Sw1 = (PTA->PDIR & (1 << 4)) >> 4;     

        asm volatile ("nop");                 // A 'do nothing' instruction to make single-step debugging easier
    }

    return 0; // (Unreachable, but included for completeness)
}


// === INTERRUPT SERVICE ROUTINE FOR PORT C AND D ===
void PORTC_PORTD_IRQHandler(void) {

    if (PORTC->ISFR & (1 << 3)) {         // Check if PTC3 caused the interrupt
        PORTC->PCR[3] |= (1 << 24);       // Clear the interrupt flag on PCR[3] (write 1 to ISF bit)

        if (!Sw1) {                       // If Sw1 == 0 (i.e., button on PTA4 is pressed)
            PTD->PTOR = (1 << 5);         // Toggle PTD5 (i.e., toggle LED)
        }
    }

    PORTC->ISFR |= 0xFFFFFFFF;            // Clear all interrupt flags for Port C (write 1s to all bits)
}
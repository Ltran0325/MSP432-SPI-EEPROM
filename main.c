/*******************************************************************************
*                       MSP432 SPI EEPROM                                      *
*                                                                              *
* Author:  Long Tran                                                           *
* Device:  MSP432P401R LaunchPad                                               *
* Program: Write and Read a byte to SPI EEPROM (25LC040)                       *
*                                                                              *
*******************************************************************************/

#include "msp.h"
#include <stdint.h>

// EEPROM Instructions
#define READ    0x03
#define WRITE   0x02
#define WRDI    0x04
#define WREN    0x06
#define RDSR    0x05
#define WRSR    0x01

uint8_t SPI_transfer(uint8_t data);
void wait_busy(void);
void read_EEPROM(uint8_t address);
void write_EEPROM(uint8_t address, uint8_t byte);

uint8_t RDxBuffer = 0;

int main(void)
{
    volatile uint32_t i;

    WDT_A->CTL = WDT_A_CTL_PW |             // Stop watchdog timer
                 WDT_A_CTL_HOLD;
    
    //-- Setup EEPROM Pins
    P1->SEL0 |= BIT4 | BIT5 | BIT6 | BIT7;  // set 4-SPI pin as second function

    P8->DIR |= BIT7;    // CS Pin GPIO
    P8->OUT |= BIT7;

    //-- Setup eUSCI_B SPI registers
    EUSCI_B0->CTLW0 |= EUSCI_B_CTLW0_SWRST; // Put state machine in reset

    EUSCI_B0->CTLW0 = EUSCI_B_CTLW0_SWRST | // Remain in reset state
                        EUSCI_B_CTLW0_MST | // SPI master
                       EUSCI_B_CTLW0_SYNC | // Synchronous mode
                        EUSCI_B_CTLW0_MSB | // MSB first
                     EUSCI_B_CTLW0_MODE_1 | // 4-pin mode
                       EUSCI_B_CTLW0_STEM | // STE mode select
                  EUSCI_B_CTLW0_SSEL__ACLK; // ACLK

    EUSCI_B0->BRW = 1;  //fBitClock = fBRCLK/(UCBRx+1).
    
    EUSCI_B0->CTLW0 &= ~EUSCI_B_CTLW0_SWRST; // Enable eUSCI_B SPI
    
    while(1)
    {
        read_EEPROM(0);         // read EEPROM at address
        write_EEPROM(0, 0xC9);  // write a byte to address

        for(i = 0; i < 1000; i++){} 
    }
}

uint8_t SPI_transfer(uint8_t data){

    // begin transmission
    EUSCI_B0->TXBUF = data;

    // wait while eUSCI_B is busy
    while(EUSCI_B0->STATW & EUSCI_B_STATW_SPI_BUSY){}

    // read recieved value
    return EUSCI_B0->RXBUF;
}

void wait_busy(void){

    char status = 0;

    do{
        P8->OUT &= ~BIT7;    // CS select

        SPI_transfer(RDSR);
        status = SPI_transfer(0) & BIT0;

        P8->OUT |= BIT7;     // CS release
    } while(status == 1);    // wait while write in progress

}

void read_EEPROM(uint8_t address){

    wait_busy();
    P8->OUT &= ~BIT7;   // CS select
    SPI_transfer(READ);
    SPI_transfer(address);
    RDxBuffer = SPI_transfer(0);
    P8->OUT |= BIT7;    // CS release
}

void write_EEPROM(uint8_t address, uint8_t byte){

    wait_busy();

    // Protect Release
    P8->OUT &= ~BIT7;   // CS select
    SPI_transfer(WRSR);
    SPI_transfer(0x02);
    P8->OUT |= BIT7;    // CS release

    // Write Enable
    P8->OUT &= ~BIT7;   // CS select
    SPI_transfer(WREN);
    P8->OUT |= BIT7;    // CS release

    // Write
    P8->OUT &= ~BIT7;   // CS select
    SPI_transfer(WRITE);
    SPI_transfer(address);
    SPI_transfer(byte);
    P8->OUT |= BIT7;    // CS release

}

# MSP432-SPI-EEPROM

### SPI EEPROM Operation:
Read and write a byte to SPI EEPROM (25LC040)

https://github.com/Ltran0325/MSP432-SPI-EEPROM/blob/main/main.c

25LC040 Datasheet:

http://ww1.microchip.com/downloads/en/devicedoc/21204e.pdf

### READ:

![image](https://user-images.githubusercontent.com/62213019/113335699-28cd4880-92da-11eb-974d-c92428ee64c9.png)

Source: 25LC040 datasheet

#### To read a byte from 25LC040:
1. Pull CS low
2. Send READ instruction byte
3. Send lower address byte
4. Send dummy byte to read data output (recieve and trasmit concurrently)
5. Pull CS high

### WRITE:

![image](https://user-images.githubusercontent.com/62213019/113335761-3e427280-92da-11eb-9d71-49c8a015225f.png)

Source: 25LC040 datasheet

#### To write a byte to 25LC040:
1. Pull CS low
2. Send WRITE instruction byte
3. Send lower address byte
4. Send byte to be written
5. Pull CS high

### Circuit Setup:
![image](https://user-images.githubusercontent.com/62213019/113356078-97200400-92f6-11eb-88fc-5f6e8cfd3292.png)

Source: 25LC040 datasheet

![image](https://user-images.githubusercontent.com/62213019/113356022-81aada00-92f6-11eb-8e76-0e11fa0d790d.png)






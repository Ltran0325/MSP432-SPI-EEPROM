# MSP432-SPI-EEPROM

### SPI EEPROM Operation:
Read and write a byte to SPI EEPROM (25LC040)


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





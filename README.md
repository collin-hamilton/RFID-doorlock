# RFID-doorlock
A simple door lock created using an Arduino Mega 2560R3

Modules Needed:
- Elegoo Mega 2560R3
- ULN2003 stepper motor drivermodule
- Stepper motor 28BYJ-48
- 1602 LCD
- RC552 RFID Module
- RGB LED
- Passive Buzzer
- 3 * 220Ω Resistors
- Membrane Switch Module


## IMPORTANT NOTE: The RFID module's pins MUST align with the pins shown in the diagram if using a Mega 2560R3. These pins are dedicated SPI pins by the CPU. See the graphic for the necessary pinouts for other Arduino models.
![RFID pinnout](https://user-images.githubusercontent.com/45021778/229664187-6c7eac8e-1589-40c7-8d12-239a70478398.png)


## IMPORTANT NOTE: The RBG LED must be connected to a PWM digital pin. These pins may vary depending on the Arduino model. 

## Below are the wiring diagrams for each module:
![LCD 1602 wiring diagram](https://user-images.githubusercontent.com/45021778/229663741-ee6433c4-ed2d-416b-906c-b09940e442df.png)
![membrane switch wiring diagram](https://user-images.githubusercontent.com/45021778/229663746-863dfb39-6d87-45d7-965d-bd69b0f94a28.png)
![passive buzzer wiring diagram](https://user-images.githubusercontent.com/45021778/229663749-f6b010f3-ac53-4f78-b0ef-53c237f6ef25.png)
![RC522 RFID module wiring diagram](https://user-images.githubusercontent.com/45021778/229663750-f8b7d179-de1a-4b4f-b9ce-00a7284682e8.png)
![RGB led wiring diagram](https://user-images.githubusercontent.com/45021778/229663751-70bc0935-d097-49fc-bf55-8262d018aa31.png)
![stepper motor 28BYJ-48 wiring diagram](https://user-images.githubusercontent.com/45021778/229663754-14ef7e4c-13dc-4037-b8f0-b0edd1e2bd80.png)


PWM exclamation:

![pwm exclamation](https://user-images.githubusercontent.com/45021778/229673783-e52b21b5-8ee6-435b-be63-2d811c9d5463.png)

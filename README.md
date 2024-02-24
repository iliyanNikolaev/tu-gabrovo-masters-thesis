<p align="center">
  <img src="readmeAssets/tu-gabrovo-header.png" alt="logo">
</p>

# Sensor Hub for Environmental Monitoring
Prototype of a thesis for the completion of a Electronics Master's degree.

## Description
This project involves the use of Arduino UNO R3 and various sensors to monitor temperature, humidity, noise level, and air quality. The information is transmitted via the serial port, where a Node.js server reads and provides an interface for visualizing the data.

## Components
- Arduino UNO R3 (ATmega328p)
- DHT22 (Temperature and Humidity Sensor)
- KY-037 (Noise Level) sensor
- MQ-135 (Gas sensor)
- LCD1601A HD44780 (Text display)
- Potentiometer 10k ohms
- TTP224 (Keypad module)
- 6 resistors of 220 ohms each
- Prototype board MB-102

## Components Descriptions
1. **DHT22 (Temperature and Humidity Sensor):**
   The DHT22 sensor is used to measure both temperature and humidity levels in the environment. It communicates with the Arduino through a digital pin and provides accurate readings.

2. **KY-037 (Noise Level Sensor):**
   The KY-037 sensor detects the noise level in the surroundings. It outputs an analog signal that corresponds to the noise level, which can be read by the Arduino through an analog pin.

3. **MQ-135 (Gas Sensor):**
   The MQ-135 sensor is capable of sensing various gases such as alcohol, benzene, smoke, and CO2. It provides analog output, which can be interpreted by the Arduino to determine the air quality.

4. **LCD1601A HD44780 (Text Display):**
   The LCD1601A HD44780 display is used to output the sensor readings in a user-friendly format. It provides a clear visual representation of the data, allowing users to monitor the atmospheric conditions easily.

5. **TTP224 (Keypad Module):**
   The TTP224 keypad module allows users to interact with the system by pressing different buttons. It provides multiple output pins, each corresponding to a different button, which can be read by the Arduino to trigger various actions.

## Setup and Installation
1. Connect the Arduino UNO R3 to the laptop via USB cable.
2. Upload the sketch (`arduino.ino`) to the Arduino using the Arduino IDE.
3. Start the Node.js server:
    ```bash
    cd server
    npm install
    node server.js
    ```
4. Open a web browser and visit http://localhost:3000 to view the interface.

## Interface
- The interface visualizes the data from the sensors.
- Pressing different buttons on the keypad module changes the display to show different sensor readings.

## License
This project is licensed under the [MIT License](LICENSE).

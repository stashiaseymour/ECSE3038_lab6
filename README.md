# ECSE3038 Lab 6: API Communication with ESP32

## Purpose

This project was developed for Lab 6 of the ECSE3038 course at The University of the West Indies.  
The goal is to practice interacting with RESTful APIs using an ESP32 microcontroller by simulating a client that:
- Sends temperature data to a server using a `PUT` request.
- Receives a command from the server to control an LED using a `GET` request.

---

## Description of Code Behavior

The program connects the ESP32 to WiFi and continuously performs the following:

### setup()

- Initializes serial communication.
- Sets the LED pin as an output.
- Connects to WiFi.

### loop()

- **GET Request to `/api/light`**
  - Sends a GET request with the required API key.
  - Receives a JSON response:  
    `{ "light": true }` or `{ "light": false }`
  - Controls the LED based on the value of `"light"`.

- **Read and Send Temperature via PUT Request**
  - Reads analog input from GPIO34 (used as a temperature sensor).
  - Converts the analog value to voltage, then to Celsius using:  
    `(voltage - 0.5) * 100`
  - Sends the temperature value in a JSON object to the server using a PUT request.
  - Receives a confirmation response from the server:
    `{ "message": "Temperature state updated" }`

---

## Included Files

- `main.cpp`: Contains the main application logic.
- `platformio.ini`: PlatformIO configuration file.
- `wokwi.toml` and `diagram.json`: Used to configure the Wokwi simulation environment.
- `.gitignore`: Used to exclude build files and any other sensitive files from version control.


# Subhashini LCD Display Project

## Overview

This Arduino project utilizes the LCDWIKI_GUI and LCDWIKI_KBV libraries to create an interactive display system with a touch screen. The display shows slokas, subhashithas (wise sayings), and sensor data (temperature and humidity). It is designed to be user-friendly and provides an engaging interface for users.

## Hardware Requirements

- ILI9486 LCD Display
- Arduino Board
- DHT22 Sensor
- Buttons for Slokas, Subhashithas, and Sensor Readings

## Installation

1. Connect the ILI9486 LCD display to the Arduino board as per the provided pin configuration.
2. Install the required libraries:
   - LCDWIKI_GUI
   - LCDWIKI_KBV
   - DHT (for the DHT22 sensor)
3. Upload the provided Arduino code to your board.

## Usage

1. **Home Screen:**
   - The initial screen displays project information.
   - Press the Sensor button to view sensor data.

2. **Slokas:**
   - Press the Sloka button to cycle through different slokas.
   - Each sloka is displayed for 3 seconds.

3. **Subhashithas:**
   - Press the Subhashitha button to cycle through wise sayings.
   - Each subhashitha is displayed for 3 seconds.

4. **Sensor Readings:**
   - Press the Sensor button to view real-time temperature and humidity data from the DHT22 sensor.
   - The data is displayed for 5 seconds.

## Additional Information

- The project avoids rapid changes when buttons are held down with a delay of 500 milliseconds.
- The display is rotated to landscape mode for optimal viewing.

Feel free to modify the code and adapt it to your specific needs. For more information, refer to the [documentation](documentation.md) in this repository.

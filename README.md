# Bee Hive Monitoring System - Polytech Sorbonne

## Project Context

Welcome to the GitHub repository for our Bee Hive Monitoring System project, an innovative initiative by engineering students at Polytech Sorbonne in the Ei-2i-4 program. This project is designed to address the alarming global decline in bee populations due to Colony Collapse Disorder (CCD) and other environmental stresses.

### Background

Since 1998, CCD has been a major issue in France and across Europe, characterized by the sudden and massive disappearance of bees from hives, particularly at the end of winter or sometimes during mid-summer. The syndrome has devastating implications not only for beekeepers but also for the global ecosystem, considering the critical role of bees as pollinators. Essential crops such as apples, almonds, avocados, and many others are at risk due to the declining bee populations, as these crops heavily rely on bee pollination.

### Objectives

Our project aims to develop a sophisticated monitoring system embedded within beehives to continuously track environmental and biological factors affecting bee colonies. The primary objectives of this system include:

- Environmental Monitoring: To measure real-time data on temperature, humidity, and other atmospheric conditions that could influence hive health.
- Predator Detection: To identify the presence of predators like the Varroa mite and Asian hornet, which are known to cause significant harm to bee colonies.
- Chemical Surveillance: To detect the presence of harmful chemicals, including widely-used insecticides that have been linked to bee mortality.

### Technical Approach

The system utilizes an array of sensors integrated within the hives, coupled with data analytics tools to process and visualize the data. These include:

- Temperature and Humidity Sensors: To monitor climate conditions inside and around the hive.
- Motion Sensors: For detecting unusual activity that may indicate the presence of predators.
- Chemical Sensors: Capable of identifying trace levels of toxic substances in the environment.
- Data Analysis: Utilizing machine learning algorithms to predict potential threats and health issues based on collected data.

## Material

### 1. Arduino MKR WAN 1310 
The MKRWAN board serves as the central component of the monitoring system. Specifically designed for LoRaWAN communication, this Arduino-compatible board offers compactness and low power consumption, making it ideal for efficient and discreet beehive monitoring.

### 2. DHT22 Temperature and Humidity Sensors
Chosen for their precision, the DHT22 sensors accurately measure temperature and humidity levels within the beehives. This critical data helps monitor bee health and environmental conditions. With their robust single-wire digital interface, these sensors ensure reliable readings even in challenging environments.

### 3. DS18B20 Temperature Sensors (x2)
Used because of their accuracy in external conditions, DS18B20 sensors play a crucial role in assessing the ambient environment surrounding the hives. Using the OneWire protocol, these sensors seamlessly integrate into the system.

### 4. H401-C3 Load Cell and HX711 Amplifier
The H401-C3 load cell, known for its precision and reliability, forms the core of the weight monitoring system. Teamed up with the HX711 amplifier, renowned for its low-noise analog-to-digital conversion, this combination provides accurate weight measurements. These measurements are essential for evaluating hive health and activity.

### 5. Luxmeter SEN0562
This waterproof digital ambient light sensor is designed to deliver accurate measurements of light intensity within the range of 1-65535 lx.

### 6. Power Supply (LiPo Battery and Solar Panel) and TPL5110 Power Management Module
The monitoring system operates on a rechargeable LiPo battery with a nominal voltage of 3.7V and a maximum voltage of approximately 4.2V, ensuring autonomy and continuous operation. A solar panel is integrated in order to continuously recharge the battery. This system is made for sustainability and energy efficiency. 
We use the TPL5110 power management module to manage the power consumption to ensure a sufficient battery life. It allows the system to be supplied only when it’s necessary.

### Consumption: 

We can see the representation of the battery’s voltage. Since the MKR WAN has to receive 3.3 V, we use a voltage divider with a R1/R2 ratio of 0.786, knowing that we have to use resistances with high values to limit the current the best way we can.

![image](https://github.com/galgosruche/OPEN-Ruche/assets/168517667/6c030098-af06-42f7-96e6-e6f57c0f0464)

### PCB Schematic

To create the routing layout using the KiCad software, we will first import a technical library containing MKRWANxxx components. Additionally, we will position 8 connectors representing the 7 sensors along with the previously mentioned voltage regulator.

![image](https://github.com/galgosruche/OPEN-Ruche/assets/168517667/e770e0e9-acd5-42f3-a5d2-8f7805084d4b)

The image above displays the actual PCB schematic, providing a visual representation of the board's layout, connectors, and sensor interfaces.

## Hardware Setup

In order to be able to assure the connection and the transmission of the data, we have to connect the components in an efficient and smart way. 

## MKRWAN 

It is the central piece of the device; it is the link between all the other components and it is responsible for the data processing and the provision of energy. The code we write help us control everything through de MKRWAN and guaranty the LoRaWAN communication.

## SOFTWARE PREREQUISITES 
1.	Hardware connections: connect all the sensors, the power source and your computer to the MKRWAN. 
2.	Arduino IDE: Make sure to have downloaded the Arduino IDE to pilot the MKRWAN via the code. 
3.	LoRaWAN: Get beforehand the network provider, in our case The Things Network, to configure the LoRaWAN connectivity.
4.	Installations: Install the different libraries necessary for the sensors and make sure to have updated the AppEUI and AppKey variables of TTN.
5.	Calibration of the weight sensor: We have to calibrate the weight sensor beforehand and here are the different steps you have to follow in order to do so;
a.	Choose a reference weight with an accurate measure and prioritize one in the range of the hive’s weight. 
b.	Place the selected object on the sensor and make sure the sensor is stabilized to have a precise measure.
c.	Keep a record of the raw value read corresponding to the measured weight 
d.	Calculate the calibration factor with the following equation: 
Calibration Factor = Reference Weight (grams) / Raw Value
e.	Calculate the weights of the measured objects by applying the CF and multiplying the raw values by the CF.

### Code summary and structure 

### Definitions and Global Variables: Several constants and variables are defined for use in the program:
  Pin assignments for various sensors.
  Calibration factors and addresses for the sensors.
  Objects are instantiated for each sensor.

### Setup Function:
  Initializes serial communication.
  Establishes settings for each sensor like scale calibration and baseline setting (tare).
  Initializes the LoRa modem and sets up parameters for the LoRa network (like frequency and data rate).

 ### Main Loop:
  The loop contains a connection routine for the LoRa network, attempting to connect if not already connected.
  Sensor readings are taken periodically, including weight, temperature, humidity, and light.
  The DHT22 sensor measures ambient temperature and humidity.
  The HX711 scale measures weight and allows for recalibration through serial commands.
  The SEN0562 light sensor calculates lux values.
  The SEN0227 and OneWire sensors provide additional temperature and humidity readings.
  Battery voltage and percentage are calculated and displayed.
  Finally, sensor data is packaged and sent over the LoRa network.

  ### Auxiliary Functions:
  readReg function to facilitate I2C communication, particularly for reading from the light sensor.

### Summary of Code Functionality

Data Collection: The code collects data from a variety of environmental sensors, consolidating temperature, humidity, weight, and light levels.
Data Transmission: Using a LoRaWAN module, the collected data is transmitted to a remote server or gateway, which is crucial for IoT applications in remote monitoring or agricultural sectors.
Dynamic Interaction: The program listens for serial input to adjust calibration factors for the weight sensor dynamically, which is useful for calibration without needing to modify and re-upload the code.
Energy Efficiency: Implements low power sleep functionality to save energy, critical for battery-operated remote sensors.

### Libraries

1. MKRWAN.h: This library is used with Arduino MKR WAN 1300 boards, which are designed for connectivity over LoRaWAN networks. It provides functions to facilitate communication over a LoRa network, making it easier to send and receive data wirelessly over long distances.

2. Wire.h: A standard library included with the Arduino IDE, used for I2C communication. The Wire library allows Arduino boards to communicate with I2C / TWI (Two Wire Interface) devices like sensors, EEPROMs, and other microcontrollers. It is essential for connecting and retrieving data from devices that support I2C.

3. HX711.h: This library is specifically used to interface with the HX711 load cell amplifier. The HX711 module is commonly used in electronic scales and consists of a precision 24-bit analog-to-digital converter (ADC) designed for weigh scales and industrial control applications to interface directly with a bridge sensor.

4. DHT.h: The DHT library is used to interface with DHT series humidity and temperature sensors, notably the DHT22 and DHT11 models. These sensors are popular due to their ability to provide both temperature and relative humidity readings as digital output.

5. OneWire.h: This library is crucial for handling the OneWire communication protocol, which is typically used for devices like the DS18B20 temperature sensor. The OneWire protocol requires only one data line (and ground) for communication with the microcontroller, which simplifies wiring and makes it suitable for simple sensor networks.

6. DFRobot_SHT20.h: This library is developed by DFRobot and is used to interface with the SHT20 temperature and humidity sensor. The SHT20 sensor offers a reliable and precise solution for measuring relative humidity and temperature, and it utilizes the I2C interface for communication.

7. DallasTemperature.h: Used in conjunction with the OneWire library, the DallasTemperature library facilitates the interaction with Dallas OneWire temperature sensors like the DS18B20. This library simplifies the process of reading temperatures from multiple sensors on a single data line.

Each library serves a specific function related to sensor interfacing and data handling in embedded systems and IoT applications, aiding developers in creating complex, sensor-driven projects with ease.

## The Things Network and BEEP

The Things Network is a payload formatter that decodes the sent data by the MKRWAN and converts them in treatable values for us to describe and use.
After that, the data is formatted following the Beep API rules and is sent to the Beep API through a webhook. The Beep-API ensures the visualization of the data as an interface made for the final users of the device.

### BEEP interface 

![image](https://github.com/galgosruche/OPEN-Ruche/assets/168517667/b4633e36-7632-4635-8582-c16a449606e1)

## Final look

![IMG_7287](https://github.com/galgosruche/OPEN-Ruche/assets/168517667/49222833-aadb-4168-8382-569d66e369e8)


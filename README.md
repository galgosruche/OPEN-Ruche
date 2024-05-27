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






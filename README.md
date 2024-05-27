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


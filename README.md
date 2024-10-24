# 🌡️ Temperature Monitoring IoT Project with MQTT and Yocto

## 🛠️ Project Overview

This project involves creating a custom Linux image using Yocto Project for an IoT system where a Raspberry Pi acts as an MQTT broker, and an ESP32 collects temperature data from a DHT11 sensor. The data is published to an MQTT topic and is processed by the Raspberry Pi.

## 🔧 Components

- **ESP32**: 📡 Collects temperature data using the DHT11 sensor and publishes it to the MQTT broker via Wi-Fi.
- **Raspberry Pi 4**: 🖥️ Hosts the MQTT broker (Mosquitto) and runs a custom Linux image built with Yocto.
- **DHT11 Sensor**: 🌡️ Measures temperature and humidity.

## ✨ Features

- **Custom Yocto Image**: 🛠️ Built specifically for the Raspberry Pi 4 to host the MQTT broker.
- **MQTT Broker**: 📡 Mosquitto, which handles the publish/subscribe mechanism for the temperature data.
- **Automated Service**: 🔄 Ensures the MQTT broker starts on boot.
- **MQTT Response Mechanism**: 📬 A script that subscribes to the MQTT topic and responds automatically.

## 📦 Yocto Recipes

1. **mosquitto_%.bb**

   - **Purpose**: 🧩 Adds the Mosquitto MQTT broker to the image. Mosquitto allows communication between the ESP32 and the Raspberry Pi through MQTT topics, handling the data flow in the project.

2. **sudo_%.bb**

   - **Purpose**: 🛡️ Installs `sudo` in the custom image, necessary to allow administrative commands to be executed within the system, enhancing control and security during the broker’s management.

4. **sysd-mqtt.bb**

   - **Purpose**: 🖥️ This custom recipe uses systemd to run a shell script (`sysd-mqtt.sh`) at boot. The script subscribes to the MQTT topic to receive messages from the ESP32 and automatically sends a response ("led on") back to the ESP32. This ensures that the system can collect temperature data and respond to the ESP32 through MQTT in real-time.

5. **linux-firmware-rpidistro_git.bb**

   - **Purpose**: 📶 Provides updated firmware files required for Raspberry Pi hardware, especially for Wi-Fi connectivity. This firmware is essential for the Wi-Fi modules on the Raspberry Pi to function properly, ensuring communication between the Raspberry Pi and the ESP32 over MQTT.

## 🏗️ How to Build the Image

1. 📥 Clone this repository.
2. 📄 Follow the steps to initialize and configure the Yocto build environment.
3. 🧩 Include the necessary layers and recipes described above.
4. 🖨️ Build the image and flash it to the Raspberry Pi.

## 🚀 Usage

Once the Raspberry Pi boots up with the custom Yocto image:

- 🟢 The Mosquitto MQTT broker will automatically start.
- 🛠️ The `sysd-mqtt.sh` script will run at boot, allowing the Raspberry Pi to subscribe to the temperature topic and respond to the ESP32.
- 📡 The ESP32 can publish temperature data to the broker, and you can subscribe to the topic to monitor the temperature data.

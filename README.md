# Project to improve treatment on children with panic attack. ESP32 + Smartwatch + LoraWan + TTN + RFID + BackEnd + Chatbot.

## Abstract

Development of a holistic health solution to support people suffering from panic disorders, 
mainly children. A low-cost product that allows many patients to improve their quality of life 
using Industry 4.0 concepts and tools such as the Internet of Things (IoT), Smart Wearables, 
Cloud Computing, 3D printing and Artificial Intelligence (AI). The solution is not limited to 
improving the patient's symptoms, but also provides opportunities for the doctors involved to 
personalize treatments and for parents/guardians to monitor the attacks that occur in real 
time.

The project has been carried out using traditional project management methodology and a 
proof of concept (PoC).

*Keywords:* Industry 4.0, Internet of Things (IoT), Health 4.0, Panic disorders and Remote 
patient monitoring.

** IA data collection and processing is out of scope in this version.

![General Architecture](https://i.ibb.co/JRqLZxj/arquitectura-general.png)

## List of materials

| Component                        | Quantity      | Unit Cost     | Total Cost    |
| -------------------------------- | ------------- | ------------- | ------------- |
| ESP32 board                      | 1             |  3.5 USD      |  3.5 USD      |
| Kit RFID RC522                   | 1             |  2.5 USD      |  2.5 USD      |
| Power source (5v)                | 1             |  2 USD        |   2 USD       |
| Test board MB-102                | 1             |  1 USD        |   1 USD       |
| Smartwatch HKT Heath (Lora)      | 1             |  100 USD      |   100 USD     |
| DSGW-210B Indoor LoRaWAN Gateway | 1             |  210 USD      |   210 USD     |
| API Whatsapp supplier            | 3             |  10 USD       |   30 USD      |
| Wires                            | 10            |  0.1 USD      |   1 USD       |
| DB & Server service              | 3             |  15 USD       |  45 USD       |
| Coste total                      |               |               | 395 USD       |

## General use case

![General use case](https://i.ibb.co/6W3cNx1/use-case-general.png)

1. Safe station is built by a RFID reader and ESP32 board connected to Wi-Fi. The patient get close the RFID key when he feel under a panic situation. Following medical indications.
2. Smartwatch will be a device connected by LoRaWan that will record heartbeats at all times.
3. Chatbot WhatsApp. With data coming from the safe station and the smartwatch, backend process will trigger a comunication process with patieten troghut a chatbot. In this way the patient will start to calm down in other hand he'll give us important information following the question & answer game pre programmed.

### Safe station

![Safe station](https://i.ibb.co/p1bTYSR/estacion-segura.jpg)

The safe station allows patients to actively report a panic attack in progress.

![Safe station schematic](https://i.ibb.co/k3m2tXL/esp32-rc522.png)

The code is attached in this repository.

### LoRaWan connection

![LoRaWan connection](https://i.ibb.co/vmgqnx2/gateway-dusun.jpg)

We enter our Internet router configuration to include the new Lora gateway. After obtained a IP Address by DHCP, we'll enter to manage Lora gateway and obtain EUI code.

![DHCP Configuration](https://i.ibb.co/k94XH87/gateway-UI-DHCP.png)

After that, we create an account on The Things Network (TTN), create a new project, and add a new gateway.

![TTN Configuration](https://i.ibb.co/JCH9JKX/lora-config.png)

The configuration JSON file is attached.

### LoRaWan Smartwatch

![LoRaWan smartwatch](https://i.ibb.co/KLVjNgX/reloj-unboxing.jpg)

This smartwatch model works with EU868MHz frequency. You can buy it here: https://www.hktlora.com/product/lorawan-smart-watch/ 

![TTN Configuration end device](https://i.ibb.co/55XMyc8/ttn-end-device.png)

We add the smartwatch as an end device from left panel. This model works with LoRaWAN 1.0.3 version. It's important to obtain this information from supplier.

You can check how to add a new device from here: https://www.thethingsindustries.com/docs/devices/adding-devices/

Before to add an end device, we need to create an application. Following this guide: https://www.thethingsindustries.com/docs/integrations/adding-applications/ 

![TTN Configuration webhook](https://i.ibb.co/cFxYsWY/webhook-ttn.png)

Here we've added a webhook to interact with the backend when the smartwatch exceeds a defined threshold for heartbeats.

![TTN Configuration decoder](https://i.ibb.co/VmkTqW8/ttn-decoder.png)

Here we've programmed a valid uplink payload for this smartwatch model. Example code is attached.

### Testing

![Test](https://i.ibb.co/F0YHbxm/test.png)

There we activated a panic episode by simulating it at 60 beats per second. In this case the chatbot sends the first message to the patients to contain the episode and collect data. Likewise, the process is activated when the patient actively touches the RFID sensor to force interaction.

*If you want to know more about the backend and chatbot definitions. Please let me know.*

# HackBMU2019_FuelHook

*Fuel Hook* is an IOT based comprehensive vehicle fuel monitoring system. 
The device accurately tracks the fuel transactions/exchanges taking place within the vehicle. 
This helps the user identify fuel theft occurring during refills and otherwise. 
This involves a systematic approach which includes measuring the fuel 
supplied to the automobile and comparing it with the self-proclaimed readings of the distributor. 
The system compares the readings instantaneously and provides the consumer with the amount of stolen fuel.
We intend to keep track of the GPS location of the times when the consumer refills his/her vehicle. 
This way the user will be able to access the exact location as well.

**Main Hardware Components:**
1.	Flow Sensor
2.	GPS Module
3.	Arduino
4.	GSM Module
5.	7-segment display array

**Main Software Components:**
1.	Arduino IDLE
2.	ThingSpeak

**FLOW_SENSOR_ONLINE_UPLOAD.ino:-**
We have used flow sensor(YFS 201)by which we are measuring the quantity of the flowing liquid. This has been connected to Wifi Module: NodeMCU(ESP 8266) which uploads the data on ThingSpeak(an online open-source platform on which we can store this data). We have experimented upon the flow sensor and the readings obtained are seen through the NodeMCU and this reading can also be seen upon the serial monitor as well as online on ThingSpeak website.

**GPS_MODULE.ino:-**
We are taking readings from GPS(Global Positioning System) Module and printing them on serial moniter in Arduino IDLE software.

**GSM_SEND_SMS.ino:-**
GSM(Global System for Mobile)is used to send the message to Mobile phone of the owners.


**DEVICE_INSERTED.ino:-**
It is the complete code for sending the data from the vehicle to the user.


**SERVER_DEVICE.ino:-**
Data from the Device inserted is send to Server device using GSM Module and then it is uploaded on server.


Amount of liquid added in the fuel tank is recoded by Arduino NANO using flow sensor. Amount of fuel added is with the GPS coordinates are sent to the Mobile phone using GSM Module by Arduino and the fuel amount is shown on 7-segment display on dashboard in real time.



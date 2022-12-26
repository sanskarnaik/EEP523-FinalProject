# final-project
This repo contains final project created by Sanskar and Sukhwinder.

**Objective:** 
We wanted a device that can be used by the patient to transmit 3 types of help signal to the Doctor depending on his/her requirements, and an App that can be used by the Doctor to see the help signal and in return send his availability message to the patient.

**Components Used:** 
1. Adafruit Feather Huzzah Microcontroller.
2. Arduino IDE.
3. Firebase-Arduino Library.
4. Firebase Realtime Database.
5. Android Studio.
6. Buttons and LEDs.

**Working:**
(Assuming the wifi is connected and Doctor's Mobile is also connected to the internet.)
When the Patient needs help, and the doctor is not close to him, he can press the red button once.
As soon as he presses the red button, "Need Help" message is updated on the Realtime Database. 
And as this database is connected to Doctor's application, the mesaage field on the app also gets updated at the same time.
By seeing the app the doctor can know, which patient is in need of help.

When the patient needs any emergency care, he can just hold the red button on the device for atleast 5 seconds.
if he does so "Emergency" message gets updated on the realtime database, and also on the doctor's mobile, by which the doctor can know which patient is in emergency.

The doctor can respond to the Patient's message by just pressing one of the time buttons. When the doctor presses "Less than 10 min" Button, green light glows on the device, so that the patient can know, that the doctor is coming in few minutes. Similarly doctor can press "Less than 20 min" Button or "later" button, and in return yellow and red light glows on the device respectively. This feature really helps the patient to know the doctor's arrival status.

**Feel Good Features:**
1. We provided a drop down menu to the app, by which the doctor has the flexibility to know about n number of patients in the hospital, and to check their current status.
2. There is a green button on the device, which is used to reset the message field on the realtime database. As sometimes, the patient can press the red button by mistake or the doctor already attended the patient, but still the message shows "need help". So to solve this problem, the patient can just press the green button and
"I am good" message will get updated on the realtime database.

**How you can use this project:**
Follow these steps:
1. Make a circuit diagram similar to the one as shown in the photo. You can use 1k ohm resistance for the Leds, and 10k ohm for the buttons.(be careful when connecting the board pins)
2. Select the proper board from the Arduino Ide boards manager, then add the libraries from include library option in the sketch tab. You have to install the ESP8266wifi library from the library manager.
You could also have to install the particular board, follow online tutorial on how to get the Adafruit Feather Huzzah Board on the Arduino IDE.
3. Make a firebase account online, and add the mock data on the realtime database, as shown in the picture.
4. Follow online tutorials on how to connect firebase realtime database to the esp8266 board.
5. Now you are ready to upload the code on the board. (Before it, please changes the wifi SSID and password for your network.)
6. Install the application on your android smartphone(newer than kitkat) by using android studio. (Don't forget to connect your application to the firebase realtime database.)
7. Now you can use the project, and can refer to the working section of this file.

I would like to thank Prof Slaughter, for providing immense support throughout the course and especially in the project.


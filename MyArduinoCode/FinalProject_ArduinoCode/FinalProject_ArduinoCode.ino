//
// Copyright 2015 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

// FirebaseDemo_ESP8266 is a sample that demo the different functions
// of the FirebaseArduino API.

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include "Button.h"

// Set these to run example.
#define FIREBASE_HOST "patient-s-database-cd92d-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "CyEkoUmUGPEI2720GAFX7eTvACYDbJefTgZSkhap"
#define WIFI_SSID "Sanskar's Galaxy A52 5G"
#define WIFI_PASSWORD "hsuh0271"

// My Variables:
Button buttonR(12);
Button buttonG(4);
int GREEN_LED = 5;
int YELLOW_LED = 15;
int RED_LED = 16;
bool green_led = false;
bool yellow_led = false;
bool red_led = false;
unsigned long previousMillis = 0;
bool onceHere = true;

void setup() {
  Serial.begin(9600);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  // My Setup:
  pinMode(0, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  Serial.begin(9600);
  buttonR.on_press(on_press);
  buttonR.on_long_press(on_long_press);
  buttonR.set_maximum_gap(5000);
  buttonG.on_press(on_press_reset);
}

void loop() {
  buttonR.init();
  buttonG.init();
  waitTimeRead(1000);
}

void on_press() {
    Serial.println("Need Help");
    Firebase.setString("BedNo/01/Message", "Need Help");
    // handle error
    if (Firebase.failed()) {
        Serial.print("Message push failed!!");
        Serial.println(Firebase.error());  
        return;
    }
}
void on_long_press() {
  Serial.println("Emergency");
  Firebase.setString("BedNo/01/Message", "Emergency");
  // handle error
  if (Firebase.failed()) {
      Serial.print("Message push failed!!");
      Serial.println(Firebase.error());  
      return;
  }
}
void waitTimeRead(const long interval) {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    String waitTime = Firebase.getString("BedNo/01/Wait Time");
    if(waitTime == "10min") {
      digitalWrite(GREEN_LED, HIGH);
      digitalWrite(RED_LED, LOW);
      digitalWrite(YELLOW_LED, LOW);
      Serial.println("10min");
    } else if(waitTime == "20min") {
      digitalWrite(GREEN_LED, LOW);
      digitalWrite(RED_LED, LOW);
      digitalWrite(YELLOW_LED, HIGH);
      Serial.println("20min");
    } else if(waitTime == "Later" || waitTime == "Nurse") {
      digitalWrite(GREEN_LED, LOW);
      digitalWrite(RED_LED, HIGH);
      digitalWrite(YELLOW_LED, LOW);
      Serial.println("Later");
    } else {
      digitalWrite(GREEN_LED, LOW);
      digitalWrite(RED_LED, LOW);
      digitalWrite(YELLOW_LED, LOW);
      Serial.println("All Led OFF");
    }
    
  }
}
void on_press_reset() {
  Serial.println("I am Good");
  Firebase.setString("BedNo/01/Message", "I am Good");
  // handle error
  if (Firebase.failed()) {
      Serial.print("Message push failed!!");
      Serial.println(Firebase.error());  
      return;
  }

  Firebase.setString("BedNo/01/Wait Time", "Null");
  // handle error
  if (Firebase.failed()) {
      Serial.print("Message push failed!!");
      Serial.println(Firebase.error());  
      return;
  }
}

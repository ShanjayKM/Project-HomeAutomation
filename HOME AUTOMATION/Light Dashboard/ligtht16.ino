/*
   MQTT Light for Home-Assistant - NodeMCU (ESP8266)
   https://home-assistant.io/components/light.mqtt/

   Libraries :
    - ESP8266 core for Arduino : https://github.com/esp8266/Arduino
    - PubSubClient : https://github.com/knolleary/pubsubclient

   Sources :
    - File > Examples > ES8266WiFi > WiFiClient
    - File > Examples > PubSubClient > mqtt_auth
    - File > Examples > PubSubClient > mqtt_esp8266

   Schematic :
    - https://github.com/mertenats/open-home-automation/blob/master/ha_mqtt_light/Schematic.png
    - GND - LED - Resistor 220 Ohms - D1/GPIO5

   Configuration (HA) : 
    light:
      platform: mqtt
      name: Office light'
      state_topic: 'office/light1/status'
      command_topic: 'office/light1/switch'
      optimistic: false

   Samuel M. - v1.1 - 08.2016
   If you like this example, please add a star! Thank you!
   https://github.com/mertenats/open-home-automation
*/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include<ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <SoftwareSerial.h>


SoftwareSerial swSer(14, 12, false, 128); //Define hardware connections

#define MQTT_VERSION MQTT_VERSION_3_1_1
WiFiServer server(80);
 IPAddress ip(192, 168, 29, 148);
IPAddress gateway(192, 168, 29, 1);  
IPAddress subnet(255, 255, 255, 0);
IPAddress dns(8, 8, 8, 8);
// Wifi: SSID and password
const char* WIFI_SSID = "Newqbitronics2.4";
const char* WIFI_PASSWORD = "QBITRON09876";

// MQTT: ID, server IP, port, username and password
const PROGMEM char* MQTT_CLIENT_ID = "qbit45";
const PROGMEM char* MQTT_SERVER_IP = "122.165.197.129";
const PROGMEM uint16_t MQTT_SERVER_PORT = 1883;
const PROGMEM char* MQTT_USER = "newqbit";
const PROGMEM char* MQTT_PASSWORD = "qbit1234";

// MQTT: topics
const char* MQTT_LIGHT1_STATE_TOPIC = "office/light1/status";
const char* MQTT_LIGHT1_COMMAND_TOPIC = "office/light1/switch";

const char* MQTT_LIGHT2_STATE_TOPIC = "office/light2/status";
const char* MQTT_LIGHT2_COMMAND_TOPIC = "office/light2/switch";

const char* MQTT_LIGHT3_STATE_TOPIC = "office/light3/status";
const char* MQTT_LIGHT3_COMMAND_TOPIC = "office/light3/switch";

const char* MQTT_LIGHT4_STATE_TOPIC = "office/light4/status";
const char* MQTT_LIGHT4_COMMAND_TOPIC = "office/light4/switch";

const char* MQTT_LIGHT5_STATE_TOPIC = "office/light5/status";
const char* MQTT_LIGHT5_COMMAND_TOPIC = "office/light5/switch";

const char* MQTT_LIGHT6_STATE_TOPIC = "office/light6/status";
const char* MQTT_LIGHT6_COMMAND_TOPIC = "office/light6/switch";

const char* MQTT_LIGHT7_STATE_TOPIC = "office/light7/status";
const char* MQTT_LIGHT7_COMMAND_TOPIC = "office/light7/switch";

const char* MQTT_LIGHT8_STATE_TOPIC = "office/light8/status";
const char* MQTT_LIGHT8_COMMAND_TOPIC = "office/light8/switch";

const char* MQTT_LIGHT9_STATE_TOPIC = "office/light9/status";
const char* MQTT_LIGHT9_COMMAND_TOPIC = "office/light9/switch";

const char* MQTT_LIGHT10_STATE_TOPIC = "office/light10/status";
const char* MQTT_LIGHT10_COMMAND_TOPIC = "office/light10/switch";

const char* MQTT_LIGHT11_STATE_TOPIC = "office/light11/status";
const char* MQTT_LIGHT11_COMMAND_TOPIC = "office/light11/switch";

const char* MQTT_LIGHT12_STATE_TOPIC = "office/light12/status";
const char* MQTT_LIGHT12_COMMAND_TOPIC = "office/light12/switch";

const char* MQTT_LIGHT13_STATE_TOPIC = "office/light13/status";
const char* MQTT_LIGHT13_COMMAND_TOPIC = "office/light13/switch";

const char* MQTT_LIGHT14_STATE_TOPIC = "office/light14/status";
const char* MQTT_LIGHT14_COMMAND_TOPIC = "office/light14/switch";

const char* MQTT_LIGHT15_STATE_TOPIC = "office/light15/status";
const char* MQTT_LIGHT15_COMMAND_TOPIC = "office/light15/switch";

const char* MQTT_LIGHT16_STATE_TOPIC = "office/light16/status";
const char* MQTT_LIGHT16_COMMAND_TOPIC = "office/light16/switch";

// payloads by default (on/off)
const char* LIGHT1_ON = "ON";
const char* LIGHT1_OFF = "OFF";
const char* LIGHT2_ON = "ON";
const char* LIGHT2_OFF = "OFF";
const char* LIGHT3_ON = "ON";
const char* LIGHT3_OFF = "OFF";
const char* LIGHT4_ON = "ON";
const char* LIGHT4_OFF = "OFF";
const char* LIGHT5_ON = "ON";
const char* LIGHT5_OFF = "OFF";
const char* LIGHT6_ON = "ON";
const char* LIGHT6_OFF = "OFF";
const char* LIGHT7_ON = "ON";
const char* LIGHT7_OFF = "OFF";
const char* LIGHT8_ON = "ON";
const char* LIGHT8_OFF = "OFF";
const char* LIGHT9_ON = "ON";
const char* LIGHT9_OFF = "OFF";
const char* LIGHT10_ON = "ON";
const char* LIGHT10_OFF = "OFF";
const char* LIGHT11_ON = "ON";
const char* LIGHT11_OFF = "OFF";
const char* LIGHT12_ON = "ON";
const char* LIGHT12_OFF = "OFF";
const char* LIGHT13_ON = "ON";
const char* LIGHT13_OFF = "OFF";
const char* LIGHT14_ON = "ON";
const char* LIGHT14_OFF = "OFF";
const char* LIGHT15_ON = "ON";
const char* LIGHT15_OFF = "OFF";
const char* LIGHT16_ON = "ON";
const char* LIGHT16_OFF = "OFF";

int f1=0;
int f2=0;
int f3=0;
int f4=0;
int f5=0;
int f6=0;
int f7=0;
int f8=0;
int f9=0;
int f10=0;
int f11=0;
int f12=0;
int f13=0;
int f14=0;
int f15=0;
int f16=0;

const PROGMEM uint16_t LED_PIN = 5;
boolean m_light1_state = false; // light is turned off by default
boolean m_light2_state = false;
boolean m_light3_state = false;
boolean m_light4_state = false;
boolean m_light5_state = false;
boolean m_light6_state = false;
boolean m_light7_state = false;
boolean m_light8_state = false;
boolean m_light9_state = false; // light is turned off by default
boolean m_light10_state = false;
boolean m_light11_state = false;
boolean m_light12_state = false;
boolean m_light13_state = false;
boolean m_light14_state = false;
boolean m_light15_state = false;
boolean m_light16_state = false;
WiFiClient wifiClient;
PubSubClient client(wifiClient);

// function called to publish the state of the light (on/off)
void publishLightState() {
  if (m_light1_state) {
    client.publish(MQTT_LIGHT1_STATE_TOPIC, LIGHT1_ON, true);
  } 
  else {
    client.publish(MQTT_LIGHT1_STATE_TOPIC, LIGHT1_OFF, true);
  } 
  if (m_light2_state) {
   client.publish(MQTT_LIGHT2_STATE_TOPIC, LIGHT2_ON, true);
  }
  else {
    client.publish(MQTT_LIGHT2_STATE_TOPIC, LIGHT2_OFF, true);
  } 
  
  if (m_light3_state) {
  client.publish(MQTT_LIGHT3_STATE_TOPIC, LIGHT3_ON, true);
  } 
  else {
    client.publish(MQTT_LIGHT3_STATE_TOPIC, LIGHT3_OFF, true);
  }
   if (m_light4_state) {
  client.publish(MQTT_LIGHT4_STATE_TOPIC, LIGHT4_ON, true);
  } 
  else {
    client.publish(MQTT_LIGHT4_STATE_TOPIC, LIGHT4_OFF, true);
  }
  if (m_light5_state) {
    client.publish(MQTT_LIGHT5_STATE_TOPIC, LIGHT5_ON, true);
  } 
  else {
    client.publish(MQTT_LIGHT5_STATE_TOPIC, LIGHT5_OFF, true);
  } 
  if (m_light6_state) {
   client.publish(MQTT_LIGHT6_STATE_TOPIC, LIGHT6_ON, true);
  }
  else {
    client.publish(MQTT_LIGHT6_STATE_TOPIC, LIGHT6_OFF, true);
  } 
  
  if (m_light7_state) {
  client.publish(MQTT_LIGHT7_STATE_TOPIC, LIGHT7_ON, true);
  } 
  else {
    client.publish(MQTT_LIGHT7_STATE_TOPIC, LIGHT7_OFF, true);
  }
   if (m_light8_state) {
  client.publish(MQTT_LIGHT8_STATE_TOPIC, LIGHT8_ON, true);
  } 
  else {
    client.publish(MQTT_LIGHT8_STATE_TOPIC, LIGHT8_OFF, true);
  }
    if (m_light9_state) {
    client.publish(MQTT_LIGHT9_STATE_TOPIC, LIGHT9_ON, true);
  } 
  else {
    client.publish(MQTT_LIGHT9_STATE_TOPIC, LIGHT9_OFF, true);
  } 
  if (m_light10_state) {
   client.publish(MQTT_LIGHT10_STATE_TOPIC, LIGHT10_ON, true);
  }
  else {
    client.publish(MQTT_LIGHT10_STATE_TOPIC, LIGHT10_OFF, true);
  } 
  
  if (m_light11_state) {
  client.publish(MQTT_LIGHT11_STATE_TOPIC, LIGHT11_ON, true);
  } 
  else {
    client.publish(MQTT_LIGHT11_STATE_TOPIC, LIGHT11_OFF, true);
  }
   if (m_light12_state) {
  client.publish(MQTT_LIGHT12_STATE_TOPIC, LIGHT12_ON, true);
  } 
  else {
    client.publish(MQTT_LIGHT12_STATE_TOPIC, LIGHT12_OFF, true);
  }
  if (m_light13_state) {
    client.publish(MQTT_LIGHT13_STATE_TOPIC, LIGHT13_ON, true);
  } 
  else {
    client.publish(MQTT_LIGHT13_STATE_TOPIC, LIGHT13_OFF, true);
  } 
  if (m_light14_state) {
   client.publish(MQTT_LIGHT14_STATE_TOPIC, LIGHT14_ON, true);
  }
  else {
    client.publish(MQTT_LIGHT14_STATE_TOPIC, LIGHT14_OFF, true);
  } 
  
  if (m_light15_state) {
  client.publish(MQTT_LIGHT15_STATE_TOPIC, LIGHT15_ON, true);
  } 
  else {
    client.publish(MQTT_LIGHT15_STATE_TOPIC, LIGHT15_OFF, true);
  }
   if (m_light16_state) {
  client.publish(MQTT_LIGHT16_STATE_TOPIC, LIGHT16_ON, true);
  } 
  else {
    client.publish(MQTT_LIGHT16_STATE_TOPIC, LIGHT16_OFF, true);
  }
}

// function called to turn on/off the light
void setLightState() {
if (m_light1_state && f1==0) 
  {
    digitalWrite(LED_PIN, HIGH);
    Serial.println("*A");
    f1=1;
  }
if (m_light1_state==false && f1==1) 
  {
    digitalWrite(LED_PIN, LOW);
    Serial.println("*a");
    f1=0;
  }
if (m_light2_state && f2==0 ) 
  {
    digitalWrite(LED_PIN, HIGH);
    Serial.println("*B");
    f2=1;
  }
if (m_light2_state==false && f2==1)  
  {
    digitalWrite(LED_PIN, LOW);
    Serial.println("*b");
    f2=0;
  }
if (m_light3_state && f3==0 ) 
  {
    digitalWrite(LED_PIN, HIGH);
    Serial.println("*C");
    f3=1;
  }
if (m_light3_state==false && f3==1)  
  {
    digitalWrite(LED_PIN, LOW);
    Serial.println("*c");
    f3=0;
  }
  
if (m_light4_state && f4==0 ) 
  {
    digitalWrite(LED_PIN, HIGH);
    Serial.println("*D");
    f4=1;
  }
if (m_light4_state==false && f4==1)  
  {
    digitalWrite(LED_PIN, LOW);
    Serial.println("*d");
     f4=0;
  }
 
if (m_light5_state && f5==0 ) 
  {
    digitalWrite(LED_PIN, HIGH);
    Serial.println("*E");
    f5=1;
  }
if (m_light5_state==false && f5==1)  
  {
    digitalWrite(LED_PIN, LOW);
    Serial.println("*e");
     f5=0;
  }
 
if (m_light6_state && f6==0 ) 
  {
    digitalWrite(LED_PIN, HIGH);
    Serial.println("*F");
    f6=1;
  }
if (m_light6_state==false && f6==1)  
  {
    digitalWrite(LED_PIN, LOW);
    Serial.println("*f");
     f6=0;
  }
 
if (m_light7_state && f7==0 ) 
  {
    digitalWrite(LED_PIN, HIGH);
    Serial.println("*G");f7=1;
  }
  
if (m_light7_state==false && f7==1)  
  {
    digitalWrite(LED_PIN, LOW);
    Serial.println("*g");
      f7=0;
  }

if (m_light8_state && f8==0 ) 
  {
    digitalWrite(LED_PIN, HIGH);
    Serial.println("*H");
    f8=1;
  }

 if (m_light8_state==false && f8==1)  
  {
    digitalWrite(LED_PIN, LOW);
    Serial.println("*h");
    f8=0;
  }
if (m_light9_state && f9==0) 
  {
    digitalWrite(LED_PIN, HIGH);
    swSer.println("*I");
    f9=1;
  }
if (m_light9_state==false && f9==1) 
  {
    digitalWrite(LED_PIN, LOW);
    swSer.println("*i");
    f9=0;
  }
if (m_light10_state && f10==0 ) 
  {
    digitalWrite(LED_PIN, HIGH);
    swSer.println("*J");
    f10=1;
  }
if (m_light10_state==false && f10==1)  
  {
    digitalWrite(LED_PIN, LOW);
    swSer.println("*j");
    f10=0;
  } 
if (m_light11_state && f11==0 ) 
  {
    digitalWrite(LED_PIN, HIGH);
    swSer.println("*K");
    f11=1;
  }
if (m_light11_state==false && f11==1)  
  {
    digitalWrite(LED_PIN, LOW);
    swSer.println("*k");
    f11=0;
  }
  
 if (m_light12_state && f12==0 ) 
  {
    digitalWrite(LED_PIN, HIGH);
    swSer.println("*L");
    f12=1;
  }
if (m_light12_state==false && f12==1)  
  {
    digitalWrite(LED_PIN, LOW);
    swSer.println("*l");
     f12=0;
  }
if (m_light13_state && f13==0 ) 
  {
    digitalWrite(LED_PIN, HIGH);
    swSer.println("*M");
    f13=1;
  }
if (m_light13_state==false && f13==1)  
  {
    digitalWrite(LED_PIN, LOW);
    swSer.println("*m");
     f13=0;
  }
 
if (m_light14_state && f14==0 ) 
  {
    digitalWrite(LED_PIN, HIGH);
    swSer.println("*N");
    f14=1;
  }
if (m_light14_state==false && f14==1)  
  {
    digitalWrite(LED_PIN, LOW);
    swSer.println("*n");
     f14=0;
  }
 
if (m_light15_state && f15==0 ) 
  {
    digitalWrite(LED_PIN, HIGH);
    swSer.println("*O");f15=1;
  }
  
if (m_light15_state==false && f15==1)  
  {
    digitalWrite(LED_PIN, LOW);
    swSer.println("*o");
      f15=0;
  }

if (m_light16_state && f16==0 ) 
  {
    digitalWrite(LED_PIN, HIGH);
    swSer.println("*P");
    f16=1;
  }

if (m_light16_state==false && f16==1)  
  {
    digitalWrite(LED_PIN, LOW);
    swSer.println("*p");
    f16=0;
  }
}

// function called when a MQTT message arrived
void callback(char* p_topic, byte* p_payload, unsigned int p_length) {
  // concat the payload into a string
  String strtopic= p_topic;
  String payload;
  for (uint16_t i = 0; i < p_length; i++) {
    payload.concat((char)p_payload[i]);
  }

  // handle message topic
  if (String(MQTT_LIGHT1_COMMAND_TOPIC).equals(strtopic)) {
    // test if the payload is equal to "ON" or "OFF"
    if (payload.equals(String(LIGHT1_ON))) {
      if (m_light1_state != true) {
        m_light1_state = true;
        setLightState();
        publishLightState();
      }
    } else if (payload.equals(String(LIGHT1_OFF))) {
      if (m_light1_state != false) {
        m_light1_state = false;
        setLightState();
        publishLightState();
      }
    }
  }

 if (String(MQTT_LIGHT2_COMMAND_TOPIC).equals(strtopic)) {
    // test if the payload is equal to "ON" or "OFF"
    if (payload.equals(String(LIGHT2_ON))) {
      if (m_light2_state != true) {
        m_light2_state = true;
        setLightState();
        publishLightState();
      }
    } else if (payload.equals(String(LIGHT2_OFF))) {
      if (m_light2_state != false) {
        m_light2_state = false;
        setLightState();
        publishLightState();
      }
    }
    }
    if (String(MQTT_LIGHT3_COMMAND_TOPIC).equals(strtopic)) {
    // test if the payload is equal to "ON" or "OFF"
    if (payload.equals(String(LIGHT3_ON))) {
      if (m_light3_state != true) {
        m_light3_state = true;
        setLightState();
        publishLightState();
      }
    } else if (payload.equals(String(LIGHT3_OFF))) {
      if (m_light3_state != false) {
        m_light3_state = false;
        setLightState();
        publishLightState();
      }
    }
    }

    if (String(MQTT_LIGHT4_COMMAND_TOPIC).equals(strtopic)) {
    // test if the payload is equal to "ON" or "OFF"
    if (payload.equals(String(LIGHT4_ON))) {
      if (m_light4_state != true) {
        m_light4_state = true;
        setLightState();
        publishLightState();
      }
    } else if (payload.equals(String(LIGHT4_OFF))) {
      if (m_light4_state != false) {
        m_light4_state = false;
        setLightState();
        publishLightState();
      }
    }
}
 if (String(MQTT_LIGHT5_COMMAND_TOPIC).equals(strtopic)) {
    // test if the payload is equal to "ON" or "OFF"
    if (payload.equals(String(LIGHT5_ON))) {
      if (m_light5_state != true) {
        m_light5_state = true;
        setLightState();
        publishLightState();
      }
    } else if (payload.equals(String(LIGHT5_OFF))) {
      if (m_light5_state != false) {
        m_light5_state = false;
        setLightState();
        publishLightState();
      }
    }
  }

 if (String(MQTT_LIGHT6_COMMAND_TOPIC).equals(strtopic)) {
    // test if the payload is equal to "ON" or "OFF"
    if (payload.equals(String(LIGHT6_ON))) {
      if (m_light6_state != true) {
        m_light6_state = true;
        setLightState();
        publishLightState();
      }
    } else if (payload.equals(String(LIGHT6_OFF))) {
      if (m_light6_state != false) {
        m_light6_state = false;
        setLightState();
        publishLightState();
      }
    }
    }
    if (String(MQTT_LIGHT7_COMMAND_TOPIC).equals(strtopic)) {
    // test if the payload is equal to "ON" or "OFF"
    if (payload.equals(String(LIGHT7_ON))) {
      if (m_light7_state != true) {
        m_light7_state = true;
        setLightState();
        publishLightState();
      }
    } else if (payload.equals(String(LIGHT7_OFF))) {
      if (m_light7_state != false) {
        m_light7_state = false;
        setLightState();
        publishLightState();
      }
    }
    }

    if (String(MQTT_LIGHT8_COMMAND_TOPIC).equals(strtopic)) {
    // test if the payload is equal to "ON" or "OFF"
    if (payload.equals(String(LIGHT8_ON))) {
      if (m_light8_state != true) {
        m_light8_state = true;
        setLightState();
        publishLightState();
      }
    } else if (payload.equals(String(LIGHT8_OFF))) {
      if (m_light8_state != false) {
        m_light8_state = false;
        setLightState();
        publishLightState();
      }
    }
    }
     if (String(MQTT_LIGHT9_COMMAND_TOPIC).equals(strtopic)) {
    // test if the payload is equal to "ON" or "OFF"
    if (payload.equals(String(LIGHT9_ON))) {
      if (m_light9_state != true) {
        m_light9_state = true;
        setLightState();
        publishLightState();
      }
    } else if (payload.equals(String(LIGHT9_OFF))) {
      if (m_light9_state != false) {
        m_light9_state = false;
        setLightState();
        publishLightState();
      }
    }
  }

 if (String(MQTT_LIGHT10_COMMAND_TOPIC).equals(strtopic)) {
    // test if the payload is equal to "ON" or "OFF"
    if (payload.equals(String(LIGHT10_ON))) {
      if (m_light10_state != true) {
        m_light10_state = true;
        setLightState();
        publishLightState();
      }
    } else if (payload.equals(String(LIGHT10_OFF))) {
      if (m_light10_state != false) {
        m_light10_state = false;
        setLightState();
        publishLightState();
      }
    }
    }
    if (String(MQTT_LIGHT11_COMMAND_TOPIC).equals(strtopic)) {
    // test if the payload is equal to "ON" or "OFF"
    if (payload.equals(String(LIGHT11_ON))) {
      if (m_light11_state != true) {
        m_light11_state = true;
        setLightState();
        publishLightState();
      }
    } else if (payload.equals(String(LIGHT11_OFF))) {
      if (m_light11_state != false) {
        m_light11_state = false;
        setLightState();
        publishLightState();
      }
    }
    }

    if (String(MQTT_LIGHT12_COMMAND_TOPIC).equals(strtopic)) {
    // test if the payload is equal to "ON" or "OFF"
    if (payload.equals(String(LIGHT12_ON))) {
      if (m_light12_state != true) {
        m_light12_state = true;
        setLightState();
        publishLightState();
      }
    } else if (payload.equals(String(LIGHT12_OFF))) {
      if (m_light12_state != false) {
        m_light12_state = false;
        setLightState();
        publishLightState();
      }
    }
}
 if (String(MQTT_LIGHT13_COMMAND_TOPIC).equals(strtopic)) {
    // test if the payload is equal to "ON" or "OFF"
    if (payload.equals(String(LIGHT13_ON))) {
      if (m_light13_state != true) {
        m_light13_state = true;
        setLightState();
        publishLightState();
      }
    } else if (payload.equals(String(LIGHT13_OFF))) {
      if (m_light13_state != false) {
        m_light13_state = false;
        setLightState();
        publishLightState();
      }
    }
  }

 if (String(MQTT_LIGHT14_COMMAND_TOPIC).equals(strtopic)) {
    // test if the payload is equal to "ON" or "OFF"
    if (payload.equals(String(LIGHT14_ON))) {
      if (m_light14_state != true) {
        m_light14_state = true;
        setLightState();
        publishLightState();
      }
    } else if (payload.equals(String(LIGHT14_OFF))) {
      if (m_light14_state != false) {
        m_light14_state = false;
        setLightState();
        publishLightState();
      }
    }
    }
    if (String(MQTT_LIGHT15_COMMAND_TOPIC).equals(strtopic)) {
    // test if the payload is equal to "ON" or "OFF"
    if (payload.equals(String(LIGHT15_ON))) {
      if (m_light15_state != true) {
        m_light15_state = true;
        setLightState();
        publishLightState();
      }
    } else if (payload.equals(String(LIGHT15_OFF))) {
      if (m_light15_state != false) {
        m_light15_state = false;
        setLightState();
        publishLightState();
      }
    }
    }

    if (String(MQTT_LIGHT16_COMMAND_TOPIC).equals(strtopic)) {
    // test if the payload is equal to "ON" or "OFF"
    if (payload.equals(String(LIGHT16_ON))) {
      if (m_light16_state != true) {
        m_light16_state = true;
        setLightState();
        publishLightState();
      }
    } else if (payload.equals(String(LIGHT16_OFF))) {
      if (m_light16_state != false) {
        m_light16_state = false;
        setLightState();
        publishLightState();
      }
    }
}
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.println("INFO: Attempting MQTT connection...");
     swSer.println("INFO: Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(MQTT_CLIENT_ID, MQTT_USER, MQTT_PASSWORD)) {
      Serial.println("INFO: connected");
      swSer.println("INFO: connected");
      // Once connected, publish an announcement...
      publishLightState();
      // ... and resubscribe
      client.subscribe(MQTT_LIGHT1_COMMAND_TOPIC);
      client.subscribe(MQTT_LIGHT2_COMMAND_TOPIC);
      client.subscribe(MQTT_LIGHT3_COMMAND_TOPIC);
      client.subscribe(MQTT_LIGHT4_COMMAND_TOPIC);
      client.subscribe(MQTT_LIGHT5_COMMAND_TOPIC);
      client.subscribe(MQTT_LIGHT6_COMMAND_TOPIC);
      client.subscribe(MQTT_LIGHT7_COMMAND_TOPIC);
      client.subscribe(MQTT_LIGHT8_COMMAND_TOPIC);
      
      client.subscribe(MQTT_LIGHT9_COMMAND_TOPIC);
      client.subscribe(MQTT_LIGHT10_COMMAND_TOPIC);
      client.subscribe(MQTT_LIGHT11_COMMAND_TOPIC);
      client.subscribe(MQTT_LIGHT12_COMMAND_TOPIC);
      client.subscribe(MQTT_LIGHT13_COMMAND_TOPIC);
      client.subscribe(MQTT_LIGHT14_COMMAND_TOPIC);
      client.subscribe(MQTT_LIGHT15_COMMAND_TOPIC);
      client.subscribe(MQTT_LIGHT16_COMMAND_TOPIC);

    } else {
      Serial.print("ERROR: failed, rc=");
      Serial.print(client.state());
      Serial.println("DEBUG: try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  // init the serial
  Serial.begin(9600);
   swSer.begin(9600);

  // init the led
  pinMode(LED_PIN, OUTPUT);
  analogWriteRange(255);
  setLightState();
  swSer.println("");
  swSer.println("\nSoftware serial test started");
  swSer.println();

  // init the WiFi connection
  Serial.println();
  Serial.println();
  Serial.print("INFO: Connecting to ");
  WiFi.mode(WIFI_STA);
  Serial.println(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
WiFi.config(ip,dns, gateway, subnet);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("INFO: WiFi connected");
  Serial.print("INFO: IP address: ");
  Serial.println(WiFi.localIP());

  // init the MQTT connection
  client.setServer(MQTT_SERVER_IP, MQTT_SERVER_PORT);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}


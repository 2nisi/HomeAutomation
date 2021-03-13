// 2nisi's variables

char oldCommand[20];
char device[20] = "";
char oldDevice[20];
char WScommand[20];
char latestCommand[20];
bool miboxIsOn = false;
bool projectorIsOn = false;
/* IRremoteESP8266: IRsendDemo - demonstrates sending IR codes with IRsend.
 *
 * Version 1.1 January, 2019
 * Based on Ken Shirriff's IrsendDemo Version 0.1 July, 2009,
 * Copyright 2009 Ken Shirriff, http://arcfn.com
 *
 * An IR LED circuit *MUST* be connected to the ESP8266 on a pin
 * as specified by kIrLed below.
 *
 * TL;DR: The IR LED needs to be driven by a transistor for a good result.
 *
 * Suggested circuit:
 *     https://github.com/crankyoldgit/IRremoteESP8266/wiki#ir-sending
 *
 * Common mistakes & tips:
 *   * Don't just connect the IR LED directly to the pin, it won't
 *     have enough current to drive the IR LED effectively.
 *   * Make sure you have the IR LED polarity correct.
 *     See: https://learn.sparkfun.com/tutorials/polarity/diode-and-led-polarity
 *   * Typical digital camera/phones can be used to see if the IR LED is flashed.
 *     Replace the IR LED with a normal LED if you don't have a digital camera
 *     when debugging.
 *   * Avoid using the following pins unless you really know what you are doing:
 *     * Pin 0/D3: Can interfere with the boot/program mode & support circuits.
 *     * Pin 1/TX/TXD0: Any serial transmissions from the ESP8266 will interfere.
 *     * Pin 3/RX/RXD0: Any serial transmissions to the ESP8266 will interfere.
 *   * ESP-01 modules are tricky. We suggest you use a module with more GPIOs
 *     for your first time. e.g. ESP-12 etc.
 */

#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>

const uint16_t kIrLed = 4;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).

IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.

// IR codes for our commands
  // on/off of Projector
  uint16_t projector_on_off[115] = {3456, 1756,  448, 452,  390, 1312,  448, 422,  420, 450,  418, 476,  390,
  446,  420, 446,  420, 476,  390, 476,  388, 448,  420, 448,  420, 446,  418, 446,  420, 1314,  452,
  450,  388, 478,  390, 478,  390, 446,  420, 448,  420, 446,  422, 442,  424, 446,  422, 448,  418,
  1310,  454, 418,  446, 450,  392, 446,  420, 1312,  454, 418,  422, 444,  450, 1284,  450, 420,
  420, 446,  448, 450,  390, 476,  416, 450,  416, 422,  446, 418,  450, 418,  444, 452,  420, 1284,
  478, 420,  416, 1284,  482, 1254,  482, 1252,  484, 1250,  486, 382,  450, 448,  444, 1258,  486,
  414,  448, 1254,  486, 384,  476, 1256,  486, 1248,  486, 1248,  488, 1246,  488};
  
  uint16_t channel_1[71] = {9080, 4500,  582, 580,  560, 602,  560, 600,  562, 602,  562, 600,  562,
  594,  568, 594,  564, 1676,  592, 1650,  620, 1618,  624, 1616,  630, 1612,  630, 1610,  632, 1608,
  634, 1610,  632, 530,  632, 1610,  632, 528,  632, 528,  632, 530,  634, 528,  632, 526,  636, 528,
  632, 530,  632, 528,  632, 1606,  636, 1608,  632, 1608,  632, 1608,  632, 1608,  632, 1608,  632, 1606,  634, 39456,  9126, 2192,  628};
  
  uint16_t channel_2[71] = {9138, 4454,  632, 532,  630, 534,  626, 534,  628, 532,  632, 530,  630,
  532,  628, 532,  630, 1608,  632, 1610,  630, 1610,  632, 1610,  632, 1608,  634, 1610,  632, 1610,
  630, 1608,  634, 530,  632, 532,  630, 1608,  632, 532,  628, 558,  604, 556,  604, 530,  632, 528,
  632, 522,  640, 1610,  632, 530,  632, 1612,  630, 1610,  632, 1608,  632, 1610,  634, 1608,  634, 1608,  632, 39470,  9138, 2188,  634};
  
  uint16_t channel_on_off[71] = {9126, 4452,  632, 558,  602, 532,  628, 530,  630, 532,  630, 558,
  602, 530,  632, 530,  630, 1608,  632, 1608,  632, 1606,  634, 1608,  632, 1608,  632, 1610,  630,
  1606,  634, 1608,  634, 530,  632, 532,  628, 1608,  632, 558,  604, 530,  630, 1608,  632, 532,
  630, 530,  630, 532,  628, 1610,  632, 530,  630, 1608,  632, 1610,  632, 530,  630, 1610,  632, 1608,  632, 1610,  630, 39452,  9126, 2188,  632};


/*  HTTPS on ESP8266 with follow redirects, chunked encoding support
 *  Version 3.0
 *  Author: Sujay Phadke
 *  Github: @electronicsguy
 *  Copyright (C) 2018 Sujay Phadke <electronicsguy123@gmail.com>
 *  All rights reserved.
 *
 *  Example Arduino program
 */
bool cellVal = "";
#include <ESP8266WiFi.h>
#include "HTTPSRedirect.h"
#include "DebugMacros.h"
#include <ESP8266mDNS.h>
#include <WiFiClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

//Week Days
String weekDays[7]={"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

//Month names
String months[12]={"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};


// Fill ssid and password with your network credentials
const char* hostServerName = "home";
const char* ssid = "CoupDeBurst";
const char* password = "Kakaroto1988";

const char* host = "script.google.com";
// Replace with your own script id to make server side changes
const char *GScriptId = "AKfycbztur81HC3JhgLG2Z1np8_svmrPAUno5nyPnL-8sd2N4nJj7r0pbNdkON9zIluhxTTO";

const int httpsPort = 443;

// echo | openssl s_client -connect script.google.com:443 |& openssl x509 -fingerprint -noout
const char* fingerprint = "";
//const uint8_t fingerprint[20] = {};

// Write to Google Spreadsheet
String url = String("/macros/s/") + GScriptId + "/exec?value=Hello";
// Fetch Google Calendar events for 1 week ahead
String url2 = String("/macros/s/") + GScriptId + "/exec?cal";
// Read from Google Spreadsheet
String url3 = String("/macros/s/") + GScriptId + "/exec?read";

String payload_base =  "{\"command\": \"appendRow\", \
                    \"sheet_name\": \"Sheet1\", \
                    \"values\": ";
String payload = "";

HTTPSRedirect* clienT = nullptr;
// used to store the values of free stack and heap
// before the HTTPSRedirect object is instantiated
// so that they can be written to Google sheets
// upon instantiation
unsigned int free_heap_before = 0;
unsigned int free_stack_before = 0;

WiFiServer ESPserver(80);//Service Port
void setup() {

  // Initialize a NTPClient to get time
  timeClient.begin();
  // Set offset time in seconds to adjust for your timezone, for example:
  // GMT +1 = 3600
  // GMT +8 = 28800
  // GMT -1 = -3600
  // GMT 0 = 0
  timeClient.setTimeOffset(3600);

  irsend.begin();
  #if ESP8266
    Serial.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY);
  #else  // ESP8266
    Serial.begin(115200, SERIAL_8N1);
  #endif  // ESP8266

  // Below is the code of HTTPS connection - 2nisi
  
  Serial.begin(115200);
  Serial.flush();
  
  free_heap_before = ESP.getFreeHeap();
  free_stack_before = ESP.getFreeContStack();
  Serial.printf("Free heap: %u\n", free_heap_before);
  Serial.printf("Free stack: %u\n", free_stack_before);
  
  Serial.println();
  Serial.print("Connecting to wifi: ");
  Serial.println(ssid);
  // flush() is needed to print the above (connecting...) message reliably, 
  // in case the wireless connection doesn't go through
  Serial.flush();

  WiFi.begin(ssid, password);

  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());


  // Set up mDNS responder:
  // - first argument is the domain name, in this example
  //   the fully-qualified domain name is "home.local"
  // - second argument is the IP address to advertise
  //   we send our IP address on the WiFi network
  if (!MDNS.begin(hostServerName)) {
    Serial.println("Error setting up MDNS responder!");
    while (1) {
      delay(1000);
    }
  }
  Serial.println("mDNS responder started");

  // Start TCP (HTTP) server
  ESPserver.begin();
  Serial.println("TCP server started");

  // Add service to MDNS-SD
  MDNS.addService("http", "tcp", 80);


  // Use HTTPSRedirect class to create a new TLS connection
  clienT = new HTTPSRedirect(httpsPort);
  clienT->setInsecure();
  clienT->setPrintResponseBody(true);
  clienT->setContentTypeHeader("application/json");
  
  Serial.print("Connecting to ");
  Serial.println(host);

  // Try to connect for a maximum of 9 times
  bool flag = false;
  for (int i=0; i<9; i++){
    int retval = clienT->connect(host, httpsPort);
    if (retval == 1) {
       flag = true;
       break;
    }
    else
      Serial.println("Connection failed. Retrying...");
  }

  if (!flag){
    Serial.print("Could not connect to server: ");
    Serial.println(host);
    Serial.println("Exiting...");
    return;
  }

  // delete HTTPSRedirect object
  delete clienT;
  clienT = nullptr;

  

}

int serverManag = 10;
int serverDelay = 4000; // in milliseconds

void loop() {
  if (serverManag == 10){
      contactCommandServer();
      serverManag = 0;
    }
  webServer(oldCommand);
  serverManag ++;
  delay(serverDelay/10);                
}

void contactCommandServer(){
  static int error_count = 0;
  static int connect_count = 0;
  const unsigned int MAX_CONNECT = 20;
  static bool flag = false;
  //Serial.printf("Free heap: %u\n", ESP.getFreeHeap());
  //Serial.printf("Free stack: %u\n", ESP.getFreeContStack());
  
  if (!flag){
    free_heap_before = ESP.getFreeHeap();
    free_stack_before = ESP.getFreeContStack();
    clienT = new HTTPSRedirect(httpsPort);
    clienT->setInsecure();
    flag = true;
    clienT->setPrintResponseBody(false);
    clienT->setContentTypeHeader("application/json");
  }

  if (clienT != nullptr){
    if (!clienT->connected()){
      clienT->connect(host, httpsPort);
      //payload = payload_base + "\"" + free_heap_before + "," + free_stack_before + "\"}";
      //clienT->POST(url2, host, payload, false);
    }
  }
  else{
    DPRINTLN("Error creating client object!");
    error_count = 5;
  }

  if (connect_count > MAX_CONNECT){
    //error_count = 5;
    connect_count = 0;
    flag = false;
    delete clienT;
    return;
  }

  Serial.println("GET Data from cell 'A1':");
  if (cellVal = clienT->GET(url3, host)){
    clienT->getResponseBody().toCharArray(WScommand,(clienT->getResponseBody().length())-1);

    if(!(strcmp(WScommand,oldCommand)==0)){
      sendIrCommand(WScommand);
      strcpy(oldCommand, WScommand);
    }
    ++connect_count;
  }
  else{
    ++error_count;
    DPRINT("Error-count while connecting: ");
    DPRINTLN(error_count);
  }
  
  if (error_count > 3){
    Serial.println("Halting processor..."); 
    delete clienT;
    clienT = nullptr;
    Serial.printf("Final free heap: %u\n", ESP.getFreeHeap());
    Serial.printf("Final stack: %u\n", ESP.getFreeContStack());
    Serial.flush();
    //ESP.deepSleep(0);
    delay(30000);
  }
  
  // In my testing on a ESP-01, a delay of less than 1500 resulted 
  // in a crash and reboot after about 50 loop runs.
  }

void sendIrCommand(char* command){
    if (strcmp(command, "PS4") == 0){
      if (projectorIsOn == false){
        irsend.sendRaw(projector_on_off, 115, 38);  // Send a raw data capture at 38kHz.
        delay(500);
        projectorIsOn = true;
      }
      if (miboxIsOn == false){
        irsend.sendRaw(channel_on_off, 71, 38);  // Send a raw data capture at 38kHz.
        miboxIsOn = true;
        delay(1500);
        Serial.println("HDMI Port Is On");
      }
      irsend.sendRaw(channel_2, 71, 38);  // Send a raw data capture at 38kHz.
      Serial.println("Inside PS4");
      
    }else if(strcmp(command, "MiBox") == 0){
      if (projectorIsOn == false){
        irsend.sendRaw(projector_on_off, 115, 38);  // Send a raw data capture at 38kHz.
        delay(500);
        projectorIsOn = true;
      }
      if (miboxIsOn == false){
        irsend.sendRaw(channel_on_off, 71, 38);  // Send a raw data capture at 38kHz.
        miboxIsOn = true;
        delay(1500);
        Serial.println("HDMI Port Is On 2");
      }
      irsend.sendRaw(channel_1, 71, 38);  // Send a raw data capture at 38kHz.
      Serial.println("Inside MiBox");
    }
  
    if(strcmp(command, "ProjectorOff") == 0 && projectorIsOn == true){
      irsend.sendRaw(projector_on_off, 115, 38);  // Send a raw data capture at 38kHz.
      delay(1500);
      irsend.sendRaw(projector_on_off, 115, 38);  // Send a raw data capture at 38kHz.
      delay(200);
      projectorIsOn = false;
      irsend.sendRaw(channel_on_off, 71, 38);  // Send a raw data capture at 38kHz.
      miboxIsOn = false;
      Serial.println("Projector Off");
    }
    strcpy(latestCommand,command);
    
}

void webServer(char* runningDevice){

  timeClient.update();
  String weekDay = weekDays[timeClient.getDay()];
  char Day[weekDay.length()-1];
  weekDay.toCharArray(Day,sizeof(Day));
  int currentHour = timeClient.getHours();
  int currentMinute = timeClient.getMinutes();

  MDNS.update();
  // Check if a client has connected
  WiFiClient clientt = ESPserver.available();
  if (!clientt) 
  {
  return;
  }
  
  // Wait until the client sends some data
  Serial.println("new client");
  while(!clientt.available())
  {
  delay(1);
  }
  
  // Read the first line of the request
  String request = clientt.readStringUntil('\r');
  clientt.flush();
  delay(50);
  // Match the request
  int value = LOW;
  
  if (request.indexOf("/COMMAND=MiBox") != -1){
   strcpy(device, "MiBox");
  }else if (request.indexOf("/COMMAND=PS4") != -1){
    strcpy(device, "PS4");
  }else if (request.indexOf("/COMMAND=ProjectorOff") != -1){
    strcpy(device, "ProjectorOff");
  }

  if(!(strcmp(oldDevice,device)==0)){
      sendIrCommand(device);
      strcpy(oldDevice, device);
    }
  
  // Return the response
  clientt.println("HTTP/1.1 200 OK");
  clientt.println("Content-Type: text/html");
  clientt.println(""); //  IMPORTANT
  clientt.println("<!DOCTYPE HTML>");
  clientt.println("<html>");
  
  clientt.println("<head>");
    clientt.println("<base target='_top'><link rel='stylesheet' href='https://cdnjs.cloudflare.com/ajax/libs/materialize/1.0.0/css/materialize.min.css'><link href='https://fonts.googleapis.com/icon?family=Material+Icons' rel='stylesheet'><meta name='viewport' content='width=device-width, initial-scale=1.0'/>");
    clientt.println("<meta http-equiv='refresh' content='5;URL='>");
  clientt.println("</head>");
  
  clientt.println("<body>");
  clientt.println("<div class='container'>");
  clientt.println("<h2> Status of the Home Automation: </h2>");
  clientt.println("<div class='row'><div class='col s12' align='left'>");
  clientt.println("<a id='ps4' href=\"/COMMAND=PS4\"  class='btn waves-effect waves-light'>Switch to PS4<i class='material-icons right'>gamepad</i></a>");
  clientt.println("<a id='mibox' href=\"/COMMAND=MiBox\" class='btn waves-effect waves-light'>Switch to MiBox<i class='material-icons right'>cast</i></a>");
  clientt.println("<a id='projector' href=\"/COMMAND=ProjectorOff\" class='btn waves-effect waves-light'>Switch Projector Off<i class='material-icons right'>tv</i></a>");
  clientt.println("</div></div>");
  clientt.println("<br><br>");
  clientt.println("<div>");

  clientt.println("<div class='row'><div class='input-field col s3'><input id='lastCommand' type='text'>"); clientt.println(latestCommand); clientt.println("<label for='lastCommand'>Last Command</label></div><div class='input-field col s3'><input id='timeOfCommand' type='text'><label for='timeOfCommand'>Time of last Command</label></div></div>");
  
  clientt.println("Projector status: ");
  if(projectorIsOn == true){
    clientt.println("ON");
  }else{
    clientt.println("OFF"); 
  }
  clientt.println("<br><br>");
  
  clientt.println("HDMI Status: ");
  if(miboxIsOn == true){
    clientt.println("ON");
  }else{
    clientt.println("OFF"); 
  }
  clientt.println("<br><br>");

  clientt.println("</div>");
  
  clientt.println("<script src='https://cdnjs.cloudflare.com/ajax/libs/materialize/1.0.0/js/materialize.min.js'>");
  
  clientt.println("document.getElementById('timeOfCommand').value = "); clientt.println(weekDay); clientt.println(" at "); clientt.println(currentHour); clientt.println(":"); clientt.println(currentMinute); clientt.println(";");
  
  clientt.println("</script>");
  
  clientt.println("</body>");
  clientt.println("</html>");
  
  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");

}

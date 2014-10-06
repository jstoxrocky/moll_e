#include <SPI.h>
#include <WiFi.h>
//#include <SD.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"




char ssid[] = "Forbidden_Forest";      //  your network SSID (name) 
char pass[] = "6e6e6e6e6e";   // your network password
int keyIndex = 0;                 // your network key Index number (needed only for WEP)
//const int laser_pin = 8;
//const int chipSelect = 4;
int count = 0;
int status = WL_IDLE_STATUS;
WiFiServer server(80);

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *bMotor = AFMS.getMotor(1); //back
Adafruit_DCMotor *fMotor = AFMS.getMotor(4); //front
Adafruit_DCMotor *aMotor = AFMS.getMotor(3); //axel



void setup() {
  
  
      Serial.begin(9600);      // initialize serial communication
//      pinMode(laser_pin, OUTPUT);      // set the LED pin mode

        AFMS.begin();  // create with the default frequency 1.6KHz
      //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
      
      // Set the speed to start, from 0 (off) to 255 (max speed)
      fMotor->setSpeed(0);
      fMotor->run(FORWARD);
      fMotor->run(RELEASE);
    
      bMotor->setSpeed(0);
      bMotor->run(FORWARD);
      bMotor->run(RELEASE);
    
      aMotor->setSpeed(0);
      aMotor->run(FORWARD);
      aMotor->run(RELEASE);



      //SD card stuff
//      Serial.print("Initializing SD card...");
//      // see if the card is present and can be initialized:
//      if (!SD.begin(chipSelect)) {
//          Serial.println("Card failed, or not present");
//          // don't do anything more:
//          return;
//      }
//      Serial.println("card initialized."); 





      // check for the presence of the shield:
      if (WiFi.status() == WL_NO_SHIELD) {
        Serial.println("WiFi shield not present"); 
        while(true);        // don't continue
      } 


    // attempt to connect to Wifi network:
    while ( status != WL_CONNECTED) { 
          Serial.print("Attempting to connect to Network named: ");
          Serial.println(ssid);                   // print the network name (SSID);
    
          // Connect to WPA/WPA2 network. Change this line if using open or WEP network:    
          status = WiFi.begin(ssid, pass);
          // wait 10 seconds for connection:
          delay(10000);
    } 
    
  server.begin();                           // start the web server on port 80
  printWifiStatus();                        // you're connected now, so print out the status
  
}


void loop() {
      // listen for incoming clients
      WiFiClient client = server.available();
      if (client) {
          Serial.println("new client");
    
          // an http request ends with a blank line
          boolean currentLineIsBlank = true;
          while (client.connected()) {
              if (client.available()) {
                  char c = client.read();
        
                  // if you've gotten to the end of the line (received a newline
                  // character) and the line is blank, the http request has ended,
                  // so you can send a reply
                  if (c == '\n' && currentLineIsBlank) {
                  // send a standard http response header
                      
                      
                      String POST = "";
                      
                      while(client.available()){

                          c = client.read();
                          // save the variables somewhere
                          POST += c;
                      }
                       
                          Serial.println(POST);
                      
                          uint8_t i;
                          int del = 200;
                          int spe = 100;
                          
                          if((POST == "aw") || (POST == "wa")){
                              aMotor->run(BACKWARD);
                              fMotor->run(FORWARD);
                              bMotor->run(FORWARD);
                              aMotor->setSpeed(255);
                              fMotor->setSpeed(spe); 
                              bMotor->setSpeed(spe);  
                          }
                          else if((POST == "dw") || (POST == "wd")){
                              aMotor->run(FORWARD);
                              fMotor->run(FORWARD);
                              bMotor->run(FORWARD);
                              aMotor->setSpeed(255);
                              fMotor->setSpeed(spe); 
                              bMotor->setSpeed(spe);  
                          }
                          else if((POST == "as") || (POST == "sa")){
                              aMotor->run(BACKWARD);
                              fMotor->run(BACKWARD);
                              bMotor->run(BACKWARD);
                              aMotor->setSpeed(255);
                              fMotor->setSpeed(spe); 
                              bMotor->setSpeed(spe);  
                          }
                          else if((POST == "ds") || (POST == "sd")){
                              aMotor->run(FORWARD);
                              fMotor->run(BACKWARD);
                              bMotor->run(BACKWARD);
                              aMotor->setSpeed(255);
                              fMotor->setSpeed(spe); 
                              bMotor->setSpeed(spe);  
                          }
                          else if(POST == "w"){
                              aMotor->run(FORWARD);
                              fMotor->run(FORWARD);
                              bMotor->run(FORWARD);
                              aMotor->setSpeed(0);
                              fMotor->setSpeed(spe); 
                              bMotor->setSpeed(spe);  
                          }
                          else if(POST == "s"){
                              aMotor->run(BACKWARD);
                              fMotor->run(BACKWARD);
                              bMotor->run(BACKWARD);
                              aMotor->setSpeed(0); 
                              fMotor->setSpeed(spe); 
                              bMotor->setSpeed(spe);  

                              
                          }
                          else if(POST == "stop"){
                              aMotor->setSpeed(0); 
                              fMotor->setSpeed(0); 
                              bMotor->setSpeed(0);
                              aMotor->run(RELEASE);
                              fMotor->run(RELEASE);
                              bMotor->run(RELEASE);
                          }
        
          
                      
                      
          
                      //load html/css/js for website only once
                      if (count <= 0){
                        
                          client.println("HTTP/1.1 200 OK");
                          client.println("Content-Type: text/html");
                          client.println("Connection: close");  // the connection will be closed after completion of the response
	                  //client.println("Refresh: 5");  // refresh the page automatically every 5 sec
                          client.println();
                          client.println("<!DOCTYPE html>");
                          client.println("<html>");
                          client.println("<head>");
                          client.println("<script src='http://ajax.googleapis.com/ajax/libs/jquery/1.10.2/jquery.min.js'></script>");
                          client.println("<script src='https://rawgit.com/joestox/moll_e/master/script.js'></script>");
                          client.println("</head>");
                          client.println("</html>");
                      }
                    
                      count = 1;
                      break;
               
                  }
              
                  if (c == '\n') {
                      // you're starting a new line
                      currentLineIsBlank = true;
                  } 
                  else if (c != '\r') {
                      // you've gotten a character on the current line
                      currentLineIsBlank = false;
                  }
              }
          }
          // give the web browser time to receive the data
          
          if (count == 0){
            delay(1);
          }
          else{
            delay(1);
          }
          count=1;
          
          // close the connection:
          client.stop();
          Serial.println("client disonnected");
      } 
}


void printWifiStatus() {
  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
}

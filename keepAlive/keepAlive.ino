#include <SPI.h>
#include <WiFi.h>

//Connection THings
char ssid[] = "Forbidden_Forest";      //  your network SSID (name) 
char pass[] = "6e6e6e6e6e";   // your network password
int keyIndex = 0;                 // your network key Index number (needed only for WEP)
int count = 0;
int status = WL_IDLE_STATUS;
WiFiServer server(80);


void setup() {
	
			Serial.begin(9600);      // initialize serial communication

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
					Serial.println("client exists");
		
					// an http request ends with a blank line
					boolean currentLineIsBlank = true;
					
					while (client.connected()) {
						
//							Serial.println("client connected");

							if (client.available()) {
									
//									Serial.println("client available");

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
										    
										    if (POST=="1"){
										    	Serial.println("page loaded");
										    	count = 1;

										    }
          
											

											//load html/css/js for website only once
											if (count < 1){
												
													Serial.println("sending data to client");
													client.println("HTTP/1.1 200 OK");
													client.println("Content-Type: text/html");
//                          client.println("Connection: close");  // the connection will be closed after completion of the response
													client.println("Connection: keep-alive");

													//client.println("Refresh: 5");  // refresh the page automatically every 5 sec
													client.println();
													client.println("<!DOCTYPE html>");
													client.println("<html>");
													client.println("<head>");
													client.println("<script src='http://ajax.googleapis.com/ajax/libs/jquery/1.10.2/jquery.min.js'></script>");
													client.println("<script src='https://rawgit.com/joestox/moll_e/master/script.js'></script>");
													client.println("</head>");
													client.println("</html>");
//                                                                                                        delay(1000);
											}
										
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
							} // if client is available

//							delay(100);

					} //while client is connected

					// give the web browser time to receive the data
                     delay(100);

                                        
					// close the connection:
//                                        if (count <= 1){
//                                        Serial.println(count);
                                        client.stop();
                			Serial.println("client disonnected");
//                                        }
					
			} 

}


void printWifiStatus() {
	// print your WiFi shield's IP address:
	IPAddress ip = WiFi.localIP();
	Serial.print("IP Address: ");
	Serial.println(ip);
}



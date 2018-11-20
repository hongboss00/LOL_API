#include <JsonListener.h>
#include <ESP8266WiFi.h>
#include <Wire.h>

#include "ssd1306_i2c.h"
#include "font.h"
#include "TimeClient.h"



void setup()
{
	WiFi.begin("Home", "");


	WiFiClient client;
	const int httpPort = 80;
	if (!client.connect("www.google.com", httpPort)) {
		Serial.println("connection failed");
		return;
	}

	// This will send the request to the server
	client.print(String("GET / HTTP/1.1\r\n") +
		String("Host: www.google.com\r\n") +
		String("Connection: close\r\n\r\n"));
	int repeatCounter = 0;
	while (!client.available() && repeatCounter < 10) {
		delay(1000);
		Serial.println(".");
		repeatCounter++;
	}

	String line;

	int size = 0;
	client.setNoDelay(false);
	while (client.connected()) {
		while ((size = client.available()) > 0) {
			line = client.readString();
			Serial.print(line);
		}
	}


}


void loop()
{


}

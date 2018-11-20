#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include "lol_api_client.h"

LOL_API::LOL_API(boolean) {

}

void LOL_API::doupdate(String url) {
	JsonStreamingParser parser;
	parser.setListener(this);
	WiFiClient client;
	const int httpPort = 80;
	if (!client.connect("api.wunderground.com", httpPort)) {
		Serial.println("connection failed");
		return;          //void형태이므로 retturn값없이 그냥 함수를 종료함을 나타냄 즉 있으나 마나.
	}

	Serial.print("Requesting URL: ");
	Serial.println(url);

	// This will send the request to the server
	client.print(String("GET ") + url + " HTTP/1.1\r\n" +
		"Host: api.wunderground.com\r\n" +
		"Connection: close\r\n\r\n");
	int retryCounter = 0;
	while (!client.available()) {
		delay(1000);
		retryCounter++;
		if (retryCounter > 10) {
			return;
		}
	}

	int pos = 0;
	boolean isBody = false;
	char c;

	int size = 0;
	client.setNoDelay(false);
	// while(client.connected()) {
	do {
		while ((size = client.available()) > 0) {
			c = client.read();
			if (c == '{' || c == '[') {
				isBody = true;
			}
			if (isBody) {
				parser.parse(c);
			}
		}
	} while (client.connected());

}

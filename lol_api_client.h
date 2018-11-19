//LOL_API_CLIENT.h by.hongboss
#include <JsonListener.h>
#include <JsonStreamingParser.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

class LOL_API : public JsonListener {
private:
	String URL;
	void doupdate(String url);
public:
	LOL_API(boolean );
	String summonerChampion();
	String getTier();
	String getMatchList();     //last 10 match available
	String getMatchTime();
	String getSpellTime();

};
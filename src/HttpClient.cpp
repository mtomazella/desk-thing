#include "HttpClient.hpp"
#include "Config.hpp"

void HttpClient::init()
{
  WiFi.setHostname(_deviceName);
  WiFi.mode(WIFI_STA);
  WiFi.begin(_ssid, _password);

  PRINTS("Connecting to WiFi SSID: ");
  PRINTS(_ssid);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    PRINTS(".");
  }

  PRINTS("Connected to WiFi");
}

void HttpClient::maintainConnection()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    PRINTS("WiFi connection lost. Reconnecting...");
    WiFi.disconnect();
    WiFi.begin(_ssid, _password);

    while (WiFi.status() != WL_CONNECTED)
    {
      delay(500);
      PRINTS(".");
    }

    PRINTS("Reconnected to WiFi");
  }
}

int HttpClient::getTime()
{
  client.begin("https://time.now/developer/api/time?timezone=America%2FSao_Paulo");
  int httpCode = client.GET();

  if (httpCode < 0 || httpCode != HTTP_CODE_OK)
  {
    PRINTS(F("HTTP GET request failed, error: "));
    PRINTS(httpCode);
    PRINTS(String(client.errorToString(httpCode)).c_str());
    return -1;
  }

  JsonDocument filter;
  filter["unixtime"] = true;
  JsonDocument time;
  deserializeJson(time, client.getString(), DeserializationOption::Filter(filter));

  return time["unixtime"].as<long>();
}
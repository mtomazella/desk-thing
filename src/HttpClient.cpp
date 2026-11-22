#include "HttpClient.hpp"

void HttpClient::init()
{
  WiFi.setHostname(_deviceName);
  WiFi.mode(WIFI_STA);
  WiFi.begin(_ssid, _password);

  Serial.print(F("Connecting to WiFi SSID: "));
  Serial.println(_ssid);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(F("."));
  }

  Serial.println("Connected to WiFi");
}

void HttpClient::maintainConnection()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("WiFi connection lost. Reconnecting...");
    WiFi.disconnect();
    WiFi.begin(_ssid, _password);

    while (WiFi.status() != WL_CONNECTED)
    {
      delay(500);
      Serial.print(F("."));
    }

    Serial.println("Reconnected to WiFi");
  }
}

int HttpClient::getTime()
{
  client.begin("https://time.now/developer/api/time?timezone=America%2FSao_Paulo");
  int httpCode = client.GET();

  if (httpCode < 0 || httpCode != HTTP_CODE_OK)
  {
    Serial.print(F("HTTP GET request failed, error: "));
    Serial.print(httpCode);
    Serial.println(client.errorToString(httpCode));
    return -1;
  }

  JsonDocument filter;
  filter["unixtime"] = true;
  JsonDocument time;
  deserializeJson(time, client.getString(), DeserializationOption::Filter(filter));

  return time["unixtime"].as<long>();
}
#pragma once
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

class HttpClient
{
public:
  HttpClient(
      const char *deviceName,
      const char *ssid, const char *password)
      : _deviceName(deviceName),
        _ssid(ssid),
        _password(password) {}

  void init();
  void maintainConnection();

  int getTime();

private:
  HTTPClient client;
  const char *_deviceName;
  const char *_ssid;
  const char *_password;
};
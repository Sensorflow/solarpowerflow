#include "Sensor.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#ifndef DALLAS_TEMPERATURE_SENSOR_H
#define DALLAS_TEMPERATURE_SENSOR_H


class DallasTemperatureSensor: public Sensor {
public:
  DallasTemperatureSensor(DeviceAddress address, int pin, int precision = 9, String name = "");
  const char* getName();
  float* getValues(unsigned int quantities, unsigned int * readValues);
  static const char* getType();
  static Sensor* fromConfig(void *);
  static OneWire *oneWire_;
  static DallasTemperature *sensor_;
  static int lastRequest_; //To call only one temp request on every read wave
private:
  char name_[10];
  float values_[4];
  DeviceAddress address_;
  int localLastRequest_;
};


#endif //SENSOR_MONITOR_DEVICE_H

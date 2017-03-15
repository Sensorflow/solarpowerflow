//
// Created by alvaro on 8/08/15.
//

#include "DallasTemperatureSensor.h"

OneWire* DallasTemperatureSensor::oneWire_ = 0;
DallasTemperature* DallasTemperatureSensor::sensor_ = 0;
int DallasTemperatureSensor::lastRequest_ = 1; //Value 0 is reserved to detect overflow

DallasTemperatureSensor::DallasTemperatureSensor(DeviceAddress address, int pin, int precision, String name){
  localLastRequest_ = 1;

  for(int i = 0; i < 8; i++){
    address_[i] = address[i];
  }

  // Initialize if needed
  if(oneWire_ == 0){
    oneWire_ = new OneWire(pin);
    sensor_ = new DallasTemperature(DallasTemperatureSensor::oneWire_);
  }

  sensor_->setResolution(address_, precision);

  if(name.length() == 0){
    sprintf(name_, "dallas_%d",pin);
  } else {
    strcpy(name_, name.c_str());
  }
}

const char * DallasTemperatureSensor::getName(){
    return name_;
}

const char * DallasTemperatureSensor::getType(){
    return "DallasTemperature";
}


float * DallasTemperatureSensor::getValues(unsigned int quantities, unsigned int * readValues){
  // lastRequest_ is 0 when overflow
 if(localLastRequest_ < lastRequest_ || lastRequest_ == 0){
    //Last read was not consumed
    localLastRequest_ = lastRequest_;
    //Now on next read a new request will be done (unless another sensor has already requested it)
  } else{
    // Last request was consumed
    lastRequest_++;
    localLastRequest_ = lastRequest_;
    sensor_->requestTemperatures();
  }

  values_[0] = sensor_->getTempC(address_);
  *readValues = 1;
  return values_;
}

Sensor * DallasTemperatureSensor::fromConfig(void *data){
  DeviceAddress address;
  int pin = 1;
  DallasTemperatureSensor *s = new DallasTemperatureSensor(address, pin);
  return (Sensor *)s;

}

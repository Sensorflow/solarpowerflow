//
// Created by alvaro on 8/08/15.
//

#include "BH1750Sensor.h"

BH1750Sensor::BH1750Sensor(int address, String name){
  sensor_ = new BH1750(address);
  sensor_->begin(BH1750_CONTINUOUS_HIGH_RES_MODE);
  if(name.length() == 0){
    sprintf(name_, "bh1750_%02X",address);
  } else {
    strcpy(name_, name.c_str());
  }
}

const char * BH1750Sensor::getName(){
    return name_;
}

const char * BH1750Sensor::getType(){
    return "BH1750";
}


float * BH1750Sensor::getValues(unsigned int quantities, unsigned int * readValues){
  values_[0] = (float)sensor_->readLightLevel();
  *readValues = 1;
  return values_;
}

Sensor * BH1750Sensor::fromConfig(void *data){

  BH1750Sensor *s = new BH1750Sensor();
  return (Sensor *)s;

}

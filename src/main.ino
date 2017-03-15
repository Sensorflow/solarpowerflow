#include <SensorflowListener.h>
#include <INA219Sensor.h>
#include <BH1750Sensor.h>
#include <DallasTemperatureSensor.h>

#define INTERRUPT_PIN 2
#define WAKE_PIN 3
#define MAX485_WRITE_PIN 13

#define DALLAS_TEMPERATURE_PIN 5
#define DALLAS_TEMPERATURE_PRECISION 9
SensorflowListener listener(&Serial, INTERRUPT_PIN, WAKE_PIN, MAX485_WRITE_PIN);

void setup() {
  Serial.begin(115200);

  Sensor *s;
  s = new INA219Sensor(0x40, "p1");
  listener.devices[s->getName()] = s;
  s = new INA219Sensor(0x41, "p2");
  listener.devices[s->getName()] = s;
  s = new INA219Sensor(0x44, "p3");
  listener.devices[s->getName()] = s;

  s = new BH1750Sensor(0x23, "ligth");
  listener.devices[s->getName()] = s;


  DeviceAddress address[] = {
    { 0x28, 0xD8, 0x7C, 0x88, 0x6, 0x0, 0x0, 0x23 }, //negro
    { 0x28, 0x64, 0xC9, 0x88, 0x6, 0x0, 0x0, 0xC4 }, //azul
    { 0x28, 0x61, 0x6B, 0x88, 0x6, 0x0, 0x0, 0x9F },//rojo
    { 0x28, 0x4D, 0x78, 0x87, 0x6, 0x0, 0x0, 0xFC } //Amarillo
  };
  s = new DallasTemperatureSensor(address[0], DALLAS_TEMPERATURE_PIN, DALLAS_TEMPERATURE_PRECISION, "t1");
  listener.devices[s->getName()] = s;
  s = new DallasTemperatureSensor(address[1], DALLAS_TEMPERATURE_PIN, DALLAS_TEMPERATURE_PRECISION, "t2");
  listener.devices[s->getName()] = s;
  s = new DallasTemperatureSensor(address[2], DALLAS_TEMPERATURE_PIN, DALLAS_TEMPERATURE_PRECISION, "t3");
  listener.devices[s->getName()] = s;
  s = new DallasTemperatureSensor(address[3], DALLAS_TEMPERATURE_PIN, DALLAS_TEMPERATURE_PRECISION, "t4");
  listener.devices[s->getName()] = s;

  listener.online();

}

void loop() {
  // put your main code here, to run repeatedly:
  listener.next(false);
}

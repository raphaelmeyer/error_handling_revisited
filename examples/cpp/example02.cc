#include <iostream>

struct Volume { int ml; };
struct Moisture { int percentage; };
struct Temperature { double celsius; };

class ThermoSensor {
public:
  bool read(Temperature & temperature) {
    temperature.celsius = 21.5;
    // return false;
    return true;
  }
};

class MoistureSensor {
public:
  bool read(Moisture & moisture) {
    moisture.percentage = 40;
    // return false;
    return true;
  }
};

class Pump {
public:
  bool pump(Volume amount) {
    // return false;
    return true;
  }
};

class WateringSystem {
public:
  bool water(Volume & amount) {
    Moisture moisture;
    if(moisture_sensor.read(moisture)) {
      Temperature temperature;
      if(thermo_sensor.read(temperature)) {
        if(calculate_amount(moisture, temperature, amount)) {
          if(pump.pump(amount)) {
            return true;
          }
        }
      }
    }
    return false;
  }

private:
  bool calculate_amount(Moisture moisture, Temperature temperature, Volume & amount) {
    amount.ml = 178;
    return true;
  }

  MoistureSensor moisture_sensor;
  ThermoSensor thermo_sensor;
  Pump pump;
};

int main() {
  Volume amount;
  if(WateringSystem{}.water(amount)) {
    std::cout << "Water " << amount.ml << " ml\n";
  } else {
    std::cout << "Watering error\n";
  }
}

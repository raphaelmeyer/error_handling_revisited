#include <iostream>

struct Volume { int ml; };
struct Moisture { int percentage; };
struct Temperature { double celsius; };

class ThermoSensor {
public:
  bool read(Temperature & temperature) {
    temperature.celsius = 21.5;
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
  bool pump(Volume amount) { return true; }
};

class WateringSystem {
public:
  bool water(Volume & amount) {
    Moisture moisture;
    if(not moisture_sensor.read(moisture)) {
      return false;
    }
    Temperature temperature;
    if(not thermo_sensor.read(temperature)) {
      return false;
    }
    if(not calculate_amount(moisture, temperature, amount)) {
      return false;
    }
    if(not pump.pump(amount)) {
      return false;
    }
    return true;
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

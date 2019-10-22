#include <iostream>

struct Volume { int ml; };
struct Moisture { int percentage; };
struct Temperature { double celsius; };

class ThermoSensor {
public:
  Temperature read() { return {21.5}; }
};

class MoistureSensor {
public:
  Moisture read() { return {40}; }
};

class Pump {
public:
  void pump(Volume amount) {}
};

class WateringSystem {
public:
  Volume water() {
    auto const moisture = moisture_sensor.read();
    auto const temperature = thermo_sensor.read();
    auto const amount = calculate_amount(moisture, temperature);
    pump.pump(amount);
    return amount;
  }

private:
  Volume calculate_amount(Moisture moisture, Temperature temperature) {
    return {178};
  }

  MoistureSensor moisture_sensor;
  ThermoSensor thermo_sensor;
  Pump pump;
};

int main() {
  const auto amount = WateringSystem{}.water();
  std::cout << "Water " << amount.ml << " ml\n";
}

#include <stdexcept>
#include <iostream>

struct Volume { int ml; };
struct Moisture { int percentage; };
struct Temperature { double celsius; };

class SensorError : public std::runtime_error {
  using std::runtime_error::runtime_error;
};
class PumpError : public std::runtime_error {
  using std::runtime_error::runtime_error;
};
class WateringError : public std::runtime_error {
  using std::runtime_error::runtime_error;
};

class ThermoSensor {
public:
  Temperature read() {
    // throw SensorError{"Temperature sensor error"};
    return {21.5};
  }
};

class MoistureSensor {
public:
  Moisture read() {
    // throw SensorError{"Moisture sensor error"};
    return {40};
  }
};

class Pump {
public:
  void pump(Volume amount) {
    // throw PumpError{"Pump error"};
  }
};

class WateringSystem {
public:
  Volume water() {
    try {
      auto const moisture = moisture_sensor.read();
      auto const temperature = thermo_sensor.read();
      auto const amount = calculate_amount(moisture, temperature);
      pump.pump(amount);
      return amount;
    } catch(SensorError const & e) {
      throw WateringError{e.what()};
    } catch(PumpError const & e) {
      throw WateringError{"Pump error"};
    }
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
  try {
    auto const amount = WateringSystem{}.water();
    std::cout << "Water " << amount.ml << " ml\n";
  } catch(std::runtime_error const & e) {
    std::cout << e.what() << "\n";
  }
}

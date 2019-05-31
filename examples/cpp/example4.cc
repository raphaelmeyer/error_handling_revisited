#include <stdexcept>

class Volume {};
class Moisture {};
class Temperature {};

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
  Temperature read() { return {}; }
};

class MoistureSensor {
public:
  Moisture read() { return {}; }
};

class Pump {
public:
  void pump(Volume amount) {}
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
    } catch (SensorError const &) {
      throw WateringError{"..."};
    } catch (PumpError const &) {
      throw WateringError{"..."};
    }
  }

private:
  Volume calculate_amount(Moisture moisture, Temperature temperature) {
    return {};
  }

  MoistureSensor moisture_sensor;
  ThermoSensor thermo_sensor;
  Pump pump;
};

int main() {
  WateringSystem system;
  system.water();
}

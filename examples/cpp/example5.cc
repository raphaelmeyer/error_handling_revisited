#include <optional>

class Volume {};
class Moisture {};
class Temperature {};

class ThermoSensor {
public:
  std::optional<Temperature> read() { return Temperature{}; }
};

class MoistureSensor {
public:
  std::optional<Moisture> read() { return Moisture{}; }
};

class Pump {
public:
  bool pump(Volume amount) { return true; }
};

class WateringSystem {
public:
  std::optional<Volume> water() {
    auto const moisture = moisture_sensor.read();
    if (not moisture) {
      return std::nullopt;
    }
    auto const temperature = thermo_sensor.read();
    if (not temperature) {
      return std::nullopt;
    }
    auto const amount = calculate_amount(moisture.value(), temperature.value());
    if (not pump.pump(amount)) {
      return std::nullopt;
    }
    return amount;
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

#include <iostream>
#include <optional>

struct Volume { int ml; };
struct Moisture { int percentage; };
struct Temperature { double celsius; };

class ThermoSensor {
public:
  std::optional<Temperature> read() {
    // return std::nullopt;
    return Temperature{21.5};
  }
};

class MoistureSensor {
public:
  std::optional<Moisture> read() {
    // return std::nullopt;
    return Moisture{40};
  }
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
    if (not amount) {
      return std::nullopt;
    }
    if (not pump.pump(amount.value())) {
      return std::nullopt;
    }
    return amount;
  }

private:
  std::optional<Volume> calculate_amount(Moisture moisture, Temperature temperature) {
    return Volume{178};
  }

  MoistureSensor moisture_sensor;
  ThermoSensor thermo_sensor;
  Pump pump;
};

int main() {
  auto const amount = WateringSystem{}.water();
  if (amount) {
    std::cout << "Water " << amount.value().ml << " ml\n";
  } else {
    std::cout << "Watering error\n";
  }
}

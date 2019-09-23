#include <optional>
#include <variant>
#include <iostream>

template <class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template <class... Ts> overloaded(Ts...)->overloaded<Ts...>;

class Volume {};
class Moisture {};
class Temperature {};
class Error {};

class ThermoSensor {
public:
  std::variant<Error, Temperature> read() { return Temperature{}; }
};

class MoistureSensor {
public:
  std::variant<Error, Moisture> read() { return Moisture{}; }
};

class Pump {
public:
  std::optional<Error> pump(Volume amount) { return std::nullopt; }
};

class WateringSystem {
public:
  std::variant<Error, Volume> water() {
    auto const moisture = moisture_sensor.read();
    if(auto const error = std::get_if<Error>(&moisture); error) {
      return *error;
    }

    auto const temperature = thermo_sensor.read();
    if(auto const error = std::get_if<Error>(&temperature); error) {
      return *error;
    }

    auto const amount = calculate_amount(std::get<Moisture>(moisture),
                                         std::get<Temperature>(temperature));

    if(auto const error = pump.pump(amount); error) {
      return error.value();
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
  auto const result = system.water();
  auto const amount = std::get_if<Volume>(&result);
  if (amount) {
    std::cout << "Amount = ...\n";
  } else {
    std::cout << "Error!\n";
  }

}

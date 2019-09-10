#include <optional>
#include <variant>

#include <iostream>

template <class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template <class... Ts> overloaded(Ts...)->overloaded<Ts...>;

class Error {};

class Volume {};
class Moisture {};
class Temperature {};

template <typename T>
using Result = std::variant<Error, T>;

using Amount = Result<Volume>;

class ThermoSensor {
public:
  Result<Temperature> read() { return Temperature{}; }
};

class MoistureSensor {
public:
  Result<Moisture> read() { return Moisture{}; }
};

class Pump {
public:
  std::optional<Error> pump(Volume amount) { return std::nullopt; }
};

class WateringSystem {
public:
  Amount water() {
    auto const moisture = moisture_sensor.read();
    return std::visit(overloaded{
      [](Error const &e) { return Amount{e}; },
      [&](Moisture const &moisture) {
        auto const temperature = thermo_sensor.read();
        return std::visit(overloaded{
          [](Error const &e) { return Amount{e}; },
          [&](Temperature const &temperature) {
            auto const amount =
              calculate_amount(moisture, temperature);
              auto const pump_error = pump.pump(amount);
              if (pump_error) {
                return Amount{pump_error.value()};
              }
              return Amount{amount};
          }}, temperature);
      }}, moisture);
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
  auto const result = system.water();
  auto const amount = std::get_if<Volume>(&result);
  if (amount) {
    std::cout << "Amount = ...\n";
  } else {
    std::cout << "Error!\n";
  }
}
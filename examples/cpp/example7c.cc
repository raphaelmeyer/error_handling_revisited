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
  Result<std::monostate> pump(Volume amount) { return std::monostate{}; }
};

class WateringSystem {
public:
  Amount water() {
    return std::visit(overloaded{
      [](Error const & e) { return Amount{e}; },
      [&](Moisture const &moisture) {
        return std::visit(overloaded{
          [](Error const & e) { return Amount{e}; },
          [&](Temperature const &temperature) {
            auto const amount = calculate_amount(moisture, temperature);
            return std::visit(overloaded{
              [](Error const & e) { return Amount{e}; },
              [&](auto const & _) { return Amount{amount}; }
            }, pump.pump(amount));
          }}, thermo_sensor.read());
      }}, moisture_sensor.read());
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

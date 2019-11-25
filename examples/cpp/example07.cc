#include <iostream>
#include <variant>

template <class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template <class... Ts> overloaded(Ts...)->overloaded<Ts...>;

struct Volume { int ml; };
struct Moisture { int percentage; };
struct Temperature { double celsius; };
struct Error { std::string what; };

template <typename T>
using Result = std::variant<T, Error>;

using Amount = Result<Volume>;

class ThermoSensor {
public:
  Result<Temperature> read() {
    // return Error{"Temperature sensor error"};
    return Temperature{21.5};
  }
};

class MoistureSensor {
public:
  Result<Moisture> read() {
    // return Error{"Moisture sensor error"};
    return Moisture{40};
   }
};

class Pump {
public:
  Result<std::monostate> pump(Volume amount) {
    // return Error{"Pump error"};
    return std::monostate{};
  }
};

class WateringSystem {
public:
  Amount water() {
    auto const moisture = moisture_sensor.read();
    return std::visit(overloaded{
      [](Error const & e) { return Amount{e}; },
      [&](Moisture const & moisture) {
        auto const temperature = thermo_sensor.read();
        return std::visit(overloaded{
          [](Error const & e) { return Amount{e}; },
          [&](Temperature const & temperature) {
            auto const amount = calculate_amount(moisture, temperature);
            return std::visit(overloaded{
              [](Error const & e) { return Amount{e}; },
              [&](Volume const & amount) {
                auto const pump_result = pump.pump(amount);
                return std::visit(overloaded{
                  [](Error const & e) { return Amount{e}; },
                  [&](auto const &) { return Amount{amount}; }
                }, pump_result);
            }}, amount);
        }}, temperature);
    }}, moisture);
  }

private:
  Result<Volume> calculate_amount(Moisture moisture, Temperature temperature) {
    return Volume{178};
  }

  MoistureSensor moisture_sensor;
  ThermoSensor thermo_sensor;
  Pump pump;
};

int main() {
  auto const result = WateringSystem{}.water();
  std::visit(overloaded{
    [](Volume const & amount) {
      std::cout << "Water " << amount.ml << " ml\n"; },
    [](Error const & error) {
      std::cout << error.what << "\n"; }
  }, result);
}

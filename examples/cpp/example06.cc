#include <iostream>
#include <optional>
#include <variant>

template <class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template <class... Ts> overloaded(Ts...)->overloaded<Ts...>;

struct Volume { int ml; };
struct Moisture { int percentage; };
struct Temperature { double celsius; };
struct Error { std::string what; };

class ThermoSensor {
public:
  std::variant<Temperature, Error> read() {
    // return Error{"Temperature sensor error"};
    return Temperature{21.5};
  }
};

class MoistureSensor {
public:
  std::variant<Moisture, Error> read() {
    // return Error{"Moisture sensor error"};
    return Moisture{40};
  }
};

class Pump {
public:
  std::optional<Error> pump(Volume amount) {
    // return Error{"Pump error"};
    return std::nullopt;
  }
};

class WateringSystem {
public:
  std::variant<Volume, Error> water() {
    auto const moisture = moisture_sensor.read();
    if (auto const error = std::get_if<Error>(&moisture); error) {
      return *error;
    }

    auto const temperature = thermo_sensor.read();
    if (auto const error = std::get_if<Error>(&temperature); error) {
      return *error;
    }

    auto const amount = calculate_amount(std::get<Moisture>(moisture), std::get<Temperature>(temperature));
    if (auto const error = std::get_if<Error>(&amount); error) {
      return *error;
    }

    if (auto const pump_error = pump.pump(std::get<Volume>(amount)); pump_error) {
      return pump_error.value();
    }

    return amount;
  }

private:
  std::variant<Volume, Error> calculate_amount(Moisture moisture, Temperature temperature) {
    return Volume{178};
  }

  MoistureSensor moisture_sensor;
  ThermoSensor thermo_sensor;
  Pump pump;
};

int main() {
  auto const result = WateringSystem{}.water();
  if(auto const amount = std::get_if<Volume>(&result); amount) {
    std::cout << "Water " << amount->ml << " ml\n";
  } else {
    std::cout << std::get<Error>(result).what << "\n";
  }
}

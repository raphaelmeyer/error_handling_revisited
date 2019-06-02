#include <optional>
#include <variant>

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
    auto error = std::get_if<Error>(&moisture);
    if (error) {
      return *error;
    }

    auto const temperature = thermo_sensor.read();
    error = std::get_if<Error>(&temperature);
    if (error) {
      return *error;
    }

    auto const amount = calculate_amount(std::get<Moisture>(moisture),
                                         std::get<Temperature>(temperature));

    auto const pump_error = pump.pump(amount);
    if (pump_error) {
      return pump_error.value();
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

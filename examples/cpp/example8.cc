#include <variant>
#include <iostream>

template<typename Ok, typename Err>
auto make_ok(Ok && value);

template<typename Ok, typename Err>
auto make_err(Err && value);

template<typename Ok, typename Err>
class Result {
public:
  Result(Ok && value) : _value{ok_t{std::move(value)}} {}
  Result(Err && value) : _value{err_t{std::move(value)}} {}

  Result(Ok const & value) : _value{ok_t{value}} {}
  Result(Err const & value) : _value{err_t{value}} {}

  Ok const & ok() const { return std::get<ok_t>(_value).value; }
  Err const & err() const { return std::get<err_t>(_value).value; }

  bool is_ok() const { return std::holds_alternative<ok_t>(_value); }
  bool is_err() const { return std::holds_alternative<err_t>(_value); }

private:
  struct ok_t { Ok value; };
  struct err_t { Err value; };
  using value_t = std::variant<ok_t, err_t>;

  value_t _value;

  Result(ok_t && value) : _value{std::move(value)} {}
  Result(err_t && value) : _value{std::move(value)} {}

  friend auto make_ok<Ok, Err>(Ok && value);
  friend auto make_err<Ok, Err>(Err && value);
};

template<typename Ok, typename Err>
auto make_ok(Ok && value) {
  return Result<Ok, Err>{typename Result<Ok, Err>::ok_t{value}};
}

template<typename Ok, typename Err>
auto make_err(Err && value) {
  return Result<Ok, Err>{typename Result<Ok, Err>::err_t{value}};
}

struct Volume { int ml; };
struct Moisture {};
struct Temperature {};
struct Error { std::string what; };

class ThermoSensor {
public:
  Result<Temperature, Error> read() { return Temperature{}; }
};

class MoistureSensor {
public:
  Result<Moisture, Error> read() {
    // return Error{"Temperature sensor error"};
    return Moisture{};
  }
};

class Pump {
public:
  Result<std::monostate, Error> pump(Volume amount) { return std::monostate{}; }
};

class WateringSystem {
public:
  Result<Volume, Error> water() {
    auto const moisture = moisture_sensor.read();
    if(moisture.is_err()) {
      return moisture.err();
    }

    auto const temperature = thermo_sensor.read();
    if(temperature.is_err()) {
      return temperature.err();
    }

    auto const amount = calculate_amount(moisture.ok(), temperature.ok());

    auto const pump_result = pump.pump(amount);
    if(pump_result.is_err()) {
      return pump_result.err();
    }

    return amount;
  }

private:
  Volume calculate_amount(Moisture moisture, Temperature temperature) {
    return Volume{42};
  }

  MoistureSensor moisture_sensor;
  ThermoSensor thermo_sensor;
  Pump pump;
};

int main() {
  auto const amount = WateringSystem{}.water();
  if(amount.is_ok()) {
    std::cout << "Water " << amount.ok().ml << " ml\n";
  } else {
    std::cout << amount.err().what << "\n";
  }
}

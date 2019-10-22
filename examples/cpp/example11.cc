#include <iostream>
#include <variant>

template<typename OkType, typename ErrType>
auto make_ok(OkType value);

template<typename OkType, typename ErrType>
auto make_err(ErrType value);

template<typename OkType, typename ErrType>
class Result
{
public:
  Result() = default;

  template<typename T, typename std::enable_if<
    std::is_convertible<T, std::variant<ErrType, OkType>>{}, int>::type = 0>
  Result(T && value) : _value{std::forward<T>(value)} {}

  ErrType const & err() const { return std::get<err_index>(_value); }
  OkType const & ok() const { return std::get<ok_index>(_value); }

  bool is_err() const { return _value.index() == err_index; }
  bool is_ok() const { return _value.index() == ok_index; }

private:
  constexpr static std::size_t const err_index = 0;
  constexpr static std::size_t const ok_index = 1;
  std::variant<ErrType, OkType> _value;

  Result(std::variant<ErrType, OkType> value) : _value{std::move(value)} {}

  friend auto make_ok<OkType, ErrType>(OkType value);
  friend auto make_err<OkType, ErrType>(ErrType value);
};

template<typename OkType, typename ErrType>
auto make_ok(OkType value) {
  using T = Result<OkType, ErrType>;
  return T{std::variant<ErrType, OkType>{std::in_place_index<T::ok_index>, std::move(value)}};
}

template<typename OkType, typename ErrType>
auto make_err(ErrType value) {
  using T = Result<OkType, ErrType>;
  return T{std::variant<ErrType, OkType>{std::in_place_index<T::err_index>, std::move(value)}};
}

template<typename In, typename ErrType, typename Func>
auto operator>>=(Result<In, ErrType> const & value, Func f) -> decltype(f(value.ok())) {
  if(value.is_err()) {
    return value.err();
  }
  return f(value.ok());
}

template<typename In, typename ErrType, typename Func>
auto operator>>(Result<In, ErrType> const & value, Func f) -> decltype(f()) {
  if(value.is_err()) {
    return value.err();
  }
  return f();
}

struct Volume { int ml; };
struct Moisture { int percentage; };
struct Temperature { double celsius; };
struct Error { std::string what; };

class ThermoSensor {
public:
  Result<Temperature, Error> read() {
    // return Error{"Temperature sensor error"};
    return Temperature{};
  }
};

class MoistureSensor {
public:
  Result<Moisture, Error> read() {
    // return Error{"Moisture sensor error"};
    return Moisture{};
  }
};

class Pump {
public:
  Result<std::monostate, Error> pump(Volume amount) {
    // return Error{"Pump error"};
    return std::monostate{};
  }
};

class WateringSystem {
public:
  Result<Volume, Error> water() {
    return moisture_sensor.read() >>= [&](auto moisture) {
      return thermo_sensor.read() >>= [&](auto temperature) {
        return calculate_amount(moisture, temperature) >>= [&](auto amount) {
          return pump.pump(amount) >> [&]() {
            return Result<Volume, Error>{amount};
          };
        };
      };
    };
  }

private:
  Result<Volume, Error> calculate_amount(Moisture moisture, Temperature temperature) {
    return Volume{178};
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

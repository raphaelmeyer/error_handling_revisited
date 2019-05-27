class Volume {};
class Moisture {};
class Temperature {};

class ThermoSensor {
public:
  Temperature temperature() {
    return {};
  }
};

class MoistureSensor {
public:
  Moisture moisture() {
    return {};
  }
};

class Pump {
public:
  void pump(Volume amount) {
  }
};

class WateringSystem {
public:
  Volume water() {
    auto const moisture = moisture_sensor.moisture();
    auto const temperature = thermo_sensor.temperature();
    auto const amount = calculate_amount(moisture, temperature);
    pump.pump(amount);
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

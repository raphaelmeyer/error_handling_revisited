class Volume {};
class Moisture {};
class Temperature {};

class ThermoSensor {
public:
  bool read(Temperature &) { return true; }
};

class MoistureSensor {
public:
  bool read(Moisture &) { return true; }
};

class Pump {
public:
  bool pump(Volume amount) { return true; }
};

class WateringSystem {
public:
  bool water(Volume amount) {
    Moisture moisture;
    if (moisture_sensor.read(moisture)) {
      Temperature temperature;
      if (thermo_sensor.read(temperature)) {
        amount = calculate_amount(moisture, temperature);
        if (pump.pump(amount)) {
          return true;
        }
      }
    }
    return false;
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
  Volume amount;
  system.water(amount);
}

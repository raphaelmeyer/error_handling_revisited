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
    if (not moisture_sensor.read(moisture)) {
      return false;
    }
    Temperature temperature;
    if (not thermo_sensor.read(temperature)) {
      return false;
    }
    amount = calculate_amount(moisture, temperature);
    if (not pump.pump(amount)) {
      return false;
    }
    return true;
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

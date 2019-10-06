bool MoistureSensor::read(Moisture & moisture) { /* ... */ }
// ...

bool WateringSystem::water(Volume & amount) {
  Moisture moisture;
  if(moisture_sensor.read(moisture)) {
    Temperature temperature;
    if(thermo_sensor.read(temperature)) {
      amount = calculate_amount(moisture, temperature);
      if(pump.pump(amount)) {
        return true;
      }
    }
  }
  return false;
}

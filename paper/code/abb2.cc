bool MoistureSensor::read(Moisture & moisture) { /* ... */ }
// ...

bool WateringSystem::water(Volume & amount) {
  Moisture moisture;
  if(not moisture_sensor.read(moisture)) {
    return false;
  }
  Temperature temperature;
  if(not thermo_sensor.read(temperature)) {
    return false;
  }
  amount = calculate_amount(moisture, temperature);
  if(not pump.pump(amount)) {
    return false;
  }
  return true;
}

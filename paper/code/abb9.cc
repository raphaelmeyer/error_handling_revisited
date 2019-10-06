Result<Moisture, Error> MoistureSensor::read() { /* ... */ }
// ...

Result<Volume, Error> WateringSystem::water() {
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

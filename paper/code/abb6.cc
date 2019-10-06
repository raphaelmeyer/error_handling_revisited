std::optional<Moisture> MoistureSensor::read() { /* ... */ }
// ...

std::optional<Volume> WateringSystem::water() {
  auto const moisture = moisture_sensor.read();
  if (not moisture) {
    return std::nullopt;
  }
  auto const temperature = thermo_sensor.read();
  if (not temperature) {
    return std::nullopt;
  }
  auto const amount = calculate_amount(moisture.value(), temperature.value());
  if (not pump.pump(amount)) {
    return std::nullopt;
  }
  return amount;
}

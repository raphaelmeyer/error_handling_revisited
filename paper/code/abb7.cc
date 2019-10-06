std::variant<Moisture, Error> MoistureSensor::read() { /* ... */ }
// ...

std::variant<Volume, Error> WateringSystem::water() {
  auto const moisture = moisture_sensor.read();
  if(auto const error = std::get_if<Error>(&moisture); error) {
    return *error;
  }

  // ...
}

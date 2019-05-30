```cpp
class WateringSystem {
public:
  Volume water() {
    auto const moisture = moisture_sensor.moisture();
    auto const temperature = thermo_sensor.temperature();

    auto const amount =
      calculate_amount(moisture, temperature);

    pump.pump(amount);

    return amount;
  }
}
```

```cpp
class WateringSystem {
public:
  Volume water() {
    auto const moisture = moisture_sensor.read();
    auto const temperature = thermo_sensor.read();

    auto const amount =
      calculate_amount(moisture, temperature);

    pump.pump(amount);

    return amount;
  }
}
```

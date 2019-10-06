readMoisture :: Maybe Moisture
-- ...

waterPlant :: Maybe Volume
waterPlant = do
  moisture <- readMoisture
  temperature <- readTemperature
  amount <- calculateAmount moisture temperature
  pump amount
  return amount

data Volume = Volume Int deriving (Show)
data Moisture = Moisture Int deriving (Show)
data Temperature = Temperature Float deriving (Show)

data WateringSystem = WateringSystem

readMoisture :: WateringSystem -> Maybe (Moisture, WateringSystem)
readMoisture _ = Just (Moisture 40, WateringSystem)

readTemperature :: WateringSystem -> Maybe (Temperature, WateringSystem)
readTemperature _ = Just (Temperature 21.5, WateringSystem)

calculateAmount :: Moisture -> Temperature -> Maybe Volume
calculateAmount _ _ = Just (Volume 123)

pump :: Volume -> WateringSystem -> Maybe WateringSystem
pump _ _ = Just WateringSystem

water :: WateringSystem -> Maybe (Volume, WateringSystem)
water watering = do
  (moisture, moistDone) <- readMoisture watering
  (temperature, tempDone) <- readTemperature moistDone
  amount <- calculateAmount moisture temperature
  watered <- pump amount tempDone
  return (amount, watered)

main = do
  let result = water WateringSystem
  maybe (return ()) (putStrLn . show . fst) result

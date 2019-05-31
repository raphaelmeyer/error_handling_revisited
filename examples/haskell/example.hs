data Volume = Volume Int deriving (Show)
data Moisture = Moisture Int deriving (Show)
data Temperature = Temperature Float deriving (Show)

readMoisture :: Maybe Moisture
readMoisture = Just (Moisture 40)

readTemperature :: Maybe Temperature
readTemperature = Just (Temperature 21.5)

calculateAmount :: Moisture -> Temperature -> Maybe Volume
calculateAmount _ _ = Just (Volume 123)

pump :: Volume -> Maybe ()
pump _ = Just ()

water :: Maybe Volume
water = do
  moisture <- readMoisture
  temperature <- readTemperature
  amount <- calculateAmount moisture temperature
  pump amount
  return amount

main = do
  let amount = water
  maybe (return ()) (putStrLn . show) amount

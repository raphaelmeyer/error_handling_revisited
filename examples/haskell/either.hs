data Volume = Volume Int deriving (Show)
data Moisture = Moisture Int deriving (Show)
data Temperature = Temperature Float deriving (Show)

data Error = Error String deriving (Show)

readMoisture :: Either Error Moisture
readMoisture = Right (Moisture 40)

readTemperature :: Either Error Temperature
-- readTemperature = Right (Temperature 21.5)
readTemperature = Left (Error "Temperature sensor offline")

calculateAmount :: Moisture -> Temperature -> Either Error Volume
calculateAmount _ _ = Right (Volume 123)

pump :: Volume -> Either Error ()
pump _ = Right ()

water_plant :: Either Error Volume
water_plant = do
  moisture <- readMoisture
  temperature <- readTemperature
  amount <- calculateAmount moisture temperature
  pump amount
  return amount

main = do
  let amount = water_plant
  either (putStrLn . ("! " ++) . show) (putStrLn . show) amount

data Volume = Volume Int deriving (Show)
data Moisture = Moisture Int deriving (Show)
data Temperature = Temperature Float deriving (Show)

data Error = Error String deriving (Show)

readMoisture :: Either Error Moisture
-- readMoisture = Left (Error "Moisture sensor error")
readMoisture = Right (Moisture 40)

readTemperature :: Either Error Temperature
-- readTemperature = Left (Error "Temperature sensor error")
readTemperature = Right (Temperature 21.5)

calculateAmount :: Moisture -> Temperature -> Either Error Volume
calculateAmount _ _ = Right (Volume 178)

pump :: Volume -> Either Error ()
-- pump _ = Left (Error "Pump error")
pump _ = Right ()

waterPlant :: Either Error Volume
waterPlant =
  readMoisture >>= (\ moisture ->
    readTemperature >>= (\ temperature ->
      calculateAmount moisture temperature >>= (\ amount ->
        pump amount >> return amount )))

main = case waterPlant of
  Right amount -> print amount
  Left error   -> print error

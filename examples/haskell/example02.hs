data Volume = Volume Int deriving (Show)
data Moisture = Moisture Int deriving (Show)
data Temperature = Temperature Float deriving (Show)

readMoisture :: Maybe Moisture
-- readMoisture = Nothing
readMoisture = Just (Moisture 40)

readTemperature :: Maybe Temperature
-- readTemperature = Nothing
readTemperature = Just (Temperature 21.5)

calculateAmount :: Moisture -> Temperature -> Maybe Volume
calculateAmount _ _ = Just (Volume 178)

pump :: Volume -> Maybe ()
-- pump _ = Nothing
pump _ = Just ()

waterPlant :: Maybe Volume
waterPlant =
  readMoisture >>= (\ moisture ->
    readTemperature >>= (\ temperature ->
      calculateAmount moisture temperature >>= (\ amount ->
        pump amount >> return amount )))

main = case waterPlant of
  Just amount -> print amount
  Nothing     -> print "Watering error"

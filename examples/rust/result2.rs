struct Moisture {
    percent: i32,
}

struct Temperature {
    celsius: i32,
}

struct Volume {
    ml: i32,
}

fn read_moisture() -> Result<Moisture, String> {
    //Err(String::from("Moisture sensor error"))
    Ok(Moisture{percent: 32})
}

fn read_temperature() -> Result<Temperature, String> {
    //Err(String::from("Temperature sensor error"))
    Ok(Temperature{celsius: 23})
}

fn calculate_amount(m: Moisture, t: Temperature) -> Volume {
    Volume{ml: 42}
}

fn pump(v: &Volume) -> Result<(), String> {
    Ok(())
}

fn water_plant() -> Result<Volume, String> {
    let moisture = read_moisture()?;
    let temperature = read_temperature()?;
    let amount = calculate_amount(moisture, temperature);
    pump(&amount)?;
    Ok(amount)
}

fn main() {
    match water_plant() {
        Err(e) => println!("{}", e),
        Ok(amount) => println!("Water {:?} ml", amount.ml),
    }
}

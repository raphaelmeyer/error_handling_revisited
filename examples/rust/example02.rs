struct Moisture {
    percentage: i32,
}

struct Temperature {
    celsius: f64,
}

struct Volume {
    ml: i32,
}

fn read_moisture() -> Result<Moisture, String> {
    // Err(String::from("Moisture sensor error"))
    Ok(Moisture{percentage: 40})
}

fn read_temperature() -> Result<Temperature, String> {
    // Err(String::from("Temperature sensor error"))
    Ok(Temperature{celsius: 21.5})
}

fn calculate_amount(m: Moisture, t: Temperature) -> Result<Volume, String> {
    Ok(Volume{ml: 178})
}

fn pump(v: &Volume) -> Result<(), String> {
    // Err(String::from("Pump error"))
    Ok(())
}

fn water_plant() -> Result<Volume, String> {
    let moisture = read_moisture()?;
    let temperature = read_temperature()?;
    let amount = calculate_amount(moisture, temperature)?;
    pump(&amount)?;
    Ok(amount)
}

fn main() {
    match water_plant() {
        Err(e) => println!("{}", e),
        Ok(amount) => println!("Water {:?} ml", amount.ml),
    }
}

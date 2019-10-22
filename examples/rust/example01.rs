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
    let moisture = match read_moisture() {
        Ok(m) => m,
        Err(e) => return Err(e),
    };
    let temperature = match read_temperature() {
        Ok(t) => t,
        Err(e) => return Err(e),
    };
    let amount = match calculate_amount(moisture, temperature) {
        Ok(v) => v,
        Err(e) => return Err(e),
    };
    match pump(&amount) {
        Ok(_) => Ok(amount),
        Err(e) => Err(e),
    }
}

fn main() {
    match water_plant() {
        Err(e) => println!("{}", e),
        Ok(amount) => println!("Water {:?} ml", amount.ml),
    }
}

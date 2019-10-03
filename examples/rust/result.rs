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
    let moisture = match read_moisture() {
        Ok(m) => m,
        Err(e) => return Err(e),
    };
    let temperature = match read_temperature() {
        Ok(t) => t,
        Err(e) => return Err(e),
    };
    let amount = calculate_amount(moisture, temperature);
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

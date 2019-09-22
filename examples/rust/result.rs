
struct Moisture {
    percent: i32,
}

struct Volume {
    ml: i32,
}

fn read_moisture() -> Result<Moisture, String> {
    return Err(String::from("Moisture sensor error"));
}

fn read_temperature() -> Result<Temperature, String> {
    return Err(String::from("Temperature sensor error"));
}

fn calculate_amount() -> Volume {
    
}

fn water_plant() -> Result<Volume, String> {
    let moisture = match read_moisture() {
        Err(e) => return Err(e),
        Ok(m) => m,
    };

    let temperature = match read_temperature() {
        Err(e) => return Err(e),
        Ok(t) => t,
    }

    let amount = calculate_amount(moisture, temperature);

    match pump(amount) => {
        Ok(_) => Ok(amount),
        Err(e) => Err(e),
    }

    // Ok(Volume{ml: 42})
}

fn main() {
    match water_plant() {
        Err(e) => println!("{}", e),
        Ok(amount) => println!("Volume {:?}", amount.ml),
    }
}

/*
fn write_info(info: &Info) -> io::Result<()> {
    let mut file = match File::create("my_best_friends.txt") {
        Err(e) => return Err(e),
        Ok(f) => f,
    };
    if let Err(e) = file.write_all(format!("name: {}\n", info.name).as_bytes()) {
        return Err(e)
    }
    // ...
    Ok(())
}

fn write_info(info: &Info) -> io::Result<()> {
    let mut file = File::create("my_best_friends.txt")?;
    // Early return on error
    file.write_all(format!("name: {}\n", info.name).as_bytes())?;
    file.write_all(format!("age: {}\n", info.age).as_bytes())?;
    file.write_all(format!("rating: {}\n", info.rating).as_bytes())?;
    Ok(())
}

*/

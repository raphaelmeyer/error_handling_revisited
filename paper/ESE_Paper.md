# C++ Error Handling Revisited

## Was wir von funktionalen Sprachen lernen können

Raphael Meyer, bbv Software Services AG

**Die Behandlung von Fehlern und Ausnahmesituationen ist nicht nur ein wichtiger Teil jeder Software, sondern oft auch sehr umfangreich.
Gerade bei Embedded-Software, welche von der Interaktion mit Hardware geprägt ist, ist eine sorgfältige Fehlerbehandlung für den einwandfreien Betrieb der entwickelten Geräte unabdingbar.
Funktionale Programmiersprachen bieten hier interessante Konzepte, welche nicht ganz neu sind, in letzter Zeit aber vermehrt wiederentdeckt werden.
Die beiden in C++17 dazu gestossenen Templateklassen `std::optional` und `std::variant` können helfen, die Signaturen von Funktionen und Methoden sprechender zu gestalten.**

In der Softwareentwicklung gibt es unterschiedliche Typen von Fehlern.
Wir konzentrieren uns hier auf Interaktionen mit der Aussenwelt, die nicht zum gewünschten Ergebnis führen.
Zum Beispiel die Bewegung eines Motors, die nicht zu Ende geführt werden kann.
Mit anderen Worten sprechen wir von Funktionen mit Seiteneffekten, die nicht erfolgreich ausgeführt werden konnten.

### Wie können Fehler kommuniziert werden?

Eine Funktion, die eine Interaktion mit Seiteneffekten abstrahiert, kann das Resultat auf unterschiedliche Art zurückmelden.
In C++ ist es unter anderem üblich, einen _Return Code_ zurückzugeben.
Dies kann ein einfacher boolscher Wert, eine Enumeration oder ein Zahlencode sein.
Die Verwendung von C++ Exceptions ist eine weitere Möglichkeit.

Verwendet eine Funktion _Return Codes_, so muss ein allfälliger Rückgabewert als Ausgabeparameter zurückgegeben werden.
Ausgabeparameter können beispielsweise mit Referenzen oder (intelligenten) Zeigern implementiert werden.
Der Nachteil ist, dass deren Absicht ohne zusätzliche Dokumentation oftmals nicht ersichtlich ist.
Es tauchen Fragen zu den Besitzverhältnissen auf und es braucht weitere Erklärungen zum Zustand oder zur Gültigkeit eines Ausgabeparameters im Fehlerfall.

Die Auswertung von Return Codes kann auf unterschiedliche Art geschehen.
Die zwei häufigsten Muster sind verschachtelte if-Anweisungen und _Early Returns_.
Verschachtelte if-Anweisungen skalieren schlecht mit dem Ablauf, den man in einem Block ausführen möchte.
Die Verschachtelungstiefe nimmt mit jedem zusätzlichen Schritt zu.

Betrachten wir zur Veranschaulichung ein einfaches Beispiel.
Wir haben ein einfaches Gerät zum automatischen Bewässern einer Topfpflanze.
Aufgrund der Umgebungstemperatur und der Feuchtigkeit im Topf soll jeweils entschieden werden, wie viel Wasser in den Topf gepumpt wird.

```cpp
bool MoistureSensor::read(Moisture & moisture) { /* ... */ }
// ...

bool WateringSystem::water(Volume & amount) {
  Moisture moisture;
  if(moisture_sensor.read(moisture)) {
    Temperature temperature;
    if(thermo_sensor.read(temperature)) {
      amount = calculate_amount(moisture, temperature);
      if(pump.pump(amount)) {
        return true;
      }
    }
  }
  return false;
}
```
Abb. 1: Return Codes und verschachtelte if-Anweisungen

Beim _Early Return_ unterbrechen die if-Anweisungen zwischen den einzelnen Schritten leider den ursprünglichen Ablauf, und wirken sich nachteilig auf die Lesbarkeit aus.
Ein prominentes Beispiel für _Early Return_ ist die Programmiersprache Go.
In Go ist es das Standardvorgehen zur Fehlerauswertung.

```cpp
bool MoistureSensor::read(Moisture & moisture) { /* ... */ }
// ...

bool WateringSystem::water(Volume & amount) {
  Moisture moisture;
  if(not moisture_sensor.read(moisture)) {
    return false;
  }
  Temperature temperature;
  if(not thermo_sensor.read(temperature)) {
    return false;
  }
  amount = calculate_amount(moisture, temperature);
  if(not pump.pump(amount)) {
    return false;
  }
  return true;
}
```
Abb. 2: Return Codes und _Early Returns_

Werden Exceptions verwendet, so bleibt der eigentliche Ablauf kompakt und übersichtlich.
Die Ausgabeparameter entfallen ebenso.
In der Embedded Softwareentwicklung werden Exceptions jedoch aus verschiedenen Gründen vielfach vermieden, manchmal auch ungerechtfertigt.

```cpp
Volume WateringSystem::water() {
  try {
    auto const moisture = moisture_sensor.read();
    auto const temperature = thermo_sensor.read();
    auto const amount = calculate_amount(moisture, temperature);
    pump.pump(amount);
    return amount;
  } catch(std::exception const &) {
    // ...
  }
}
```
Abb. 3: Beispiel unter Verwendung von Exceptions

### Ein Blick über den Zaun

Die Behandlung von Seiteneffekten ist in der Programmiersprache Haskell auf elegante Art und Weise gelöst.
Das erwähnte Beispiel könnte in Haskell folgendermassen aussehen:

```haskell
readMoisture :: Maybe Moisture
-- ...

waterPlant :: Maybe Volume
waterPlant = do
  moisture <- readMoisture
  temperature <- readTemperature
  amount <- calculateAmount moisture temperature
  pump amount
  return amount
```
Abb. 4: beispielhafte Implementierung in Haskell

Der Code wird durch die Fehlerbehandlung nicht gestört.
Es ist aber trotzdem klar, dass hier Seiteneffekte behandelt werden.
Das `Maybe Volume` in der Funktionssignatur signalisiert, dass die Funktion nur _vielleicht_ einen Wert zurück gibt.
Der Rückgabewert kann entweder `Just <volume>` oder `Nothing` sein.

Die Anweisung `do` bedeutet, dass die darin aufgerufenen Funktionen vielleicht auch nichts zurückgeben.
Sobald die erste innere Funktion nichts zurückliefert, werden die nachfolgende Aufrufe nicht mehr getätigt, und die Funktion gibt `Nothing` zurück.

Wenn zusätzlich zum Auftreten eines Fehler auch Informationen zum Fehler mitgeteilt werden sollten, kann der abstrakte Datentyp `Either` verwendet werden.
Ein `Either` hat entweder den Wert `Right <value>` oder `Left <error>`.
Ist der Wert ein `Left`, handelt es sich um einen Fehler.

In der noch jungen Programmiersprache Rust werden die beiden Typen `Option` und `Result` verwendet, um Fehler zu melden.
Sie können mit `Maybe` und `Either` aus Haskell verglichen werden.
Ausserdem enthält Rust Spracheigenschaften, die hilfreich sind bei der Verwendung der beiden Typen.
Zum Beispiel das Statement `match` oder der Operator `?`.

```rust
fn read_moisture() -> Result<Moisture, String> {
  // ...
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
```
Abb. 5: exemplarische Implementation in Rust

Das `match` ist eine vereinfachte Form von dem, was man in Haskell als Pattern Matching kennt.
Es ist darauf abgestimmt, mit Typen wie `Result` umzugehen.

### Neues aus C++17

Mit C++17 wurde die Klasse `std::optional` in die Standard Library aufgenommen.
Sie kann als C++ Variante von `Maybe` angesehen werden.

Mit `std::optional` muss ein Rückgabewert nicht mehr als Ausgabeparameter definiert werden.
Das Verhalten einer Funktion lässt sich so einfacher aus der Signatur ableiten, als bei einer Implementation mit Return Code und Ausgabeparameter.

```cpp
std::optional<Moisture> MoistureSensor::read() { /* ... */ }
// ...

std::optional<Volume> WateringSystem::water() {
  auto const moisture = moisture_sensor.read();
  if (not moisture) {
    return std::nullopt;
  }
  auto const temperature = thermo_sensor.read();
  if (not temperature) {
    return std::nullopt;
  }
  auto const amount = calculate_amount(moisture.value(), temperature.value());
  if (not pump.pump(amount)) {
    return std::nullopt;
  }
  return amount;
}
```
Abb 6: Verwendung von std::optional

`std::variant` ist eine weitere Templateklasse, welche mit C++17 neu dazugekommen ist.
Damit lassen sich Typen wie ein `Either` aus Haskell oder ein `Result` aus Rust nachbilden.

```cpp
std::variant<Moisture, Error> MoistureSensor::read() { /* ... */ }
// ...

std::variant<Volume, Error> WateringSystem::water() {
  auto const moisture = moisture_sensor.read();
  if(auto const error = std::get_if<Error>(&moisture); error) {
    return *error;
  }

  // ...
}
```
Abb. 7: direkte Verwendung von std::variant

Verwendet man std::variant direkt, um ein Result zu imitieren, so ist dessen Verwendung zuweilen etwas umständlich.
Dies rührt unter anderem daher, dass Templateklassen aus der Standard Library möglichst allgemein gehalten werden, damit Erweiterungen in alle Richtungen möglich sind.

Mit einem einfachen Wrapper um `std::variant`, kann man die Lesbarkeit des Code aber stark erhöhen.

```cpp
template<typename Ok, typename Err>
class Result {
public:
  Result(Ok const & value);
  Result(Err const & value);

  Ok const & ok() const;
  Err const & err() const;

  bool is_ok() const;
  bool is_err() const;

private:
  struct ok_t { Ok value; };
  struct err_t { Err value; };
  std::variant<ok_t, err_t> _value;
};
```
Abb. 8: eine einfache Implementation von `Result`

```cpp
Result<Moisture, Error> MoistureSensor::read() { /* ... */ }
// ...

Result<Volume, Error> WateringSystem::water() {
  auto const moisture = moisture_sensor.read();
  if(moisture.is_err()) {
    return moisture.err();
  }
  auto const temperature = thermo_sensor.read();
  if(temperature.is_err()) {
    return temperature.err();
  }
  auto const amount = calculate_amount(moisture.ok(), temperature.ok());
  auto const pump_result = pump.pump(amount);
  if(pump_result.is_err()) {
    return pump_result.err();
  }
  return amount;
}
```
Abb. 9: Anwendungsbeispiel mit der eigenen Klasse `Result`

Das Weiterleiten von Fehlern erfolgt zwar immer noch manuell mit if-Anweisungen,
aber die Signaturen drücken die Absicht der Funktionen und Methoden besser aus.
Der Code wird durch das Interface der Klasse `Result` klarer.

Natürlich ist es denkbar, das man die Funktionsweise eines Haskell `do`-Blocks oder dem `?`-Operator aus Rust nachzubilden versucht.
Man wird dabei aber kaum darum herum kommen, dass Funktionsaufrufe in Form von Funktionsobjekten benötigt werden.
Das heisst wiederum, dass diese zusätzlich eingepackt werden müssen, beispielsweise mit Lambda-Ausdrücken oder `std::bind`.

### Zusammenfassung

Wie am Beispiel von Haskell gezeigt, bieten funktionale Programmiersprachen interessante Möglichkeiten zur Fehlerbehandlung an.
Entstanden ist dies vor allem aus einer Notwendigkeit heraus, denn auch funktionale Sprachen müssen mit Seiteneffekten umgehen können.
Die Eleganz, mit der dieses Problem gelöst wurde, hat dazu geführt, dass Merkmale von funktionalen Sprachen vermehrt auch in konventionelle und etablierte Sprachen einfliessen.

Die beiden Templateklassen `std::optional` und `std::variant` aus C++17 sind ein gutes Hilfsmittel, um Funktionen sprechender zu gestalten.
Durch das Vermeiden von Ausgabeparametern kommen Fragen nach deren Gültigkeit oder Zustand im Fehlerfall erst gar nicht auf.

### Literatur- und Quellenverzeichnis

* [1] Learn You a Haskell for Great Good!, Miran Lipovača
* [2] https://golang.org/
* [3] https://www.rust-lang.org/

### Autor

Raphael Meyer ist Software-Ingenieur mit über zehn Jahren Erfahrung in der Geräteentwicklung. Er interessiert sich stark für Themen in der Software-Entwicklung, die dazu beitragen qualitativ hochstehende Produkte zu entwickeln. Deshalb ist er auch in der Software Crafters Community aktiv. Ausserdem ist Raphael Meyer ein Organisator der C++ Usergroup Zentralschweiz.

### Kontakt
* Internet: [bbv.ch](https://www.bbv.ch/)
* Email: [raphael.meyer@bbv.ch](mailto:raphael.meyer@bbv.ch)

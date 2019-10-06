# C++ Error Handling Revisited

## Was wir von funktionalen Sprachen lernen können

Raphael Meyer, bbv Software Services AG

**Die Behandlung von Fehlern und Ausnahmesituationen ist nicht nur ein wichtiger Teil jeder Software, sondern oft auch sehr umfangreich.
Gerade bei Embedded-Software, welche von der Interaktion mit Hardware geprägt ist, ist eine sorgfältige Fehlerbehandlung für den einwandfreien Betrieb der entwickelten Geräte unabdingbar.**

**Leider trägt die Fehler- und Ausnahmebehandlung aber oft dazu bei, dass Abläufe im Code schlechter lesbar sind.
Der Code zu Ausnahmebehandlung drängt sich dazwischen und reisst die eigentlichen Abläufe visuell auseinander.**

**Funktionale Programmiersprachen bieten hier interessante Konzepte, welche nicht ganz neu sind, in letzter Zeit aber vermehrt wiederentdeckt werden.
Die beiden in C++17 dazu gestossenen Templateklassen `std::optional` und `std::variant` können helfen, die Signaturen von Funktionen und Methoden sprechender zu gestalten.**

In der Softwareentwicklung gibt es unterschiedliche Typen von Fehlern.
Wir konzentrieren uns hier auf Interaktionen mit der Aussenwelt, die nicht zum gewünschten Ergebnis führen.
Zum Beispiel die Bewegung eines Motors, die nicht zu Ende geführt werden kann.
Mit anderen Worten ausgedrückt sprechen wir von Funktionen mit Seiteneffekten.

### Wie können Fehler kommuniziert werden?

Eine Funktion, die eine Interaktion mit Seiteneffekten abstrahiert, kann das Result auf unterschiedliche Art zurückmelden.
In C++ ist es unter anderem üblich, einen _Return Code_ zurückzugeben.
Dies kann ein einfacher boolscher Wert, eine Enumeration oder ein Zahlencode sein.
Die Verwendung von C++ Exceptions ist eine weitere Möglichkeit.

Verwendet eine Funktion _Return Codes_, so muss ein allfälliger Rückgabewert als Ausgabeparameter zurückgegeben werden.
Ausgabeparameter können beispielsweise mit Referenzen oder (intelligenten) Zeigern implementiert werden.
Der Nachteil ist, dass deren Intention ohne zusätzliche Dokumentation oftmals nicht ersichtlich ist.
Es tauchen Fragen zu den Besitzverhältnissen auf und es braucht weitere Erklärungen zum Zustand oder zur Gültigkeit eines Ausgabeparameters im Fehlerfall.

Betrachten wir zur Veranschaulichung ein einfaches Beispiel.
Wir haben ein einfaches Gerät zum automatischen Bewässern einer Topfpflanze.
Aufgrund der Umgebungstemperatur und der Feuchtigkeit im Topf soll jeweils entschieden werden, wie viel Wasser in den Topf gepumpt wird.

```cpp
<code nested if>
```
Abb. 1: Return Codes und verschachtelte if-Anweisungen

Die Auswertung der Return Codes kann auf unterschiedlich Art geschehen.
Die zwei häufigsten Muster sind verschachtelte if-Anweisungen und _Early Returns_.
Verschachtelte if-Anweisungen skalieren schlecht mit dem Ablauf, den man in einem Block ausführen möchte.
Die Verschachtelungstiefe nimmt mit jedem zusätzlichen Schritt zu.

```cpp
<code with early returns>
```
Abb. 2: Return Codes und _Early Returns_

In der Sprache Go sind _Early Returns_ das Standardvorgehen, um Fehler auszuwerten.
Die if-Anweisungen zwischen den einzelnen Schritten unterbrechen leider zum Nachteil der Lesbarkeit den ursprünglichen Ablauf.

```cpp
<code with early returns>
```
Abb. 3: Das Beispiel unter Verwendung von Exceptions

Werden Exceptions verwendet, so bleibt der Ablauf kompakt und übersichtlich.
Oftmals werden Exceptions aber in Embedded Software vermieden, machmal zu Recht, machmal zu Unrecht.

### Ein Blick über den Zaun

Die Behandlung von Seiteneffekten ist in der Programmiersprache Haskell auf elegante Art und Weise gelöst.
Das erwähnte Beispiel könnte in Haskell folgendermassen aussehen:

```haskell
<mit maybe>
```
Abb. 4: beispielhafte Implementierung in Haskell

Der Code wird nicht durch die Fehlerbehandlung gestört.
Es ist aber trotzdem klar, dass hier Seiteneffekte behandelt werden.
Das `Maybe Volume` in der Funktionssignatur signalisiert, dass die Funktion nur _vielleicht_ einen Wert zurück gibt.
Der Rückgabewert kann entweder `Just <volume>` oder `Nothing` sein.

Das `do` bedeutet, dass die in der Funktion aufgerufenen Funktionen vielleicht auch nichts zurückgeben.
Sobald die erste innere Funktion nichts zurück liefert, werden die nachfolgende Aufrufe nicht mehr getätigt, und die Funktion gibt `Nothing` zurück.

Wenn zusätzlich zum Auftreten eines Fehler auch Informationen zum Fehler mitgeteilt werden sollten, kann der abstrakte Datentyp `Either` verwendet werden.
Ein `Either` hat entweder den Wert `Right <value>` oder `Left <error>`.
Ist der Wert ein `Left`, handelt es sich um einen Fehler.

```haskell
<mit either>
```
Abb. 5: `Either` anstelle von `Maybe`

### Einfluss von Haskell auf andere Programmiersprachen

In der noch jungen Programmiersprache Rust werden die beiden Typen `Option` und `Result` verwendet, um Fehler zu melden.
Sie können mit `Maybe` und `Either` aus Haskell verglichen werden.
Ausserdem enthält Rust Spracheigenschaften, die bei deren Anwendung hilfreiche Unterstützung anbieten.
Zum Beispiel das Statement `match` oder Operator ?.

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
Abb. 6: exemplarische Implementation in Rust

Das `match` ist eine vereinfachte Form von dem, was man in Haskell als Pattern Matching kennt.
Es ist darauf abgestimmt, mit Typen wie `Result` umzugehen.

### std::optional

Mit C++17 wurde die Klasse std::optional in die Standard Library aufgenommen.
Sie kann als C++ Variante von `Maybe` angesehen werden.

```cpp
<code mit std::optional, aber was?>
```
> Abb : ...

Das std::optional eignet sich ...
> std::optional -> no invalid output param in case of error


### "Result" Wrapper um std::variant

Eine weitere Templateklasse, welche mit C++17 dazugekommen ist, ist das std::variant.
Damit lassen sich Typen wie ein `Maybe` aus Haskell oder ein `Result` aus Rust nachbilden.

```cpp
<nur ein aufruf as water(), um zu zeigen, dass std::variant etwas umständlich sein kann>
```
Abb N : ...

Verwendet man std::variant direkt, um ein Result zu imitieren, so ist dessen Verwendung zuweilen etwas umständlich.
Dies rührt unter anderem daher, dass Templateklassen aus der Standard Library möglichst allgemein gehalten werden, damit Erweiterungen in alle Richtungen möglich sind.

Mit einem einfachen Wrapper um std::variant, kann man die lesbarkeit des Code aber stark erhöhen.

```cpp
template<typename ...> class Result { ... }
```

```cpp
Result<Volume> WateringSystem::water() { ... }
```

Das Weiterleiten von Fehlern erfolgt zwar immer noch manuell, aber aus den Funktions- und Methodensignaturen,
lässt sich viel leichter ablesen, wie das Verhalten ist, als wenn zum Beispiel Outputparamater und Returncodes verwendet werden.
Natürlich ist es denkbar, das man die Funktionsweise eines Haskell `do`-Blocks oder dem Operator `?` aus Rust nachzubilden versucht.
Man wird dabei aber kaum darum herum kommen, dass Funktionsaufrufe in einem Block in Form von Funktionsobjekten benötigt werden.
Das heisst wiederum, dass diese zusätzlich eingepackt werden müssen, beispielsweise mit Lambda-Ausdrücken oder std::bind.

### Zusammenfassung

Funktionale Programmiersprachen, wie zum Beispiel Haskell bieten interessante Möglichkeiten zur Fehlerbehandlung an.
Entstanden ist dies vor allem aus einer Notwendigkeit heraus, denn auch funktionale Sprachen müssen mit Seiteneffekten umgehen können.
Die Eleganz, mit der dieses Problem gelöst wurde, hat dazu geführt, dass Merkmale von funktionalen Sprachen vermehrt auch in konventionelle und etablierte Sprachen einfliessen.

Die beiden Templateklassen `std::optional` und `std::variant` aus C++17 sind ein gutes Hilfsmittel, um Funktionen sprechender zu gestalten.
Durch das Vermeiden von Ausgabeparametern kommen Fragen nach deren Gültigkeit oder Zustand im Fehlerfall erst gar nicht auf.

### Literatur- und Quellenverzeichnis

[1] Learn You a Haskell for Great Good!, Miran Lipovača
[2] https://golang.org/
[3] https://www.rust-lang.org/

### Autor

Raphael Meyer ist Software-Ingenieur mit über zehn Jahren Erfahrung in der Geräteentwicklung. Er interessiert sich stark für Themen in der Software-Entwicklung, die dazu beitragen qualitativ hochstehende Produkte zu entwicklen. Deshalb ist er auch in der Software Crafters Community aktiv. Ausserdem ist Raphael Meyer ein Organisator der C++ Usergroup Zentralschweiz.

[!me.png]

### Kontakt
* Internet: [bbv.ch](https://www.bbv.ch/)
* Email: [raphael.meyer@bbv.ch](mailto:raphael.meyer@bbv.ch)

# C++ Error Handling Revisited

## <sub title>

Raphael Meyer, bbv Software Services AG

**Die Behandlung von Fehlern und Ausnahmesituationen ist nicht nur ein wichtiger Teil jeder Software, sondern oft auch sehr umfangreich.
Gerade bei Embedded-Software, welche von der Interaktion mit Hardware geprägt ist, ist eine sorgfältige Fehlerbehandlung für den einwandfreien Betrieb der entwickelten Geräte unabdingbar.**

**Leider trägt die Fehler- und Ausnahmebehandlung aber oft dazu bei, dass Abläufe im Code schlechter lesbar sind.
Der Code zu Ausnahmebehandlung drängt sich dazwischen und reisst die eigentlichen Abläufe visuell auseinander.**

**Funktionale Programmiersprachen bieten hier interessante Konzepte, welche nicht ganz neu sind, in letzter Zeit aber vermehrt wiederentdeckt werden.
Die beiden in C++17 dazugestossenen Templateklassen `std::optional` und `std::variant` können helfen, die Signaturen von Funktionen und Methoden sprechender zu gestalten.**

In der Softwareentwicklung gibt es unterschiedliche Typen von Fehlern.
Wir konzentrieren uns hier auf Interaktionen mit der Aussenwelt, die nicht zum gewünschten Ergebnis führen.
Zum Beispiel die Bewegung eines Motors, die nicht zu Ende geführt werden kann.
Mit anderen Worten ausgedrückt sprechen wir von Funktionen mit Seiteneffekten.

### Wie können Fehler kommuniziert werden?

Eine Funktion, die eine Interaktion mit Seiteneffekten abstrahiert, kann das Result auf unterschiedliche Art zurückmelden.
In C++ ist es unter anderem üblich, ein Ergebnis als boolschen Wert, Enumeration oder Zahlencode zurückzugeben.
Die Verwendung von C++ Exceptions ist eine weitere Möglichkeit.

Betrachten wir zur Veranschaulichung ein einfaches Beispiel.
Wir haben ein einfaches Gerät zum automatischen Bewässern einer Topfpflanze.
Aufgrund der Umgebungstemperatur und der Feuchtigkeit im Topf soll jeweils entschieden werden, wieviel Wasser in den Topf gepumpt wird.

```cpp
<c++ code ohne error handling>
```
Abb/Code 1 : Code Beispiel Bewässerungsfunktion

> what is output parameter called in german?

Verwendet eine Funktion Returncodes, so muss ein allfälliger Rückgabewert als Outputparameter zurückgegeben werden.
Outputparameter können beispielsweise mit Referenzen oder (Smart)-Pointers implementiert werden.
Der Nachteil ist, dass deren Intention oftmals aus der reinen Funktionssignatur nicht klar ist, und es zusätzliche Dokumentation braucht.
Es tauchen Fragen zu deren _Ownership_ auf.
Und es braucht weitere Erklärungen zum Zustand oder zur Gültigkeit eines _Outputparamaters_ im Fehlerfall.

> what is ownership in german ?

```cpp
<code nested if>
```
> Abb: bla bla bla

Verschachtelte if-Anweisungen skalieren schlecht mit dem Ablauf, den man in einem Code-Block ausführen möchte.
Die Verschachtelungstiefe nimmt mit jedem zusätzlichen Schritt zu.

```cpp
<code with early returns>
```

> warum early return, no nesting, used in golang

> should I add the exceptions code example as well ?

Werden Exceptions verwendet, so bleibt der Ablauf kompakt und übersichtlich.
Oftmals werden Exceptions aber in Embedded Software vermieden, machmal zu Recht, machmal zu Unrecht.


> should I discusss these different cases of error handling?
> - Fehler zurückliefern (-> sensor::read())
> - Fehler propagieren (-> water_plant)
> - Fehler auswerten (-> main)


### Ein Blick über den Zaun

Die Behandlung von Seiteneffekten ist in Haskell auf elegante Art und Weise gelöst.
Das erwähnte Beispiel könnte in Haskell folgendermassen aussehen:

```haskell
<mit maybe>
```
> Abb N : ...

Der Code wird nicht durch die Fehlerbehandlung gestört.
Aber es ist trotzdem klar, dass hier Seiteneffekte behandelt werden.
Das Maybe Volume in der Funktionssignatur zeigt, dass die Funktion vielleicht einen Wert zurückgibt.
Vielleicht kommt jedoch nichts zurück, das `Maybe Volume` hat den Wert `Nothing`.
Das do heisst, dass die in der Funktion aufgerufenen Funktionen vielleicht auch nichts zurückgeben.
Sobald die erste innere Funktion nichts zurückliefert, werden die nachfolgende Aufrufe nicht mehr getätigt, und die Funktion gibt `Nothing` zurück.

Wenn nicht nur mitgeteilt werden sollte, dass ein Fehler aufgetreten ist, sondern auch Informationen zum Fehler,
dann kann der abstrakte Datentyp `Either` verwendet werden.
Ein `Either` hat entweder den Wert `Right` oder `Left`. Ist der Wert ein `Left`, handelt es sich um einen Fehler.

```haskell
<mit either>
```
> Abb N : ...

Der `do`-Block verhält sich gleich wie diejenige mit Maybe, im Fehlerfall einfach ein `Left` zurückgegeben,
welches den Fehler enthält.


### Rust

In der noch jungen Programmiersprache Rust werden die beiden Typen `Option` und `Result` verwendet, um Fehler zu melden.
Das `Option` entspricht in etwa dem `Maybe` aus Haskell, `Result` dem `Either`.
Sie sind ein wesentlicher Bestandteil der Sprache und werden auch in der Rust Standard Library <heisst das so?> verwendet.
Deshalb bietet Rust auch Sprachefeatures <in german?> zu deren Anwendung an.
Zum Beispiel das Statement `match` oder Operator ?.


```rust
<read_sensor>
```
Abb N : Funktion die ein Result zurückgibt.

```rust
<water_plant>
```
Abb N : Mit dem ?-Operator ist der Code schon fast so Elegant wie in Haskell.

```rust
<main>
```
> Abb N : Mit `match` kann ...

Das `match` ist dem Pattern Matching von Haskell nachempfunden, wenn auch nicht so mächtig.
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
Natürlich ist es denkbar, das man die Funktionsweise eines Haskell `do`-Blocks oder dem Operator ? aus Rust nachzubilden versucht.
Man wird dabei aber kaum darum herum kommen, dass Funktionsaufrufe in einem Block in Form von Funktionsobjekten benötigt werden.
Das heisst wiederum, dass diese zusätzlich eingepackt werden müssen, beispielsweise mit Lambda-Ausdrücken oder std::bind.

### Zusammenfassung

Funktionale Programmiersprachen, wie zum Beispiel Haskell bieten interessante Möglichkeiten für des Errorhandling an.
Entstanden ist dies vorallem aus einer Notwendigkeit heraus.
Denn auch funktionale Sprachen müssen mit Seiteneffekten umgehen können.
Die Eleganz, mit dem das gelöst wurde, hat dazu geführt, dass Merkmale von funktionalen Sprachen, vermehrt auch in konventionelle und etablierte Sprachen einfliessen.

Die beiden Templateklassen std::optional und std::variant aus C++17 sind ein gutes Hilfsmittel,
um Funktionen sprechender zu gestalten.
Mit dem vermeiden von Outputparameter kommen Fragen nach der Gültigkeit oder dem Zustand im Fehlerfall erst gar nicht auf.



### Literatur- und Quellenverzeichnis

[1] Learn You a Haskell for Great Good, ...

### Autor

Raphael Meyer ist Software-Ingenieur mit über zehn Jahren Erfahrung in der Geräteentwicklung. Er interessiert sich stark für Themen in der Software-Entwicklung, die dazu beitragen qualitativ hochstehende Produkte zu entwicklen. Deshalb ist er auch in der Software Crafters Community aktiv. Ausserdem ist Raphael Meyer ein Organisator der C++ Usergroup Zentralschweiz.

[!me.png]

### Kontakt
Internet: [bbv.ch](https://www.bbv.ch/)
Email: [raphael.meyer@bbv.ch](mailto:raphael.meyer@bbv.ch)

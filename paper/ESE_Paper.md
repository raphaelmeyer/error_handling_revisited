# C++ Error Handling Revisited

## <sub title>

Raphael Meyer, bbv Software Services AG

> TODO write an abstract for the paper instead

**Die Behandlung von Fehlern und Ausnahmesituationen ist nicht nur ein wichtiger Teil jeder Software, sondern oft auch sehr umfangreich. Gerade bei Embedded-Software, welche von der Interaktion mit Hardware geprägt ist, ist eine sorgfältige Fehlerbehandlung für den einwandfreien Betrieb der entwickelten Geräte unabdingbar.**

**Leider trägt die Fehler- und Ausnahmebehandlung aber oft dazu bei, dass Abläufe im Code schlechter lesbar sind. Der Code zu Ausnahmebehandlung drängt sich dazwischen und reißt die eigentlichen Abläufe visuell auseinander.**

**Funktionale Programmiersprachen bieten hier interessante Konzepte, welche nicht ganz neu sind, aber in letzter Zeit vermehrt wiederentdeckt werden. Wir werden einen kurzen Blick auf das Fehlerhandling in Haskell werfen und betrachten, wie sich diese Konzepte in C++ umsetzen und anwenden lassen. Dabei treffen wir auch einige neue Features aus C++17 an.**




In der Softwareentwicklung gibt es unterschiedliche Typen von Fehlern.
Wir konzentrieren uns hier auf Interaktionen mit der Aussenwelt, die nicht zum gewünschten Ergebnis führen.
Zum Beispiel die Bewegung eines Motors, die nicht zu Ende geführt werden kann, oder eine ungültige Eingabe eines Anwenders.
Bei der Interaktion mit der physikalischen Welt, sprechen wir auch von Seiteneffekten.

Eine Funktion, die eine Interaktion mit Seiteneffekten abstrahiert, kann das Result auf unterschiedliche Weise zurückmelden.
In C++ üblich sind unter anderem Return-Codes in Form von boolschen Werten oder Zahlencodes.
Exceptions sind ein in C++ enthaltenes Sprachkonstrukt, um Fehler zurückzugeben.



Betrachten wir zur Veranschaulichung ein einfaches Beispiel.
Wir haben ein einfaches Gerät zum automatischen Bewässern einer Topfpflanze.
Aufgrund der Feuchtigkeit im Topf und der Umgebungstemperatur wird jeweils entschieden, wieviel Wasser in den Topf gepumpt werden soll.

```cpp
<c++ code ohne error handling>
```
Abb/Code 1 : Code Beispiel Bewässerungsfunktion



Verwendet eine Funktion Return-Codes, so muss ein allfälliger Return-Wert als Outputparameter zurückgegeben werden.
Outputparameter können beispielsweise mit Referenzen oder (Smart)-Pointers implementiert werden.
Sie haben jedoch oft den Nachteil, dass deren Intention oftmals aus der reinen Funktionssignatur nicht klar sind, und es zusätzliche Dokumentation braucht.


```cpp

```
Abb 2 : Funktionen mit Return Codes

Die üblichen ... sind verschachtelte if-Anweisungen, Early-Return oder Exceptions.

Fehler aus der Funktion zurück geben:
- status code/bool -> output parameter
- exception

status code auswerten
- verschachtelte if-Anweisungen
- Early-Return
-

Verschachtelte if-Anweisungen skalieren jedoch schlecht mit dem Ablauf, den man in einem Code-Block ausführen möchte.
Die Verschachtelungstiefe nimmt mit jedem zusätzlichen Schritt zu.




Die Behandlung von Seiteneffekten ist in Haskell auf elegante Art und Weise gelöst.
Das erwähnte Beispiel könnte in Haskell folgendermassen aussehen:

```haskell
```

Der Code wird nicht durch die Fehlerbehandlung gestört, aber dennoch ist klar, dass hier Seiteneffekte behandelt werden.
Das Maybe Volume in der Funktionssignatur zeigt, dass die Funktion vielleicht einen Wert zurückgibt.
Vielleicht kommt jedoch nichts zurück.
Das do heisst, dass die in der Funktion aufgerufenen Funktionen vielleicht auch nichts zurückgeben.
Sobald die erste innere Funktion nichts zurückliefert, werden die nachfolgende Aufrufe nicht mehr getätigt, und die Funktion gibt nichts zurück.

```haskell
data Maybe a = Just a | Nothing
```
Abb X : Das Maybe ist ein abstrakter Datentyp, der einen anderen Typen einpackt (to wrap?). Ein Maybe ist entweder einfach ein Wert des eingepackten Typs (Just a) oder nichts (Nothing).






### <Zwischen Titel>

Mehr text ...

### Zusammenfassung

...

### Literatur- und Quellenverzeichnis

[1] ...

### Autor

Raphael Meyer ist Software-Ingenieur mit über zehn Jahren Erfahrung in der Geräteentwicklung. Er interessiert sich stark für Themen in der Software-Entwicklung, die dazu beitragen qualitativ hochstehende Produkte zu entwicklen. Deshalb ist er auch in der Software Crafters Community aktiv. Ausserdem ist Raphael Meyer ein Organisator der C++ Usergroup Zentralschweiz.

[!me.png]

### Kontakt
Internet: [bbv.ch](https://www.bbv.ch/)
Email: [raphael.meyer@bbv.ch](mailto:raphael.meyer@bbv.ch)

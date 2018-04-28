# Cyvasse Projekt
### Mitglieder:
-Nils Niggemann

### Beschreibung:
"Cyvasse" ist ein Strategiespiel aus der Fantasy-Reihe "A Song of Ice and Fire" von George R. R. Martin.
Es handelt sich hierbei um ein Brettspiel, welches in vielen Aspekten an Schach erinnert. Dieses Projekt dient der Entwicklung eines Programms, mit welchem zwei Personen lokal gegeneinander spielen können.
Die Regeln sollen vorläufig entnommen werden von der Seite http://gameofcyvasse.com/ , können aber unter Umständen noch angepasst werden.
Grafiken teils verwendet aus [freepik](https://de.freepik.com), oder selbst erstellt.
### Wie man spielt:
Die genauen Regeln sind in http://gameofcyvasse.com/ zu finden. Zunächst gibt es eine Phase, in der die Spieler bei verdecktem gegnerischen Feld ihre Figuren und Landschaften platzieren können, indem zuerst auf die entsprechende Figur oder Landschaft in der Auswahlleiste geklickt wird und diese dann durch einen Klick auf das Spielfeld an die gewünschte Position bringt. Figuren können auch nach der ersten Platzierung noch ausgewählt werden. Jeder Spieler beendet seinen Aufbau, indem er auf "End Turn" klickt.
Hat das Spiel begonnen, so können Figuren ähnlich bewegt werden, wie in der Aufbauphase, wobei hier die Regeln für die Figurenbewegungen gelten. Ist der "Attack"- Button aktiviert, dann greift die ausgewählte Figur das danach anvisierte Spielfeld an. Eine Bewegung auf ein besetztes Feld ohne gleichzeitigen Angriff ist nicht erlaubt.

### Inhalte:
##### Essentielle Inhalte:
- [x] Grafikunterstützte Oberfläche
  - [x] Texturen für Spielfiguren (10x2) Bilder 128x128 Px
  - [x] Texturen für Spielfeld (Größe: 8x8) Bilder 128x128 Px
- [x] Spielfiguren mit Maus bewegen
  - [x] Nur legale Züge werden zugelassen
  - [x] Spielfigur entfernen, wenn sie geschlagen wurden
- [x] Aufbauphase
  - [x] Wenn Spieler 2 am Zug ist wird der dem anderen Spieler gehörende Teil des Spielfelds abgedeckt

##### Optionale Features:
- [ ] Fehlermeldungen bei nicht legalen Zügen
- [x] Legale Spielzüge werden angezeigt
- [ ] "Zug zurück" Option, "Wiederhol"- Option
- [ ] Speicheroption
- [ ] Anzeige des Regelwerks im Spiel
- [ ] Menü
- [ ] interaktives Tutorial
- [ ] Siegesbildschirm und Zugcounter
- [ ] Sound

## Willkommen!

Sie sind hier, um jmbde-QT zu helfen? Wunderbar, fühlen Sie sich frei und lesen Sie die folgenden Abschnitte, um zu wissen, wie man an etwas arbeitet und woher man Hilfe bekommen kann. Ihr Beitrag ist sehr wichtig, jmbde-QT wird durch Menschen wie Sie immer besser und besser. :smile:

## Welche Art von Beiträgen suchen wir?

- Wenn Ihnen jmbde-QT gefällt, starten Sie dieses Projekt und teilen Sie es mit Ihren Freunden.
- Melden Sie Fehler oder fordern Sie neue Funktionen an unter [opening issues](https://github.com/jmuelbert/jmbde-QT/issues/new/choose). Bitte folgen Sie den Problemvorlagen und stellen Sie detaillierte Informationen zur Verfügung, dies wird den Entwicklern helfen, den Grund des Fehlers zu finden und zu verstehen, welche Funktion Sie genau anfordern.
- Helfen Sie anderen Personen bei Problemen/Anfragen in anderen Plattformen, wenn Sie in der Lage sind, ihnen zu helfen.
- Schreiben Sie Tutorials und Blogs über die Verwendung von jmbde-QT.
- Verbessern Sie die Dokumentation, einschließlich der Markdown-Dateien und der Kommentare in den Codes.
- Schreiben Sie Codes für neue Funktionen oder Fehlerbehebungen.

## Ihr erster Beitrag

**Arbeiten Sie an Ihrer ersten Pull-Anfrage?** Sie können von dieser *freien* Serie [Wie man zu einem Open-Source-Projekt auf GitHub beiträgt] (https://egghead.io/series/how-to-contribute-to-an-open-source-project-on-github) lernen. Im Grunde genommen müssen Sie dieses Repository abspalten, Codes auf Ihre Abspaltung schreiben, eine Pull-Anfrage öffnen, wenn Sie fertig sind, auf Überprüfungen warten und Vorschläge von den Betreuern einbringen.

**Fangen Sie an Software zu entwickeln?** Es gibt einen großen Unterschied zwischen Entwickeln und ambitionierter Programmierung, aber das ist nicht schwer. Das erste, was Sie wissen sollten, ist objektorientierte Programmierung. Im Grunde genommen müssen Sie wissen, wie Klassen in C++ funktionieren, und Sie sollten wissen, dass es eine Regel ist, die Klassendefinitionen in die `.h`/`.hpp`-Dateien und die Implementierung der Funktionen in die `.cpp`-Dateien zu packen. Der Quellcode von jmbde-QT ist ein gutes Beispiel. In einer Suchmaschine nachzuschauen ist für das, was Sie implementieren wollen, ist normalerweise hilfreich. Kopieren und modifizieren Sie den Quellcode, wenn Sie etwas Ähnliches wie eine bestehende Funktion implementieren wollen. Wenn Sie nach einer IDE zum Entwickeln suchen, ist [VS Code](https://code.visualstudio.com/) wahrscheinlich eine gute Wahl.

**Erstes Mal zu Qt?** Keine Angst, Qt ist nicht schwer zu beginnen. Sie müssen zuerst Qt>=5.15 und CMake>=3.5 installieren. Linux-Benutzer können sie mit dem Paketmanager auf Ihrem System installieren. Windows-Benutzer können Qt [hier](https://www.qt.io/download) herunterladen, und es wird empfohlen, [Visual Studio](https://visualstudio.microsoft.com/) zu verwenden und das CMake-Plugin zu installieren. Lesen Sie den Abschnitt [build from source](https://github.com/jmuelbert/jmbde-QT), um zu erfahren, wie man baut. Lesen Sie den Abschnitt [Qt docs](https://doc.qt.io/), um zu erfahren, wie die in Qt eingebauten Widgets verwendet werden, wie die Benutzeroberfläche gestaltet wird und wie die [Signale und Slots](https://doc.qt.io/qt-5/signalsandslots.html) verwendet werden. Normalerweise benötigen Sie nichts aus dem std-Namensraum, verwenden Sie zum Beispiel `QString` statt `std::string`.

**Wissen Sie nicht, wo Sie anfangen sollen?** Sie können damit anfangen, die [issues](https://github.com/jmuelbert/jmbde-QT/issues) durchzusehen und ein Thema zu finden, das Sie interessiert. Die [guten Erstausgaben](https://github.com/jmuelbert/jmbde-QT/issues?q=is%3Aissue+is%3Aopen+Label%3A%22gute+Erste+Erste+Ausgabe%22) könnte für Sie geeignet sein.

## Vor dem Schreiben von Codes

Bitte öffnen Sie ein Problem (beschreiben Sie das Merkmal/den Fehler wie normale Probleme und sagen Sie, dass Sie daran arbeiten werden, wahrscheinlich mit einem Entwurf, wie Sie es implementieren möchten), bevor Sie Codes für eine Pull-Anfrage schreiben, aus diesen Gründen:

1. Sie können Hilfe von anderen erhalten.
2. Andere können wissen, dass Sie daran arbeiten, dies erspart Ihnen mögliche Doppelarbeiten.
3. Sie werden benachrichtigt, wenn diese Funktion nicht akzeptiert wird, oder wenn der "Fehler" tatsächlich kein Fehler ist usw., was Ihnen Zeit spart.

## Regeln für Beiträge

- Denken Sie daran, dass es das Ziel ist, ein jmbde-QT für Benutzer, nicht für Entwickler zu erstellen.
- Tun Sie eine Sache bei einer Pull-Anfrage. Wenn Sie mehrere Funktionen hinzufügen/mehrere Fehler beheben wollen und diese nicht relevant sind, öffnen Sie mehrere Pull-Requests. Möglicherweise müssen Sie mehrere Zweige erstellen, um mehrere Pull-Anfragen zu öffnen, Sie können das Verzweigen von Git [hier] lernen (https://learngitbranching.js.org/).
- Fügen Sie neue Funktionen auf dem Master-Zweig hinzu und beheben Sie den Fehler auf dem letzten aktiven Zweig (Master-, Beta- und Stable-Zweig), in dem der Fehler aufgetreten ist.
- Bitte schreiben Sie [clear commit messages](https://chris.beams.io/posts/git-commit/). Es wird auch empfohlen, [Konventionelle Commits](https://www.conventionalcommits.org/) zu schreiben. Sie können [commitizen/cz-cli](https://github.com/commitizen/cz-cli) verwenden, um Commit-Nachrichten zu schreiben. Die Regeln sind jedoch optional, der Schlüssel ist, dass andere und Sie selbst in Zukunft verstehen sollten, was geändert wurde und warum diese Änderungen vorgenommen wurden.
- Benutzen Sie Clang-Format 9 (benutzen Sie `clang-format --version`, um Ihre Version zu überprüfen, Sie müssen möglicherweise den Binärpfad für Ihre IDE im Clang-Format einstellen, z.B. kann die Standardversion von clang-format im VS-Code clang-format-6 sein) und `.clang-format` im Wurzelverzeichnis, um Ihre Codes zu formatieren.
- Entfernen Sie keine Features, es sei denn, es ist notwendig. Fügen Sie stattdessen eine Option zur Deaktivierung einer Funktion hinzu.
- Halten Sie die Einstellungsdatei die ganze Zeit abwärtskompatibel.
- Windows, Linux und Mac OS sollten unterstützt werden.
- Beide hell/dunkel Systemthemen sollten unterstützt werden.
- Jeder sollte sich an den [Verhaltenskodex](CODE_OF_CONDUCT.md) halten, um eine belästigungsfreie Gemeinschaft aufzubauen.

## FAQ

- Kann ich es gut machen, wenn ich gerade erst angefangen habe?
  - Jeder weiß am Anfang nichts. Machen Sie sich keine Sorgen, unsere coolen Mitwirkenden helfen Ihnen, wenn Sie auf Schwierigkeiten stoßen. Wenn Sie :Herz: Open Source und weiter versuchen, wird alles besser und besser werden.
- Muss ich etwas über CMake lernen?
  - Nein, Sie müssen nur wissen, wie man [aus dem Quellcode baut] (https://github.com/jmuelbert/jmbde-QT).
- Einige Dateien fehlen beim Kompilieren.
  - Wenn die CI-Tests bestanden werden, liegt das wahrscheinlich daran, dass die Untermodule aktualisiert werden. Sie können die folgenden Befehle ausführen:

    ````sh
    git add .
    git reset --hard
    git submodule update --init
    ```

    Sie können auch `git rm` alle Submodule versuchen und sie dann erneut initialisieren oder sogar das Repo auf Ihrer Platte löschen und erneut klonen.

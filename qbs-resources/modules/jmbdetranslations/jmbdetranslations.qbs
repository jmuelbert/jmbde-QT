import qbs 1.0
import qbs.File
import qbs.TextFile

Module {
    additionalProductTypes: ["jmbde.desktop.file"]

    Rule {
        multiplex: true
        inputs: ["jmbde.desktop.template", "jmbde.desktop.translations"]

        outputArtifacts: {
            var artifacts = [];
            for (var i in inputs["jmbde.desktop.template"]) {
                var input = inputs["jmbde.desktop.template"][i];
                var artifact = {
                    filePath: input.fileName.replace(".in", ""),
                    fileTags: ["jmbde.desktop.file"]
                };
                artifacts.push(artifact);
            }
            return artifacts;
        }
        outputFileTags: ["jmbde.desktop.file"]

        prepare: {
            var cmds = [];
            for (var i in inputs["jmbde.desktop.template"]) {
                var input = inputs["jmbde.desktop.template"][i];
                var cmd = new JavaScriptCommand();
                cmd.description = "merge translations of " + input.filePath;
                cmd.highlight = "filegen";
                cmd.inputFilePath = input.filePath;
                cmd.sourceCode = function() {
                    // Collect translations
                    var translations = "";
                    for (var j in inputs["jmbde.desktop.translations"]) {
                        var t = inputs["jmbde.desktop.translations"][j];
                        var file = new TextFile(t.filePath, TextFile.ReadOnly);
                        while (!file.atEof()) {
                            var line = file.readLine();
                            var re = /\w+\[\w+\]=/
                            if (line.match(re) && !line.startsWith("Icon"))
                                translations += line + "\n";
                        }
                        file.close();
                    }

                    // Replace marker with translations
                    var contents = "";
                    var file = new TextFile(inputFilePath, TextFile.ReadOnly);
                    while (!file.atEof()) {
                        var line = file.readLine();
                        var re = /#TRANSLATIONS/;
                        if (line.match(re))
                            contents += translations;
                        else
                            contents += line + "\n";
                    }
                    file.close();
                    file = new TextFile(output.filePath, TextFile.WriteOnly);
                    file.write(contents);
                    file.close();
                };
                cmds.push(cmd);
            }
            return cmds;
        }
    }
}
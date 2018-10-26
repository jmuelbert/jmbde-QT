import qbs
import qbs.TextFile

Product {
    name: "app_version_header"
    type: "hpp"

    Group {
        files: [ "app_version.h.in" ]
        fileTags: [ "hpp.in" ]
    }

    Depends { name: "app" }

    Rule {
        inputs: [ "hpp.in" ]
        Artifact {
            filePath: "app/app_version.h"
            fileTags: "hpp"
        }

        prepare: {
            var cmd = new JavaScriptCommand();
            cmd.description = "generating app_version.h";
            cmd.highlight = "codegen";
            cmd.onWindows = (product.moduleProperty("qbs", "targetOS").contains("windows"));
            cmd.sourceCode = function() {
                var file = new TextFile(input.filePath);
                var content = file.readAll();
                // replace quoted quotes
                content = content.replace(/\\\"/g, '"');
                // replace Windows line endings
                if (onWindows)
                    content = content.replace(/\r\n/g, "\n");
                // replace the magic qmake incantations
                content = content.replace(/(\n#define APP_VERSION_DISPLAY_DEF) .+\n/, "$1 "
                        + product.moduleProperty("app", "app_display_version") + "\n");
                content = content.replace(/(\n#define APP_VERSION) .+\n/, "$1 "
                        + product.moduleProperty("app", "app_version") + "\n");
                content = content.replace(/(\n#define APP_VERSION_MAJOR) .+\n/, "$1 "
                        + product.moduleProperty("app", "app_version_major") + "\n");
                content = content.replace(/(\n#define APP_VERSION_MINOR) .+\n/, "$1 "
                        + product.moduleProperty("APP", "app_version_minor") + "\n");
                content = content.replace(/(\n#define APP_VERSION_RELEASE) .+\n/, "$1 "
                        + product.moduleProperty("app", "app_version_release") + "\n");
                content = content.replace("$${APP_COPYRIGHT_YEAR}",
                        product.moduleProperty("app", "app_copyright_year"));
                content = content.replace("$${APP_DISPLAY_NAME}",
                        product.moduleProperty("app", "app_display_name"));
                content = content.replace("$${APP_ID}",
                        product.moduleProperty("app", "app_id"));
                content = content.replace("$${APP_CASED_ID}",
                        product.moduleProperty("app", "app_cased_id"));
                file = new TextFile(output.filePath, TextFile.WriteOnly);
                file.truncate();
                file.write(content);
                file.close();
            }
            return cmd;
        }
    }

    Export {
        Depends { name: "cpp" }
        cpp.includePaths: product.buildDirectory
    }
}

import qbs

AppleApplicationDiskImage {
    condition: qbs.targetOS.contains("macos")
    name: "Cocoa Application DMG"
    targetName: "jmbde-" + version
    version: "1.0"

    Depends { name: "jmbde" }
    Depends { name: "ib" }

    files: [
        "jmbde/dmg.iconset",
        "jmbde/en_US.lproj/LICENSE",
        "jmbde/de_DE.lproj/LICENSE",
    ]

    // set to false to use a solid-color background (see dmg.backgroundColor below)
    property bool useImageBackground: true
    Group {
        condition: useImageBackground
        files: ["CocoaApplication/background*"]
    }

    dmg.backgroundColor: "#41cd52"
    dmg.badgeVolumeIcon: true
    dmg.iconPositions: [
        {"x": 200, "y": 200, "path": "jmbde.app"},
        {"x": 400, "y": 200, "path": "Applications"}
    ]
    dmg.windowX: 420
    dmg.windowY: 250
    dmg.windowWidth: 600
    dmg.windowHeight: 422 // this *includes* the macOS title bar height of 22
    dmg.iconSize: 64
}

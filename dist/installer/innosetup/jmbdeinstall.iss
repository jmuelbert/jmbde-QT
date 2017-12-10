; -- jmbdeinstall.iss --

#pragma option -v+
#pragma verboselevel 9

;#define Debug

;#define AppEnterprise

#define MyAppName "jmbde"
#define MyAppVersion GetFileVersion("..\..\..\..\build-jmbde-Desktop_Qt_5_9_3_MSVC2017_64bit-Release\bin\jmbde.exe")
#define MyAppPublisher "J�rgen M�lbert"
#define MyAppUrl "http://jmuelbert.github.io/jmbde-QT/"
#define MyAppExeName "jmbde.exe"

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId=4266AC04-A059-4542-B7EC-E4765D5EC2A3
AppName={#MyAppName}
AppVersion={#MyAppVersion}
; AppVerName={#AppName,#AppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppUrl}
AppSupportURL={#MyAppUrl}
DefaultDirName={pf}\{#MyAppName}
DefaultGroupName={#MyAppName}
AllowNoIcons=yes
LicenseFile="..\..\..\EUPL-1.2_en.txt"
OutputDir=..\..\..\..\dist
OutputBaseFilename={#MyAppName}_{#MyAppVersion}
Compression=lzma2
SolidCompression=yes
; Uncomment the following line to disable the "Select Setup Language"
; dialog and have it rely solely on auto-detection.
;ShowLanguageDialog=no
; If you want all languages to be listed in the "Select Setup Language"
; dialog, even those that can't be displayed in the active code page,
; uncomment the following line. Note: Unicode Inno Setup always displays
; all languages.
;ShowUndisplayableLanguages=yes

; "ArchitecturesInstallIn64BitMode=x64" requests that the install be
; done in "64-bit mode" on x64, meaning it should use the native
; 64-bit Program Files directory and the 64-bit view of the registry.
; On all other architectures it will install in "32-bit mode".
ArchitecturesInstallIn64BitMode=x64
; Note: We don't set ProcessorsAllowed because we want this
; installation to run on all architectures (including Itanium,
; since it's capable of running 32-bit code too).

[Languages]
Name: en; MessagesFile: "compiler:Default.isl"
Name: de; MessagesFile: "compiler:Languages\German.isl"

[Components]
Name: "main"; Description: "Main Files"; Types: full compact custom; Flags: fixed
Name: "help"; Description: "Help Files"; Types: full
Name: "translations\english"; Description: "English"; Types: full
Name: "translations\dutch"; Description: "Dutch"; Types: full

[Types]
Name: "full"; Description: "Full installation"
Name: "compact"; Description: "Compact installation"
Name: "custom"; Description: "Custom installation"; Flags: iscustom

[Files]
; Install MyProg-x64.exe if running in 64-bit mode (x64; see above),
; MyProg.exe otherwise.
; Place all x64 files here
Source: "..\..\..\..\build-jmbde-Desktop_Qt_5_9_3_MSVC2017_64bit-Release\bin\jmbde.exe"; DestDir: "{app}"; DestName: "jmbde.exe"; Check: Is64BitInstallMode
; The 32-Bit DLL's
; The QTCore Libs
Source: "C:\Qt\5.9.3\msvc2017_64\bin\D3Dcompiler_47.dll"; DestDir: "{app}"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "C:\Qt\5.9.3\msvc2017_64\bin\libEGL.dll"; DestDir: "{app}"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "C:\Qt\5.9.3\msvc2017_64\bin\libGLESV2.dll"; DestDir: "{app}"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "C:\Qt\5.9.3\msvc2017_64\bin\opengl32sw.dll"; DestDir: "{app}"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "C:\Qt\5.9.3\msvc2017_64\bin\Qt5Core.dll"; DestDir: "{app}"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "C:\Qt\5.9.3\msvc2017_64\bin\Qt5Gui.dll"; DestDir: "{app}"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "C:\Qt\5.9.3\msvc2017_64\bin\Qt5Help.dll"; DestDir: "{app}"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "C:\Qt\5.9.3\msvc2017_64\bin\Qt5PrintSupport.dll"; DestDir: "{app}"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "C:\Qt\5.9.3\msvc2017_64\bin\Qt5Sql.dll"; DestDir: "{app}"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "C:\Qt\5.9.3\msvc2017_64\bin\Qt5Svg.dll"; DestDir: "{app}"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "C:\Qt\5.9.3\msvc2017_64\bin\Qt5Widgets.dll"; DestDir: "{app}"; Check: Is64BitInstallMode; Flags: solidbreak
; The QT Plugins
;
; Icons
Source: "C:\Qt\5.9.3\msvc2017_64\plugins\iconengines\qsvgicon.dll"; DestDir: "{app}\iconengines"; Check: Is64BitInstallMode; Flags: solidbreak
; Images
Source: "C:\Qt\5.9.3\msvc2017_64\plugins\imageformats\qgif.dll"; DestDir: "{app}\imageformats"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "C:\Qt\5.9.3\msvc2017_64\plugins\imageformats\qicns.dll"; DestDir: "{app}\imageformats"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "C:\Qt\5.9.3\msvc2017_64\plugins\imageformats\qico.dll"; DestDir: "{app}\imageformats"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "C:\Qt\5.9.3\msvc2017_64\plugins\imageformats\qjpeg.dll"; DestDir: "{app}\imageformats"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "C:\Qt\5.9.3\msvc2017_64\plugins\imageformats\qsvg.dll"; DestDir: "{app}\imageformats"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "C:\Qt\5.9.3\msvc2017_64\plugins\imageformats\qtga.dll"; DestDir: "{app}\imageformats"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "C:\Qt\5.9.3\msvc2017_64\plugins\imageformats\qtiff.dll"; DestDir: "{app}\imageformats"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "C:\Qt\5.9.3\msvc2017_64\plugins\imageformats\qwbmp.dll"; DestDir: "{app}\imageformats"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "C:\Qt\5.9.3\msvc2017_64\plugins\imageformats\qwebp.dll"; DestDir: "{app}\imageformats"; Check: Is64BitInstallMode; Flags: solidbreak
; Platforms
Source: "C:\Qt\5.9.3\msvc2017_64\plugins\platforms\qwindows.dll"; DestDir: "{app}\platforms"; Check: Is64BitInstallMode; Flags: solidbreak
; Printsupport
Source: "C:\Qt\5.9.3\msvc2017_64\plugins\printsupport\windowsprintersupport.dll"; DestDir: "{app}\printsupport"; Check: Is64BitInstallMode; Flags: solidbreak
; Sql
Source: "C:\Qt\5.9.3\msvc2017_64\plugins\sqldrivers\qsqlite.dll"; DestDir: "{app}\sqldrivers"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "C:\Qt\5.9.3\msvc2017_64\plugins\sqldrivers\qsqlmysql.dll"; DestDir: "{app}\sqldrivers"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "C:\Qt\5.9.3\msvc2017_64\plugins\sqldrivers\qsqlodbc.dll"; DestDir: "{app}\sqldrivers"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "C:\Qt\5.9.3\msvc2017_64\plugins\sqldrivers\qsqlpsql.dll"; DestDir: "{app}\sqldrivers"; Check: Is64BitInstallMode; Flags: solidbreak
; Translations
Source: "C:\Qt\5.9.3\msvc2017_64\translations\qt_ar.qm"; Destdir: "{app}\translations"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "C:\Qt\5.9.3\msvc2017_64\translations\qt_bg.qm"; Destdir: "{app}\translations"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "C:\Qt\5.9.3\msvc2017_64\translations\qt_ca.qm"; Destdir: "{app}\translations"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "C:\Qt\5.9.3\msvc2017_64\translations\qt_cs.qm"; Destdir: "{app}\translations"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "C:\Qt\5.9.3\msvc2017_64\translations\qt_da.qm"; Destdir: "{app}\translations"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "C:\Qt\5.9.3\msvc2017_64\translations\qt_de.qm"; Destdir: "{app}\translations"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "C:\Qt\5.9.3\msvc2017_64\translations\qt_en.qm"; Destdir: "{app}\translations"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "C:\Qt\5.9.3\msvc2017_64\translations\qt_es.qm"; Destdir: "{app}\translations"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "C:\Qt\5.9.3\msvc2017_64\translations\qt_fa.qm"; Destdir: "{app}\translations"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "C:\Qt\5.9.3\msvc2017_64\translations\qt_fi.qm"; Destdir: "{app}\translations"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "C:\Qt\5.9.3\msvc2017_64\translations\qt_fr.qm"; Destdir: "{app}\translations"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "C:\Qt\5.9.3\msvc2017_64\translations\qt_gl.qm"; Destdir: "{app}\translations"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "C:\Qt\5.9.3\msvc2017_64\translations\qt_he.qm"; Destdir: "{app}\translations"; Check: Is64BitInstallMode; Flags: solidbreak
;
; jmbde tranlations
; The Translations
Source: "..\..\..\..\build-jmbde-Desktop_Qt_5_9_3_MSVC2017_64bit-Release\share\jmbde\translations\jmbde_ar_DZ.qm"; DestDir: "{app}\translations"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "..\..\..\..\build-jmbde-Desktop_Qt_5_9_3_MSVC2017_64bit-Release\share\jmbde\translations\jmbde_bg.qm"; DestDir: "{app}\translations"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "..\..\..\..\build-jmbde-Desktop_Qt_5_9_3_MSVC2017_64bit-Release\share\jmbde\translations\jmbde_cs.qm"; DestDir: "{app}\translations"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "..\..\..\..\build-jmbde-Desktop_Qt_5_9_3_MSVC2017_64bit-Release\share\jmbde\translations\jmbde_de.qm"; DestDir: "{app}\translations"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "..\..\..\..\build-jmbde-Desktop_Qt_5_9_3_MSVC2017_64bit-Release\share\jmbde\translations\jmbde_en.qm"; DestDir: "{app}\translations"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "..\..\..\..\build-jmbde-Desktop_Qt_5_9_3_MSVC2017_64bit-Release\share\jmbde\translations\jmbde_es.qm"; DestDir: "{app}\translations"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "..\..\..\..\build-jmbde-Desktop_Qt_5_9_3_MSVC2017_64bit-Release\share\jmbde\translations\jmbde_fi.qm"; DestDir: "{app}\translations"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "..\..\..\..\build-jmbde-Desktop_Qt_5_9_3_MSVC2017_64bit-Release\share\jmbde\translations\jmbde_fr.qm"; DestDir: "{app}\translations"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "..\..\..\..\build-jmbde-Desktop_Qt_5_9_3_MSVC2017_64bit-Release\share\jmbde\translations\jmbde_he.qm"; DestDir: "{app}\translations"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "..\..\..\..\build-jmbde-Desktop_Qt_5_9_3_MSVC2017_64bit-Release\share\jmbde\translations\jmbde_hu.qm"; DestDir: "{app}\translations"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "..\..\..\..\build-jmbde-Desktop_Qt_5_9_3_MSVC2017_64bit-Release\share\jmbde\translations\jmbde_it.qm"; DestDir: "{app}\translations"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "..\..\..\..\build-jmbde-Desktop_Qt_5_9_3_MSVC2017_64bit-Release\share\jmbde\translations\jmbde_ja.qm"; DestDir: "{app}\translations"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "..\..\..\..\build-jmbde-Desktop_Qt_5_9_3_MSVC2017_64bit-Release\share\jmbde\translations\jmbde_nb.qm"; DestDir: "{app}\translations"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "..\..\..\..\build-jmbde-Desktop_Qt_5_9_3_MSVC2017_64bit-Release\share\jmbde\translations\jmbde_nl.qm"; DestDir: "{app}\translations"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "..\..\..\..\build-jmbde-Desktop_Qt_5_9_3_MSVC2017_64bit-Release\share\jmbde\translations\jmbde_pl.qm"; DestDir: "{app}\translations"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "..\..\..\..\build-jmbde-Desktop_Qt_5_9_3_MSVC2017_64bit-Release\share\jmbde\translations\jmbde_pt.qm"; DestDir: "{app}\translations"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "..\..\..\..\build-jmbde-Desktop_Qt_5_9_3_MSVC2017_64bit-Release\share\jmbde\translations\jmbde_pt_PT.qm"; DestDir: "{app}\translations"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "..\..\..\..\build-jmbde-Desktop_Qt_5_9_3_MSVC2017_64bit-Release\share\jmbde\translations\jmbde_ru.qm"; DestDir: "{app}\translations"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "..\..\..\..\build-jmbde-Desktop_Qt_5_9_3_MSVC2017_64bit-Release\share\jmbde\translations\jmbde_tr.qm"; DestDir: "{app}\translations"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "..\..\..\..\build-jmbde-Desktop_Qt_5_9_3_MSVC2017_64bit-Release\share\jmbde\translations\jmbde_uk.qm"; DestDir: "{app}\translations"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "..\..\..\..\build-jmbde-Desktop_Qt_5_9_3_MSVC2017_64bit-Release\share\jmbde\translations\jmbde_zh.qm"; DestDir: "{app}\translations"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "..\..\..\..\build-jmbde-Desktop_Qt_5_9_3_MSVC2017_64bit-Release\share\jmbde\translations\jmbde_zh_TW.qm"; DestDir: "{app}\translations"; Check: Is64BitInstallMode; Flags: solidbreak

; Place all x86 files here, first one should be marked 'solidbreak'
Source: "..\..\..\..\build-jmbde-Desktop_Qt_5_9_3_MSVC2015_32bit-Release\bin\jmbde.exe"; DestDir: "{app}"; Check: not Is64BitInstallMode; Flags: solidbreak
; The 32-Bit DLL's
; The QTCore Libs
Source: "C:\Qt\5.9.3\\msvc2015\bin\D3Dcompiler_47.dll"; DestDir: "{app}"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "C:\Qt\5.9.3\\msvc2015\bin\libEGL.dll"; DestDir: "{app}"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "C:\Qt\5.9.3\\msvc2015\bin\libGLESV2.dll"; DestDir: "{app}"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "C:\Qt\5.9.3\\msvc2015\bin\opengl32sw.dll"; DestDir: "{app}"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "C:\Qt\5.9.3\\msvc2015\bin\Qt5Core.dll"; DestDir: "{app}"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "C:\Qt\5.9.3\\msvc2015\bin\Qt5Gui.dll"; DestDir: "{app}"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "C:\Qt\5.9.3\\msvc2015\bin\Qt5Help.dll"; DestDir: "{app}"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "C:\Qt\5.9.3\\msvc2015\bin\Qt5PrintSupport.dll"; DestDir: "{app}"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "C:\Qt\5.9.3\\msvc2015\bin\Qt5Sql.dll"; DestDir: "{app}"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "C:\Qt\5.9.3\\msvc2015\bin\Qt5Svg.dll"; DestDir: "{app}"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "C:\Qt\5.9.3\\msvc2015\bin\Qt5Widgets.dll"; DestDir: "{app}"; Check: not Is64BitInstallMode; Flags: solidbreak
; The QT Plugins
;
; Icons
Source: "C:\Qt\5.9.3\msvc2015\plugins\iconengines\qsvgicon.dll"; DestDir: "{app}\iconengines"; Check: not Is64BitInstallMode; Flags: solidbreak
; Images
Source: "C:\Qt\5.9.3\msvc2015\plugins\imageformats\qgif.dll"; DestDir: "{app}\imageformats"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "C:\Qt\5.9.3\msvc2015\plugins\imageformats\qicns.dll"; DestDir: "{app}\imageformats"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "C:\Qt\5.9.3\msvc2015\plugins\imageformats\qico.dll"; DestDir: "{app}\imageformats"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "C:\Qt\5.9.3\msvc2015\plugins\imageformats\qjpeg.dll"; DestDir: "{app}\imageformats"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "C:\Qt\5.9.3\msvc2015\plugins\imageformats\qsvg.dll"; DestDir: "{app}\imageformats"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "C:\Qt\5.9.3\msvc2015\plugins\imageformats\qtga.dll"; DestDir: "{app}\imageformats"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "C:\Qt\5.9.3\msvc2015\plugins\imageformats\qtiff.dll"; DestDir: "{app}\imageformats"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "C:\Qt\5.9.3\msvc2015\plugins\imageformats\qwbmp.dll"; DestDir: "{app}\imageformats"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "C:\Qt\5.9.3\msvc2015\plugins\imageformats\qwebp.dll"; DestDir: "{app}\imageformats"; Check: not Is64BitInstallMode; Flags: solidbreak
; Platforms
Source: "C:\Qt\5.9.3\msvc2015\plugins\platforms\qwindows.dll"; DestDir: "{app}\platforms"; Check: not Is64BitInstallMode; Flags: solidbreak
; Printsupport
Source: "C:\Qt\5.9.3\msvc2015\plugins\printsupport\windowsprintersupport.dll"; DestDir: "{app}\printsupport"; Check: not Is64BitInstallMode; Flags: solidbreak
; Sql
Source: "C:\Qt\5.9.3\msvc2015\plugins\sqldrivers\qsqlite.dll"; DestDir: "{app}\sqldrivers"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "C:\Qt\5.9.3\msvc2015\plugins\sqldrivers\qsqlmysql.dll"; DestDir: "{app}\sqldrivers"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "C:\Qt\5.9.3\msvc2015\plugins\sqldrivers\qsqlodbc.dll"; DestDir: "{app}\sqldrivers"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "C:\Qt\5.9.3\msvc2015\plugins\sqldrivers\qsqlpsql.dll"; DestDir: "{app}\sqldrivers"; Check: not Is64BitInstallMode; Flags: solidbreak
; Translations
Source: "C:\Qt\5.9.3\msvc2015\translations\qt_ar.qm"; Destdir: "{app}\translations"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "C:\Qt\5.9.3\msvc2015\translations\qt_bg.qm"; Destdir: "{app}\translations"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "C:\Qt\5.9.3\msvc2015\translations\qt_ca.qm"; Destdir: "{app}\translations"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "C:\Qt\5.9.3\msvc2015\translations\qt_cs.qm"; Destdir: "{app}\translations"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "C:\Qt\5.9.3\msvc2015\translations\qt_da.qm"; Destdir: "{app}\translations"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "C:\Qt\5.9.3\msvc2015\translations\qt_de.qm"; Destdir: "{app}\translations"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "C:\Qt\5.9.3\msvc2015\translations\qt_en.qm"; Destdir: "{app}\translations"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "C:\Qt\5.9.3\msvc2015\translations\qt_es.qm"; Destdir: "{app}\translations"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "C:\Qt\5.9.3\msvc2015\translations\qt_fa.qm"; Destdir: "{app}\translations"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "C:\Qt\5.9.3\msvc2015\translations\qt_fi.qm"; Destdir: "{app}\translations"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "C:\Qt\5.9.3\msvc2015\translations\qt_fr.qm"; Destdir: "{app}\translations"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "C:\Qt\5.9.3\msvc2015\translations\qt_gl.qm"; Destdir: "{app}\translations"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "C:\Qt\5.9.3\msvc2015\translations\qt_he.qm"; Destdir: "{app}\translations"; Check: not Is64BitInstallMode; Flags: solidbreak
;
; jmbde tranlations
; The Translations
Source: "..\..\..\..\build-jmbde-Desktop_Qt_5_9_3_MSVC2015_32bit-Release\share\jmbde\translations\jmbde_ar_DZ.qm"; DestDir: "{app}\translations"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "..\..\..\..\build-jmbde-Desktop_Qt_5_9_3_MSVC2015_32bit-Release\share\jmbde\translations\jmbde_bg.qm"; DestDir: "{app}\translations"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "..\..\..\..\build-jmbde-Desktop_Qt_5_9_3_MSVC2015_32bit-Release\share\jmbde\translations\jmbde_cs.qm"; DestDir: "{app}\translations"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "..\..\..\..\build-jmbde-Desktop_Qt_5_9_3_MSVC2015_32bit-Release\share\jmbde\translations\jmbde_de.qm"; DestDir: "{app}\translations"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "..\..\..\..\build-jmbde-Desktop_Qt_5_9_3_MSVC2015_32bit-Release\share\jmbde\translations\jmbde_en.qm"; DestDir: "{app}\translations"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "..\..\..\..\build-jmbde-Desktop_Qt_5_9_3_MSVC2015_32bit-Release\share\jmbde\translations\jmbde_es.qm"; DestDir: "{app}\translations"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "..\..\..\..\build-jmbde-Desktop_Qt_5_9_3_MSVC2015_32bit-Release\share\jmbde\translations\jmbde_fi.qm"; DestDir: "{app}\translations"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "..\..\..\..\build-jmbde-Desktop_Qt_5_9_3_MSVC2015_32bit-Release\share\jmbde\translations\jmbde_fr.qm"; DestDir: "{app}\translations"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "..\..\..\..\build-jmbde-Desktop_Qt_5_9_3_MSVC2015_32bit-Release\share\jmbde\translations\jmbde_he.qm"; DestDir: "{app}\translations"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "..\..\..\..\build-jmbde-Desktop_Qt_5_9_3_MSVC2015_32bit-Release\share\jmbde\translations\jmbde_hu.qm"; DestDir: "{app}\translations"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "..\..\..\..\build-jmbde-Desktop_Qt_5_9_3_MSVC2015_32bit-Release\share\jmbde\translations\jmbde_it.qm"; DestDir: "{app}\translations"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "..\..\..\..\build-jmbde-Desktop_Qt_5_9_3_MSVC2015_32bit-Release\share\jmbde\translations\jmbde_ja.qm"; DestDir: "{app}\translations"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "..\..\..\..\build-jmbde-Desktop_Qt_5_9_3_MSVC2015_32bit-Release\share\jmbde\translations\jmbde_nb.qm"; DestDir: "{app}\translations"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "..\..\..\..\build-jmbde-Desktop_Qt_5_9_3_MSVC2015_32bit-Release\share\jmbde\translations\jmbde_nl.qm"; DestDir: "{app}\translations"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "..\..\..\..\build-jmbde-Desktop_Qt_5_9_3_MSVC2015_32bit-Release\share\jmbde\translations\jmbde_pl.qm"; DestDir: "{app}\translations"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "..\..\..\..\build-jmbde-Desktop_Qt_5_9_3_MSVC2015_32bit-Release\share\jmbde\translations\jmbde_pt.qm"; DestDir: "{app}\translations"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "..\..\..\..\build-jmbde-Desktop_Qt_5_9_3_MSVC2015_32bit-Release\share\jmbde\translations\jmbde_pt_PT.qm"; DestDir: "{app}\translations"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "..\..\..\..\build-jmbde-Desktop_Qt_5_9_3_MSVC2015_32bit-Release\share\jmbde\translations\jmbde_ru.qm"; DestDir: "{app}\translations"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "..\..\..\..\build-jmbde-Desktop_Qt_5_9_3_MSVC2015_32bit-Release\share\jmbde\translations\jmbde_tr.qm"; DestDir: "{app}\translations"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "..\..\..\..\build-jmbde-Desktop_Qt_5_9_3_MSVC2015_32bit-Release\share\jmbde\translations\jmbde_uk.qm"; DestDir: "{app}\translations"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "..\..\..\..\build-jmbde-Desktop_Qt_5_9_3_MSVC2015_32bit-Release\share\jmbde\translations\jmbde_zh.qm"; DestDir: "{app}\translations"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "..\..\..\..\build-jmbde-Desktop_Qt_5_9_3_MSVC2015_32bit-Release\share\jmbde\translations\jmbde_zh_TW.qm"; DestDir: "{app}\translations"; Check: not Is64BitInstallMode; Flags: solidbreak

;
; Place all common files here, first one should be marked 'solidbreak'
;
;
;
; Licenses and Documentation
Source: "..\..\..\EUPL-1.2_de.txt"; DestDir: "{app}"; Flags: solidbreak
Source: "..\..\..\EUPL-1.2_en.txt"; DestDir: "{app}"; Flags: solidbreak
Source: "..\..\..\README.md"; DestDir: "{app}"; Flags: isreadme

[Icons]
Name: "{group}\Juergen Muelbert"; Filename: "{app}\jmbde.exe"


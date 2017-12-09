; -- jmbdeinstall.iss --

[Setup]
AppName=jmbde
AppVersion=0.4.7
DefaultDirName={pf}\jmbde
DefaultGroupName=Juergen Muelbert
UninstallDisplayIcon={app}\jmdbe.exe
Compression=lzma2
SolidCompression=yes
OutputDir=userdocs:Inno Setup Examples Output
; "ArchitecturesInstallIn64BitMode=x64" requests that the install be
; done in "64-bit mode" on x64, meaning it should use the native
; 64-bit Program Files directory and the 64-bit view of the registry.
; On all other architectures it will install in "32-bit mode".
ArchitecturesInstallIn64BitMode=x64
; Note: We don't set ProcessorsAllowed because we want this
; installation to run on all architectures (including Itanium,
; since it's capable of running 32-bit code too).

[Files]
; Install MyProg-x64.exe if running in 64-bit mode (x64; see above),
; MyProg.exe otherwise.
; Place all x64 files here
Source: "bin-x64\jmbde.exe"; DestDir: "{app}"; DestName: "jmbde.exe"; Check: Is64BitInstallMode
; The 32-Bit DLL's
; The QTCore Libs
Source: "bin-x64\D3Dcompiler_47.dll"; DestDir: "{app}"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "bin-x64\libEGL.dll"; DestDir: "{app}"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "bin-x64\libGLESV2.dll"; DestDir: "{app}"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "bin-x64\opengl32sw.dll"; DestDir: "{app}"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "bin-x64\Qt5Core.dll"; DestDir: "{app}"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "bin-x64\Qt5Gui.dll"; DestDir: "{app}"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "bin-x64\Qt5Help.dll"; DestDir: "{app}"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "bin-x64\Qt5PrintSupport.dll"; DestDir: "{app}"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "bin-x64\Qt5Sql.dll"; DestDir: "{app}"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "bin-x64\Qt5Svg.dll"; DestDir: "{app}"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "bin-x64\Qt5Widgets.dll"; DestDir: "{app}"; Check: Is64BitInstallMode; Flags: solidbreak
; The QT Plugins
;
; Icons
Source: "bin-x64\iconengines\qsvgicon.dll"; DestDir: "{app}\iconengines"; Check: Is64BitInstallMode; Flags: solidbreak
; Images
Source: "bin-x64\imageformats\qgif.dll"; DestDir: "{app}\imageformats"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "bin-x64\imageformats\qicns.dll"; DestDir: "{app}\imageformats"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "bin-x64\imageformats\qico.dll"; DestDir: "{app}\imageformats"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "bin-x64\imageformats\qjpeg.dll"; DestDir: "{app}\imageformats"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "bin-x64\imageformats\qsvg.dll"; DestDir: "{app}\imageformats"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "bin-x64\imageformats\qtga.dll"; DestDir: "{app}\imageformats"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "bin-x64\imageformats\qtiff.dll"; DestDir: "{app}\imageformats"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "bin-x64\imageformats\qwbmp.dll"; DestDir: "{app}\imageformats"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "bin-x64\imageformats\qwebp.dll"; DestDir: "{app}\imageformats"; Check: Is64BitInstallMode; Flags: solidbreak
; Platforms
Source: "bin-64\platforms\qwindows.dll"; DestDir: "{app}\platforms"; Check: Is64BitInstallMode; Flags: solidbreak
; Printsupport
Source: "bin-x64\printsupport\windowsprintersupport.dll"; DestDir: "{app}\printsupport"; Check: Is64BitInstallMode; Flags: solidbreak
; Sql
Source: "bin-x64\sqldrivers\qsqlite.dll"; DestDir: "{app}\sqldrivers"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "bin-x64\sqldrivers\qsqlmysql.dll"; DestDir: "{app}\sqldrivers"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "bin-x64\sqldrivers\qsqlodbc.dll"; DestDir: "{app}\sqldrivers"; Check: Is64BitInstallMode; Flags: solidbreak
Source: "bin-x64\sqldrivers\qsqlpsql.dll"; DestDir: "{app}\sqldrivers"; Check: Is64BitInstallMode; Flags: solidbreak

; Place all x86 files here, first one should be marked 'solidbreak'
Source: "bin-x86\jmbde.exe"; DestDir: "{app}"; Check: not Is64BitInstallMode; Flags: solidbreak
; The 32-Bit DLL's
; The QTCore Libs
Source: "bin-x86\D3Dcompiler_47.dll"; DestDir: "{app}"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "bin-x86\libEGL.dll"; DestDir: "{app}"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "bin-x86\libGLESV2.dll"; DestDir: "{app}"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "bin-x86\opengl32sw.dll"; DestDir: "{app}"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "bin-x86\Qt5Core.dll"; DestDir: "{app}"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "bin-x86\Qt5Gui.dll"; DestDir: "{app}"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "bin-x86\Qt5Help.dll"; DestDir: "{app}"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "bin-x86\Qt5PrintSupport.dll"; DestDir: "{app}"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "bin-x86\Qt5Sql.dll"; DestDir: "{app}"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "bin-x86\Qt5Svg.dll"; DestDir: "{app}"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "bin-x86\Qt5Widgets.dll"; DestDir: "{app}"; Check: not Is64BitInstallMode; Flags: solidbreak
; The QT Plugins
;
; Icons
Source: "bin-x86\iconengines\qsvgicon.dll"; DestDir: "{app}\iconengines"; Check: not Is64BitInstallMode; Flags: solidbreak
; Images
Source: "bin-x86\imageformats\qgif.dll"; DestDir: "{app}\imageformats"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "bin-x86\imageformats\qicns.dll"; DestDir: "{app}\imageformats"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "bin-x86\imageformats\qico.dll"; DestDir: "{app}\imageformats"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "bin-x86\imageformats\qjpeg.dll"; DestDir: "{app}\imageformats"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "bin-x86\imageformats\qsvg.dll"; DestDir: "{app}\imageformats"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "bin-x86\imageformats\qtga.dll"; DestDir: "{app}\imageformats"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "bin-x86\imageformats\qtiff.dll"; DestDir: "{app}\imageformats"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "bin-x86\imageformats\qwbmp.dll"; DestDir: "{app}\imageformats"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "bin-x86\imageformats\qwebp.dll"; DestDir: "{app}\imageformats"; Check: not Is64BitInstallMode; Flags: solidbreak
; Platforms
Source: "bin-x86\platforms\qwindows.dll"; DestDir: "{app}\platforms"; Check: not Is64BitInstallMode; Flags: solidbreak
; Printsupport
Source: "bin-x86\printsupport\windowsprintersupport.dll"; DestDir: "{app}\printsupport"; Check: not Is64BitInstallMode; Flags: solidbreak
; Sql
Source: "bin-x86\sqldrivers\qsqlite.dll"; DestDir: "{app}\sqldrivers"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "bin-x86\sqldrivers\qsqlmysql.dll"; DestDir: "{app}\sqldrivers"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "bin-x86\sqldrivers\qsqlodbc.dll"; DestDir: "{app}\sqldrivers"; Check: not Is64BitInstallMode; Flags: solidbreak
Source: "bin-x86\sqldrivers\qsqlpsql.dll"; DestDir: "{app}\sqldrivers"; Check: not Is64BitInstallMode; Flags: solidbreak
;
; Place all common files here, first one should be marked 'solidbreak'
;
;
; The Translations
Source: "share\jmbde\translations\jmbde_ar_DZ.qm"; DestDir: "{app}\translations"; Flags: solidbreak
Source: "share\jmbde\translations\jmbde_bg.qm"; DestDir: "{app}\translations"; Flags: solidbreak
Source: "share\jmbde\translations\jmbde_cs.qm"; DestDir: "{app}\translations"; Flags: solidbreak
Source: "share\jmbde\translations\jmbde_de.qm"; DestDir: "{app}\translations"; Flags: solidbreak
Source: "share\jmbde\translations\jmbde_en.qm"; DestDir: "{app}\translations"; Flags: solidbreak
Source: "share\jmbde\translations\jmbde_es.qm"; DestDir: "{app}\translations"; Flags: solidbreak
Source: "share\jmbde\translations\jmbde_fi.qm"; DestDir: "{app}\translations"; Flags: solidbreak
Source: "share\jmbde\translations\jmbde_fr.qm"; DestDir: "{app}\translations"; Flags: solidbreak
Source: "share\jmbde\translations\jmbde_he.qm"; DestDir: "{app}\translations"; Flags: solidbreak
Source: "share\jmbde\translations\jmbde_hu.qm"; DestDir: "{app}\translations"; Flags: solidbreak
Source: "share\jmbde\translations\jmbde_it.qm"; DestDir: "{app}\translations"; Flags: solidbreak
Source: "share\jmbde\translations\jmbde_ja.qm"; DestDir: "{app}\translations"; Flags: solidbreak
Source: "share\jmbde\translations\jmbde_nb.qm"; DestDir: "{app}\translations"; Flags: solidbreak
Source: "share\jmbde\translations\jmbde_nl.qm"; DestDir: "{app}\translations"; Flags: solidbreak
Source: "share\jmbde\translations\jmbde_pl.qm"; DestDir: "{app}\translations"; Flags: solidbreak
Source: "share\jmbde\translations\jmbde_pt.qm"; DestDir: "{app}\translations"; Flags: solidbreak
Source: "share\jmbde\translations\jmbde_pt_PT.qm"; DestDir: "{app}\translations"; Flags: solidbreak
Source: "share\jmbde\translations\jmbde_ru.qm"; DestDir: "{app}\translations"; Flags: solidbreak
Source: "share\jmbde\translations\jmbde_tr.qm"; DestDir: "{app}\translations"; Flags: solidbreak
Source: "share\jmbde\translations\jmbde_uk.qm"; DestDir: "{app}\translations"; Flags: solidbreak
Source: "share\jmbde\translations\jmbde_zh.qm"; DestDir: "{app}\translations"; Flags: solidbreak
Source: "share\jmbde\translations\jmbde_zh_TW.qm"; DestDir: "{app}\translations"; Flags: solidbreak
;
; Licenses and Documentation
Source: "EUPL-1.2_de"; DestDir: "{app}"; Flags: solidbreak
Source: "EUPL-1.2_en"; DestDir: "{app}"; Flags: solidbreak
Source: "README.md"; DestDir: "{app}"; Flags: isreadme


[Icons]
Name: "{group}\Juergen Muelbert"; Filename: "{app}\jmbde.exe"

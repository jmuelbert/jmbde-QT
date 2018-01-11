/**************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Installer Framework.
**
** $QT_BEGIN_LICENSE:GPL-EXCEPT$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
**************************************************************************/

// constructor
function Component()
{
    component.loaded.connect(this, Component.prototype.loaded);
    installer.installationFinished.connect(this, Component.prototype.installationFinishedPageIsShown);
    installer.finishButtonClicked.connect(this, Component.prototype.installationFinished);
    installer.setDefaultPageVisible(QInstaller.ComponentSelection, false);
}

Component.prototype.createOperationsForArchive = function(archive)
{
    // if there are additional plugin 7zips, these must be extracted in .app/Contents on OS X
    // if (systemInfo.productType !== "osx" || archive.indexOf('jmbde.7z') !== -1)
    //     component.addOperation("Extract", archive, "@TargetDir@");
    // else
    //     component.addOperation("Extract", archive, "@TargetDir@/jmbde.app/Contents");
}

Component.prototype.loaded = function()
{
    try {
        // if (installer.value("os") == "win" && installer.isInstaller())
        // -- Windows -- 
    } catch(e) {
        print(e);
    }
}

Component.prototype.beginInstallation = function()
{
    component.jmbdeBinaryPath = installer.value("TargetDir");

    if (installer.value("os") == "win") {
        component.jmbdeBinaryPath = component.jmbdeBinaryPath + "\\bin\\jmbde.exe";
        component.jmbdeBinaryPath = component.jmbdeBinaryPath.replace(/\//g, "\\");
    }
    else if (installer.value("os") == "x11")
        component.jmbdeBinaryPath = component.jmbedBinaryPath + "/bin/jmbe";
    else if (installer.value("os") == "mac")
        component.jmbdeBinaryPath = component.jmbdeBinaryPath + "/jmbde.app/Contents/MacOS/jmbde";

    if ( installer.value("os") === "win" )
        component.setStopProcessForUpdateRequest(component.jmbdeBinaryPath, true);
}

Component.prototype.createOperations = function()
{
    // Call the base createOperations and afterwards set some registry settings
    component.createOperations();
    if ( installer.value("os") == "win" )
    {
        component.addOperation( "CreateShortcut",
                                component.jmbdeBinaryPath,
                                "@StartMenuDir@jmbde " + installer.value("ProductVersion") + ".lnk",
                                "workingDirectory=@homeDir@" );

        // only install c runtime if it is needed, no minor version check of the c runtime till we need it
        if (installer.value("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\VisualStudio\\12.0\\VC\\Runtimes\\x86\\Installed") != 1) {
           // return value 3010 means it need a reboot, but in most cases it is not needed for run Qt application
           // return value 5100 means there's a newer version of the runtime already installed
           component.addElevatedOperation("Execute", "{0,1638,3010,5100}", "@TargetDir@\\lib\\vcredist_msvc2013\\vcredist_x86.exe", "/norestart", "/q");
        }

        registerWindowsFileTypeExtensions();

        }
    if ( installer.value("os") == "x11" )
    {
        component.addOperation( "InstallIcons", "@TargetDir@/share/icons" );
        component.addOperation( "CreateDesktopEntry",
                                "jmbde.desktop",
                                "Type=Application\nExec=" + component.jmbdeBinaryPath + "\nPath=@TargetDir@\nName=jmbde\nGenericName=The BDE Tool.\nGenericName[de]=Das BDE Werkzeug\nIcon=jmbde\nTerminal=false\nCategories=Business;Qt;\nMimeType=;"
                                );
    }
}

function isRoot()
{
    if (installer.value("os") == "x11" || installer.value("os") == "mac")
    {
        var id = installer.execute("/usr/bin/id", new Array("-u"))[0];
        id = id.replace(/(\r\n|\n|\r)/gm,"");
        if (id === "0")
        {
            return true;
        }
    }
    return false;
}

Component.prototype.installationFinishedPageIsShown = function()
{
    isroot = isRoot();
    try {
        if (component.installed && installer.isInstaller() && installer.status == QInstaller.Success && !isroot) {
            installer.addWizardPageItem( component, "LaunchjmbdeCheckBoxForm", QInstaller.InstallationFinished );
        }
    } catch(e) {
        print(e);
    }
}

Component.prototype.installationFinished = function()
{
    try {
        if (component.installed && installer.isInstaller() && installer.status == QInstaller.Success && !isroot) {
            var isLaunchjmbdeCheckBoxChecked = component.userInterface("LaunchjmbdeCheckBoxForm").launchjmbdeCheckBox.checked;
            if (isLaunchjmbdeCheckBoxChecked)
                installer.executeDetached(component.jmbedBinaryPath, new Array(), "@homeDir@");
        }
    } catch(e) {
        print(e);
    }
}

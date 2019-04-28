%global app_id com.github.jmuelbert.jmbde-QT

Name:           jmbde
Version:        0.4.23
Epoch:          1
Release:        1%{?dist}
Summary:        A BDE Tool
# tiled itself is GPLv2+, libtiled and tmxviewer are BSD
License:        EUPL_1_2
URL:            http://jmuelbert.github.io/jmbde-QT
Source0:        https://github.com/jmuelbert/%{name}/archive/v%{version}/%{name}-%{version}.tar.gz

BuildRequires:  pkgconfig(Qt5Core)
BuildRequires:  qt5-qttools-devel
BuildRequires:  desktop-file-utils

%description
A BDE Tool. Tiled is free software and written
in C++, using the Qt application framework.


%define pluginwarning Warning: This plugin does not offer full compatibility with jmbde features.


%prep
%setup -q

%build
%qmake_qt5 -r PREFIX=%{_prefix} LIBDIR=%{_libdir} RPATH=no USE_FHS_PLUGIN_PATH=yes
make %{?_smp_mflags}

%install
make install INSTALL_ROOT=%{buildroot}

# Clean build artefacts
find -name ".uic" -or -name ".moc" -or -name ".rcc" | xargs rm -rf

# Validate desktop file
desktop-file-validate %{buildroot}/%{_datadir}/applications/%{app_id}.desktop

# Appdata
install -D -p -m644 %{app_id}.appdata.xml %{buildroot}/%{_datadir}/appdata/%{app_id}.appdata.xml
appstream-util validate-relax --nonet %{buildroot}/%{_datadir}/appdata/*.appdata.xml

# locale files
%find_lang %{name} --with-qt

# Removed development file (this version does not install headers anyway)
rm %{buildroot}/%{_libdir}/lib%{name}.so

%post
/sbin/ldconfig
/bin/touch --no-create %{_datadir}/icons/hicolor &>/dev/null || :
/usr/bin/update-mime-database %{_datadir}/mime &> /dev/null || :
/usr/bin/update-desktop-database &> /dev/null || :

%postun
/sbin/ldconfig
if [ $1 -eq 0 ] ; then
    /bin/touch --no-create %{_datadir}/icons/hicolor &>/dev/null
    /usr/bin/gtk-update-icon-cache %{_datadir}/icons/hicolor &>/dev/null || :
fi
/usr/bin/update-mime-database %{_datadir}/mime &> /dev/null || :
/usr/bin/update-desktop-database &> /dev/null || :

%posttrans
/usr/bin/gtk-update-icon-cache %{_datadir}/icons/hicolor &>/dev/null || :


%files -f %{name}.lang
%doc AUTHORS NEWS.md README.md LICENSE LICENSE.EUPL_1_2
%{_bindir}/%{name}
%{_datadir}/applications/%{app_id}.desktop
%{_datadir}/icons/hicolor/*/apps/*%{name}*
%{_datadir}/icons/hicolor/*/mimetypes/*%{name}*
%{_datadir}/mime/packages/%{app_id}.xml
%{_datadir}/thumbnailers/%{name}.thumbnailer
%{_datadir}/appdata/%{app_id}.appdata.xml
%dir %{_datadir}/%{name}/
%dir %{_datadir}/%{name}/translations
%{_libdir}/lib%{name}.so.*

%dir %{_libdir}/%{name}/
%dir %{_libdir}/%{name}/plugins/

# Core plugins
%{_libdir}/%{name}/plugins/libcsv.so
%{_libdir}/%{name}/plugins/libjson.so
%{_libdir}/%{name}/plugins/liblua.so

%{_mandir}/man1/%{name}.1*

%changelog

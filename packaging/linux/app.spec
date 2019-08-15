# Copyright (c) 2019 Jürgen Mülbert. All rights reserved.
#
# This file is part of jmbde
#
# Licensed under the EUPL, Version 1.2 or – as soon they
# will be approved by the European Commission - subsequent
# versions of the EUPL (the "Licence");
# You may not use this work except in compliance with the
# Licence.
# You may obtain a copy of the Licence at:
#
# https://joinup.ec.europa.eu/page/eupl-text-11-12
#
# Unless required by applicable law or agreed to in
# writing, software distributed under the Licence is
# distributed on an "AS IS" basis,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
# express or implied.
# See the Licence for the specific language governing
# permissions and limitations under the Licence.
#
# Lizenziert unter der EUPL, Version 1.2 oder - sobald
#  diese von der Europäischen Kommission genehmigt wurden -
# Folgeversionen der EUPL ("Lizenz");
# Sie dürfen dieses Werk ausschließlich gemäß
# dieser Lizenz nutzen.
# Eine Kopie der Lizenz finden Sie hier:
#
# https://joinup.ec.europa.eu/page/eupl-text-11-12
#
# Sofern nicht durch anwendbare Rechtsvorschriften
# gefordert oder in schriftlicher Form vereinbart, wird
# die unter der Lizenz verbreitete Software "so wie sie
# ist", OHNE JEGLICHE GEWÄHRLEISTUNG ODER BEDINGUNGEN -
# ausdrücklich oder stillschweigend - verbreitet.
# Die sprachspezifischen Genehmigungen und Beschränkungen
# unter der Lizenz sind dem Lizenztext zu entnehmen.

Name:           jmbde
Summary:        A little BDE program
Version:        0.4.25
Release:        0%{?dist}
Group:          Applications/Business
License:        EUPL-1.2
Url:            http://jmuelbert.github.io/jmbde-QT/
Source:         https://github.com/jmuelbert/%{name}/archive/v%{version}.tar.gz#/%{name}-%{version}.tar.gz
BuildRequires:  cmake
BuildRequires:  desktop-file-utils
BuildRequires:  hicolor-icon-theme
BuildRequires:  pkgconfig(appstream-glib)
BuildRequires:  pkgconfig(Qt5Concurrent) >= 5.12
BuildRequires:  pkgconfig(Qt5Core) >= 5.12
BuildRequires:  pkgconfig(Qt5Gui) >= 5.12
BuildRequires:  pkgconfig(Qt5Multimedia) >= 5.12
BuildRequires:  pkgconfig(Qt5Network) >= 5.12
BuildRequires:  pkgconfig(Qt5PrintSupport) >= 5.12
BuildRequires:  pkgconfig(Qt5Script) >= 5.12
BuildRequires:  pkgconfig(Qt5WebKit) >= 5.12
BuildRequires:  pkgconfig(Qt5WebKitWidgets) >= 5.12
BuildRequires:  pkgconfig(Qt5Widgets) >= 5.12
BuildRequires:  pkgconfig(Qt5XmlPatterns) >= 5.12

%description
A little BDE program

%prep
%setup -q

%build
mkdir build
pushd build
cmake ../ -DCMAKE_INSTALL_PREFIX=%{_prefix}
make %{?_smp_mflags}
popd

%install
pushd
make install DESTDIR=%{buildroot}
popd
install -Dm 0644 packaging/%{name}.appdata.xml %{buildroot}%{_datadir}/appdata/%{name}.appdata.xml

%check
desktop-file-validate %{buildroot}%{_datadir}/applications/*.desktop

# Exclude openSUSE. The appstream-glib package is broken there.
%if !0%{?suse_version}
appstream-util validate-relax --nonet %{buildroot}%{_datadir}/appdata/*.appdata.xml
%endif

%post
%desktop_database_post
%icon_theme_cache_post

%postun
%desktop_database_postun
%icon_theme_cache_postun

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root)
%doc CHANGELOG COPYING README.md TODO
%{_bindir}/%{name}
%{_datadir}/%{name}/
%{_datadir}/applications/%{name}.desktop
%{_datadir}/icons/hicolor/*/apps/%{name}.png
%{_datadir}/appdata/%{name}.appdata.xml


* Wed Jul 03 2019 Jürgen Mülbert <juergen.muelbert@gmail.com>
- Initial RPM build

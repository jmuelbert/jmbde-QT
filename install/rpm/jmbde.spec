#
# Copyright 2013 Jürgen Mülbert <develop@juergen-muelbert.de>
#
# Licensed under the EUPL, Version 1.1 or – as soon they
# will be approved by the European Commission - subsequent
# versions of the EUPL (the "Licence");
# You may not use this work except in compliance with the
# Licence.
# You may obtain a copy of the Licence at:
#
# http://ec.europa.eu/idabc/eupl
#
# Unless required by applicable law or agreed to in
# writing, software distributed under the Licence is
# distributed on an "AS IS" basis,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
# express or implied.
# See the Licence for the specific language governing
# permissions and limitations under the Licence.


# See also http://en.opensuse.org/openSUSE:Specfile_guidelines

Name:           jmbde
Version:        0.0.1
Release:        24
Summary:        A little BDE tool
License:        EUPL-1.1
Group:          Applications/Databases
Url:            http://www.juergen-muelbert.de/projekte/jmbde
Source0:        %{name}-%{version}.tar.bz2
BuildRequires:	libqt4-devel >= 4.8
BuildRequires:	update-desktop-files
BuildRoot:	%{_tmppath}/%{name}-%{version}-root-%(id -u -n)
Requires:       libqt4 libqt4-sql libqt4-sql-sqlite
Requires:		libqt4


%description
Get an BDE Application

%files
%defattr(-,root,root)
%{_bindir}/%{name}
# %{buildroot}%{_datadir}/%{name}
# %{buildroot}%{_datadir}/%{name}/translations
# %{buildroot}%{_datadir}/%{name}/translations/%{name}_de.qm
%{_datadir}/applications/%{name}.desktop
%{_datadir}/pixmaps/jmbde.png

%doc NEWS TODO

%prep
%setup -q

%build
%{_bindir}/qmake

%{__make}

%install
%{__rm} -rf %{buildroot}
%{__mkdir_p} %{buildroot}
%{__mkdir_p} %{buildroot}%{_bindir}
%{__mkdir_p} %{buildroot}%{_datadir}/%{name}
%{__mkdir_p} %{buildroot}%{_datadir}/%{name}/translations
%{__mkdir_p} %{buildroot}%{_datadir}/applications
%{__mkdir_p} %{buildroot}%{_datadir}/pixmaps
%{__cp} jmbde.png %{buildroot}%{_datadir}/pixmaps
# %{__cp} src/translations/%{name}_de.qm %{buildroot}%{_datadir}/%{name}/translations
%{__cp} src/%{name} %{buildroot}%{_bindir}/%{name}
%{__chmod} 755 %{buildroot}%{_bindir}/%{name}

%suse_update_desktop_file -i %{name} 
	
%clean
%{__rm} -rf %{buildroot}




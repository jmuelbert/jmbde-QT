#
# Copyright 2013, 2014 Jürgen Mülbert <develop@juergen-muelbert.de>
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
Version:        0.3.4
Release:        2
Summary:        A little BDE tool
License:        EUPL-1.1
Group:          Productivity/Office/Database
Url:           	http://www.juergen-muelbert.de/de/projects/jmbde
%define	rversion 0.3.4
Source0:	    %{name}-%{version}.tar.bz2
BuildRoot:		%{_tmppath}/%{name}-%{version}-build

BuildRequires:	libstdc++-devel
BuildRequires:	gcc-c++
BuildRequires:	make
BuildRequires:	pkgconfig
BuildRequires:	sqlite3

###################################################################
# SuSE, openSUSE
###################################################################
%if 0%{?suse_version}
BuildRequires:	libqt4-devel >= 4.8
BuildRequires:	update-desktop-files
%endif

####################################################################
# Fedora, RHEL or CentOS
####################################################################
%if 0%{?fedora_version} || 0%{?rhel_version} || 0%{?centos_version}
BuildRequires:	desktop-file-utils
BuildRequires:	qt4-devel >= 4.8
%endif

Provides:	%{name} = %{version}


%description
Get an BDE Application


%files
%defattr(-,root,root)
%doc AUTHORS NEWS README TODO
%{_bindir}/%{name}
%{_datadir}/%{name}
%{_datadir}/%{name}/database
%{_datadir}/%{name}/translations
%{_datadir}/pixmaps
%{_datadir}/applications




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
%{__mkdir_p} %{buildroot}%{_datadir}/%{name}/database
%{__mkdir_p} %{buildroot}%{_datadir}/%{name}/translations
%{__mkdir_p} %{buildroot}%{_datadir}/applications
%{__mkdir_p} %{buildroot}%{_datadir}/pixmaps
%{__cp} bin/%{name} %{buildroot}%{_bindir}/%{name}
%{__cp} dist/%{name}.png %{buildroot}%{_datadir}/pixmaps
%{__cp} share/%{name}/database/%{name}sqlite.db %{buildroot}%{_datadir}/%{name}/database
%{__cp} share/%{name}/translations/%{name}_de.qm %{buildroot}%{_datadir}/%{name}/translations
%{__cp} share/%{name}/translations/%{name}_it.qm %{buildroot}%{_datadir}/%{name}/translations
%{__cp} share/%{name}/translations/%{name}_es.qm %{buildroot}%{_datadir}/%{name}/translations
%if 0%{?suse_version}
  %suse_update_desktop_file -i %{name} Office Database
%else
%if 0%{?fedora_version}
  desktop-file-install --dir=%{buildroot}%{datadir}/applications/ --add-category Office --add-category Qt --add-category Database
%endif
%endif


%clean
%{__rm} -rf %{buildroot}

%changelog
%if 0%{?suse_version}
%define _qt5_qmake /usr/%_lib/qt5/bin/qmake
%endif
%define lrelease lrelease
%if 0%{?fedora_version}
%define  debug_package %{nil}
%endif

Name:                   jmbde
Summary:                A BDE tools
Group:                  Business
Version:                0.4.11
Release:                1
License:                GPL-2.0+
Url:                    http://github.com/jmuelbert/jmbde-QT
Source0:                %{name}-%{version}.tar.gz
BuildRoot:              %{_tmppath}/%{name}-%{version}-build


BuildRequires:          libstdc++-devel 
BuildRequires:          gcc-c++ 
BuildRequires:          make
BuildRequires:          pkgconfig
BuildRequires:          pkgconfig(Qt5Core)
BuildRequires:          pkgconfig(Qt5Gui)
BuildRequires:          pkgconfig(Qt5Network)
BuildRequires:          pkgconfig(Qt5WebKitWidgets)
%if 0%{?suse_version}
BuildRequires:          update-desktop-files
BuildRequires:          pkgconfig(Qt5Test)
BuildRequires:          pkgconfig(Qt5PrintSupport)
BuildRequires:          libqt5-qttools-devel
%endif
%if 0%{?fedora_version}
BuildRequires:          desktop-file-utils
BuildRequires:          pkgconfig(gstreamer-0.10) pkgconfig(gstreamer-app-0.10)
BuildRequires:          pkgconfig(sqlite3)
BuildRequires:          qt5-qttools-devel
%endif


%description
A BDE tool to collect the IT-Components in a company

 
%prep
%setup -q -n %{name}-%{version}

%build
%{_qt5_qmake} 
make

%install
make INSTALL_ROOT="%buildroot" install

%files 
%defattr(-,root,root,755)
%_bindir/%{name}
%{_datadir}/applications/%{name}.desktop
%{_datadir}/icons/hicolor/*/apps/%{name}.*

%changelog

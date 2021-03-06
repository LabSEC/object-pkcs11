Name:           object-pkcs11
Version:        0.0.1
Release:        1%{?dist}
Summary:        C++ Object Oriented Wrapper for PKCS#11

License:        BSD License 2.0
URL:            https://labsec.github.io/object-pkcs11/
Source:         https://github.com/dettonijr/%{name}/archive/%{version}.tar.gz#/%{name}-%{version}.tar.gz

BuildRequires:  gcc-c++
BuildRequires:  make

%description
A library that allows you to access PKCS#11 modules using C++ RAII objects
instead of calling the CryptoKi C functions directly.

%package        devel
Summary:        Development files for %{name}
Requires:       %{name}%{?_isa} = %{version}-%{release}

%description    devel
The %{name}-devel package contains libraries and header files for
developing applications that use %{name}.

%prep
%autosetup -n %{name}-%{version}

%build
make 

%install
make install DESTDIR=%{buildroot}

%check
make test

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%files
%{_libdir}/*.so

%files devel
%{_includedir}/*


%changelog
* Thu Aug 24 2017 Claudio Dettoni - 0.0.1-1
- First version

Name:           objectpkcs11
Version:        0.0.1
Release:        1%{?dist}
Summary:        C++ Object Oriented Wrapper for PKCS#11

License:        BSD License 2.0
URL:            https://labsec.github.io/object-pkcs11/
Source0:        https://github.com/LabSEC/object-pkcs11/archive/dev.zip

BuildRequires:  gcc
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

%build
make 

%install
make install DESTDIR=%{buildroot}

%check
make test

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig


%files
%{_libdir}/*.so.*
%{_libdir}/*.so

%files devel
%{_includedir}/*
%{_libdir}/*.so
%{_libdir}/*.so.*


%changelog
* Thu Aug 24 2017 Claudio Dettoni - 0.0.1-1
- First version

Name:           test_1953072
Version:        1.0
Release:        1%{?dist}
Summary:        1953072_rpm.spec
 
License:        GPLv2
Source0:         %{name}-%{version}.tar.gz
Buildroot:      %{_tmppath}/%{name}-buildroot

%description
"1953072 rpm test"

%prep
%setup -q
 

%install
rm -rf %{buildroot}
mkdir -p $RPM_BUILD_ROOT
cp -rf $RPM_BUILD_DIR/%{name}-%{version}/* $RPM_BUILD_ROOT/
 
%pre
echo "准备安装test_1953072"

%post
echo "完成安装test_1953072"

%preun
echo "准备卸载test_1953072"

%postun
echo "完成卸载test_1953072"

%clean
rm -rf $RPM_BUILD_ROOT
 
%files
%defattr(-,root,root)
/usr/sbin/stu
/usr/lib64/stu
/etc/stu
/home/stu/u1953072

%doc
 
 
 
%changelog


CXX = g++
CXXFLAGS = -Wall
RM = rm -f
OBJ = test
SOURCE = test.o
LIBFLAGS= -L /usr/lib64/stu -l_1953072
LIBSOURCES = lib_1953072.so
LIBPATH = /usr/lib64/stu
INSTALLPATH1 = /usr/sbin/stu
INSTALLPATH20 = /home/stu
INSTALLPATH2 = /home/stu/u1953072
INSTALLPATH3 = /etc/stu

all : $(SOURCE)
	$(CXX) $(CXXFLAGS) -o $(OBJ) test.cpp $(LIBFLAGS) -Wl,-rpath=$(LIBPATH)

so : readconfig.cpp
	$(CXX) -fPIC -shared readconfig.cpp -o $(LIBSOURCES)
	@if [ -d $(LIBPATH) ];\
	then \
		cp -f $(LIBSOURCES) $(LIBPATH) ;\
	else \
		mkdir $(LIBPATH) ;\
		cp -f $(LIBSOURCES) $(LIBPATH) ;\
	fi

install : 
	@if [ -d $(INSTALLPATH1) ];\
	then \
		cp -f $(OBJ) $(INSTALLPATH1)/test_1953072 ;\
	else \
		mkdir $(INSTALLPATH1) ;\
		cp -f $(OBJ) $(INSTALLPATH1)/test_1953072 ;\
	fi

	@if [ -d $(LIBPATH) ];\
	then \
		cp -f $(LIBSOURCES) $(LIBPATH) ;\
	else \
		mkdir $(LIBPATH) ;\
		cp -f $(LIBSOURCES) $(LIBPATH) ;\
	fi

	@if [ ! -d $(INSTALLPATH20) ];\
	then \
		mkdir $(INSTALLPATH20) ;\
	fi

	@if [ -d $(INSTALLPATH2) ];\
	then \
		cp -f 1953072.dat $(INSTALLPATH2) ;\
	else \
		mkdir $(INSTALLPATH2) ;\
		cp -f 1953072.dat $(INSTALLPATH2) ;\
	fi

	@if [ -d $(INSTALLPATH3) ];\
	then \
		cp -f stu_1953072.conf $(INSTALLPATH3) ;\
	else \
		mkdir $(INSTALLPATH3) ;\
		cp -f stu_1953072.conf $(INSTALLPATH3) ;\
	fi

rpm : 
	rpmdev-setuptree
	mkdir -p $$HOME/rpmbuild/SOURCES/test_1953072-1.0/usr/sbin/stu
	mkdir -p $$HOME/rpmbuild/SOURCES/test_1953072-1.0/usr/lib64/stu
	mkdir -p $$HOME/rpmbuild/SOURCES/test_1953072-1.0/etc/stu
	mkdir -p $$HOME/rpmbuild/SOURCES/test_1953072-1.0/home/stu/u1953072
	cp -f test $$HOME/rpmbuild/SOURCES/test_1953072-1.0/usr/sbin/stu
	cd $$HOME/rpmbuild/SOURCES/test_1953072-1.0/usr/sbin/stu/ ; mv test test_1953072
	cp -f lib_1953072.so $$HOME/rpmbuild/SOURCES/test_1953072-1.0/usr/lib64/stu
	cp -f stu_1953072.conf $$HOME/rpmbuild/SOURCES/test_1953072-1.0/etc/stu
	cp -f 1953072.dat $$HOME/rpmbuild/SOURCES/test_1953072-1.0/home/stu/u1953072
	cp -f test_1953072.service /usr/lib/systemd/system
	cp -f 1953072_rpm.spec $$HOME/rpmbuild/SPECS
	cd $$HOME/rpmbuild/SOURCES/ ; tar -cvf test_1953072-1.0.tar.gz test_1953072-1.0
	rpmbuild -bb 1953072_rpm.spec
	mv $$HOME/rpmbuild/RPMS/x86_64/test_1953072-1.0-1.el8.x86_64.rpm test_1953072.rpm


uninstall : 
	rm -f /usr/sbin/stu/test_1953072
	rm -f /usr/lib64/stu/lib_1953072.so
	rm -f /etc/stu/stu_1953072.conf
	rm -f /home/stu/u1953072/1953072.dat
	@if [ !"$(ls -A /home/stu/u1953072)" ];\
	then \
		rm -rf /home/stu/u1953072 ;\
	fi
	rm -f /usr/lib/systemd/system/test_1953072.service
	rm -rf $$HOME/rpmbuild

.PHONY : clean
clean :
	$(RM) $(SOURCE) $(OBJ) *.rpm *.so

SUBDIRS = $(shell find . * -type d | grep -v "\.")
ROOT := $(shell pwd)

all:
	@for subdir in $(SUBDIRS); do        $(MAKE) -C $$subdir;    done
	rm -f `ls -F -R | grep '*' | sed 's/[/*]//g'`
	@echo -----$$subdir $@ finished-----
	@for subdir in $(SUBDIRS); \
	do cd $$subdir; \
	file `ls -lR | grep -v ^d | awk '{print $$9}'` | grep -v "client"| grep "executable" | awk -F '[ :]' '{print i$$1}' i=`pwd`/ | xargs -i cp {} $(ROOT); \
	cd ..; \
	done
	@echo -----$(ROOT) cp finished-----
	rename tcp u1953072_tcp *
	@echo -----$@-----finished-----

.PHONY:clean
clean:
	@for subdir in $(SUBDIRS); do        $(MAKE) -C $$subdir clean;        done
	rm -f `ls -F -R | grep '*' | sed 's/[/*]//g'`
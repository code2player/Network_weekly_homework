SUBDIRS = $(shell find . * -type d | grep -v "\.")

all:
	@for subdir in $(SUBDIRS); do        $(MAKE) -C $$subdir;   $(MAKE) -C $$subdir cpnames;     done

.PHONY:clean
clean:
	@for subdir in $(SUBDIRS); do        $(MAKE) -C $$subdir clean;        done
	rm -f `ls -F -R | grep '*' | sed 's/[/*]//g'`
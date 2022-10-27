SUBDIRS = $(shell find . * -type d | grep -v "\.")

all:
	@for subdir in $(SUBDIRS); do        $(MAKE) -C $$subdir;        done

.PHONY:clean
clean:
	@for subdir in $(SUBDIRS); do        $(MAKE) -C $$subdir clean;        done
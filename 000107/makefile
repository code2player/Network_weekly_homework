SUBDIRS = $(shell find . * -type d | grep -v "\.")

all:
	@for subdir in $(SUBDIRS); do        $(MAKE) -C $$subdir;        done

static:
	@for subdir in $(SUBDIRS); do        $(MAKE) -C $$subdir static;        done

dynamic:
	@for subdir in $(SUBDIRS); do        $(MAKE) -C $$subdir dynamic;        done

install:
	@for subdir in $(SUBDIRS); do        $(MAKE) -C $$subdir install;        done

.PHONY:clean
clean:
	@for subdir in $(SUBDIRS); do        $(MAKE) -C $$subdir clean;        done
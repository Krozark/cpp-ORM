export CC = g++
INCPATH = -I"$(CURDIR)"
LIBS = -lmysqlcppconn 
#-lpthread 
export DEFINES = 
export FLAGS = -g -std=c++0x $(INCPATH) $(LIBS) $(DEFINES)
export TOP = $(CURDIR)
export OBJ_DIR = $(TOP)/obj

SRC = $(wildcard *.c*)
OBJ = $(SRC:.cpp=.o) $(SRC:*.cpp=.o)

SUBDIRS = ORM obj

export EXEC = ORM-test


CLEANDIRS = $(SUBDIRS:%=clean-%)

.PHONY: subdirs $(SUBDIRS)
.PHONY: subdirs $(CLEANDIRS)

all: $(OBJ) subdirs

doc : doc/html 

doc/html :
	cd doc && doxygen

subdirs: $(SUBDIRS)
     
$(SUBDIRS):
	$(MAKE) -C $@


.cpp.o:
	$(CC) $(FLAGS) -o $@ -c $^;
	@mv $@ "$(OBJ_DIR)"

.c.o :
	$(CC) $(FLAGS) -o $@ -c $^;
	@mv $@ "$(OBJ_DIR)"


clean: $(CLEANDIRS)

$(CLEANDIRS): 
	$(MAKE) -C $(@:clean-%=%) clean
	@rm -f *.o
	@rm -f $(EXEC)


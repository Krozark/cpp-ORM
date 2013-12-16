OBJ = $(wildcard *.o)

static : $(OBJ)
	ar rcs $(TOP)/$(STATIC) $^

shared : $(OBJ)
	gcc -shared -Wl,-soname,$(TOP)/$(SHARED) -o $(TOP)/$(SHARED) $^
	
clean:
	@rm -f *.o

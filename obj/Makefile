OBJ = $(wildcard *.o)

all: $(EXEC)
	
$(EXEC): $(OBJ)
	$(CC) $^ $(FLAGS) -o "$(TOP)/$(EXEC)"

clean:
	@rm -f *.o

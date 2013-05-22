all: main.exe

.cpp.o:
	$(CC) $(FLAGS) -o "$@" -c "$<" 
	@cp $@ "$(OBJ_DIR)"

.c.o:
	$(CC) $(FLAGS) -o "$@" -c "$<"
	@cp $@ "$(OBJ_DIR)"


main.exe: Bdd.o MySQLBdd.o MySQLQuery.o Query.o
#	$(CC) $^ $(FLAGS) -o $@


clean:
	@rm -f *.o
	@rm -f *.exe

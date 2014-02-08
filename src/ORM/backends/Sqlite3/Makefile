all: main.exe

.cpp.o:
	$(CC) $(FLAGS) -o "$@" -c "$<" 
	@cp $@ "$(OBJ_DIR)"

.c.o:
	$(CC) $(FLAGS) -o "$@" -c "$<"
	@cp $@ "$(OBJ_DIR)"


main.exe: Sqlite3Bdd.o Sqlite3Query.o Sqlite3TableCreator.o


clean:
	@rm -f *.o
	@rm -f *.exe

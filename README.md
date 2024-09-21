gcc -Wall lv.c main.c -o program

valgrind --type-check=full ./program


OR


fcc -Wall lv.c main.c -o program
./program

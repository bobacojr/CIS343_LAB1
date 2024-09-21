gcc -Wall lv.c main.c -o program

valgrind --leak-check=full ./program


OR


gcc -Wall lv.c main.c -o program

./program

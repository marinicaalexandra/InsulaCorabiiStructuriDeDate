build:
	gcc -std=gnu11 -g -o tema3 main.c functii.c
run:
	./tema3
clean:
	rm tema3
valgrind:
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./tema3 1
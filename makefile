
ifeq ($(OS),Windows_NT)
gonosz_akaszto: main.c game.c dictionary.c econio.c interface.c
	gcc -o gonosz_akaszto.exe main.c game.c dictionary.c econio.c interface.c -lm
else
gonosz_akaszto: main.c game.c dictionary.c econio.c interface.c
	gcc -o gonosz_akaszto main.c game.c dictionary.c econio.c interface.c -lm
endif
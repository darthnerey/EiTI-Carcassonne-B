@echo off
tcc -c user_mode.c
tcc -c file_io.c
tcc -c drawing.c
tcc -c board.c
tcc game.c user_mode.o file_io.o drawing.o board.o -o game.exe


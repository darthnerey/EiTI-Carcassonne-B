@echo off
tcc -c user_mode.c
tcc -c file_io.c
tcc -c drawing.c
tcc -c board.c
tcc -c utils.c
tcc -c tile.c
tcc -c tile_pool.c
tcc game.c user_mode.o file_io.o drawing.o board.o tile.o utils.o tile_pool.o -o game.exe


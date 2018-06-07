@echo off
tcc -c AI.c
tcc -c AutoMode.c
tcc -c Board.c
tcc -c Drawing.c
tcc -c FileIO.c
tcc -c Ruleset.c
tcc -c Tile.c
tcc -c TilePool.c
tcc -c UserMode.c
tcc -c Utils.c
tcc game.c AI.o AutoMode.o Board.o Drawing.o FileIO.o Ruleset.o Tile.o TilePool.o UserMode.o Utils.o -o game.exe


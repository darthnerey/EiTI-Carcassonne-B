/* =========================== */
/* ======== Includes  ======== */
/* =========================== */

#include "file_io.h"

extern int app_returns;

/* =========================== */
/* ======== Functions ======== */
/* =========================== */

/*!
	Reads board data from a file
*/
bool read_board(char* path, Board* board)
{
	const char* err_file_open = "Can't open file: ";
	const char* file_mode_read = "r";
	char chr, pchr = '\0';
	int x = 0, y = 0;
	
	FILE* handle = NULL;
	handle = fopen(path, file_mode_read);
	if (handle == NULL) 
	{
		printf("%s'%s'\n", err_file_open, path);
		app_returns = -1;
		return;
	}
	
	do
	{
		chr = fgetc(handle);
		
		switch (chr)
		{
			case ' ': 
				x++;
				break;
			case '\n': 
				y++; 
				x = 0;
				break;
			case T_Field:
			case T_Road:
			case T_Temple:
			case T_City:
			case T_Shield:
			case T_Nothing:
				board->Tiles[x][y].Top = (T_Part)chr;
				board->Tiles[x][y].Right = (T_Part)(chr = fgetc(handle));
				board->Tiles[x][y].Bottom = (T_Part)(chr = fgetc(handle));
				board->Tiles[x][y].Left = (T_Part)(chr = fgetc(handle));
				board->Tiles[x][y].Middle = (T_Part)(chr = fgetc(handle));
				break;
			default:
				// printf("Unidentified symbol: '%c'", chr);
				break;
		}
		
		pchr = chr;
	}
	while (chr != EOF);
	
	fclose(handle);
	return true;
}

/*!
	Writes board data into a file
*/
bool write_board(char* path, const Board* board)
{
	const char* err_file_open = "Can't open file: ";
	const char* file_mode_write = "w";
	FILE* handle;
	int x, y = 0;
	
	handle = fopen(path, file_mode_write);
	if (handle == NULL) 
	{
		printf("%s'%s'\n", err_file_open, path);
		app_returns = -1;
		return false;
	}
	
	for (; y < MAX_BOARD; y++)
	{
		for (x = 0; x < MAX_BOARD; x++)
		{
			fputc(board->Tiles[x][y].Top, handle);
			fputc(board->Tiles[x][y].Right, handle);
			fputc(board->Tiles[x][y].Bottom, handle);
			fputc(board->Tiles[x][y].Left, handle);
			fputc(board->Tiles[x][y].Middle, handle);
			fputc(' ', handle);
		}
		fputc('\n', handle);
	}
	
	fclose(handle);
	return true;
}
#include "AutoMode.h"

int AutoMode(char* list_path, char* board_path)
{
	ListRef list = LoadList(list_path);
	if (list == NULL) return -1;

	BoardRef board = NULL;

	if (FileExists(board_path))
		board = LoadBoard(board_path);
	else
	{
		Size Zero;
		Zero.W = 0;
		Zero.H = 0;
		board = AllocBoard(Zero);
	}

	if (board == NULL)
		return -1;

	AIMove(board, &list);

	SaveList(list, list_path);
	SaveBoard(board, board_path);

	return 0;
}

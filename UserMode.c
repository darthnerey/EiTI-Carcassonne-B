#include "UserMode.h"

CommandRef CreateCommand(void* method, const char* name, const char* help)
{
	CommandRef result = (CommandRef)malloc(sizeof(Command));
	if (result == NULL) return NULL;
	result->Method = method;
	result->Name = name;
	result->Help = help;
	return result;
}

void UserCls(GameState* state)
{
	ClearScreen();
}

void UserHelp(GameState* state)
{
	for (int32_t i = 0; i < state->CommandsTotal; i++)
		printf("\t%s %s\n", state->Commands[i]->Name, state->Commands[i]->Help);
}

void UserExit(GameState* state)
{
	exit(0);
}

void UserPrintTiles(GameState* state)
{
	if (!PrintListFile(state->List))
	{
		printf("No tiles allocated!\n");
	}
}

void UserPrintBoard(GameState* state)
{
	if (!PrintBoardGrid(state->Board))
	{
		printf("No board allocated!\n");
	}
}

void UserAIMove(GameState* state)
{
	AIRandomMove(state->Board, &state->List);
}

void UserAIDebug(GameState* state)
{
	int32_t rounds = Random(2, 8);

	ListRef List = GenerateList(rounds);

	if (state->List == NULL)
	{
		state->List = List;
	}
	else
	{
		InsertAfterList(state->List, List);
	}

	for (int32_t i = 0; i < rounds; i++) 
	{
		AIRandomMove(state->Board, &state->List);
		PrintBoardFile(state->Board);
		printf("\n");
	}
}

void UserTileGen(GameState* state)
{
	int32_t number = 0;
	printf("Number of tiles: ");
	if (scanf("%i", &number) > 0)
	{
		ListRef List = GenerateList(number);

		if (state->List == NULL)
		{
			state->List = List;
		}
		else
		{
			InsertAfterList(state->List, List);
		}
	}
	else
	{
		printf("Tilegen: please, provide a proper number!\n");
	}
}

void UserLoadTiles(GameState* state)
{
	char path[128];
	printf("File: ");
	if (scanf("%s", path) != 1)
		printf("Please, provide a file path!\n");
	else 
	{
		while (state->List != NULL)
			FreeList(&state->List);
		state->List = LoadList(path);
	}
}

void UserSaveTiles(GameState* state)
{
	char path[128];
	printf("File: ");
	if (scanf("%s", path) != 1)
		printf("Please, provide a file path!\n");
	else 
		SaveList(state->List, path);
}

void UserLoadBoard(GameState* state)
{
	char path[128];
	printf("File: ");
	if (scanf("%s", path) != 1)
		printf("Please, provide a file path!\n");
	else
	{
		FreeBoard(&state->Board);
		state->Board = LoadBoard(path);
	}
}

void UserSaveBoard(GameState* state)
{
	char path[128];
	printf("File: ");
	if (scanf("%s", path) != 1)
		printf("Please, provide a file path!\n");
	else
		SaveBoard(state->Board, path);
}

void UserMove(GameState* state)
{
	char temp[128];
	temp[0] = '\0';
	printf("Tile: ");
	if (scanf("%s", temp) > 0)
	{
		TileRef Tile = TileFromString(temp);
		if (IsTileValid(Tile))
		{
			Point point;
		retry_x:
			printf("X: ");
			if (scanf("%i", &point.X) < 1)
			{
				printf("Invalid coordinate value!\n");
				goto retry_x;
			}
		retry_y:
			printf("Y: ");
			if (scanf("%i", &point.Y) < 1)
			{
				printf("Invalid coordinate value!\n");
				goto retry_y;
			}
			if (TileExists(state->Board, point))
			{
				printf("Position is already occupied!\n");
				goto retry_x;
			}
			if (!TryPlaceTile(state->Board, Tile, point))
			{
				printf("Position isn't legal!\n");
				goto retry_x;
			}
		}
		else
		{
			printf("Invalid tile!\n");
		}
	}
}

bool UserInput(GameState* state)
{
	char buffer[256];
	buffer[0] = '\0';
	if (scanf("%s", buffer) > 0)
	{
		for (int32_t i = 0; i < state->CommandsTotal; i++)
		{
			if (strcmp(buffer, state->Commands[i]->Name) == 0)
			{
				CommandRef Command = state->Commands[i];
				if (Command != NULL)
				{
					void(*method_ptr)(GameState*) = Command->Method;
					method_ptr(state);
					return true;
				}
			}
		}
	}
	return false;
}

int UserMode(const char* path)
{
	CommandRef Commands[] = {
		CreateCommand(UserCls, "cls", "- Clears the screen"),
		CreateCommand(UserHelp, "help", "- Prints this help screen"),
		CreateCommand(UserExit, "exit", " - Exits the program"),
		CreateCommand(UserMove, "play", "[tile] - Play a tile manually"),
		CreateCommand(UserAIMove, "ai", "- AI plays a random tile"),
		CreateCommand(UserAIDebug, "debug_ai", "- AI plays a random set of random tiles"),
		CreateCommand(UserPrintTiles, "printTiles", "- Prints the tile list out"),
		CreateCommand(UserPrintBoard, "printBoard", "- Prints the board out"),
		CreateCommand(UserTileGen, "tilegen", "[n] - Runs the tile generator"),
		CreateCommand(UserLoadTiles, "loadTiles", "[filename] - Reads a tile list file"),
		CreateCommand(UserSaveTiles, "saveTiles", "[filename] - Writes a tile list file"),
		CreateCommand(UserLoadBoard, "loadBoard", "[filename] - Reads a board file"),
		CreateCommand(UserSaveBoard, "saveBoard", "[filename] - Writes a board file")
	};

	GameState state;
	state.Commands = Commands;
	state.CommandsTotal = 13;
	state.Board = NULL;
	state.List = NULL;

	if (strcmp(path, "/user") != 0)
		state.List = LoadList(path);

	Size Zero;
	Zero.W = 0;
	Zero.H = 0;
	state.Board = AllocBoard(Zero);

	while (true)
	{
		if (UserInput(&state))
		{

		}
		else
		{
			UserHelp(&state);
		}
	}
	return 0;
}

#include "Game.h"

int Usage(char* exename)
{
	printf("Usage: \n" \
		"\t%s [tiles] [board] - Auto Mode\n" \
		"\t%s [tiles]         - User Mode (loads a tile list)\n" \
		"\t%s /tilegen [n]    - Generate n tiles into 'tiles.txt'\n" \
		"\t%s /about          - Print out misc info\n" \
		"\t%s /user           - User Mode\n",
		exename, exename, exename, exename, exename
	);
	return 0;
}

int GenerateTiles(int32_t number)
{
	if (number < 1 || number > 1024)
	{
		printf("TileGen: Improper argument [n] - it should be a number between 1 and 1024\n");
		return -1;
	}
	ListRef List = GenerateList(number);
	SaveList(List, "tiles.txt");
	return 0;
}

int About()
{
	printf("Coded through sleepless nights by: Leonid Sawin and Mazen Ibrahim\n");
	return 0;
}

int main(int argc, char** argv)
{
	srand((uint32_t)time(NULL));
	BuildRuleset();
	if (argc == 3)
	{
		if (strcmp(argv[1], "/tilegen") == 0)
			return GenerateTiles(atoi(argv[2]));
		return AutoMode(argv[1], argv[2]);
	}
	else if (argc == 2)
	{
		if (strcmp(argv[1], "/about") == 0)
			return About();
		return UserMode(argv[1]);
	}
	else return Usage(argv[0]);
}
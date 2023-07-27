#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <io.h>
#include <stdlib.h>
#include <time.h>
#include <sys\locking.h>
#include <string.h>
#include <ctype.h>
#include "GamePlay.h"
using namespace std;

int main()
{
	setlocale(0, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	GamePlay play;

	play.read_words_from_file();
	play.print_words();

	play.game();

	


	return 0;
}
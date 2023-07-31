#include <windows.h>
#include <iostream>

#include "GamePlay.h"
#include "Picture.h"
#include "Menu.h"
using namespace std;

int main()
{
	setlocale(0, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	navigate_menu();

	return 0;
}
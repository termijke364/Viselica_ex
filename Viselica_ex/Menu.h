#pragma once

#include "GamePlay.h"
#include "Picture.h"
#include "Player.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;




enum Key { Arrow = 224, Enter = 13, Up = 72, Down = 80 }; 
enum Menu { Load, Play, Exit };

Player player;
GamePlay play(player);

string get_menu_name(Menu menu) 
{
	switch (menu)
	{
	case Exit:
		return "Выход";
	case Load:
		return "Загрузить слова из файла";
	case Play:
		return "Играть!";
	default:
		return "Unknown";
	}
}



void draw_menu(int current_choice) 
{
	system("cls");

	auto end = Menu::Exit;
	auto start = Menu::Load;

	for (int i = start; i <= end; i++) 
	{
		cout << (current_choice == i ? '>' : ' ') << get_menu_name((Menu)i) << endl;
	}
}

void change_choice(int& choice) 
{
	auto key = _getch();
	switch (key)
	{
	case Up:
		choice--;
		choice = choice < 0 ? choice = 0 : choice;
		break;
	case Down:
		choice++;
		choice = choice > Menu::Exit ? choice = Menu::Exit : choice;
		break;
	}
}

void select_menu(const int& choice) 
{
	

	switch (choice) {
	case Load:
		play.read_words_from_file();
		break;

	case Play:
		play.game();
		break;

	case Exit:
		std::cout << "Выход из программы\n";
		break;
	}
}

void navigate_menu() 
{
	int choice = 0; 

	while (true) 
	{
		draw_menu(choice);

		int key = _getch(); 

		switch (key) 
		{
		case Arrow:
			change_choice(choice);
			break;

		case Enter:
			select_menu(choice);
			if (choice == Menu::Exit)
				return;

			break;
		}
	}
}

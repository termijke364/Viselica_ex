#pragma once
#include <iostream>
#include <string>
#include <string.h>

using namespace std;


class Player
{
	char _letter;

public:

	Player(){}

	char get_letter()
	{
		cin >> _letter;

		return _letter;
	}
};


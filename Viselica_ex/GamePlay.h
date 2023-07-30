#pragma once
#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <io.h>
#include <stdlib.h>
#include <time.h>
#include <sys\locking.h>
#include <string.h>
#include <ctype.h>
#include <fstream>
#include <string>
#include <string.h>
#include <sstream>
#include "Player.h"
#include <vector>

using namespace std;

const char input_words[]{ "words.txt" };

class GamePlay
{
	int _max_try;
	int _try_count{};
	string word;
	string _file_words[6];

	int _word_size;
	Player& _player;

public:

	GamePlay(Player& player) :_player(player) {}

	void read_words_from_file()
	{
		auto stream = fstream(input_words, ios_base::in);

		if (!stream.is_open())
		{
			return;
		}

		auto delimeter = '\n';
		string buffer;
		int index = 0;

		while (getline(stream, buffer))
		{
			stringstream stream_line(buffer);

			string words;

			getline(stream_line, words, delimeter);
			string convert = words;

			for (size_t i = 0; i < words.size(); i++)
			{
				char letter = words[i];
				letter += 2;
				convert[i] = letter;
				words[i] = convert[i];
			}

			_file_words[index] = words;
			index++;
		}

		stream.close();
	}

	char toUpper(char letter) {
		if (letter >= 'а' && letter <= 'я') {
			return letter - 32;
		}
		else if (letter >= 'А' && letter <= 'Я') {
			return letter;
		}
		else {
			return letter + 0;
		}
	}

	void print_words() //для проверки работы загрузки слов из файла
	{
		for (int i = 0; i < _file_words->length() + 1; i++)
		{
			cout << _file_words[i] << endl;
			cout << _file_words[i].size() << endl;
		}
	}

	void words_description(int index_word)
	{
		switch (index_word)
		{
		case 0:
			cout << "Kis Kis" << endl;
			break;
		case 1:
			cout << "Овощь green" << endl;
			break;
		case 2:
			cout << "WHROOM!!! WHROOM!!! Motherfucker!!!" << endl;
			break;
		case 3:
			cout << "Шиндовс98" << endl;
			break;
		case 4:
			cout << "Чай, кофе, пить!" << endl;
			break;
		case 5:
			cout << "AppleWatch, Xiaomi Mi Band" << endl;
			break;
		default:
			break;
		}
	}

	void game()
	{
		if (_file_words->empty())
		{
			cout << "Список пуст. Загрузите слова из файла (пункт меню №1)";
			return;
		}

		srand(time(NULL));
		int index_word = rand() & _file_words->size();
		word = _file_words[index_word];
		
		const int _size = _file_words[index_word].size();

		_max_try = _size;

		vector<char> tmp_word;
		auto delimeter = '_';

		for (int i = 0; i < _size; i++)
		{
			tmp_word.push_back(delimeter);
		}



		do
		{
			system("cls");
			cout << "Ваше слово: " << endl;
			words_description(index_word);

			cout << "\nЭто слово состоит из " << _size << " букв" << endl;

			cout << "Разгаданное слово: " << endl;
			for (int i = 0; i < _size; i++)
			{
				cout << tmp_word[i];
			}

			cout << "\nОсталось попыток: " << _max_try - _try_count+1 << endl;

			cout << "\nВведите букву(язык русский!), регистр не важен: " << endl;

			char _letter = _player.get_letter();
			_letter = toUpper(_letter);

			vector<char> letters;
			letters.push_back(_letter);

			for (int i = 0; i < word.size(); i++)
			{
				if (_letter == tmp_word[i])
				{
					cout << "Такая буква уже была, выберите другую!" << endl;
					system("pause");
					break;
				}
				if (word[i] == _letter)
				{
					cout << "Есть такая буква!" << endl;
					tmp_word[i] = word[i];
					for (int j = 0; j < _size; j++)
					{
						if (word[j] == _letter)
						{
							tmp_word[j] = word[j];
						}
					}
					_try_count++;
					system("pause");
					break;
				}
				else if (i != word.size() - 1)
				{
					continue;
				}
				else
				{
					cout << "Нет такой буквы!" << endl;
					_try_count++;
					system("pause");
					break;
				}
			}

			if (is_win(tmp_word, _file_words[index_word]))

			{
				system("cls");
				cout << "ВЫ ПОБЕДИЛИ!!" << endl;
				get_stat(index_word, tmp_word, _size);
				return;
			}

			if (_try_count == _max_try+1)
			{
				system("cls");
				cout << "YOU LOOOSE!!!" << endl;
				get_stat(index_word, tmp_word, _size);

				return;
			}
		} while (_try_count != _max_try+1);
	}

	void get_stat(int index, vector<char> vec, int size)
	{
		cout << "Статистика игры: " << endl;
		cout << "Затрачено попыток: " << _try_count << endl;
		cout << "Загаданое слово: " << _file_words[index] << endl;
		cout << "Буквы введенные игроком: " << endl;
		
		for (auto& i : vec)
		{
			cout << i << ", ";
		}

	}

private:

	bool is_win(vector<char> vec, string str)
	{
		for (int i = 0; i < vec.size(); i++)
		{
			if (vec[i] != str[i])
			{
				return false;
			}
		}

		return true;
	}
};

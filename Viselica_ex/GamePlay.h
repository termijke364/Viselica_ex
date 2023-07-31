#pragma once
#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <fstream>
#include <string>
#include <string.h>
#include <sstream>
#include <vector>
#include <time.h>

#include "Player.h"
#include "Picture.h"
using namespace std;

const char input_words[]{ "words.txt" };

class GamePlay
{
	string _word;
	int _max_try{};
	int _try_count{};
	string _file_words[6];
	vector<char> _input_letters;

	Picture* _picture;
	Player& _player;

public:

	GamePlay(Player& player) :_player(player) {}

	void read_words_from_file()
	{
		system("cls");
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
		cout << "Данные из файла успешно загружены!" << endl;
		system("pause");
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

	void words_description(int index_word)
	{
		switch (index_word)
		{
		case 0:
			cout << "Когда остальные слепо следуют за истиной, помни - ничто не (.....)." <<
				" \nКогда остальные ограничены моралью или законом, помни -  всё дозволено." << endl;
			break;
		case 1:
			cout << "Крыльями машет, Зубами клацает, Ноздри раздувает, Огонь извергает!" << endl;
			break;
		case 2:
			cout << "Получил власть, которая и не снилась его отцу" << endl;
			break;
		case 3:
			cout << "Умирает последней" << endl;
			break;
		case 4:
			cout << "Чай, кофе, пить!" << endl;
			break;
		case 5:
			cout << "Свет это поток ...., обладающих определённой энергией," <<
				"\nимпульсом, собственным моментом импульса и нулевой массой " << endl;
			break;
		default:
			break;
		}
	}

	void game()
	{
		if (_file_words->empty())
		{
			system("cls");
			cout << "Список пуст. Загрузите слова из файла (пункт меню №1)" << endl;;
			system("pause");
			return;
		}

		srand(time(NULL));
		int index_word = rand() & (_file_words->size() - 1);
		_word = _file_words[index_word];

		const int _size = _file_words[index_word].size();

		_max_try = _size;

		vector<char> tmp_word;
		auto delimeter = '_';

		for (int i = 0; i < _size; i++)
		{
			tmp_word.push_back(delimeter);
		}
		clock_t start = clock();

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

			cout << "\nОсталось попыток: " << _max_try - _try_count << endl;

			cout << "\nВведите букву(язык русский!), регистр не важен: " << endl;

			char _letter = _player.get_letter();
			_letter = toUpper(_letter);

			_input_letters.push_back(_letter);

			for (int i = 0; i < _word.size(); i++)
			{
				if (_letter == tmp_word[i])
				{
					cout << "Такая буква уже была, выберите другую!" << endl;
					system("pause");
					break;
				}
				if (_word[i] == _letter)
				{
					cout << "Есть такая буква!" << endl;
					tmp_word[i] = _word[i];
					for (int j = 0; j < _size; j++)
					{
						if (_word[j] == _letter)
						{
							tmp_word[j] = _word[j];
						}
					}
					_try_count++;
					system("pause");
					break;
				}
				else if (i != _word.size() - 1)
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
				clock_t end = clock();
				system("cls");

				get_stat(index_word, _input_letters, _size);

				double duration = (double)(end - start) / CLOCKS_PER_SEC;
				cout << "\nВы потратили время: " << duration / 60 << " минут(ы)" << endl;

				_picture->print_win_logo();
				system("pause");

				exit(1);
			}

			if (_try_count == _max_try)
			{
				clock_t end = clock();
				system("cls");

				get_stat(index_word, _input_letters, _size);

				double duration = (double)(end - start) / CLOCKS_PER_SEC;
				cout << "\nВы потратили время: " << duration / 60 << " минут(ы)" << endl;

				_picture->print_loose_logo();
				system("pause");

				exit(1);
			}
		} while (_try_count != _max_try || _max_try == 0 || _try_count < 0);
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

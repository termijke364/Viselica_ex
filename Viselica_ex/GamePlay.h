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
		cout << "������ �� ����� ������� ���������!" << endl;
		system("pause");
	}

	char toUpper(char letter) {
		if (letter >= '�' && letter <= '�') {
			return letter - 32;
		}
		else if (letter >= '�' && letter <= '�') {
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
			cout << "����� ��������� ����� ������� �� �������, ����� - ����� �� (.....)." <<
				" \n����� ��������� ���������� ������� ��� �������, ����� -  �� ���������." << endl;
			break;
		case 1:
			cout << "�������� �����, ������ �������, ������ ���������, ����� ���������!" << endl;
			break;
		case 2:
			cout << "������� ������, ������� � �� ������� ��� ����" << endl;
			break;
		case 3:
			cout << "������� ���������" << endl;
			break;
		case 4:
			cout << "���, ����, ����!" << endl;
			break;
		case 5:
			cout << "���� ��� ����� ...., ���������� ����������� ��������," <<
				"\n���������, ����������� �������� �������� � ������� ������ " << endl;
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
			cout << "������ ����. ��������� ����� �� ����� (����� ���� �1)" << endl;;
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
			cout << "���� �����: " << endl;
			words_description(index_word);

			cout << "\n��� ����� ������� �� " << _size << " ����" << endl;

			cout << "����������� �����: " << endl;
			for (int i = 0; i < _size; i++)
			{
				cout << tmp_word[i];
			}

			cout << "\n�������� �������: " << _max_try - _try_count << endl;

			cout << "\n������� �����(���� �������!), ������� �� �����: " << endl;

			char _letter = _player.get_letter();
			_letter = toUpper(_letter);

			_input_letters.push_back(_letter);

			for (int i = 0; i < _word.size(); i++)
			{
				if (_letter == tmp_word[i])
				{
					cout << "����� ����� ��� ����, �������� ������!" << endl;
					system("pause");
					break;
				}
				if (_word[i] == _letter)
				{
					cout << "���� ����� �����!" << endl;
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
					cout << "��� ����� �����!" << endl;
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
				cout << "\n�� ��������� �����: " << duration / 60 << " �����(�)" << endl;

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
				cout << "\n�� ��������� �����: " << duration / 60 << " �����(�)" << endl;

				_picture->print_loose_logo();
				system("pause");

				exit(1);
			}
		} while (_try_count != _max_try || _max_try == 0 || _try_count < 0);
	}

	void get_stat(int index, vector<char> vec, int size)
	{
		cout << "���������� ����: " << endl;
		cout << "��������� �������: " << _try_count << endl;
		cout << "��������� �����: " << _file_words[index] << endl;
		cout << "����� ��������� �������: " << endl;

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

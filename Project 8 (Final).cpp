#include <iostream>
#include <random>
#include <stdlib.h>
#include <chrono>

using namespace std;
int num;
enum TCell : char
{
	CROSS = 'X',
	ZERO = 'O',
	EMPTY = '_'
};

enum TProgress
{
	IN_PROGRESS,
	WON_PEOPLE,
	WON_ROBOT,
	DRAW
};

struct TCoord
{
	size_t y;
	size_t x;
};

struct TGame
{
	TCell** ppField{ nullptr };
	const size_t size{ 3 };
	TCell people {CROSS};
	TCell robot{ZERO};
	size_t turn{ 0 };
	TProgress progress{ IN_PROGRESS };
};

 inline void clearScr()
{
	system("cls");
}

int32_t __fastcall getRandomNum(int32_t min, int32_t max)
{
	const static auto seed = chrono::system_clock::now().time_since_epoch().count();
	static mt19937_64 generator(seed);
	uniform_int_distribution<int32_t> dis(min, max);
	return dis(generator);
}

void  __fastcall initGame(TGame & i)
{
	i.ppField = new TCell * [i.size];
	for (size_t j = 0; j < i.size; j++)
	{
		i.ppField[j] = new TCell[i.size];
	}

	for (size_t y = 0; y < i.size ; y++)
	{
		for (size_t x = 0; x < i.size; x++)
		{
			i.ppField[y][x] = EMPTY;
		}
	}

	if (getRandomNum(0, 1000) > 500)
	{
		i.people = CROSS;
		i.robot = ZERO;
		i.turn = 0;
	}
	else
	{
		i.people = ZERO;
		i.robot = CROSS;
		i.turn = 1;

	}
}

void __fastcall deinitGame(TGame & i)
{
	
	for (size_t j = 0; j < i.size; j++)
	{
		delete [] i.ppField[j];
	}
	delete[] i.ppField;
	i.ppField = nullptr;
}

void __fastcall printGame(const TGame& i)
{
	cout << "     ";
	for (size_t x = 0; x < i.size; x++)

		cout << x + 1 << "   ";
	cout << endl;
	
	for (size_t y = 0; y < i.size; y++)
	{
		cout << " " << y + 1 << " | ";
		for (size_t x = 0; x < i.size; x++)
		{
			cout << i.ppField[y][x] << " | ";
		}
		cout << endl;
	}
	cout << endl << " people: " << i.people << endl << " Computer: " << i.robot << endl << endl;
}

TProgress __fastcall getWon(const TGame & i)
{
	for (size_t y = 0; y < i.size; y++)
	{
		
		if (i.ppField[y][0] == i.ppField[y][1] && i.ppField[y][0] == i.ppField[y][2])
		{
			if (i.ppField[y][0] == i.people)
				return WON_PEOPLE;

			if (i.ppField[y][0] == i.robot)
				return WON_ROBOT;
		}
	}

	for (size_t x = 0; x < i.size; x++)
	{

		if (i.ppField[0][x] == i.ppField[1][x] && i.ppField[0][x] == i.ppField[2][x])
		{
			if (i.ppField[0][x] == i.people)
				return WON_PEOPLE;

			if (i.ppField[0][x] == i.robot)
				return WON_ROBOT;
		}
	}

	

		if (i.ppField[0][0] == i.ppField[1][1] && i.ppField[0][0] == i.ppField[2][2])
		{
			if (i.ppField[0][0] == i.people)
				return WON_PEOPLE;

			if (i.ppField[0][0] == i.robot)
				return WON_ROBOT;
		}
	
		if (i.ppField[2][0] == i.ppField[1][1] && i.ppField[1][1] == i.ppField[0][2])
		{
			if (i.ppField[1][1] == i.people)
				return WON_PEOPLE;

			if (i.ppField[1][1] == i.robot)
				return WON_ROBOT;
		}

		bool draw{ true };

		for (size_t y = 0; y < i.size; y++)
		{
			
			for (size_t x = 0; x < i.size; x++)
			{
				if (i.ppField[y][x] == EMPTY)
				{
					draw = false;
					break;
				}
			}
			if (!draw)
				break;
		}

		if (draw)
			return DRAW;


	return IN_PROGRESS;
}

TCoord getPeopleCoord(const TGame & i)
{
	TCoord c;
	do
	{
		cout << "Enter X(1..3): ";
		cin >> c.x;
		cout << "Enter Y(1..3): ";
		cin >> c.y;
		c.x--;
		c.y--;
	} while (c.x > 2 || c.y > 2 || i.ppField[c.y][c.x] != EMPTY);
	
	return c;
}
TCoord __fastcall getRobotCoord(TGame & i)
{

	for (size_t y = 0; y < i.size; y++)
	{

		for (size_t x = 0; x < i.size; x++)
		{
			if (i.ppField[y][x] == EMPTY)
			{
				i.ppField[y][x] = i.robot;
				if (getWon(i) == WON_ROBOT)
				{
					i.ppField[y][x] = EMPTY;
					return { y, x };
				}
				i.ppField[y][x] = EMPTY;
			}
		}
	}

	for (size_t y = 0; y < i.size; y++)
	{

		for (size_t x = 0; x < i.size; x++)
		{
			if (i.ppField[y][x] == EMPTY)
			{
				i.ppField[y][x] = i.robot;
				if (getWon(i) == WON_PEOPLE)
				{
					i.ppField[y][x] = EMPTY;
					return { y, x };
				}
				i.ppField[y][x] = EMPTY;
			}
		}
	}




	if (i.ppField[1][1] == EMPTY)
	{
		return { 1, 1 };
	}

	TCoord buf[4];
	size_t{ 0 };

	if (i.ppField[0][0] == EMPTY)
	{
		buf[num] = { 0, 0 };
		num++;
	}
	if (i.ppField[2][2] == EMPTY)
	{
		buf[num] = { 2, 2 };
		num++;
	}
	if (i.ppField[0][2] == EMPTY)
	{
		buf[num] = { 0, 2 };
		num++;
	}
	if (i.ppField[2][0] == EMPTY)
	{
		buf[num] = { 2, 0 };
		num++;
	}
	if (num > 0)
	{
		const size_t index = rand() % num;
		return buf[index];
	}

	num = 0;
	if (i.ppField[0][1] == EMPTY)
	{
		buf[num] = { 0, 1 };
		num++;
	}
	if (i.ppField[1][0] == EMPTY)
	{
		buf[num] = { 1, 0 };
		num++;
	}
	if (i.ppField[1][2] == EMPTY)
	{
		buf[num] = { 1, 2 };
		num++;
	}
	if (i.ppField[2][1] == EMPTY)
	{
		buf[num] = { 2, 1 };
		num++;
	}
	if (num > 0)
	{
		const size_t index = rand() % num;
		return buf[index];
	}
}

 inline void congrats(const TGame& i)
{
	if (i.progress == WON_PEOPLE)
		cout << " People won! >o<" << endl;
	if (i.progress == WON_ROBOT)
		cout << " Robot won! =(" << endl;
	if (i.progress == DRAW)
		cout << " DRAW! -_-" << endl;
}

int main()
{
	TGame i;
	initGame(i);

	clearScr();
	printGame(i);

	do
	{

		if (i.turn % 2 == 0)
		{
			TCoord c = getPeopleCoord(i);
			i.ppField[c.y][c.x] = i.people;
		}
		else
		{
			TCoord c = getRobotCoord(i);
			i.ppField[c.y][c.x] = i.robot;
		}

		clearScr();
		printGame(i);
		i.turn++;
		i.progress = getWon(i);

	} while (i.progress == IN_PROGRESS);

	congrats(i);
	deinitGame(i);
}



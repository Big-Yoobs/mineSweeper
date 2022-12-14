// mineSweeper.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

using namespace std;

void mineField();
void mineField(bool showBombs);
int amountOfBoom(int x, int y);

char list[20][20];
char bombList[20][20];

char xAxis[] = { "ABCDEFGHIJKLMNOPQRST" };

int rowCounter[20];

int firstNumber = 0;
int lastNumber = 20;
int firstRandomNumber = 0;
int secondRandomNumber = 0;

int main()
{
	srand(time(NULL));

	for (int i = 0; i < 20; i++)
	{
		for (int x = 0; x < 20; x++)
		{
			bombList[i][x] = '.';
		}
	}

	for (int a = 0; a < 30; a++)
	{ 
		firstRandomNumber = rand() % (lastNumber - firstNumber + 1) + firstNumber;
		secondRandomNumber = rand() % (lastNumber - firstNumber + 1) + firstNumber;
		//cout << firstRandomNumber << " - " << secondRandomNumber << "\n";

		for (int i = 0; i < 20; i++)
		{
			for (int x = 0; x < 20; x++)
			{
				list[i][x] = '.';
				if (firstRandomNumber == i && secondRandomNumber == x)
				{
					bombList[i][x] = 'B';
				}
			}
		}
	}
	
	while (!0)
	{
		mineField();
		cout << "\n\n";
		char charXCord;
		int inputYCord;
		int inputXCord;

		cout << "Enter X cordinate: ";
		cin >> charXCord;
		cout << "Enter Y cordinate: ";
		cin >> inputYCord;

		for (int i = 0; i < 20; i++)
		{
			if (xAxis[i] == charXCord )
			{
				inputXCord = i;
				break;
			}
		}
		inputYCord = 20 - inputYCord;

		int gurPur = amountOfBoom(inputXCord, inputYCord);

		switch (gurPur)
		{
			case -1:
				cout << "L+Ratio\n";
				break;
			case 9:
				cout << "ded\n";
				mineField(true);
				return 0;
				break;
			default:
				char options[] = { "e12345678B" };
				list[inputYCord][inputXCord] = options[gurPur];
				if (!gurPur)
				{
					vector<vector<int>> coordinates;
					vector<int> firstCoords = { inputXCord, inputYCord };
					coordinates.push_back(firstCoords);
					while (coordinates.size()) {
						int coords[2];
						coords[0] = coordinates[0][0];
						coords[1] = coordinates[0][1];
						coordinates.erase(coordinates.begin());

						for (int ix = coords[0] - 1; ix <= coords[0] + 1; ix++)
						{
							for (int iy = coords[1] - 1; iy <= coords[1] + 1; iy++)
							{
								if (ix == coords[0] && iy == coords[1]) continue;
								int boomAmount = amountOfBoom(ix, iy);
								if (boomAmount == -1 || list[iy][ix] != '.') continue;
								char character = options[boomAmount];
								list[iy][ix] = character;
								if (!boomAmount)
								{
									vector<int> newCoords = { ix, iy };
									coordinates.push_back(newCoords);
								}
							}
						}
					}
				}
		}
	}
	cout << "Cords x:" << secondRandomNumber + 1 << " Cords y: " << 20 - firstRandomNumber ;
}

void mineField(bool showBombs)
{
	for (int i = 0; i < 20; i++)
	{
		cout << (20 - i) << (i <= 10 ? "   " : "    ");
		for (int x = 0; x < 20; x++)
		{
			if (showBombs && bombList[i][x] == 'B') {
				cout << "B";
				continue;
			}
			/*string colors[] = {
				"\u001b[37m",
				"\u001b[37m",
				"\u001b[34m",
				"\u001b[32m",
				"\u001b[31m",
				"\u001b[33m",
				"\u001b[35m",
				"\u001b[36m",
				"",
				""
			};*/
			char conversions[] = {
				'.',
				'e',
				'1',
				'2',
				'3',
				'4',
				'5',
				'6',
				'7',
				'8',
				'B'
			};
			//string colorCode = "";
			for (int a = 0; a < size(conversions); a++) {
				if (conversions[a] == list[i][x]) {
					//colorCode = colors[a];
					break;
				}
			}
			cout  << list[i][x] << " " ;
		}
		cout << "\n";
	}
	cout << "\n     ";
	for (char character : xAxis) 
	{
		cout << character << " ";
	}
}


/*

<< colorCode


<< "\u001b[37m"



\u001b[36m
 << "\u001b[37m"
*/

void mineField()
{
	mineField(false);
}

int amountOfBoom(int x, int y)
{
	if (x >= 20 || y >= 20 || x < 0 || y < 0)
	{
		return -1;
	}
	if (bombList[y][x] == 'B')
	{
		return 9;
	}
	int numberOfBombs = 0;
	for (int ix = x - 1; ix <= x + 1; ix++) 
	{
		if (ix < 0 || ix >= 20) continue;
		for (int iy = y - 1; iy <= y + 1; iy++)
		{
			if (iy < 0 || iy >= 20) continue;
			if (bombList[iy][ix] == 'B')
			{
				numberOfBombs++;
			}
		}
	}
	return numberOfBombs;
}

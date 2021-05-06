#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

const int ROWS = 3;
const int COLS = 3;
const int SIZE = 10;

// Assignment 3
// By: Danny Beaudoin
// 10 April 2021
// Bird watching program that tracks birds and makes calculations
// based on amount of sightings of each bird / location, using References.

void loadArrays(ifstream&, string[], int[][COLS], int&);
void computeSum(const int[SIZE][COLS], int[], const int&);
void findBird(const int[SIZE][COLS], int&, int&, const int&);
void mostSightings(const int[SIZE], int&, int);
void printReport(ofstream&, const string[SIZE], const int[][COLS], const int[], const int&, const int&);
void getTotalSightings(const int[SIZE], const int&, int&);

int main()
{
	int sightings[SIZE][3];
	string bird[SIZE];
	int totalAreaSightings[SIZE] = { 0 };
	int noBirds;
	int highestRow, highestCol, mostSeen;

	ifstream fin("birds.dat");
	if (!fin.is_open())
	{
		cout << "error opening birds.dat file - contact systems";
		system("pause");
		exit(-1);
	}
	ofstream fout("birds.rpt");
	if (!fout.is_open())
	{
		cout << "error opening birds.rpt file - contact systems";
		system("pause");
		exit(-2);
	}

	cout << "\n\nLoad arrays\n\n";
	loadArrays(fin, bird, sightings, noBirds);
	cout << "\n\n=======================================================\n\n";

	cout << "\n\nCompute total sightings by area\n\n";
	computeSum(sightings, totalAreaSightings, noBirds);
	cout << "\n\n=======================================================\n\n";

	cout << "\n\nFind most seen bird and highest number of sightings:\n\n";
	findBird(sightings, highestRow, highestCol, noBirds);
	cout << "\n\n" << bird[highestRow] << " had the most number of sightings = "
		<< sightings[highestRow][highestCol] << endl;
	cout << "\n\n=======================================================\n\n";
	
	cout << "\n\nFind the most seen bird:\n\n";
	mostSightings(totalAreaSightings, mostSeen, noBirds);
	cout << "\n\n Most seen bird is " << bird[mostSeen] << endl;

	cout << "\n\n=======================================================\n\n";

	printReport(fout, bird, sightings, totalAreaSightings, mostSeen, noBirds);
	cout << "\n\n=======================================================\n\n";

	fout.close();
	fin.close();

	cout << "program ended successfully" << endl;
	cout << "\n\n Printing birds.dat file\n\n";
	system("type birds.dat");
	cout << "\n\n Printing birds.rpt file\n\n";
	system("type birds.rpt");
	system("pause");
}

void loadArrays(ifstream & fin, string bird[SIZE], int sightings[SIZE][COLS], int& noBirds)
{
	if (!fin.is_open())
	{
		cout << "Error. Input file does not exist!\n";
		exit(-1);
	}

	noBirds = 0;
	for (; noBirds < SIZE; noBirds++)
	{
		if (fin.eof())
			break;

		getline(fin, bird[noBirds]);

		if (fin.eof())
		{
			std::cout << "File not formatted properly! Missing bird sightings amount!";
			exit(-1);
		}

		for (int col = 0; col < COLS; col++)
		{
			fin >> sightings[noBirds][col];
		}
		fin.ignore(80, '\n');

	}
}

void computeSum(const int sightings[SIZE][COLS], int totalAreaSightings[], const int & noBirds)
{
	int total = 0;
	for (int index = 0; index < noBirds; index++)
	{
		for (int col = 0; col < COLS; col++)
		{
			total += sightings[index][col];
		}
		totalAreaSightings[index] += total;
		
		total = 0;
	}
}

void findBird(const int sightings[SIZE][COLS], int & highestRow, int & highestCol, const int & noBirds)
{
	highestRow = 0;
	highestCol = 0;
	int highest = -1;
	for (int index = 0; index < noBirds; index++)
	{
		for (int col = 0; col < COLS; col++)
		{
			if (sightings[index][col] > highest)
			{
				highest = sightings[index][col];
				highestRow = index;
				highestCol = col;
			}
		}
	}
}

void mostSightings(const int totalAreaSightings[SIZE], int & mostSeen, int noBirds)
{
	mostSeen = 0;
	for (int index = 0; index < noBirds; index++)
	{
		if (totalAreaSightings[index] > totalAreaSightings[mostSeen])
		{
			mostSeen = index;
		}
	}
}

void getTotalSightings(const int totalAreaSightings[], const int& noBirds, int & totalSightings)
{
	for (int index = 0; index < noBirds; index++)
	{
		totalSightings += totalAreaSightings[index];
	}
}

void printReport(ofstream & fout, const string bird[SIZE], 
	const int sightings[SIZE][COLS], const int totalAreaSightings[], 
	const int & mostSeen, const int & noBirds)
{
	int totalSightings = 0;
	getTotalSightings(totalAreaSightings, noBirds, totalSightings);
	if (!fout.is_open())
	{
		cout << "Error. Output file does not exist!\n";
		exit(-1);
	}
	fout << left << setw(20) << "Type of Bird" << right 
		 << setw(15) << "Area #1" << setw(15) << "Area #2"
		 << setw(15) << "Area #3" << setw(15) << "Total" << '\n';
	for (int index = 0; index < noBirds; index++)
	{
		fout << left << setw(20) << bird[index] << '\t';
		for (int length = 0; length < 3; length++)
		{
			fout << right << setw(15) << sightings[index][length] << '\t';
		}
		if (totalAreaSightings[index] == totalAreaSightings[mostSeen])
		{
			fout << right << setw(10) << totalAreaSightings[index] << '\t' 
				 << right << setw(25) << " ** Most Sightings **";
			fout << endl;
		}
		else
		{
			fout << right << setw(10) << totalAreaSightings[index] << '\t';
			fout << endl;
		}
	}
	fout << "\n\nTotal Number of Sightings = " << totalSightings << " ";
	fout << "\n\n";
}
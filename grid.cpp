/*
	CSCI 270 Fall 2018
	Programming Assignment
	Name   : Colin Heath
	Email  : colinjhe@usc.edu
	USC ID : 8235366620
*/
#include <iostream>
#include <vector>
#include <string>
//	Feel free to include any other C++ standard library if necessary.

using namespace std;
//	You can add any custom classes / helper functions here.

struct TileHealth 
{
	int noPowerUp;
	int onlyP;
	int onlyD;
	int bothPD;
};

int solve(int N, vector<vector<string> > G) 
{
/*
	Please complete this function.
	N: Number of rows / columns of the grid.
	G: A 2d vector (N*N) indicating the grid.
		G[0][0] is the top left corner
		G[N-1][N-1] is the bottom right corner
	Return: the minimum life Brain needs to complete his task.
*/

	//Declare an array of the same size as G. The array will hold structs to track the health needed at each tile.
	TileHealth** requiredHealth = new TileHealth*[N];
	for(int i = 0; i < N; i++)
	{
		requiredHealth[i] = new TileHealth[N];

		for(int j = 0; j < N; j++)
		{
			requiredHealth[i][j].noPowerUp = 0;
			requiredHealth[i][j].onlyP = 0;
			requiredHealth[i][j].onlyD = 0;
			requiredHealth[i][j].bothPD = 0;
		}
	}

	requiredHealth[N-1][N-1].noPowerUp = std::max(1, 1 - std::stoi(G[N-1][N-1]));

	//Fill out the rightmost column and bottommost row, for starters.

	return requiredHealth[0][0].noPowerUp;
}

//	The main function reads the input and outputs your answer.
//	Please do not modify it. (Assume the input is well-formed;
//	You don't need to do any error-check)
int main(int argc, char **argv) {
	int N;
	vector<vector<string> > G;
	cin >> N;
	G.resize(N);
	for (int i=0; i<N; i++) {
		for (int j=0; j<N; j++) {
			string tmp;
			cin >> tmp;
			G[i].push_back(tmp);
		}
	}
	cout << solve(N, G) << endl;
	return 0;
}
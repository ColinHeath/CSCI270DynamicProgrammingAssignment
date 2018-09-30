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
#include <climits>
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

	//Declare an array with one more row and one more column than G.
	//It's larger than G so that I can avoid edge case logic for the rightmost and bottommost tiles.
	TileHealth** requiredHealth = new TileHealth*[N+1];
	for(int i = 0; i < N+1; i++)
	{
		requiredHealth[i] = new TileHealth[N+1];

		for(int j = 0; j < N+1; j++)
		{
			requiredHealth[i][j].noPowerUp = INT_MAX;
			requiredHealth[i][j].onlyP = INT_MAX;
			requiredHealth[i][j].onlyD = INT_MAX;
			requiredHealth[i][j].bothPD = INT_MAX;
		}
	}

	//These two entries MUST be one, so that the tile at [N-1][N-1] recognizes a need for a finishing health of 1.
	requiredHealth[N][N-1].noPowerUp = 1;
	requiredHealth[N][N-1].onlyP = 1;
	requiredHealth[N][N-1].onlyD = 1;
	requiredHealth[N][N-1].bothPD = 1;

	requiredHealth[N-1][N].noPowerUp = 1;
	requiredHealth[N-1][N].onlyP = 1;
	requiredHealth[N-1][N].onlyD = 1;
	requiredHealth[N-1][N].bothPD = 1;

	//Iterate in reverse through each row of the array, starting at (N-1, N-1), and fill in all four properties of the tile.
	for(int i = N-1; i >= 0; i--)
	{
		for(int j = N-1; j >= 0; j--)
		{
			TileHealth rightTile = requiredHealth[i+1][j];
			TileHealth downTile = requiredHealth[i][j+1];
			//First, handle the Power-Up Case:
			if(G[i][j] == "P")
			{
				requiredHealth[i][j].noPowerUp = std::min(rightTile.onlyP, downTile.onlyP);
				requiredHealth[i][j].onlyP = std::min(rightTile.onlyP, downTile.onlyP);
				requiredHealth[i][j].onlyD = std::min(rightTile.bothPD, downTile.bothPD);
				requiredHealth[i][j].bothPD = std::min(rightTile.bothPD, downTile.bothPD);	
			}
			else if(G[i][j] == "D")
			{
				requiredHealth[i][j].noPowerUp = std::min(rightTile.onlyD, downTile.onlyD);
				requiredHealth[i][j].onlyP = std::min(rightTile.bothPD, downTile.bothPD);
				requiredHealth[i][j].onlyD = std::min(rightTile.onlyD, downTile.onlyD);
				requiredHealth[i][j].bothPD = std::min(rightTile.bothPD, downTile.bothPD);	
			}
			else //Either malformed (which we were promised wouldn't happen) or integer
			{
				int tileDamage = std::stoi(G[i][j]);

				requiredHealth[i][j].noPowerUp = std::max(1, std::min(rightTile.noPowerUp, downTile.noPowerUp) - tileDamage);
				
				if(tileDamage < 0) //If Guard
				{
					requiredHealth[i][j].onlyP = std::max(1, std::min(rightTile.noPowerUp, downTile.noPowerUp));
					requiredHealth[i][j].onlyD = std::max(1, std::min(rightTile.onlyD, downTile.onlyD) - tileDamage);
					requiredHealth[i][j].bothPD = std::max(1, std::min(rightTile.onlyD, downTile.onlyD));
				}
				else
				{
					requiredHealth[i][j].onlyP = std::max(1, std::min(rightTile.onlyP, downTile.onlyP) - tileDamage);
					requiredHealth[i][j].onlyD = std::max(1, std::min(rightTile.noPowerUp, downTile.noPowerUp) - (2*tileDamage));
					requiredHealth[i][j].bothPD = std::max(1, std::min(rightTile.onlyP, downTile.onlyP) - (2*tileDamage));
				}
			}
		}
	}

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
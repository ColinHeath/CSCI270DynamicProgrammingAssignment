/*
	CSCI 270 Fall 2018
	Programming Assignment
	Name   :
	Email  :
	USC ID :
*/
#include <iostream>
#include <vector>
#include <string>
//	Feel free to include any other C++ standard library if necessary.

using namespace std;
//	You can add any custom classes / helper functions here.

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

	int** requiredHealth = new int*[N];

	for(int i = 0; i < N; i++)
	{
		requiredHealth[i] = new int[N];

		for(int j = 0; j < N; j++)
		{
			requiredHealth[i][j] = 0;
		}
	}

/*
	Start at bottom-right. Walk up and left to top and leftmost side, then step back along the diagonal.
	You'll be building up the values in the array. This implementation doesn't involve power-up tiles.
*/

	//Start by filling out the outermost segment.
	requiredHealth[N-1][N-1] = std::max(1, 1 - G[N-1][N-1]);

	for(int k = N - 2; k >= 0; k--)
	{
		requiredHealth[N-1][k] = std::max(1, requiredHealth[N-1][k+1] - G[N-1][k]);
		requiredHealth[k][N-1] = std::max(1, requiredHealth[k+1][N-1] - G[k][N-1]);
	}

	for(int l = N - 2; l >= 0; l--)
	{
		int valueOut = std::min(requiredHealth[l+1][l], requiredHealth[l][l+1]);
		requiredHealth[l][l] = std::max(1, valueOut - G[l][l]);

		for(int m = l; m >= 0; m--)
		{
			valueOut = std::min(requiredHealth[l+1][m], requiredHealth[l][m+1]);
			requiredHealth[l][m] = std::max(1, valueOut - G[l][m]);
		}

		for(int n = l; n >= 0; n--)
		{
			valueOut = std::min(requiredHealth[n][l+1], requiredHealth[n+1][l]);
			requiredHealth[n][l] = std::max(1, valueOut - G[n][l]);
		}
	}

	return requiredHealth[0][0];
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
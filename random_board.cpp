//	Daniel Chang
//	CSCI 4350
//	10/3/2018
//	random_board.cpp
//	random_board takes 8 puzzle state, seed and number of moves to be made as input and randomize the board then outputs the processed board.

#include <iostream>
#include <vector>


using namespace std;

int main(int argv, char* argc[]) 
{
	vector< vector<int> > board (3,vector<int>(3));
	int seed = atoi(argc[1]);
	int number_of_moves = atoi(argc[2]);
	srandom(seed);
	
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			cin >> board[i][j];							//Read in the board state
		}
	}
	
    for (int i = 0; i < number_of_moves; i++) 
	{
		int move = int((4.0*random()) / (RAND_MAX + 1.0));
		int dx[] = {-1,1,0,0};
		int dy[] = {0,0,-1,1};
		int x,y;
		for(int j = 0; j < 3; j++)
		{
			for(int k=0;k < 3; k++)
			{
				if(board[j][k]==0)						//Find the indexes of zero
				{
					x = j;
					y = k;
				}
			}
		}
		
		int newx = x + dx[move];
		int newy = y + dy[move];
		if(newx >= 0 && newx <= 2 && newy >= 0 && newy <= 2)
		{ 
			swap(board[newx][newy],board[x][y]);		//Move the zero
		}
	}
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			cout << board[i][j] << " ";
		}
		cout<<endl;
	}
	cout<<endl;
  
  return 0;
    
}
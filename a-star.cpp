//	Daniel Chang
//	CSCI 4350
//	10/3/2018
//	a-star.cpp
//	a-star solves 8 puzzle problem by a* algorithm
//	This program contains several heuristic:
//		0 - h(n) = 0
//		1 - h(n) = Number of tiles displaced from the goal
//		2 - h(n) = Sum of Manhattan (city-block) distances of all tiles from the goal
//		3 - h(n) = A novel heuristic of your own design, which I decided to check the number of rows and columns that are out of place


#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <math.h>


using namespace std;

typedef pair<vector<vector<int> > , int> state;				//stores the state variables (board pattern, id)
vector<vector<int> > goal (3,vector<int>(3));				//stores the goal that the program is trying to reach
vector<vector<int> > board (3,vector<int>(3));				//stores the randomized board that program recieves to solve
map<vector<vector<int> > ,bool> visited;					//stores all states that program has visited
map<vector<vector<int> > , vector<vector<int> > >parent;	//stores the parent node of each node

int numnode = 0;											//for counting N
int heuristic = 2;											//for deciding what heuristic to go with, default to 2(Manhattan) if none is entered

//Checks if there are any inversion within the puzzle, used by issvolable()
int getinvcount(int arr[])
{
    int inv_count = 0;
    for (int i = 0; i < 9 - 1; i++)
        for (int j = i+1; j < 9; j++)
             if (arr[j] && arr[i] &&  arr[i] > arr[j])
                  inv_count++;
    return inv_count;
}

//Check if the puzzle received was valid
bool issolvable(vector<vector<int> > puzzle)				
{
	int arr[8];
	int p=0;
	for(int i=0;i<3;i++ )
	{
		for(int j=0;j<3;j++)
		{
			arr[p]=puzzle[i][j];
			p++;
		}
	}
	int invcount =getinvcount(arr);

    return (invcount%2 == 0);
}

//Check if a state has been visited
bool visit(vector<vector<int> > a)
{
	numnode++;
	if(visited[a]==true)
		return true;
	else
		return false;
}

//Check if the direction zero is moving to is valid
bool isvalid(int x,int y)
{
	if(x>=0&&x<=2&&y>=0&&y<=2) 
	{
		return true;
	}
	return false;
}

//------------------------------------Heuristic---------------------------------------
//0 - h(n) = 0
int uniformcost(state a)
{
	return 0;
}

//1 - h(n) = Number of tiles displaced from the goal
int num_of_tiles(state a)
{
	vector<vector<int> > tmp=a.first;
	int total=a.second;
	for(int i =0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			if(tmp[i][j] != 0)
			{
				for(int u=0;u<3;++u)
				{
					for(int v=0;v<3;++v)
					{
						if(goal[u][v]!=tmp[i][j])
						total++;
					}
				}
			}
		}
	}
	return total;
}

//2 - h(n) = Sum of Manhattan (city-block) distances of all tiles from the goal
int manhattan(state a)
{
	vector<vector<int> > tmp=a.first;
	int total=a.second;

	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			if(tmp[i][j] != 0)
			{
				for(int k = 0; k < 3; k++)
				{
					for(int l = 0; l < 3; l++)
					{
						if(goal[k][l] == tmp[i][j])
							total+=abs(k-i)+abs(l-j);
					}
				}
			}
		}
	}
	return total;
}

//3 - h(n) = A novel heuristic of your own design
/*I decided to check the number of rows and columns that are out of place, for example

	0 1 2
	5 6 7 <
	3 4 8 <
    ^ ^
	this state has 2 rows that are out of place and 2 columns that are out of place, so h(n) = 4
*/
int novel(state a)
{
	vector<vector<int> > tmp=a.first;
	int total=a.second;
	
	for(int i = 0; i<3; i++)
	{
		if(goal[i][0] != tmp[i][0] || goal[i][1] != tmp[i][1] || goal[i][2] || tmp[i][2])
			total++;
		if(goal[0][i] != tmp[0][i] || goal[1][i] != tmp[1][i] || goal[2][i] || tmp[2][i])
			total++;
	}
	return total;
}
//-----------------------------------End of Heuristic-----------------------------------------------


//Move the zero to manipulate the board
//Add new nodes as it expands
vector<vector<vector<int> > > possible_moves(vector<vector<int> > st)
{
	vector<vector<vector<int> > > lst;
	int dx[] = {-1,1,0,0};
	int dy[] = {0,0,-1,1};
	int x,y;
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			if(st[i][j]==0)
			{
				x = i;
				y = j;
			}
		}
	}
	for(int i=0;i<4;i++)
	{
		vector<vector<int> > d = st;
		int newx = x + dx[i];
		int newy = y + dy[i];
		if(isvalid(newx,newy))
		{ 
			swap(d[newx][newy],d[x][y]);
			lst.push_back(d);
		}

	}
	return lst;

}

//The comparator function that uses h(n) to make better decisions
struct cmp
{
	bool operator() (state a, state b)
	{
		int hn1, hn2;
		if(heuristic == 0)
		{
			hn1 = uniformcost(a);
			hn2 = uniformcost(b);
		}
		else if(heuristic == 1)
		{
			hn1 = num_of_tiles(a);
			hn2 = num_of_tiles(b);
		}
		else if(heuristic == 2)
		{
			hn1 = manhattan(a);
			hn2 = manhattan(b);
		}
		else if(heuristic == 3)
		{
			hn1 = novel(a);
			hn2 = novel(b);
		}
		return hn1 > hn2;
	}
};

//Recursively function 
//Prints the state of the puzzle from unsolved to goal
void print_state(vector<vector<int> > v)
{
	if(parent.count(v))
	{
		print_state(parent[v]);
	}
	for(int i = 0 ; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			cout<<v[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
}

//solve() function will attempt to solve the puzzle by using heuristic function
// uses map to check to backtrack for useful data V, N, d, b
void solve()
{
	priority_queue<state,vector<state>,cmp> frontier;
	frontier.push(state(board,0));

	while(!frontier.empty())
	{
		state s=frontier.top();
		vector<vector<int> > st=s.first;
		int moves=s.second;

		frontier.pop();
		visited[st]=true;
		if(st==goal)	//Check goal
		{
			int depth = moves + 1;
			double branch = pow(numnode, 1/double(depth));
			cout << "V = " << visited.size() << endl;
			cout << "N = " << numnode << endl;
			cout << "d = " << depth << endl;
			cout << "b = " << branch << endl;
			print_state(st);
			break;
		}

		vector<vector<vector<int> > > adjacents=possible_moves(st);
		vector<vector<vector<int> > > :: iterator itr;
		for( itr = adjacents.begin(); itr!=adjacents.end();itr++)
		{
			vector<vector<int> > p=*itr;
			if(!visit(p))	//Check if visited
			{
				frontier.push(state(p,moves+1));		//push onto frontier
				parent.insert(pair<vector<vector<int> > ,vector<vector<int> > > (p,st));
			}
		}
	}
}

int main(int argv, char* argc[])
{	
	if(argc[1])	heuristic = atoi(argc[1]);		//Check argc for heuristic input
	
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			goal[i][j]=3*i+j;					//Sets up puzzle goal
		}
	}
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			cin >> board[i][j];					//Receives initial puzzle state
		}
	}
	if(issolvable(board))						//Check if puzzle is valid
		solve();
	else 
		cout<<"invalid puzzle"<<endl;
	return 0;

}
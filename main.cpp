/* ---------------------------------------------------------------------------
** Project 2 - Mitra, The Messenger of Love
** COP3530 - Spring 2016
**
** Authors: 
** 	Brandon Goldman, Michael Riccardi, Harrison Magoutas, Ryan Gruszczyk
** -------------------------------------------------------------------------*/

#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <string>

using namespace std;

struct Edge; // empty declaration to make the compiler happy

struct Vertex
{
	bool visited;
	string value;
	vector<Edge*> edges;
	Vertex(string v)
	{
		value = v;
		visited = false;
	}
	void addEdge(Edge* e)
	{
		edges.push_back(e);
	}
};

struct Edge
{
	int weight;
	Vertex* next;
	Edge(Vertex* n, int w)
	{
		weight = w;
		next = n;
	}
};

struct Graph
{
	vector<Vertex*> vertices;
	Graph()
	{
	}
	void addVertex(Vertex* v)
	{
		vertices.push_back(v);
	}
};

struct realm
{
	vector <int> magis;
	string charm;
};

vector<int> maxIncantations(vector<int> magi)
{
	// determine most number of possible steps
	int magiSeqSize = magi.size();
	vector<int> P (magiSeqSize);
	vector<int> M (magiSeqSize+1);
	
	int L = 0;
	
	for (int i = 0; i <= magiSeqSize-1; i++)
	{
		int low = 1;
		int high = L;
		
		while (low <= high)
		{
			int mid = ceil((low+high)/2);
			
			if (magi[M[mid]] < magi[i])
			{
				low = mid+1;
			}
			else
			{
				high = mid-1;
			}
		}
		
		// After searching, low is 1 greater than the length
		// of the longest prefix of magi[i]
		int newLow = low;
		
		// The predecessor of magi[i] is the last
		// index of the subsequence of length newLow-1
		
		
		
	}
}

// edit distance algorithm to find string alignment
int minIncantationsBetween(string startingRealm, string endingRealm)
{
	// return minimum number of incantations needed to go start -> end
	int sizeOfStart = startingRealm.length() + 1;
	int sizeOfEnd = endingRealm.length() + 1;
	int distanceBetween[sizeOfStart][sizeOfEnd];

	// PSEUDOCODE FROM THE INTERWEBS WOO!!
	// parse string
	// for size of A (0:i)
	// 		for size of B (0:j)
	//			if i=0, dist[i][j] = j;
	//			if j=0, dist[i][j] = i;
	//			if char at A(i-1) = char at B(j-1)
	//				dist[i][j] = dist[i-1][j-1];
	//			else dist[i][j] = 1 + findMinOf(dist[i][j-1], dist[i-1][j], dist[i-1][j-1]);

	for(int i = 0; i <= startingRealm.size(); i++)
	{
		for(int j = 0; j <= endingRealm.size(); j++)
		{
			if (i == 0)
			{
				distanceBetween[i][j] = j;
			}
			else if (j == 0)
			{
				distanceBetween[i][j] = i;
			}
			else if (startingRealm.at(i - 1) == endingRealm.at(j - 1))
			{
				distanceBetween[i][j] = distanceBetween[i-1][j-1];
			}
			else
			{
				distanceBetween[i][j] = 1 + min( min(distanceBetween[i][j-1], distanceBetween[i-1][j]), distanceBetween[i-1][j-1]);
			}
		}
	}

	return distanceBetween[ startingRealm.length() ][ endingRealm.length() ];
}

// Dijkstra's Method to determine least heavy path start -> end

bool checkIfPossibleStartToFinish()
{
	// does # steps start to finish == # possible incantations
	// if not, bool is IMPOSSIBLE, print statement in different method
	
	// Michael: this might be covered in Dijkstra's algorithm
}

void shortestPath(Graph graph)
{
	// cout incantations + " " + gems;
}

Graph makeGraph(vector<realm> realms)
{
	// for return trip, reverse vector
}

// if impossible, make num of incantations = -1 || set minIncantations = -1

int main()
{
  int numOfRealms, numOfMagi, magiPower;
  string charm, startingCharm, destinationCharm;
  vector <int> sequenceOfMagi;

  cin >> numOfRealms;

  for(int i = 0; i < numOfRealms; i++)
  {
  	cin >> charm;
  	cin >> numOfMagi;
  	sequenceOfMagi.resize(numOfMagi);	// set size of vector to number of magi
  	
  	for(int j = 0; j < numOfMagi; j++)
  	{
  		cin >> sequenceOfMagi.at(j);
  	}
  }

  cin >> startingCharm;
  cin >> destinationCharm;

  return 0;
}

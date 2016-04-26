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
#include <cmath>
#include <climits>

using namespace std;

struct Realm
{
	vector<int> magi;
	string charm;
	Realm()
	{
		charm = "";
	}
	Realm(string c, vector<int> m)
	{
		charm = c;
		magi = m;
	}
};

struct Edge; // empty declaration to make the compiler happy

struct Vertex
{
	bool visited;
	Realm realm;
	int distance;
	int cost;
	vector<Edge*> edges;
	Vertex(Realm r)
	{
		realm = r;
		visited = false;
		distance = INT_MAX;
		cost = 0;
	}
	void addEdge(Edge* e)
	{
		edges.push_back(e);
	}
};

struct Edge
{
	int weight;
	int cost;
	Vertex* next;
	Edge(Vertex* n, int w, int c)
	{
		weight = w;
		next = n;
		cost = c;
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
		int newLong = low;
		
		// The predecessor of magi[i] is the last
		// index of the subsequence of length newLow-1
		P[i] = M[newLong-1];
		M[newLong] = i;
		
		if (newLong > L)
		{
			// if we found a subsequence longer than any we've found yet, update L
			L = newLong;
		}
	}
	
	// Reconstruct the longest increasing subsequence
	vector<int> subSequence (L);
	int k = M[L];
	
	for (int i = L-1; i>=0; i--)
	{
		subSequence[i] = magi[k];
		k = P[k];
	}
	
	return subSequence;
}

// Call this to test the maxIncantations() function
void test_maxIncantations()
{
	bool debugFlag = true;
	if (debugFlag) {
		std::cout << "Debugging is turned ON for test_maxIncantations()" << endl;
	}
	
	int testSize; // temporary storage for size
	
	if (debugFlag) { std::cout << "Define a size for the test sequence vector." << endl; } // debug line
	
		std::cin >> testSize; // get size from user at test runtime
	
		vector<int> testVector (testSize); // temporary storage for a test vector
	
	for (int i = 0; i<testSize; i++) // iterate through sequence
	{
		if (debugFlag) { std::cout << "Define the value at index " << i << endl; } // debug line
		
			std::cin >> testVector[i]; // store each magi value of sequence
		
		if (debugFlag) { std::cout << "Value of " << testVector[i] << " was stored at " << i << endl; } // debug line
	}
	
	if (debugFlag) { std::cout << "About to call maxIncantations()..." << endl; } // debug line
	
		vector<int> testMagiSeq = maxIncantations(testVector); // declare another vector that will store the return vector from calling maxIncantations()
	
	if (debugFlag) { std::cout << "Finished call for maxIncantations()." << endl; } // debug line

	// Iterate through and print the vector values with the maximum incantations
	if (debugFlag) { std::cout << "Iterating output..." << endl; } // debug line
		for (auto it = testMagiSeq.begin(); it!= testMagiSeq.end(); it++)
		{
			std::cout << *it << " "; // dereferencing the values of the maxIncantations sequence
		}
	
		std::cout << endl;
	if (debugFlag) { std::cout << "Completed." << endl; } // debug line
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

Graph makeGraph(vector<Realm> realms)
{
	Graph graph = Graph();
	
	// add each realm to the graph
	for(int i = 0; i < realms.size(); i++)
	{
		graph.addVertex(new Vertex(realms[i]));
	}
	
	// for each realm
	for(int i = 0; i < realms.size(); i++)
	{
		// try to link each to the realms after it
		for(int j = 0; j < realms.size(); j++)
		{
			if(i == j) { continue; }
			//cout << "i = " << i << "; j = " << j << endl;
			vector<int> incantations = maxIncantations(realms[i].magi);
			
			int available = incantations.size(); // # of incantations possible 
			int needed = minIncantationsBetween(realms[i].charm, realms[j].charm); // # of incantations needed
			if(available >= needed) // if it is possible to travel from realm[i] to realm[j]
			{
				int cost = 0;
				for(int k = 0; k < needed; k++)
				{
					cost += incantations[k];
				}
				// add edge connecting the two, with weight of the # of incantations needed
				graph.vertices[i]->addEdge(new Edge(graph.vertices[j], needed, cost));
			}
		}
	}
	
	return graph;
}

// Dijkstra's Method to determine least heavy path start -> end
void shortestPath(Graph &graph, string startingCharm, string destinationCharm)
{
	int N = graph.vertices.size();
	
	int startIndex = -1;
	int destinationIndex = -1;
	bool startFound = false;
	bool destinationFound = false;
	
	for(int i=0; i < graph.vertices.size(); i++)
	{
		if(graph.vertices[i]->realm.charm == startingCharm)
		{
			startIndex = i;
			startFound = true;
		}
		if(graph.vertices[i]->realm.charm == destinationCharm)
		{
			destinationIndex = i;
			destinationFound = true;
		}
		if(startFound && destinationFound)
		{
			break;
		}
	}
	
	if(startIndex == -1 || destinationIndex == -1)
	{
		cout << "IMPOSSIBLE" << endl;
		return;
	}
	
	/* 1. Assign to every node a tentative distance value: set it to zero
	 * for our initial node and to infinity for all other nodes. */

	graph.vertices[startIndex]->distance = 0;
	// others are set to INT_MAX by default
	
	/* 2. Set the initial node as current. Mark all other nodes unvisited.
	 * Create a set of all the unvisited nodes called the unvisited set. */
	 
	Vertex* curVertex = graph.vertices[startIndex];
	// others are unvisited by default
	
	int minDistance = INT_MAX;
	Vertex* minVertex = NULL;
	
	int shortestIndex = -1;
	
	do
	{
		minVertex = curVertex->edges[0]->next;
		minDistance = curVertex->distance;
		//cout << curVertex->realm.charm << endl;

		/* 3. For the current node, consider all of its unvisited neighbors and
		 * calculate their tentative distances. Compare the newly calculated
		 * tentative distance to the current assigned value and assign the
		 * smaller one. For example, if the current node A is marked with a
		 * distance of 6, and the edge connecting it with a neighbor B has
		 * length 2, then the distance to B (through A) will be 6 + 2 = 8.
		 * If B was previously marked with a distance greater than 8 then
		 * change it to 8. Otherwise, keep the current value. */
		 
		//cout << curVertex->edges.size() << endl;
				
		for(int i=0; i < curVertex->edges.size(); i++)
		{
			Edge* curEdge = curVertex->edges[i];
			int curWeight = curEdge->weight;
			int curCost = curEdge->cost;
			Vertex* next = curEdge->next;
			
			if(!next->visited)
			{				
				//cout << "  " << next->realm.charm << endl;
				
				int tentative_distance = curVertex->distance + curWeight;
				
				if(tentative_distance < next->distance)
				{
					next->distance = tentative_distance;
					next->cost = curVertex->cost + curCost;
					//cout << "    shorter found" << endl;
				}				
			}			
		}
		
		/* 4. When we are done considering all of the neighbors of the current node,
		*  mark the current node as visited and remove it from the unvisited set.
		*  A visited node will never be checked again. */
		curVertex->visited = true;
	
		/* 6. Otherwise, select the unvisited node that is marked with the smallest
		 * tentative distance, set it as the new "current node", and go back to step 3. */
		 
		int shortestDistance = INT_MAX;
		shortestIndex = -1;
		
		for(int i=0; i < graph.vertices.size(); i++)
		{
			Vertex* Vi = graph.vertices[i];
			if(!Vi->visited)
			{
				if(Vi->distance < shortestDistance)
				{
					shortestIndex = i;
					shortestDistance = Vi->distance;
				}
			}
		}
		if(shortestIndex >= 0)
		{
			curVertex = graph.vertices[shortestIndex];
		}
	
		/* 5. If the destination node has been marked visited (when planning a
		 * route between two specific nodes) or if the smallest tentative distance
		 * among the nodes in the unvisited set is infinity (when planning a complete
		 * traversal; occurs when there is no connection between the initial node and
		 * remaining unvisited nodes), then stop. The algorithm has finished. */
		 
	} while(!graph.vertices[destinationIndex]->visited && shortestIndex >= 0);
	
	if(graph.vertices[destinationIndex]->visited)
	{
		cout << graph.vertices[destinationIndex]->distance << " " << graph.vertices[destinationIndex]->cost << endl;
	}
	else
	{
		cout << "IMPOSSIBLE" << endl;
	}
}

int main()
{
	int numOfRealms, numOfMagi, magiPower;
	string charm, startingCharm, destinationCharm;
	vector<Realm> realms;
	vector <int> sequenceOfMagi;

	cin >> numOfRealms;

	for(int i = 0; i < numOfRealms; i++)
	{
		Realm realm = Realm();
		cin >> realm.charm;
		cin >> numOfMagi;

		sequenceOfMagi.resize(numOfMagi); // set size of vector to number of magi
  	
		for(int j = 0; j < numOfMagi; j++)
		{
			int power;
			cin >> sequenceOfMagi[j];
			realm.magi.push_back(power);
		}
		realm.magi = sequenceOfMagi;
		realms.push_back(realm);
	}

	cin >> startingCharm;
	cin >> destinationCharm;

	Graph graph = makeGraph(realms);
	shortestPath(graph, startingCharm, destinationCharm);
	Graph graph2 = makeGraph(realms); // second graph because the method modifies the original
	shortestPath(graph2, destinationCharm, startingCharm);

	return 0;
}

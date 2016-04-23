/* ---------------------------------------------------------------------------
** Project 2 - Mitra, The Messenger of Love
** COP3530 - Spring 2016
**
** Authors: 
** 	Brandon Goldman, Michael Riccardi, Harrison Magoutas, Ryan Gruszczyk
**
** -------------------------------------------------------------------------*/

#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>

using namespace std;

struct realm
{
	// vector <int> magis;
	// string charm;
};

int  maxIncantations(vector <int> magi)
{
	// determine most number of possible steps
}

int minIncantationsBetween(string startingRealm, string endingRealm)
{
	// return minimum number of incantations needed to go start -> end
}

// Dijkstra's Method to determine least heavy path start -> end

bool checkIfPossibleStartToFinish()
{
	// does # steps start to finish == # possible incantations
	// if not, bool is IMPOSSIBLE, print statement in different method
}

void int shortestPath(DirectedWeightedGraph graph)
{
	// cout incantations + " " + gems;
}

DirectedWeightedGraph makeGraph(vector <realm> realms)
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

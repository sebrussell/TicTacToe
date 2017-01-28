#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <memory>
#include <ctime>
#include <iostream>

#include "GameState.h"
#include "Tree.h"
#include "Allegro.h"
#include "Draw.h"

// nice colour (42, 120, 242);



//list of functions so main can use them, would be better in a different file 

int main(int argc, char **argv)															//start of main 
{
	double deltaTime = 0;
	double totalTime = 0;
	std::clock_t begin, end;

	Allegro allegro;
	allegro.Initialise();

	srand(time(NULL));

	Draw draw;
	Tree test;
	test.GenerateTree();

	int position;
	std::string tempString;

	bool gameOver = false;
	bool playerToGoFirst = true;

	while (1 == 1)																						
	{
		begin = clock();
		
		draw.Update(test.GetNode());
		draw.GetInput();

		if (playerToGoFirst == true)
		{
			if (test.GetNode()->DidXGoLast() == false)
			{
				std::cout << "Enter position";
				tempString = test.GetNode()->GetBoardString();
				std::cin >> position;
				tempString[position] = 'x';

				for (std::shared_ptr<GameState> l : test.GetNode()->GetChildNodes())		//change this to actual not 2015 stuff
				{
					if (l->GetBoardString() == tempString)
					{
						test.SetNode(l);
						break;
					}
				}
			}
			else
			{
				std::shared_ptr<GameState> tempNode = test.GetNode()->GetChildNodes().front();

				if (test.GetNode()->GetChildNodes().size() > 0)
				{
					for (std::shared_ptr<GameState> l : test.GetNode()->GetChildNodes())		//change this to actual not 2015 stuff
					{
						if (l->GetNodeValue() < tempNode->GetNodeValue())
						{
							tempNode = l;
						}
					}
				}
				else
				{
					gameOver = true;
				}


				test.SetNode(tempNode);
			}
		}
		else
		{
			if (test.GetNode()->DidXGoLast() == true)
			{
				std::cout << "Enter position";
				tempString = test.GetNode()->GetBoardString();
				std::cin >> position;
				tempString[position] = 'o';

				for (std::shared_ptr<GameState> l : test.GetNode()->GetChildNodes())		//change this to actual not 2015 stuff
				{
					if (l->GetBoardString() == tempString)
					{
						test.SetNode(l);
						break;
					}
				}
			}
			else
			{
				std::shared_ptr<GameState> tempNode = test.GetNode()->GetChildNodes().front();

				if (test.GetNode()->GetChildNodes().size() > 0)
				{
					for (std::shared_ptr<GameState> l : test.GetNode()->GetChildNodes())		//change this to actual not 2015 stuff
					{
						if (l->GetNodeValue() > tempNode->GetNodeValue())
						{
							tempNode = l;
						}
					}
				}
				else
				{
					gameOver = true;
				}


				test.SetNode(tempNode);
			}
		}		
		
		end = clock();
		deltaTime = double(end - begin) / CLOCKS_PER_SEC;															//this is used for delta time and timers
		totalTime += deltaTime;
	}
	return 0;
}
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

void PlayGame(int _mousePosition, bool _playerLastWent, Tree& _tree);

int main(int argc, char **argv)
{
	Allegro allegro;
	Draw draw(allegro.display);
	Tree tree;

	bool playerToGoFirst = false;

	while (tree.GetNode()->GetGameStatus() == GameState::playing)
	{
		draw.Update(tree.GetNode());
		PlayGame(draw.GetInput(), playerToGoFirst, tree);
	}

	draw.DrawOutcome(tree.GetNode());
	return 0;
}

void PlayGame(int _mousePosition, bool _playerWentFirst, Tree& _tree)
{
	std::string tempString;

	if ((_tree.GetNode()->DidXGoLast() == false && _playerWentFirst == true) || (_tree.GetNode()->DidXGoLast() == true && _playerWentFirst == false))
	{
		if (_mousePosition >= 0 && _mousePosition < 9)
		{
			tempString = _tree.GetNode()->GetBoardString();

			if (_playerWentFirst == true && _tree.GetNode()->DidXGoLast() == false)
			{
				tempString[_mousePosition] = 'x';
			}
			else
			{
				tempString[_mousePosition] = 'o';
			}
		}
		for (std::shared_ptr<GameState> node : _tree.GetNode()->GetChildNodes())
		{
			if (node->GetBoardString() == tempString)
			{
				_tree.SetNode(node);
				break;
			}
		}
	}
	else
	{
		std::shared_ptr<GameState> tempNode = _tree.GetNode()->GetChildNodes().front();

		for (std::shared_ptr<GameState> node : _tree.GetNode()->GetChildNodes())
		{
			if (_playerWentFirst == true)
			{
				if (node->GetNodeValue() < tempNode->GetNodeValue())
				{
					tempNode = node;
				}
			}
			else
			{
				if (node->GetNodeValue() > tempNode->GetNodeValue())
				{
					tempNode = node;
				}
			}
			
		}
		_tree.SetNode(tempNode);
	}
}

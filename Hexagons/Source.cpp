#include "Tree.h"
#include "Allegro.h"
#include <stdlib.h>

void PlayGame(int _mousePosition, bool _playerLastWent, Tree& _tree, bool _computerVsComputer);

//add an auto mode / random picking of node / crazy mode where every 5th is random - make it evident

int main(int argc, char **argv)
{
	bool playerToGoFirst = false;
	bool computerVsComputer = true;
	bool replay = false;
	int menuInput;

	Allegro allegro;
	Tree tree;

	srand(time(NULL));

	do
	{
		while (tree.GetNode()->GetGameStatus() == GameState::playing)
		{
			allegro.Update(tree.GetNode());
			if (computerVsComputer == false)
			{
				PlayGame(allegro.GetInput(false), playerToGoFirst, tree, computerVsComputer);
			}
			else
			{
				if (playerToGoFirst == true)
				{
					PlayGame(allegro.GetInput(false), playerToGoFirst, tree, computerVsComputer);
					playerToGoFirst = false;
				}
				else
				{
					PlayGame(allegro.GetInput(false), playerToGoFirst, tree, computerVsComputer);
					playerToGoFirst = true;
				}
			}
		}
		allegro.DrawOutcome(tree.GetNode());
		replay = false;

		do
		{
			menuInput = allegro.GetInput(true);
			if (menuInput == 0)
			{
				replay = true;
				tree.Reset();
				if (playerToGoFirst == true)
				{
					playerToGoFirst = false;
				}
				else
				{
					playerToGoFirst = true;
				}
			}
		} while (menuInput == -1);


	} while (replay == true);


	return 0;
}

void PlayGame(int _mousePosition, bool _playerWentFirst, Tree& _tree, bool _computerVsComputer)
{
	std::string tempString;

	if (_computerVsComputer == false)
	{
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
	else
	{
		std::shared_ptr<GameState> tempNode = _tree.GetNode()->GetChildNodes().front();
		
		if (_playerWentFirst == true)
		{
			for (std::shared_ptr<GameState> node : _tree.GetNode()->GetChildNodes())
			{
				if (node->GetNodeValue() < tempNode->GetNodeValue())
				{
					tempNode = node;  //add so it picks the best 4?
				}
			}
		}
		else
		{
			int randomAmount = rand() % _tree.GetNode()->GetChildNodes().size();

			for (std::shared_ptr<GameState> node : _tree.GetNode()->GetChildNodes())
			{
				if (randomAmount <= 0)
				{
					break;
				}
				tempNode = node;
				randomAmount--;
			}

		}
		_tree.SetNode(tempNode);
	}
}

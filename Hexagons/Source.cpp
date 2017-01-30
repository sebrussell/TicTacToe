#include "Tree.h"
#include "Allegro.h"

void PlayGame(int _mousePosition, bool _playerLastWent, Tree& _tree);

int main(int argc, char **argv)
{
	bool playerToGoFirst = false;
	bool replay = false;
	int menuInput;

	Allegro allegro;	
	Tree tree;

	do
	{		
		while (tree.GetNode()->GetGameStatus() == GameState::playing)
		{
			allegro.Update(tree.GetNode());
			PlayGame(allegro.GetInput(false), playerToGoFirst, tree);
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

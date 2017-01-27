#include "GameState.h"

GameState::GameState()
{
	m_boardString = "         ";
	m_boardStatus = playing;
	m_xTurnLast = false;
	m_nodeValue = 0;
	m_multiplier = 1;
}

GameState::GameState(std::string _board)
{
	m_boardString = _board;
	m_xTurnLast = false;
	m_nodeValue = 0;
	m_multiplier = 1;
	CheckForWin();
}

GameState::~GameState()
{
}

void GameState::CheckForWin()
{
	m_boardStatus = draw;

	for (size_t i = 0; i < 9; i++)
	{
		if (m_boardString[i] == ' ')
		{
			m_boardStatus = playing;
			m_multiplier += 1;
		}
	}

	if (m_boardString[0] == m_boardString[1] && m_boardString[1] == m_boardString[2] && m_boardString[0] != ' ')		//remove the empty check
	{
		if (m_boardString[0] == 'x')
		{
			m_boardStatus = xWon;
		}
		else
		{
			m_boardStatus = oWon;
		}
	}

	if (m_boardString[3] == m_boardString[4] && m_boardString[4] == m_boardString[5] && m_boardString[3] != ' ')
	{
		if (m_boardString[3] == 'x')
		{
			m_boardStatus = xWon;
		}
		else
		{
			m_boardStatus = oWon;
		}
	}

	if (m_boardString[6] == m_boardString[7] && m_boardString[7] == m_boardString[8] && m_boardString[6] != ' ')
	{
		if (m_boardString[6] == 'x')
		{
			m_boardStatus = xWon;
		}
		else
		{
			m_boardStatus = oWon;
		}
	}

	if (m_boardString[0] == m_boardString[3] && m_boardString[3] == m_boardString[6] && m_boardString[0] != ' ')
	{
		if (m_boardString[0] == 'x')
		{
			m_boardStatus = xWon;
		}
		else
		{
			m_boardStatus = oWon;
		}
	}

	if (m_boardString[1] == m_boardString[4] && m_boardString[4] == m_boardString[7] && m_boardString[1] != ' ')
	{
		if (m_boardString[1] == 'x')
		{
			m_boardStatus = xWon;
		}
		else
		{
			m_boardStatus = oWon;
		}
	}

	if (m_boardString[2] == m_boardString[5] && m_boardString[5] == m_boardString[8] && m_boardString[2] != ' ')
	{
		if (m_boardString[2] == 'x')
		{
			m_boardStatus = xWon;
		}
		else
		{
			m_boardStatus = oWon;
		}
	}

	if (m_boardString[0] == m_boardString[4] && m_boardString[4] == m_boardString[8] && m_boardString[0] != ' ')
	{
		if (m_boardString[0] == 'x')
		{
			m_boardStatus = xWon;
		}
		else
		{
			m_boardStatus = oWon;
		}
	}

	if (m_boardString[2] == m_boardString[4] && m_boardString[4] == m_boardString[6] && m_boardString[2] != ' ')
	{
		if (m_boardString[2] == 'x')
		{
			m_boardStatus = xWon;
		}
		else
		{
			m_boardStatus = oWon;
		}
	}

	switch (m_boardStatus)
	{
	case GameState::playing:
		m_nodeValue = 0;
		break;
	case GameState::xWon:
		m_nodeValue = 10;
		break;
	case GameState::oWon:
		m_nodeValue = -10;
		break;
	case GameState::draw:
		m_nodeValue = -5;
		break;
	default:
		m_nodeValue = 0;
		break;
	}

	m_nodeValue *= m_multiplier;
}

std::string GameState::GetBoardString()
{
	return m_boardString;
}

void GameState::SetBoardString(std::string _board)
{
	m_boardString = _board;
}

void GameState::AddChild(std::shared_ptr<GameState>& _child)
{
	m_childNodes.push_back(_child);
}

GameState::Status GameState::GetGameStatus()
{
	return m_boardStatus;
}

void GameState::TurnPlaced(bool _xturn)
{
	m_xTurnLast = _xturn;
}

bool GameState::DidXGoLast()
{
	return m_xTurnLast;
}

int GameState::GetNodeValue()
{
	return m_nodeValue;
}

void GameState::SetNodeValue(double _value)
{
	m_nodeValue += _value;
}

std::list<std::shared_ptr<GameState>> GameState::GetChildNodes()
{
	return m_childNodes;
}





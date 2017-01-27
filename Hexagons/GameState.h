#pragma once
#include <string>
//#include <vector>
#include <list>
#include <memory>

class GameState
{
public:
	enum Status
	{
		playing,
		xWon,
		oWon,
		draw,
	};
	GameState();
	GameState(std::string _board);
	~GameState();
	void CheckForWin();
	std::string GetBoardString();
	void SetBoardString(std::string _board);
	void AddChild(std::shared_ptr<GameState>& _child);
	Status GetGameStatus();
	void TurnPlaced(bool _xturn);
	bool DidXGoLast();
	int GetNodeValue();
	void SetNodeValue(double _value);
	std::list<std::shared_ptr<GameState>> GetChildNodes();
private:
	std::string m_boardString;
	Status m_boardStatus;
	std::list<std::shared_ptr<GameState>> m_childNodes;
	bool m_xTurnLast;
	double m_nodeValue;
	int m_multiplier;
};


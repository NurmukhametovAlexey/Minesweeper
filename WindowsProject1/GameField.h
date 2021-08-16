#include "wx/wx.h"

#pragma once
class GameField
{
	struct ButtonState
	{
		bool hasMine;
		bool flagged;
		int neighbourMines;

		ButtonState(int neigbourMines) {
			hasMine = false;
			flagged = false;
			neighbourMines = neigbourMines;
		}

		ButtonState(): ButtonState(0) {}
	};

private:
	
	int gameFieldWidth;
	int gameFieldHeight;
	int minesCount;

	int flagsCount;

	ButtonState** btnState;
	bool firstClick;

	wxButton*** btn;

public:
	GameField(wxButton*** btn, int gameFieldWidth, int gameFieldHeight, int minesCount);
	~GameField();

	void checkButton(int i, int j);
	void flagButton(int i, int j);

private:
	void resetGame();
	void setupMines(int iClicked, int jClicked);
	int countNeighbourMines(int buttonI, int buttonJ);
	void countAllNeighbourMines();
	void resetButtonState(ButtonState& button);
	void openZeroes(int buttonI, int buttonJ);
	bool checkForVictory();
	void showMines();
};


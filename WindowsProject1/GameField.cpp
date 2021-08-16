#include "GameField.h"

GameField::GameField(wxButton*** btn, int gameFieldWidth, int gameFieldHeight, int minesCount)
{
	this->btn = btn;
	this->gameFieldWidth = gameFieldWidth;
	this->gameFieldHeight = gameFieldHeight;
	this->minesCount = minesCount;

	firstClick = true;

	btnState = new ButtonState* [gameFieldHeight];
	for (int i = 0; i < gameFieldHeight; i++) {
		btnState[i] = new ButtonState[gameFieldWidth];
	}
}

GameField::~GameField()
{
	for (int i = 0; i < gameFieldHeight; i++) {
		delete[] btnState[i];
	}
	delete[] btnState;
}

void GameField::resetGame()
{
	for (int i = 0; i < gameFieldWidth; i++) {
		for (int j = 0; j < gameFieldHeight; j++) {
			btn[i][j]->Enable();
			btn[i][j]->SetLabel(wxEmptyString);
			resetButtonState(btnState[i][j]);
		}
	}
	firstClick = true;
}

void GameField::setupMines(int iClicked, int jClicked)
{
	srand(time(0));
	int i, j;
	for (int n = minesCount; n != 0; ) {
		i = rand() % gameFieldHeight;
		j = rand() % gameFieldWidth;

		if ((i != iClicked || j != jClicked) && !btnState[i][j].hasMine) {
			btnState[i][j].hasMine = true;
			n--;
			//btn[i][j]->SetLabel("m");
		}
	}
	countAllNeighbourMines();

	
}

void GameField::checkButton(int i, int j)
{
	if (btnState[i][j].flagged)
		return;

	if (btnState[i][j].hasMine) {
		showMines();
		wxMessageBox("GAME OVER");
		resetGame();
		return;
	}

	if (firstClick) {
		setupMines(i, j);
		firstClick = false;
	}

	if (btnState[i][j].neighbourMines > 0) {
		btn[i][j]->SetLabel(std::to_string(btnState[i][j].neighbourMines));
	}
	
	if (btnState[i][j].neighbourMines == 0) {
		openZeroes(i, j);
	}

	btn[i][j]->Disable();
}

void GameField::flagButton(int i, int j)
{
	if (firstClick) {
		setupMines(i, j);
		firstClick = false;
	}

	static int currentFlagsCount = 0;

	if (!btnState[i][j].flagged) {
		currentFlagsCount++;
		btnState[i][j].flagged = true;
	}
	else {
		currentFlagsCount--;
		btnState[i][j].flagged = false;
	}
	btn[i][j]->SetLabel(btnState[i][j].flagged? "?":"");

	if (currentFlagsCount > flagsCount && checkForVictory()) {
		wxMessageBox("CONGRATULATIONS! YOU WIN!");
		resetGame();
		return;
	}
}

int GameField::countNeighbourMines(int buttonI, int buttonJ)
{
	int minesCount = 0;
	for (int i = std::max(0, buttonI - 1); i <= std::min(gameFieldHeight-1, buttonI + 1); i++) {
		for (int j = std::max(0, buttonJ - 1); j <= std::min(gameFieldWidth-1, buttonJ + 1); j++) {
			if (i != buttonI || j != buttonJ)
				minesCount += btnState[i][j].hasMine;
		}
	}
	return minesCount;
}

void GameField::openZeroes(int buttonI, int buttonJ)
{
	for (int i = std::max(0, buttonI - 1); i <= std::min(gameFieldHeight - 1, buttonI + 1); i++) {
		for (int j = std::max(0, buttonJ - 1); j <= std::min(gameFieldWidth - 1, buttonJ + 1); j++) {
			if ((i != buttonI || j != buttonJ) && btn[i][j]->IsEnabled()) {

				btn[i][j]->Disable();
				if (btnState[i][j].neighbourMines == 0)
					openZeroes(i, j);
				else
					btn[i][j]->SetLabel(std::to_string(btnState[i][j].neighbourMines));

			}
		}
	}
}

void GameField::countAllNeighbourMines()
{
	for (int i = 0; i < gameFieldHeight; i++) {
		for (int j = 0; j < gameFieldWidth; j++) {
			btnState[i][j].neighbourMines = countNeighbourMines(i, j);
		}
	}
}

void GameField::resetButtonState(ButtonState& button)
{
	button.hasMine = false;
	button.flagged = false;
	button.neighbourMines = 0;
}

bool GameField::checkForVictory() {
	for (int i = 0; i < gameFieldHeight; i++) {
		for (int j = 0; j < gameFieldWidth; j++) {
			if (btnState[i][j].hasMine && !btnState[i][j].flagged)
				return false;
		}
	}
	return true;
}

void GameField::showMines() {
	for (int i = 0; i < gameFieldHeight; i++) {
		for (int j = 0; j < gameFieldWidth; j++) {
			if (btnState[i][j].hasMine)
				btn[i][j]->SetLabel("M");
		}
	}
}

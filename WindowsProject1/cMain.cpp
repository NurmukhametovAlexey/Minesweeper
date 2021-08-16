#include "cMain.h"
#include <random>


cMain::cMain() : wxFrame(nullptr, wxID_ANY, "My first gui project!", wxPoint(100, 100), wxSize(800, 500))
{
	btn = new wxButton** [gameFieldHeight];
	for (int i = 0; i < gameFieldHeight; i++) {
		btn[i] = new wxButton * [gameFieldWidth];
	}

	wxGridSizer* grid = new wxGridSizer(gameFieldWidth, gameFieldHeight, 0, 0);

	wxFont font(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);

	for (int i = 0; i < gameFieldWidth; i++) {
		for (int j = 0; j < gameFieldHeight; j++) {
			btn[i][j] = new wxButton(this, i * gameFieldWidth + j);
			grid->Add(btn[i][j], 1, wxEXPAND | wxALL);

			btn[i][j]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnLeftButtonClicked, this);
			btn[i][j]->Bind(wxEVT_RIGHT_DOWN, wxMouseEventHandler(cMain::OnRightButtonClicked), this);

			btn[i][j]->SetFont(font);
		}
	}

	this->SetSizer(grid);
	grid->Layout();

	gameField = new GameField(btn, gameFieldWidth, gameFieldHeight, minesCount);
}

cMain::~cMain()
{
	for (int i = 0; i < gameFieldHeight; i++)
		delete btn[i];
	delete[] btn;
	delete gameField;
}


// Checks if the button has a mine inside 
void cMain::OnLeftButtonClicked(wxCommandEvent& evt)
{
	int i = evt.GetId() / gameFieldWidth;
	int j = evt.GetId() % gameFieldWidth;

	gameField->checkButton(i, j);
	evt.Skip();
}

// Flags the field
void cMain::OnRightButtonClicked(wxMouseEvent& evt)
{
	int i = evt.GetId() / gameFieldWidth;
	int j = evt.GetId() % gameFieldWidth;

	gameField->flagButton(i, j);

	evt.Skip();
}



#pragma once

#include "wx/wx.h"
#include "GameField.h"


class cMain : public wxFrame
{
public:
	cMain();
	~cMain();

public:
	int gameFieldWidth = 16;
	int gameFieldHeight = 16;
	int minesCount = 30;

	wxButton*** btn;

	GameField* gameField;

	
	void OnLeftButtonClicked(wxCommandEvent & evt);
	void OnRightButtonClicked(wxMouseEvent& evt);
};


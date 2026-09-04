#include"../../inc/ui/Interface.h"

FinalInterface::FinalInterface() :Interface(L"END"){}
FinalInterface::~FinalInterface(){}

void FinalInterface::OnEnter(){}
void FinalInterface::OnExit(){}
void FinalInterface::Update()
{
	Application* app = GetApplication();
	if (IsKeyDown(VK_ESCAPE))
	{
		GetApplication()->ChangeInterface(L"Main");
	}
	LOGFONT style;
	gettextstyle(&style);
	settextstyle(80, 0, L"Consolas");
	RECT rect0{ 0,0,1000,560 };
	if (gameMode == SINGLE_PLAYER)
	{
		if (!app->_Winner)
		{
			drawtext(L"Winner :Player!!", &rect0, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
		else if (app->_Winner)
		{
			drawtext(L"Winner :Ai!!", &rect0, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
	}
	else
	{
		if (!app->_Winner)
		{
			drawtext(L"Winner :Player1!!", &rect0, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
		else if (app->_Winner)
		{
			drawtext(L"Winner :Player2!!", &rect0, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
	}

	//restore text style
	settextstyle(&style);
}

void FinalInterface::Draw(){}
#include"../../inc/ui/interface.h"
#include"../../inc/Globals.h"


MainInterface::MainInterface() :Interface(L"Main")
{
	_pOnePlayerButton = new Button(Rect(350, 280, 100, 60), L"1 Player");
	_pOnePlayerButton->SetUpStyle(RED)->SetHoverStyle(YELLOW)->SetDownStyle(MAGENTA)->SetOnClick(_OnClickOnePlayerButton);

	_pTwoPlayerButton = new Button(Rect(550, 280, 100, 60), L"2 Player");
	_pTwoPlayerButton->SetUpStyle(RED)->SetHoverStyle(YELLOW)->SetDownStyle(MAGENTA)->SetOnClick(_OnClickTwoPlayerButton);

	_pExitButton = new Button(Rect(900, 460, 60, 60), L"Exit");
	_pExitButton->SetUpStyle(RED)->SetHoverStyle(YELLOW)->SetDownStyle(MAGENTA)->SetOnClick(_OnClickExitButton);
}
MainInterface::~MainInterface()
{
	if (_pOnePlayerButton)
	{
		delete _pOnePlayerButton;//先删空间
		_pOnePlayerButton = nullptr;//再指针置空
	}
	if (_pTwoPlayerButton)
	{
		delete _pTwoPlayerButton;//先删空间
		_pTwoPlayerButton = nullptr;//再指针置空
	}
	if (_pExitButton)
	{
		delete _pExitButton;//先删空间
		_pExitButton = nullptr;//再指针置空
	}
}


void MainInterface::Update() //override表示重写
{
	_pOnePlayerButton->Updata();
	_pTwoPlayerButton->Updata();
	_pExitButton->Updata();
}

void MainInterface::Draw()
{
	RECT rect1 = { 0,0,1000,280 };//写大标题
	RECT rect2 = { 0,280,1000,560 };//退出提示

	LOGFONT style1;
	gettextstyle(&style1);
	settextstyle(100, 0, L"Consolas");
	drawtext(L"Joke man!", &rect1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	settextstyle(&style1);

	LOGFONT style2;
	gettextstyle(&style2);
	settextstyle(25, 0, L"Consolas");
	drawtext(L"Press Q to exit the game", &rect2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	settextstyle(&style2);

	_pOnePlayerButton->Draw();
	_pTwoPlayerButton->Draw();
	_pExitButton->Draw();
}

void MainInterface::_OnClickOnePlayerButton() //点击后需要执行的函数
{
	gameMode = SINGLE_PLAYER;
	Application* app = GetApplication();
	app->ChangeInterface(L"Pick");
}
void MainInterface::_OnClickTwoPlayerButton()
{
	gameMode = DOUBLE_PLAYER;
	Application* app = GetApplication();
	app->ChangeInterface(L"Pick");
}
void MainInterface::_OnClickExitButton()
{
	isRunning = false;
}
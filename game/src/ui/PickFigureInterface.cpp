#include"../../inc/ui/Interface.h"
#include"../../inc/utils/Random.h"


PickFigureInterface::PickFigureInterface() :Interface(L"Pick")
{
	Application* app = GetApplication();
	
	_continue=new Button(Rect(425, 460, 150, 50), L"START!!");
	_continue->SetUpStyle(RED)->SetHoverStyle(YELLOW)->SetDownStyle(MAGENTA)->SetOnClick(_OnClickContinueButton);

	//Player1
	_p1AFigureButton = new Button(Rect(50, 100, 100, 100), L"A");
	_p1AFigureButton->SetUpStyle(RED)->SetHoverStyle(YELLOW)->SetDownStyle(MAGENTA)->SetOnClick(_OnClickA1FigureButton);
	 _p1BFigureButton = new Button(Rect(200, 100, 100, 100), L"B");
	_p1BFigureButton->SetUpStyle(RED)->SetHoverStyle(YELLOW)->SetDownStyle(MAGENTA)->SetOnClick(_OnClickB1FigureButton);
	_p1CFigureButton = new Button(Rect(50, 250, 100, 100), L"C");
	_p1CFigureButton->SetUpStyle(RED)->SetHoverStyle(YELLOW)->SetDownStyle(MAGENTA)->SetOnClick(_OnClickC1FigureButton);
	_p1DFigureButton = new Button(Rect(200, 250, 100, 100), L"D");
	_p1DFigureButton->SetUpStyle(RED)->SetHoverStyle(YELLOW)->SetDownStyle(MAGENTA)->SetOnClick(_OnClickD1FigureButton);
	//Player2
	_p2AFigureButton = new Button(Rect(700, 100, 100, 100), L"A");
	_p2AFigureButton->SetUpStyle(RED)->SetHoverStyle(YELLOW)->SetDownStyle(MAGENTA)->SetOnClick(_OnClickA2FigureButton);
	 _p2BFigureButton = new Button(Rect(850, 100, 100, 100), L"B");
	_p2BFigureButton->SetUpStyle(RED)->SetHoverStyle(YELLOW)->SetDownStyle(MAGENTA)->SetOnClick(_OnClickB2FigureButton);
	 _p2CFigureButton = new Button(Rect(700, 250, 100, 100), L"C");
	_p2CFigureButton->SetUpStyle(RED)->SetHoverStyle(YELLOW)->SetDownStyle(MAGENTA)->SetOnClick(_OnClickC2FigureButton);
	_p2DFigureButton = new Button(Rect(850,250, 100, 100), L"D");
	_p2DFigureButton->SetUpStyle(RED)->SetHoverStyle(YELLOW)->SetDownStyle(MAGENTA)->SetOnClick(_OnClickD2FigureButton);

}

PickFigureInterface::~PickFigureInterface() 
{
	Application* app = GetApplication();
	//Player1
	if (_p1AFigureButton)
	{
		delete _p1AFigureButton;//先删空间
		_p1AFigureButton = nullptr;//再指针置空
	}
	if (_p1BFigureButton)
	{
		delete _p1BFigureButton;//先删空间
		_p1BFigureButton = nullptr;//再指针置空
	}
	if (_p1CFigureButton)
	{
		delete _p1CFigureButton;//先删空间
		_p1CFigureButton = nullptr;//再指针置空
	}
	if (_p1DFigureButton)
	{
		delete _p1DFigureButton;//先删空间
		_p1DFigureButton = nullptr;//再指针置空
	}
	//Player2
	if (_p2AFigureButton)
	{
		delete _p2AFigureButton;//先删空间
		_p2AFigureButton = nullptr;//再指针置空
	}
	if (_p2BFigureButton)
	{
		delete _p2BFigureButton;//先删空间
		_p2BFigureButton = nullptr;//再指针置空
	}
	if (_p2CFigureButton)
	{
		delete _p2CFigureButton;//先删空间
		_p2CFigureButton = nullptr;//再指针置空
	}
	if (_p2DFigureButton)
	{
		delete _p2DFigureButton;//先删空间
		_p2DFigureButton = nullptr;//再指针置空
	}
	if (_continue)
	{
		delete _continue;
		_continue = nullptr;
	}
}

void PickFigureInterface::OnEnter()
{
	Application* app = GetApplication();

	//init Player1 and Player2
	app->_Player[0] = new Player;
	app->_Player[1] = new Player;
	app->ClearTeamMember(app->_Player[0]);
	app->ClearTeamMember(app->_Player[1]);
	for (int i = 0; i < 4; i++)
	{
		app->Figure1[i] = false;
	}
	for (int i = 0; i < 4; i++)
	{
		app->Figure2[i] = false;
	}
	app->PickDown = false;

	//init Button
	InitButtonStyle();
}
void PickFigureInterface::OnExit() {}

void PickFigureInterface::Update()
{
	Application* app = GetApplication();
	if (IsKeyDown(VK_ESCAPE))
	{
		GetApplication()->ChangeInterface(L"Main");
	}
	if (app->Figure1[0])
	{
		_p1AFigureButton->SetUpStyle(BLUE)->SetHoverStyle(BLUE)->SetDownStyle(BLUE);
	}
	if (app->Figure1[1])
	{
		_p1BFigureButton->SetUpStyle(BLUE)->SetHoverStyle(BLUE)->SetDownStyle(BLUE);
	}
	if (app->Figure1[2])
	{
		_p1CFigureButton->SetUpStyle(BLUE)->SetHoverStyle(BLUE)->SetDownStyle(BLUE);
	}
	if (app->Figure1[3])
	{
		_p1DFigureButton->SetUpStyle(BLUE)->SetHoverStyle(BLUE)->SetDownStyle(BLUE);
	}
	if (app->Figure2[0])
	{
		_p2AFigureButton->SetUpStyle(BLUE)->SetHoverStyle(BLUE)->SetDownStyle(BLUE);
	}
	if (app->Figure2[1])
	{
		_p2BFigureButton->SetUpStyle(BLUE)->SetHoverStyle(BLUE)->SetDownStyle(BLUE);
	}
	if (app->Figure2[2])
	{
		_p2CFigureButton->SetUpStyle(BLUE)->SetHoverStyle(BLUE)->SetDownStyle(BLUE);
	}
	if (app->Figure2[3])
	{
		_p2DFigureButton->SetUpStyle(BLUE)->SetHoverStyle(BLUE)->SetDownStyle(BLUE);
	}

	if (!app->MemberNoFull(app->_Player[0]) && !app->MemberNoFull(app->_Player[1]))
	{
		app->PickDown = true;
	}
	Draw();

	//Button Update
	_p1AFigureButton->Updata();
	_p1BFigureButton->Updata();
	_p1CFigureButton->Updata();
	_p1DFigureButton->Updata();
	_p2AFigureButton->Updata();
	_p2BFigureButton->Updata();
	_p2CFigureButton->Updata();
	_p2DFigureButton->Updata();


	//Button Draw
	_p1AFigureButton->Draw();
	_p1BFigureButton->Draw();
	_p1CFigureButton->Draw();
	_p1DFigureButton->Draw();
	_p2AFigureButton->Draw();
	_p2BFigureButton->Draw();
	_p2CFigureButton->Draw();
	_p2DFigureButton->Draw();

	if (app->PickDown)
	{
		_continue->Updata();
		_continue->Draw();
	}
}

void PickFigureInterface::Draw()
{
	//palyer name
	setlinecolor(LIGHTCYAN);
	line(0, 50, 100, 50);
	line(900, 50, 1000, 50);
	LOGFONT style;
	gettextstyle(&style);
	settextstyle(22, 0, L"Consolas");
	RECT rect0{ 0,0,100,50 };
	RECT rect1{ 900,0,1000,50 };
	RECT rect2{ 0,750,1000,50 };
	if (gameMode == SINGLE_PLAYER)
	{
		drawtext(L"Player", &rect0, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		drawtext(L"Ai", &rect1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	else if (gameMode == DOUBLE_PLAYER)
	{
		drawtext(L"Player1", &rect0, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		drawtext(L"Player2", &rect1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	drawtext(L"Press Esc to back last interface", &rect2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	RECT rect3{ 0,400,1000,50 };
	settextstyle(100, 0, L"Consolas");
	drawtext(L"VS", &rect3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	//restore text style
	settextstyle(&style);
}

void PickFigureInterface::InitButtonStyle()
{
	_p1AFigureButton->SetUpStyle(RED)->SetHoverStyle(YELLOW)->SetDownStyle(MAGENTA);
	_p1BFigureButton->SetUpStyle(RED)->SetHoverStyle(YELLOW)->SetDownStyle(MAGENTA);
	_p1CFigureButton->SetUpStyle(RED)->SetHoverStyle(YELLOW)->SetDownStyle(MAGENTA);
	_p1DFigureButton->SetUpStyle(RED)->SetHoverStyle(YELLOW)->SetDownStyle(MAGENTA);

	_p2AFigureButton->SetUpStyle(RED)->SetHoverStyle(YELLOW)->SetDownStyle(MAGENTA);
	_p2BFigureButton->SetUpStyle(RED)->SetHoverStyle(YELLOW)->SetDownStyle(MAGENTA);
	_p2CFigureButton->SetUpStyle(RED)->SetHoverStyle(YELLOW)->SetDownStyle(MAGENTA);
	_p2DFigureButton->SetUpStyle(RED)->SetHoverStyle(YELLOW)->SetDownStyle(MAGENTA);
}

void PickFigureInterface::_OnClickA1FigureButton()//点击后需要执行的函数
{
	Application* app = GetApplication();
	if (app->MemberNoFull(app->_Player[0]))
	{
		app->SetPlayer1TeamMember(new S0(L"name1"));
		app->Figure1[0] = true;
	}
}
void PickFigureInterface::_OnClickB1FigureButton()
{
	Application* app = GetApplication();
	if (app->MemberNoFull(app->_Player[0]))
	{
		app->SetPlayer1TeamMember(new S1(L"name2"));
		app->Figure1[1] = true;
	}
}
void PickFigureInterface::_OnClickC1FigureButton()
{
	Application* app = GetApplication();
	if (app->MemberNoFull(app->_Player[0]))
	{
		app->SetPlayer1TeamMember(new S2(L"name3"));
		app->Figure1[2] = true;
	}
}
void PickFigureInterface::_OnClickD1FigureButton()
{
	Application* app = GetApplication();
	if (app->MemberNoFull(app->_Player[0]))
	{
		app->SetPlayer1TeamMember(new S3(L"name4"));
		app->Figure1[3] = true;
	}
}

void PickFigureInterface::_OnClickA2FigureButton()//点击后需要执行的函数
{
	Application* app = GetApplication();
	if (app->MemberNoFull(app->_Player[1]))
	{
		app->SetPlayer2TeamMember(new S0(L"name1"));
		app->Figure2[0] = true;
	}
}
void PickFigureInterface::_OnClickB2FigureButton()
{
	Application* app = GetApplication();
	if (app->MemberNoFull(app->_Player[1]))
	{
		app->SetPlayer2TeamMember(new S1(L"name2"));
		app->Figure2[1] = true;
	}
}
void PickFigureInterface::_OnClickC2FigureButton()
{
	Application* app = GetApplication();
	if (app->MemberNoFull(app->_Player[1]))
	{
		app->SetPlayer2TeamMember(new S2(L"name3"));
		app->Figure2[2] = true;
	}
}
void PickFigureInterface::_OnClickD2FigureButton()
{
	Application* app = GetApplication();
	if (app->MemberNoFull(app->_Player[1]))
	{
		app->SetPlayer2TeamMember(new S3(L"name4"));
		app->Figure2[3] = true;
	}
}

void PickFigureInterface::_OnClickContinueButton()
{
	Application* app = GetApplication();
	app->ChangeInterface(L"Game");
}


#pragma once

#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#include<cstdio>
#include<string>
#include"../Defines.h"
#include"../Globals.h"
#include"../../inc/message.h"
#include"../../inc/ui/Button.h"
#include"../game/Team.h"
#include"../../inc/game/Figure.h"

class Interface
{
private:
	std::wstring _name;

public:
	Interface(const std::wstring& name) :_name(name) {}
	virtual ~Interface() {}

	const std::wstring& Name() const { return _name; }

	virtual void OnEnter() {}//函数体为空，后续要重写
	virtual void OnExit() {}

	virtual void Update() {}
	virtual void Draw() {}

};

class MainInterface final:public Interface
{
private:
	Button* _pOnePlayerButton;//用指针记得Delete
	Button* _pTwoPlayerButton;
	Button* _pExitButton;

public:
	MainInterface();
	~MainInterface() override;
	void Update() override;//override表示重写
	void Draw() override;

private:
	static void _OnClickOnePlayerButton();//点击后需要执行的函数
	static void _OnClickTwoPlayerButton();
	static void _OnClickExitButton();
};

class PickFigureInterface final:public Interface
{
private:

	Button* _p1AFigureButton;
	Button* _p1BFigureButton;
	Button* _p1CFigureButton;
	Button* _p1DFigureButton;

	Button* _p2AFigureButton;
	Button* _p2BFigureButton;
	Button* _p2CFigureButton;
	Button* _p2DFigureButton;

	Button* _continue;

public:
	PickFigureInterface();
	~PickFigureInterface() override;

	virtual void OnEnter() override;
	virtual void OnExit() override;

	void Update() override;
	void Draw() override;

	void InitButtonStyle();

private:
	static	void _OnClickA1FigureButton();//点击后需要执行的函数
	static	void _OnClickB1FigureButton();
	static	void _OnClickC1FigureButton();
	static	void _OnClickD1FigureButton();

	static	void _OnClickA2FigureButton();//点击后需要执行的函数
	static	void _OnClickB2FigureButton();
	static	void _OnClickC2FigureButton();
	static	void _OnClickD2FigureButton();

	static	void _OnClickContinueButton();
};

class GameInterface final :public Interface
{
private:
	Button* _pPlayerAttackButton;//用指针记得Delete
	Button* _pPlayerSkillButton;

	Button* _pSelectButton1;
	Button* _pSelectButton2;

public:
	GameInterface();
	~GameInterface() override;

	void OnEnter() override;
	void OnExit() override;

	void Update() override;//override表示重写
	void Draw() override;

	void IfHaveSkill();
	void ShowHPAndName();

	void SinglePlayerUpdate();
	void DoublePlayerUpdate();
	void JudgeWinner();
	void pJudgeMemberDown();
private:
	static void _OnClickAttackButton();//点击后需要执行的函数
	static void _OnClickSkillButton();
	static void _OnClickSelectButton1();
	static void _OnClickSelectButton2();
};

class FinalInterface final:public Interface
{
private:

public:
	FinalInterface();
	~FinalInterface();

	void OnEnter() override;
	void OnExit() override;

	void Update() override;//override表示重写
	void Draw() override;
};
#endif

//class ShowTextInterface final :public Interface
//{
//public:
//	ShowTextInterface();
//	~ShowTextInterface();
//
//};
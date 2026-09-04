#pragma once

#ifndef _BUTTON_H_
#define _BUTTON_H_

#include<string>
#include"../Defines.h"

enum ButtonState
{
	BUTTON_UP = 0,
	BUTTON_HOVER,
	BUTTON_DOWN,
	BUTTON_STATE_NUM
};

class  Button
{
private:
	Rect _range;
	ButtonState _state;
	COLORREF _color[BUTTON_STATE_NUM];//按钮每个状态下的颜色
	std::wstring _text;//因为项目的字符集为Unicode，所以字符串输出要用宽字符，（wchar*和std：：wastring）

	//点击事件
	void (*_onClick)(void);//函数指针

public:
	Button(const Rect& range, const std::wstring& text);
	Button* SetUpStyle(COLORREF color);
	Button* SetHoverStyle(COLORREF color);
	Button* SetDownStyle(COLORREF color);
	Button* SetTextStyle(const std::wstring& text);
	Button* SetOnClick(void(*onClick)(void));
	Button* SetName(const std::wstring& name);

	virtual void Updata();//虚函数方便继承派生多个按钮（为了扩展性）
	virtual void Draw();
	void SetRange(Rect range);
};

#endif
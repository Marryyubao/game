#include"../../inc/ui/Button.h"
#include"../../inc/message.h"
#include"../../inc/ui/Application.h"


Button::Button(const Rect& range, const std::wstring& text) :_range(range), _text(text), _onClick(nullptr)
{
	for (int i = 0; i < BUTTON_STATE_NUM; i++)
	{
		_color[i] = RED;
	}
}

Button* Button::SetUpStyle(COLORREF color)
{
	_color[BUTTON_UP] = color;
	return this;
}

Button* Button::SetHoverStyle(COLORREF color)
{
	_color[BUTTON_HOVER] = color;
	return this;
}

Button* Button::Button::SetDownStyle(COLORREF color)
{
	_color[BUTTON_DOWN] = color;
	return this;
}

Button* Button::SetTextStyle(const std::wstring& text)
{
	_text = text;
	return this;
}

Button* Button::SetOnClick(void (*onClick)(void))
{
	_onClick = onClick;
	return this;
}

Button* Button::SetName(const std::wstring& name)
{
	_text = name;
	return this;
}

void Button::Updata()
{
	MouseMessage* msg = GetMouseMessage();
	if (_range.Contains(msg->position))
	{
		if (msg->IsDown)
		{
			_state = BUTTON_DOWN;
		}
		else if (msg->IsUp)
		{
			if (_state == BUTTON_DOWN && _onClick)
			{
				_onClick();//点击后要执行的函数
			}
			_state = BUTTON_UP;
		}
		else
		{
			if (_state != BUTTON_DOWN)
			{
				_state = BUTTON_HOVER;
			}
		}
	}
	else
	{
		_state = BUTTON_UP;
	}
}
void Button::Draw()
{
	setlinestyle(PS_SOLID, 3);
	setlinecolor(_color[_state]);

	RECT rect = _range.ToEasyXRect();
	//画边框
	rectangle(rect.left, rect.top, rect.right, rect.bottom);
	//画文本
	drawtext(_text.c_str(), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);//format为中心+水平垂直居中+单行


}
void Button::SetRange(Rect range)
{
	_range = range;
}



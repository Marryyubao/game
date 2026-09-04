#include"../../inc/ui/Application.h"

Application::Application() :_currentInterface(nullptr), _nextInterface(nullptr) 
{
	for (int i = 0; i < 4; i++)
	{
		_ShowActionText[i] = 0;
	}
}
Application::~Application()
{
	for (const auto it : _interfaces)
	{
		delete it.second;
	}
}

Application* Application::RegisterInterface(Interface* intf)
{
	_interfaces.emplace(intf->Name(), intf);
	if (!_currentInterface)
	{
		_currentInterface = intf;
	}
	return this;
}

//直接设置目标界面
void  Application::SetInterface(const std::wstring& name)
{
	auto it = _interfaces.find(name);
	if (it == _interfaces.end())
	{
		return;
	}
	_currentInterface = it->second;
	_nextInterface = nullptr;
}

//在更新后再设置目标界面
void Application::ChangeInterface(const std::wstring& name)
{
	auto it = _interfaces.find(name);
	if (it == _interfaces.end())
	{
		return;
	}
	_nextInterface = it->second;
}

void Application::Update()
{
	if (_currentInterface)
	{
		_currentInterface->Update();
	}

	if (_nextInterface && _nextInterface != _currentInterface)
	{
		_currentInterface->OnExit();
		_nextInterface->OnEnter();
		_currentInterface = _nextInterface;
		_nextInterface = nullptr;
	}
}
void Application::Draw()
{
	if (_currentInterface)
	{
		_currentInterface->Draw();
	}
}

void Application::ClearTeamMember(Player* player)
{
	player->_TeamMemberOne = nullptr;
	player->_TeamMemberTwo = nullptr;
	
}

void Application::SetPlayer1TeamMember(Stats* p)
{
	if (p == nullptr)
	{
		return;
	}
	else
	{
		if (_Player[0]->_TeamMemberOne == nullptr)
		{
			_Player[0]->_TeamMemberOne = p;
		}
		else
		{
			_Player[0]->_TeamMemberTwo = p;
		}
	}
}

void Application::SetPlayer2TeamMember(Stats* p)
{
	if (p == nullptr)
	{
		return;
	}
	else
	{
		if (_Player[1]->_TeamMemberOne == nullptr)
		{
			_Player[1]->_TeamMemberOne = p;
		}
		else
		{
			_Player[1]->_TeamMemberTwo = p;
		}
	}
}

bool Application::MemberNoFull(Player* player)
{
	if (player->_TeamMemberOne == nullptr || player-> _TeamMemberTwo == nullptr)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Application::RenewActionText(int posi)
{
	for (int i = 0; i < 4; i++)
	{
		if (i == posi) _ShowActionText[i] = 1;
		else _ShowActionText[i] = 0;
	}
}

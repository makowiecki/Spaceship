#include "pch.h"
#include "InputManager.h"

std::multimap<InputManager::ActionName, std::function<void(float)>> InputManager::mActionNamesFunctions{};

InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}

void InputManager::processKeyboardState(const DirectX::Keyboard::State & keyboardState, float deltaTime)
{
	if(keyboardState.A || keyboardState.Left)
	{
		if(mActionNamesFunctions.find(ActionName::LEFT) != mActionNamesFunctions.end())
		{
			auto range = mActionNamesFunctions.equal_range(ActionName::LEFT);			
			for(auto it = range.first; it != range.second; ++it)
			{
				it->second(deltaTime);
			}
		}
	}
	else if(keyboardState.D || keyboardState.Right)
	{
		if(mActionNamesFunctions.find(ActionName::RIGHT) != mActionNamesFunctions.end())
		{
			auto range = mActionNamesFunctions.equal_range(ActionName::RIGHT);
			for(auto it = range.first; it != range.second; ++it)
			{
				it->second(deltaTime);
			}
		}
	}

	if(keyboardState.Space)
	{
		if(mActionNamesFunctions.find(ActionName::SHOOT) != mActionNamesFunctions.end())
		{
			auto range = mActionNamesFunctions.equal_range(ActionName::SHOOT);
			for(auto it = range.first; it != range.second; ++it)
			{
				it->second(deltaTime);
			}
		}
	}
}

void InputManager::bindAction(ActionName actionName, const std::function<void(float)>& function)
{
	mActionNamesFunctions.insert(std::make_pair(actionName, function));
}

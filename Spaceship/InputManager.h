#pragma once

#include <map>

class InputManager
{
public:
	InputManager();
	~InputManager();

	enum class ActionName{ LEFT, RIGHT, SHOOT };

	static void ProcessKeyboardState(const DirectX::Keyboard::State& keyboardState, float deltaTime);

	static void BindAction(ActionName actionName, const std::function<void(float)>& function);

private:

	static std::multimap<ActionName, std::function<void(float)>> mActionNamesFunctions;
};


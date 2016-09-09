#pragma once

#include <map>

class InputManager
{
public:
	InputManager();
	~InputManager();

	enum class ActionName{ LEFT, RIGHT, SHOOT };

	static void processKeyboardState(const DirectX::Keyboard::State& keyboardState, float deltaTime);

	static void bindAction(ActionName actionName, const std::function<void(float)>& function);

private:

	static std::multimap<ActionName, std::function<void(float)>> mActionNamesFunctions;
};


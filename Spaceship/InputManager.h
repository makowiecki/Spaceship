#pragma once

#include <map>

class InputManager
{
public:
	InputManager();
	~InputManager();

	enum class ActionName{ LEFT, RIGHT, SHOOT };

	/** Must be called in update to properly respond to pressed keys and to call every assigned function */
	static void ProcessKeyboardState(const DirectX::Keyboard::State& keyboardState, float deltaTime);

	/** Binds function to action name (function will be called when key assigned to actionname will be pressed) */
	static void BindAction(ActionName actionName, const std::function<void(float)>& function);

private:

	static std::multimap<ActionName, std::function<void(float)>> mActionNamesFunctions; // holds all functions assigned to ActionName (allows many function to one action name)
};


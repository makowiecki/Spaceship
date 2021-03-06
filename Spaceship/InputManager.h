#pragma once

#include <map>

/** Manages input from keyboard and handles responding to it. */
class InputManager
{
public:
	InputManager() = delete;
	InputManager(const InputManager&) = delete;
	~InputManager() = delete;
	InputManager& operator=(const InputManager&) = delete;

	enum class ActionName { LEFT, RIGHT, SHOOT };

	/** Must be called in update to properly respond to pressed keys and to call every assigned function */
	static void ProcessKeyboardState(const DirectX::Keyboard::State& keyboardState, float deltaTime);

	/** Binds function to action name (function will be called when key assigned to actionname will be pressed) */
	static void BindAction(ActionName actionName, const std::function<void(float)>& function);

private:

	static std::multimap<ActionName, std::function<void(float)>> mActionNamesFunctions; // holds all functions assigned to ActionName (allows many function to one action name)
};


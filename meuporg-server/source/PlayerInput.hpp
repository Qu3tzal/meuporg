#ifndef PLAYERINPUT_HPP_INCLUDED
#define PLAYERINPUT_HPP_INCLUDED

/*
	PlayerInput structure.
*/
struct PlayerInput
{
    bool isMoveUpKeyPressed;
    bool isMoveDownKeyPressed;
    bool isMoveLeftKeyPressed;
    bool isMoveRightKeyPressed;

    float mouseX;
    float mouseY;

    bool isEAttackKeyPressed;
    bool isAAttackKeyPressed;

    bool isMouseLeftButtonPressed;
    bool isMouseRightButtonPressed;
};

#endif // PLAYERINPUT_HPP_INCLUDED

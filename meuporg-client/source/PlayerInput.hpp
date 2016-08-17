#ifndef PLAYERINPUT_HPP_INCLUDED
#define PLAYERINPUT_HPP_INCLUDED

struct PlayerInput
{
    bool MoveUp;
    bool MoveDown;
    bool MoveLeft;
    bool MoveRight;

    bool aAttack;
    bool eAttack;

    bool leftClickPressed;
    bool rightClickPressed;

    float MouseX;
    float MouseY;
};
#endif // PLAYERINPUT_HPP_INCLUDED

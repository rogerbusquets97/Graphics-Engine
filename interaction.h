#ifndef INTERACTION_H
#define INTERACTION_H

#include "input.h"
#include "camera.h"

class Interaction
{
public:
    Interaction();
    bool Update();

private:
    bool Idle();
    bool Navigate();
    bool Focus();
    bool Transalte();
    bool Rotate();
    bool Scale();

    enum State {Idling, Navigating, Focusing, Transalting, Rotating, Scaling};
    State state = State::Idling;

public:
    Input* input;
    Camera* camera;
};

#endif // INTERACTION_H

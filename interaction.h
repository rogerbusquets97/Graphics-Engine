#ifndef INTERACTION_H
#define INTERACTION_H

#include "input.h"
#include "camera.h"

class Interaction
{
public:
    Interaction();
    bool Update();

    void ZoomInOut(int x);

private:
    bool Idle();
    bool Navigate();
    bool Focus();
    bool Transalte();
    bool Rotate();
    bool Scale();
    bool Zoom();

    enum State {Idling, Navigating, Focusing, Transalting, Rotating, Scaling, Zooming};
    State state = State::Idling;


    bool cameraChanged;

public:
    Input* input;
    Camera* camera;
};

#endif // INTERACTION_H

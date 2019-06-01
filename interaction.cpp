#include "interaction.h"
#include <QtMath>
#include <iostream>

Interaction::Interaction()
{

}

bool Interaction::Update()
{
    bool changed = false;

    switch(state)
    {
        case State::Idling:
        changed = Idle();
        break;
        case State::Navigating:
        changed = Navigate();
        break;
        case State::Focusing:
        changed = Focus();
        break;
        case State::Transalting:
        changed = Transalte();
        break;
        case State::Rotating:
        changed = Rotate();
        break;
        case State::Scaling:
        changed = Scale();
        break;
    }

    return changed;
}

bool Interaction::Idle()
{
    if(input->mouseButtons[Qt::RightButton]==MouseButtonState::Pressed)
    {
        state = State::Navigating;
        std::cout<<"GO to navigate" << std::endl;
    }

    else if(input->mouseButtons[Qt::LeftButton]==MouseButtonState::Pressed)
    {
        //Selection
    }

    // else if(selection->count() > 0)
   //{
   //    transalte/rotate/scale
    //}


    return false;
}

bool Interaction::Navigate()
{
    if(input->mouseButtons[Qt::RightButton] != MouseButtonState::Pressed)
    {
        state = State::Idling;
        return false;
    }

    bool cameraChanged = false;

    int mousex_delta = input->mousex - input->mousex_prev;
    int mousey_delta = input->mousey - input->mousey_prev;

    float &yaw = camera->yaw;
    float &pitch = camera->pitch;

    if(mousex_delta > 2 || mousey_delta > 2 || mousex_delta < -2 ||  mousey_delta < -2)
    {
        cameraChanged = true;
        yaw -= 0.3f * mousex_delta;
        pitch -= 0.3f * mousey_delta;

        while(yaw < 0.0f) yaw += 360.0f;
        while(yaw > 360.0f) yaw -= 360.0f;
        if(pitch > 89.0f) pitch = 89.0f;
        if(pitch < -89.0f) pitch = -89.0f;
    }

    QVector3D displacementVector;

    if(input->keys[Qt::Key_W] == KeyState::Pressed)
    {
        std::cout<< "Move forward"<< std::endl;
        //Forward
        cameraChanged = true;
        displacementVector += QVector3D(-sinf(qDegreesToRadians(yaw)) * cosf(qDegreesToRadians(pitch)),
                                        sinf(qDegreesToRadians(pitch)),
                                        -cosf(qDegreesToRadians(yaw)) * cosf(qDegreesToRadians(pitch)));
    }

    if(input->keys[Qt::Key_A] == KeyState::Pressed)
    {
        //Left
    }

    if(input->keys[Qt::Key_S] == KeyState::Pressed)
    {
        //Backwards
        std::cout<< "Move forward"<< std::endl;
        //Forward
        cameraChanged = true;
        displacementVector += QVector3D(sinf(qDegreesToRadians(yaw)) * cosf(qDegreesToRadians(pitch)),
                                        -sinf(qDegreesToRadians(pitch)),
                                        cosf(qDegreesToRadians(yaw)) * cosf(qDegreesToRadians(pitch)));
    }

    if(input->keys[Qt::Key_D] == KeyState::Pressed)
    {
        //Right
    }

    displacementVector *= camera->speed/60.0f;

    camera->position += displacementVector;

    return cameraChanged;
}

bool Interaction::Focus()
{
    return false;
}

bool Interaction::Transalte()
{
    return false;
}

bool Interaction::Rotate()
{
    return false;
}

bool Interaction::Scale()
{
    return false;
}

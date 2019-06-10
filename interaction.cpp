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
        case State::Zooming:
        changed = Zoom();
        break;
    }

    return changed;
}

bool Interaction::Idle()
{
    if(input->mouseButtons[Qt::RightButton]==MouseButtonState::Pressed && input->zooming_state == Zooming::Unknown_Zoom)
    {
        state = State::Navigating;
    }

   else if (input->zooming_state != Zooming::Unknown_Zoom)
   {
            state = State::Zooming;
   }

    return false;
}

bool Interaction::Navigate()
{
    if(input->mouseButtons[Qt::RightButton] != MouseButtonState::Pressed)
    {
        state = State::Idling;
        cameraChanged = false;
        return false;
    }



    int mousex_delta = input->mousex - input->mousex_prev;
    int mousey_delta = input->mousey - input->mousey_prev;

    float &yaw = camera->yaw;
    float &pitch = camera->pitch;

    if(mousex_delta > 2 || mousey_delta > 2 || mousex_delta < -2 ||  mousey_delta < -2)
    {
        cameraChanged = true;
        yaw -= 0.1f * mousex_delta;
        pitch -= 0.1f * mousey_delta;

        while(yaw < 0.0f) yaw += 360.0f;
        while(yaw > 360.0f) yaw -= 360.0f;
        if(pitch > 89.0f) pitch = 89.0f;
        if(pitch < -89.0f) pitch = -89.0f;
    }

    QVector3D forwardVec = camera->eyePosition - camera->position;
    forwardVec.normalize();
    if(input->keys[Qt::Key_W] == KeyState::Pressed)
    {
        //Forward
        cameraChanged = true;
        camera->position += forwardVec * camera->speed/60.0;
    }

    if(input->keys[Qt::Key_A] == KeyState::Pressed)
    {
        //Left
        cameraChanged = true;
        QVector3D leftVec = QVector3D::crossProduct(camera->up, forwardVec);
        camera->position += leftVec * camera->speed/60.0;

    }

    if(input->keys[Qt::Key_S] == KeyState::Pressed)
    {
        cameraChanged = true;
        camera->position -= forwardVec * camera->speed/60.0;
    }

    if(input->keys[Qt::Key_D] == KeyState::Pressed)
    {
        cameraChanged = true;
        QVector3D rightVec = QVector3D::crossProduct(forwardVec, camera->up);
        camera->position += rightVec*camera->speed/60.0;
    }

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

bool Interaction::Zoom()
{

    if (input->zooming_state == Zooming::Unknown_Zoom)
    {
        state = State::Idling;
        return false;

    }
    QVector3D displacementVector;

    int mousex_delta = input->mousex - input->mousex_prev;
    int mousey_delta = input->mousey - input->mousey_prev;

    float &yaw = camera->yaw;
    float &pitch = camera->pitch;

    if(mousex_delta > 2 || mousey_delta > 2 || mousex_delta < -2 ||  mousey_delta < -2)
    {
        yaw -= 0.3f * mousex_delta;
        pitch -= 0.3f * mousey_delta;

        while(yaw < 0.0f) yaw += 360.0f;
        while(yaw > 360.0f) yaw -= 360.0f;
        if(pitch > 89.0f) pitch = 89.0f;
        if(pitch < -89.0f) pitch = -89.0f;
    }

    if (input->zooming_state == Zooming::In)
    {

        displacementVector += (QVector3D(-sinf(qDegreesToRadians(yaw)) * cosf(qDegreesToRadians(pitch)),
                                        sinf(qDegreesToRadians(pitch)),
                                        -cosf(qDegreesToRadians(yaw)) * cosf(qDegreesToRadians(pitch))) * 8 ) ;
    }
    else if (input->zooming_state == Zooming::Out)
    {
        displacementVector += (QVector3D(sinf(qDegreesToRadians(yaw)) * cosf(qDegreesToRadians(pitch)),
                                        -sinf(qDegreesToRadians(pitch)),
                                        cosf(qDegreesToRadians(yaw)) * cosf(qDegreesToRadians(pitch))) * 8 ) ;
    }

    cameraChanged = true;

    camera->position += displacementVector;

    input->zooming_state = Zooming::Unknown_Zoom;

    return cameraChanged;
}

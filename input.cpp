#include "input.h"
#include <iostream>
Input::Input()
{

}
Input::~Input()
{

}

void Input::keyPressedEvent(QKeyEvent *event)
{
    keys[event->key()] = KeyState::Pressed;
}

void Input::keyReleasedEvent(QKeyEvent *event)
{
    keys[event->key()] = KeyState::Up;
}

void Input::mousePressedEvent(QMouseEvent *event)
{
    mouseButtons[event->button()] = MouseButtonState::Pressed;
}

void Input::mouseReleaseEvent(QMouseEvent *event)
{
     mouseButtons[event->button()] = MouseButtonState::Up;
}

void Input::mouseMoveEvent(QMouseEvent *event)
{
    mousex_prev = mousex;
    mousey_prev = mousey;

    mousex = event->x();
    mousey = event->y();
}

void Input::postUpdate()
{

}


#include "input.h"
#include "QPoint"
#include "mainwindow.h"

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
void Input::mouseWheelEvent(QWheelEvent* event)
{

  if(event->angleDelta().y()>0)
      zooming_state = Zooming::In;
  else if (event->angleDelta().y()<0)
      zooming_state = Zooming::Out;
  else
      zooming_state = Zooming::Unknown_Zoom;

  std::cout<< event->angleDelta().y()<< std::endl;
  std::cout<< (int)zooming_state << std::endl;
}
void Input::postUpdate()
{

}


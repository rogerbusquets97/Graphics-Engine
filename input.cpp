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
    std::cout<< "Key pressed" << std::endl;

}

void Input::keyReleasedEvent(QKeyEvent *event)
{
    std::cout<< "Key released" << std::endl;
}

void Input::mousePressedEvent(QMouseEvent *event)
{
    std::cout<< "mouse pressed" << std::endl;
}

void Input::mouseReleaseEvent(QMouseEvent *event)
{
    std::cout<< "mouse released" << std::endl;
}

void Input::mouseMoveEvent(QMouseEvent *event)
{
    std::cout<< "Mouse move" << std::endl;
}



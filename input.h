#ifndef INPUT_H
#define INPUT_H

#include <QKeyEvent>
#include <QWheelEvent>

enum class KeyState {Up, Pressed, Down};
enum class MouseButtonState {Up, Pressed, Down};
enum class Zooming {Unknown_Zoom = 0, In, Out };

class Interaction;

class Input
{
public:
    Input();
    ~Input();

    void keyPressedEvent(QKeyEvent* event);
    void keyReleasedEvent(QKeyEvent* event);
    void mousePressedEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseWheelEvent(QWheelEvent* event);

    void postUpdate();

    enum {
        MAX_BUTTONS = 10,
        MAX_KEYS = 300
    };

    Zooming zooming_state = Zooming::Unknown_Zoom;
    KeyState keys[MAX_KEYS];
    MouseButtonState mouseButtons[MAX_BUTTONS];

    int mousex = 0;
    int mousey = 0;
    int mousex_prev = 0;
    int mousey_prev = 0;
};

#endif // INPUT_H

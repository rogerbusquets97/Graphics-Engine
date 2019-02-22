#ifndef GAMEOBJECTWIDGET_H
#define GAMEOBJECTWIDGET_H

#include <QWidget>
#include "gameobject.h"

class GameObjectWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GameObjectWidget(QWidget *parent = nullptr, GameObject* obj);

private:
    GameObject* object;
signals:

public slots:
};

#endif // GAMEOBJECTWIDGET_H

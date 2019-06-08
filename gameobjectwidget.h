#ifndef GAMEOBJECTWIDGET_H
#define GAMEOBJECTWIDGET_H

#include <QWidget>
#include <QLabel>
#include "gameobject.h"

class GameObjectWidget : public QWidget
{
    Q_OBJECT
public:
    GameObjectWidget(QWidget *parent = nullptr, GameObject* obj = nullptr);
    inline GameObject* GetObject()const {return object;}
    inline QLabel* GetLabel()const {return label;}

private:
    GameObject* object;
    QLabel* label;
signals:

public slots:
};

#endif // GAMEOBJECTWIDGET_H

#ifndef INSPECTOR_H
#define INSPECTOR_H

#include "component.h"

#include <QWidget>

class Inspector : public QWidget
{
    Q_OBJECT
public:
    explicit Inspector(QWidget *parent = nullptr);
    std::list<Component*>* components;
    //Component Widgets

    inline void SetComponentList(std::list<Component*>* components){this->components = components;}

signals:

public slots:
};

#endif // INSPECTOR_H

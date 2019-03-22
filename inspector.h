#ifndef INSPECTOR_H
#define INSPECTOR_H

#include <QWidget>
#include "component.h"

class Inspector : public QWidget
{
    Q_OBJECT
public:
    explicit Inspector(QWidget *parent = nullptr);
    std::list<Component*>* components;
    //Component Widgets

    void SetComponentList(std::list<Component*>* components);

private:
    void UpdateContent();
signals:

public slots:

};

#endif // INSPECTOR_H

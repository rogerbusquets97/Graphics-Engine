#ifndef HIERARCHYWIDGET_H
#define HIERARCHYWIDGET_H

#include <QDockWidget>
#include <QLabel>
#include <list>
#include "gameobject.h"

class HierarchyWidget : public QDockWidget
{
    Q_OBJECT
public:
    explicit HierarchyWidget(QDockWidget *parent = nullptr);
private:

    GameObject* selected;
    std::list<QLabel> objects;


signals:

public slots:
    void OnAddGameObject(GameObject* obj);
    void OnDeleteGameObject(GameObject* obj);

};

#endif // HIERARCHYWIDGET_H

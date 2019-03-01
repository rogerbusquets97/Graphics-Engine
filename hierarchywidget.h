#ifndef HIERARCHYWIDGET_H
#define HIERARCHYWIDGET_H

#include <QWidget>
#include <QLabel>
#include <list>
#include "gameobject.h"

namespace Ui
{
   class HierarchyWidget;
}
class HierarchyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit HierarchyWidget(QWidget *parent = nullptr);
private:

    GameObject* selected;
    std::list<QLabel> objects;
    Ui::Inspector *ui;


signals:

public slots:
    void OnAddGameObject(GameObject* obj);
    void OnDeleteGameObject(GameObject* obj);

};

#endif // HIERARCHYWIDGET_H

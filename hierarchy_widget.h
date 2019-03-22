#ifndef HIERARCHY_WIDGET_H
#define HIERARCHY_WIDGET_H

#include <QWidget>
#include "gameobject.h"
#include <list>
#include <QLabel>
#include <QListWidget>

namespace Ui {
class Hierarchy_Widget;
}

class Hierarchy_Widget : public QWidget
{
    Q_OBJECT

public:
    void AddGameObject(GameObject* go);
    explicit Hierarchy_Widget(QWidget *parent = 0);
    ~Hierarchy_Widget();
    void ClearHierarchy();
private:
    Ui::Hierarchy_Widget *ui;
    GameObject* selected;
    QListWidget* list;

public slots:
    void OnAddGameObject();

    void OnDeleteGameObject();
    void OnObjectSelected(QListWidgetItem* obj);
};

#endif // HIERARCHY_WIDGET_H

#ifndef INSPECTOR_H
#define INSPECTOR_H

#include "component.h"

#include <QWidget>
#include "gameobject.h"
#include "componentshapewidget.h"

class Inspector : public QWidget
{
    Q_OBJECT
public:
    explicit Inspector(QWidget *parent = nullptr);
    GameObject* GetObject()const;
    void SetObject(GameObject* obj);

private:
    void UpdateContent();
    GameObject* selected;
    ComponentShapeWidget* shappowidgetto;
signals:

public slots:

};

#endif // INSPECTOR_H

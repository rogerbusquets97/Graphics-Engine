#ifndef INSPECTOR_H
#define INSPECTOR_H

#include "component.h"

#include <QWidget>
#include "gameobject.h"
#include "QComboBox"
#include "QPushButton"

class ShapeComponentWidget;
class TransformComponentWidget;

class Inspector : public QWidget
{
    Q_OBJECT
public:
    explicit Inspector(QWidget *parent = nullptr);
    GameObject* GetObject()const;
    void SetObject(GameObject* obj);

private:
    void UpdateContent();
    void SetAllInvisible();
    GameObject* selected = nullptr;
    ShapeComponentWidget* shapeCompoenentWidget;
    TransformComponentWidget* transformComponentWidget;


    QComboBox* comboBox;
    QPushButton* button;


signals:

public slots:
    void OnAddComponent();

};

#endif // INSPECTOR_H

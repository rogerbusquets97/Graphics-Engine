#ifndef INSPECTOR_H
#define INSPECTOR_H

#include "component.h"

#include <QWidget>
#include "gameobject.h"
#include "QComboBox"
#include "QPushButton"
#include "meshcomponentwidget.h"
#include "componentlightwidget.h"

class TransformComponentWidget;

class Inspector : public QWidget
{
    Q_OBJECT
public:
    explicit Inspector(QWidget *parent = nullptr);
    ~Inspector();
    GameObject* GetObject()const;
    void SetObject(GameObject* obj);
    void ConnectEvents();
private:
    void UpdateContent();
    void SetAllInvisible();
    void UpdateTransform();
    void BlockSignals(bool b);
    GameObject* selected = nullptr;
    TransformComponentWidget* transformComponentWidget;
    MeshComponentWidget* meshComponentWidget;
    ComponentLightWidget* componentLightWidget;


    QComboBox* comboBox;
    QPushButton* button;


signals:

public slots:
    void OnAddComponent();
    void OnUpdateSelectedTransform();
    void OnLoadMesh();
    void OnLoadDiffuse();
    void OnLoadNormal();
    void OnChangeDiffuseMirrored();
    void OnChangeNormalMirrored();
    void OnEnableDiffuse();
    void OnEnableNormal();

};

#endif // INSPECTOR_H

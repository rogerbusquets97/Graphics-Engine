#ifndef MESHCOMPONENTWIDGET_H
#define MESHCOMPONENTWIDGET_H

#include <QWidget>
#include "meshcomponent.h"

namespace Ui {
class MeshComponentWidget;
}

class MeshComponentWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MeshComponentWidget(QWidget *parent = nullptr);
    ~MeshComponentWidget();
    inline void SetMeshComponent(MeshComponent* m) {meshComponent = m;}
    inline MeshComponent* GetMeshComponent() const {return meshComponent;}
    void SetPreviewTextures();
    void OnLoadMesh();
    void OnLoadDiffuse();
    void OnLoadNormal();
    void Update();
     Ui::MeshComponentWidget *ui;
private:

    MeshComponent* meshComponent;
};

#endif // MESHCOMPONENTWIDGET_H
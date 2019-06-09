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
    void OnLoadHeightMap();
    void OnChangeDiffuseMirrored(bool aMirrored);
    void OnChangeNormalMirrored(bool aMirrored);
    void OnChangeHeightMapMirrored(bool aMirrored);
    void OnEnableDiffuse(bool a);
    void OnEnableNormal(bool a);
    void OnEnableParallax(bool a);
    void Update();
     Ui::MeshComponentWidget *ui;
private:

    MeshComponent* meshComponent;

};

#endif // MESHCOMPONENTWIDGET_H

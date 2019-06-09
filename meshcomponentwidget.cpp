#include "meshcomponentwidget.h"
#include "ui_meshcomponentwidget.h"
#include <QFileDialog>
#include "mainwindow.h"
#include <QPixmap>

MeshComponentWidget::MeshComponentWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MeshComponentWidget)
{
    ui->setupUi(this);
}

MeshComponentWidget::~MeshComponentWidget()
{
    delete ui;
}

void MeshComponentWidget::Update()
{

}

void MeshComponentWidget::OnLoadMesh()
{
    QString path = QFileDialog::getOpenFileName(this, "Load Mesh");
    if(!path.isEmpty())
    {
        meshComponent->mesh->loadModel(path.toStdString().c_str());
        w->update();
    }
}

void MeshComponentWidget::SetPreviewTextures()
{
    QString diffusePath = meshComponent->mesh->GetMaterial()->GetDiffusePath();
    if(!diffusePath.isEmpty())
    {
        QPixmap pix(diffusePath);
        ui->DiffuseImage->setPixmap(pix.scaled(100,100,Qt::KeepAspectRatio));
        ui->DiffuseImage->setVisible(true);
    }
    else
    {
        ui->DiffuseImage->setVisible(false);
    }

    QString normalPath = meshComponent->mesh->GetMaterial()->GetNormalPath();
    if(!normalPath.isEmpty())
    {
        QPixmap pix(normalPath);
        ui->NormalImage->setPixmap(pix.scaled(100,100, Qt::KeepAspectRatio));
        ui->NormalImage->setVisible(true);
    }
    else
    {
         ui->NormalImage->setVisible(false);
    }

    QString heightPath = meshComponent->mesh->GetMaterial()->GetHeightMapPath();
    if(!heightPath.isEmpty())
    {
        QPixmap pix(heightPath);
        ui->HeightMapImage->setPixmap(pix.scaled(100,100, Qt::KeepAspectRatio));
        ui->HeightMapImage->setVisible(true);
    }
    else
    {
        ui->HeightMapImage->setVisible(false);
    }


}

void MeshComponentWidget::OnLoadNormal()
{
    QString path = QFileDialog::getOpenFileName(this, "Load Normal");
    if(!path.isEmpty())
    {
        meshComponent->mesh->GetMaterial()->SetNormalMap(path);
        w->update();
    }
}

void MeshComponentWidget::OnLoadHeightMap()
{
    QString path = QFileDialog::getOpenFileName(this, "Load HeightMap");
    if(!path.isEmpty())
    {
        meshComponent->mesh->GetMaterial()->SetHeightMap(path);
        w->update();
    }
}
void MeshComponentWidget::OnLoadDiffuse()
{
    QString path = QFileDialog::getOpenFileName(this, "Load Diffuse");
    if(!path.isEmpty())
    {
        meshComponent->mesh->GetMaterial()->SetDiffuse(path);
        w->update();
    }
}

void MeshComponentWidget::OnChangeDiffuseMirrored(bool aMirrored)
{
    meshComponent->mesh->GetMaterial()->SetDiffuseMirrored(aMirrored);
}

void MeshComponentWidget::OnChangeNormalMirrored(bool aMirrored)
{
    meshComponent->mesh->GetMaterial()->SetNormalMirrored(aMirrored);
}

void MeshComponentWidget::OnChangeHeightMapMirrored(bool aMirrored)
{
    meshComponent->mesh->GetMaterial()->SetHeightMapMirrored(aMirrored);
}

void MeshComponentWidget::OnEnableNormal(bool a)
{
    meshComponent->mesh->GetMaterial()->SetNormalActive(a);
}

void MeshComponentWidget::OnChangeMaterialTilling(QVector2D t)
{
    meshComponent->mesh->GetMaterial()->SetTilling(t.x(), t.y());
}
void MeshComponentWidget::OnEnableParallax(bool a)
{
    meshComponent->mesh->GetMaterial()->SetParallaxActive(a);
}

void MeshComponentWidget::OnEnableDiffuse(bool a)
{
    meshComponent->mesh->GetMaterial()->SetDiffuseActive(a);
}


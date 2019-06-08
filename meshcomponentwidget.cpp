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
    }

    QString normalPath = meshComponent->mesh->GetMaterial()->GetNormalPath();
    if(!normalPath.isEmpty())
    {
        QPixmap pix(normalPath);
        ui->NormalImage->setPixmap(pix.scaled(100,100, Qt::KeepAspectRatio));

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

void MeshComponentWidget::OnEnableNormal(bool a)
{
    meshComponent->mesh->GetMaterial()->SetNormalActive(a);
}

void MeshComponentWidget::OnEnableDiffuse(bool a)
{
    meshComponent->mesh->GetMaterial()->SetDiffuseActive(a);
}


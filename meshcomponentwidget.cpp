#include "meshcomponentwidget.h"
#include "ui_meshcomponentwidget.h"
#include <QFileDialog>
#include "mainwindow.h"

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


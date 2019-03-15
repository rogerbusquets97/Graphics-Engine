#include "hierarchy_widget.h"
#include "ui_hierarchy_widget.h"
#include <QLayout>
#include <QVBoxLayout>
#include <QSpacerItem>
#include "gameobjectwidget.h"
#include <iostream>
#include "mainwindow.h"
#include "scene.h"

Hierarchy_Widget::Hierarchy_Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Hierarchy_Widget)
{
    ui->setupUi(this);
    list = ui->HyerarchyList;
    connect(ui->addGoButton, SIGNAL(clicked()),this,SLOT(OnAddGameObject()));
    connect(ui->DeleteButton, SIGNAL(clicked()),this, SLOT(OnDeleteGameObject()));
    connect(ui->HyerarchyList,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(OnObjectSelected(QListWidgetItem*)));

}

Hierarchy_Widget::~Hierarchy_Widget()
{
    delete ui;
}

void Hierarchy_Widget::OnAddGameObject()
{
    QString name = QString("GameObject %1").arg(w->GetCurrScene()->GetSceneGoCount() +1);
    GameObject* obj = new GameObject(nullptr, name);
    if(obj!= nullptr)
    {
        list->addItem(obj->GetName());
        w->OnAddObject(obj);
    }

}

void Hierarchy_Widget::OnDeleteGameObject()
{
    if(list->currentRow()!=-1)
    {
        w->GetCurrScene()->OnDeleteSelectedObject();
        list->takeItem(list->currentRow());
        w->GetCurrScene()->SetSelectedObject(list->currentRow());
    }
}

void Hierarchy_Widget::OnObjectSelected(QListWidgetItem* obj)
{
    w->GetCurrScene()->SetSelectedObject(list->currentRow());
}

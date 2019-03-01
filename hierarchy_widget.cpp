#include "hierarchy_widget.h"
#include "ui_hierarchy_widget.h"
#include <QLayout>
#include <QVBoxLayout>
#include <QSpacerItem>
#include "gameobjectwidget.h"
#include <iostream>
#include "mainwindow.h"

Hierarchy_Widget::Hierarchy_Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Hierarchy_Widget)
{
    ui->setupUi(this);
    list = ui->HyerarchyList;
    connect(ui->addGoButton, SIGNAL(clicked()),this,SLOT(OnAddGameObject()));
}

Hierarchy_Widget::~Hierarchy_Widget()
{
    delete ui;
}

void Hierarchy_Widget::OnAddGameObject()
{
    GameObject* obj = new GameObject(nullptr, "GameObject");
    if(obj!= nullptr)
    {
        list->addItem(obj->GetName());
    }


    std::cout << "OnAddGameObject" << std::endl;
}

void Hierarchy_Widget::OnDeleteGameObject(GameObject *obj)
{

}

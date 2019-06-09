#include "componentlightwidget.h"
#include "ui_componentlightwidget.h"

ComponentLightWidget::ComponentLightWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ComponentLightWidget)
{
    ui->setupUi(this);
}

ComponentLightWidget::~ComponentLightWidget()
{
    delete ui;
}

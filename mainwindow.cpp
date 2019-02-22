#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_rendering.h"
#include "inspector.h"

#include <iostream>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    uiMainWindow(new Ui::MainWindow),
    uiRendering(new Ui::Rendering)
{

    setTabPosition(Qt::AllDockWidgetAreas, QTabWidget::TabPosition::North);

    uiMainWindow->setupUi(this);

    QWidget *renderingWidget = new QWidget();
    uiRendering->setupUi(renderingWidget);
    renderingWidget->show();

    uiMainWindow->RenderingDock->setWidget(renderingWidget);

    uiMainWindow->RenderingDock->setFloating(false);

    inspector = new Inspector();
    uiMainWindow->InspectorDock->setWidget(inspector);

    tabifyDockWidget(uiMainWindow->RenderingDock, uiMainWindow->InspectorDock);

    // Connect Actions' triggered() signals to some slots
    connect(uiMainWindow->actionOpen_Project, SIGNAL(triggered()), this, SLOT(openProject()));
    connect(uiMainWindow->actionSave_Project, SIGNAL(triggered()), this, SLOT(saveProject()));
    connect(uiMainWindow->actionExit, SIGNAL(triggered()), this, SLOT(exitProject()));
}

MainWindow::~MainWindow()
{
    delete uiMainWindow;
    delete uiRendering;
}

void MainWindow::openProject()
{
    QString path = QFileDialog::getOpenFileName(this, "Open Project");
    if(!path.isEmpty())
    {
        std::cout << path.toStdString() << std::endl;
    }
}
void MainWindow::saveProject()
{
    std::cout<< "Save Project" << std::endl;
}

void MainWindow::exitProject()
{
    std::cout<< "Exit Project" << std::endl;
    QMessageBox::StandardButton button = QMessageBox::question(
                this, "ExtApplication", "Do you want to exit the application without saving the project?");
    if (button == QMessageBox::Yes)
    {
        std::cout << "Exit without saving changes" << std::endl;
        qApp->quit();
    }
    else
    {
        std::cout<<"Cancel exit"<<std::endl;
    }
}

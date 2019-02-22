#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_rendering.h"
#include "inspector.h"

#include <Qlist>
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

    scene.push_back(5);
}

MainWindow::~MainWindow()
{
    delete uiMainWindow;
    delete uiRendering;
}

void MainWindow::openProject()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open Project", "", tr("Scene Name (*.txt);; All Files (*)"));
    if(!fileName.isEmpty())
    {
        std::cout << fileName.toStdString() << std::endl;
    }
    else
    {
        QFile file(fileName);

        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::information(this, tr("Unable to open file"), file.errorString());
            return;
        }

        if (scene.isEmpty())
        {
        QMessageBox::information(this, tr("Scene is empty."), tr("The file you are attempting to load is empty."));
        }
        else {
           /* QDataStream in(&file);
            in.setVersion(QDataStream::Qt_4_5);
            scene.clear();
            in >> scene;*/
            QList<int>::iterator i = scene.begin();
            //nameLine->setText(i);

        }
    }
}
void MainWindow::saveProject()
{
    std::cout<< "Save Project" << std::endl;

    QString fileName = QFileDialog::getSaveFileName(this, "Save Scene", "", tr(".txt (*txt);;All Files (*)"));

    if(fileName.isEmpty())
    {
        std::cout<< "Name is empty" << std::endl;
    }
    else {
        QFile file(fileName);
        if(!file.open(QIODevice::WriteOnly))
        {
            QMessageBox::information(this, tr("Unable to open file"),
                    file.errorString());
        }

        QDataStream out(&file);
        out.setVersion(QDataStream::Qt_4_5);
        out << scene;
    }
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

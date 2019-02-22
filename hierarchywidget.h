#ifndef HIERARCHYWIDGET_H
#define HIERARCHYWIDGET_H

#include <QWidget>
#include <QLabel>
#include <list>

class HierarchyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit HierarchyWidget(QWidget *parent = nullptr);
private:

    GameOject* selected;
    std::list<QLabel> labels;


signals:

public slots:
};

#endif // HIERARCHYWIDGET_H

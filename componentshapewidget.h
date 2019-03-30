#ifndef COMPONENTSHAPEWIDGET_H
#define COMPONENTSHAPEWIDGET_H

#include <QObject>
#include <QWidget>
#include <QComboBox>

class ComponentShapeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ComponentShapeWidget(QWidget *parent = nullptr);
    virtual ~ComponentShapeWidget();
    QComboBox* combobox;
    QComboBox* colorbox;
    QComboBox* strokebox;
signals:

public slots:
};

#endif // COMPONENTSHAPEWIDGET_H

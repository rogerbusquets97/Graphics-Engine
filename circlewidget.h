#ifndef CIRCLEWIDGET_H
#define CIRCLEWIDGET_H

#include <QObject>
#include <QWidget>
#include <QPainter>

class circlewidget : public QWidget
{
    Q_OBJECT
public:
    explicit circlewidget(QWidget *parent = nullptr);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
signals:

public slots:

private:

    void paintEvent(QPaintEvent *event) override;
};

#endif // CIRCLEWIDGET_H

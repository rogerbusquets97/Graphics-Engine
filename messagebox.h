#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <QMessageBox>

class messagebox : public QMessageBox
{
public:
    messagebox();

public:
    QMessageBox::StandardButton button = QMessageBox::uestion ()
};

#endif // MESSAGEBOX_H

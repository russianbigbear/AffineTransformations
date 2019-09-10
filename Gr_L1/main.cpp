#include "widget.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.draw(w.coordinats);
    w.show();

    return a.exec();
}

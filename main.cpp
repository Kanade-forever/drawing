#include "CourseDesign.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CourseDesign w;
    w.show();

    return a.exec();
}

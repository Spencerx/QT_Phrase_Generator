#include "markovui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MarkovUI w;
    w.show();

    return a.exec();
}

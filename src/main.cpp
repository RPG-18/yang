#include <iostream>
using namespace std;

#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtWidgets/QApplication>

#include "Utils.h"
#include "Application.h"

int main(int argc, char* argv[])
{
    Q_INIT_RESOURCE(qml);

    QApplication app(argc, argv);
    Application myApp;
    return app.exec();
}

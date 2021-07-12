#include <QApplication>
#include <QMessageBox>
#include "rhi_application.h"


int main(int argc, char* argv[])
{
    Q_INIT_RESOURCE(rhi_resources);

    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    RHIApplication app(argc, argv);

    QApplication::setQuitOnLastWindowClosed(false);

    if (!app.init()) return -1;
    return app.run();
}


#include <QApplication>
#include <QMessageBox>
#include "rhi_application.h"
#include "qline_item.h"


int main(int argc, char* argv[])
{
    Q_INIT_RESOURCE(rhi_resources);

    qmlRegisterType<QLineItem>("my", 1, 0, "QLineItem");

    //QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    //QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    RHIApplication app(argc, argv);

    QApplication::setQuitOnLastWindowClosed(true);



    if (!app.init()) return -1;
    return app.run();
}


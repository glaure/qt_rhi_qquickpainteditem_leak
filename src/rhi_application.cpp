#include "rhi_application.h"
#include "QFile"
#include <QFileInfo>
#include <QQmlContext>
#include <QQmlEngine>


RHIApplication::RHIApplication(int& argc, char** argv)
    : QObject(nullptr)
    , m_app(argc, argv)
    , m_app_data(nullptr)
    , m_main_window(nullptr)
    , m_qml_main_file()
    , m_qml_reloader(nullptr)
{

}

RHIApplication::~RHIApplication()
{
    delete m_qml_reloader;
    delete m_main_window;
    delete m_app_data;
}

bool RHIApplication::init()
{
    m_app_data = new RHIApplicationData;

    m_qml_main_file.clear();

    // Setup main.qml
    QStringList main_qml_candidates = { "../qml/main.qml" };

    for (QString main_qml : main_qml_candidates)
    {
        QFile mq_file(main_qml);
        if (mq_file.exists())
        {
            m_qml_main_file = main_qml;
            break;
        }
    }

    if (m_qml_main_file.isEmpty())
    {
        m_qml_main_file = "qrc:qml/main.qml";
    }
    else
    {
        QFileInfo qml_file_info(m_qml_main_file);
        auto qml_path = qml_file_info.absolutePath();

        // Handle dynamic qml changes
        m_qml_reloader = new QmlReloader;
        m_qml_reloader->addDirectoryToWatch(qml_path, QStringList() << "*.qml" << "*.js", true);
    }
 

    if (!initGui()) return false;

    return true;
}

bool RHIApplication::initGui()
{
    m_main_window = new QQuickView;
    m_main_window->connect(m_main_window->engine(), &QQmlEngine::quit, &m_app, &QCoreApplication::quit);
    m_main_window->setSource(QUrl(m_qml_main_file));

    if (m_main_window->status() == QQuickView::Error)
        return false;

    //m_main_window->setResizeMode(QQuickView::SizeRootObjectToView);
    
    m_main_window->rootContext()->setContextProperty("app", m_app_data);

    m_main_window->show();
    //m_main_window->hide();
    if (m_qml_reloader) 
    {
        m_qml_reloader->addView(m_main_window);
    }


    return true;
}

int RHIApplication::run()
{
    int ret = 0;

    ret = m_app.exec();

    return ret;
}


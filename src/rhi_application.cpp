#include "rhi_application.h"
#include "QFile"
#include <QFileInfo>
#include <QQmlContext>
#include <QQmlEngine>
#include <QSGRendererInterface>

RHIApplication::RHIApplication(int& argc, char** argv)
    : QObject(nullptr)
    , m_app(argc, argv)
    , m_app_data(nullptr)
    , m_main_window(nullptr)
    , m_qml_main_file()
    , m_qml_reloader(nullptr)
{
    m_app_data = new RHIApplicationData;

    QString graphics_backend = "OpenGLRhi";

    // let it be configureable by command line
    if (argc > 1)
    {
        graphics_backend = QString::fromLatin1(argv[1]);

        if (graphics_backend == "OpenGL")
        {
            m_app_data->setRenderingMode(RenderingMode::Desktop_OpenGL);
        }
        else if (graphics_backend == "OpenGLRhi")
        {
            m_app_data->setRenderingMode(RenderingMode::Desktop_OpenGL_RHI);
        }
        else if (graphics_backend == "Direct3D11Rhi")
        {
            m_app_data->setRenderingMode(RenderingMode::Desktop_3D11_RHI);
        }
        else if (graphics_backend == "ANGLE_D3D11")
        {
            m_app_data->setRenderingMode(RenderingMode::ANGLE_D3D11);
        }
        else if (graphics_backend == "NullRhi")
        {
            m_app_data->setRenderingMode(RenderingMode::NullRhi);
        }
        
    }

}

RHIApplication::~RHIApplication()
{
    delete m_qml_reloader;
    delete m_main_window;
    delete m_app_data;
}

bool RHIApplication::init()
{
    qunsetenv("QT_OPENGL");

    switch (m_app_data->getRenderingMode())
    {
    case RenderingMode::Dynamic:
        break;
    case RenderingMode::Desktop_OpenGL:
        m_app.setAttribute(Qt::AA_UseDesktopOpenGL, true);
        break;
    case RenderingMode::Desktop_OpenGL_RHI:
        m_app.setAttribute(Qt::AA_UseDesktopOpenGL, true);
        QQuickWindow::setSceneGraphBackend(QSGRendererInterface::OpenGLRhi);
        break;
    case RenderingMode::Desktop_3D11_RHI:
        m_app.setAttribute(Qt::AA_UseDesktopOpenGL, true);
        QQuickWindow::setSceneGraphBackend(QSGRendererInterface::Direct3D11Rhi);
        break;
    case RenderingMode::ANGLE_D3D9:
        m_app.setAttribute(Qt::AA_UseOpenGLES, true);
        qputenv("QT_ANGLE_PLATFORM", "d3d9");
        break;
    case RenderingMode::ANGLE_D3D11:
        m_app.setAttribute(Qt::AA_UseOpenGLES, true);
        qputenv("QT_ANGLE_PLATFORM", "d3d11");
        break;
    case RenderingMode::NullRhi:
        QQuickWindow::setSceneGraphBackend(QSGRendererInterface::NullRhi);
        break;
    }


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

    auto render_if = m_main_window->rendererInterface();
    auto graphics_api = render_if->graphicsApi();

   
    m_main_window->rootContext()->setContextProperty("app", m_app_data);

    m_main_window->show();

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


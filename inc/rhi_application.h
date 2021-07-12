#pragma once

#include <QApplication>
#include <QObject>
#include <QQuickView>
#include "qml_reloader.h"


class RHIApplicationData : public QObject
{
    Q_OBJECT

public:
    RHIApplicationData()
    {}
    ~RHIApplicationData()
    {}
};



/**
 * Initializes the application and manages the GUI
 */
class RHIApplication : public QObject
{
    Q_OBJECT;

public:
    RHIApplication(int& argc, char** argv);
    ~RHIApplication();

    bool init();
    bool initGui();

    /**
     * Starts the GUI application and only returns (with an exit code) when the application should terminate
     */
    int run();

private:


private:
    QApplication            m_app;
    RHIApplicationData*     m_app_data;
    QQuickView*             m_main_window;
    QString                 m_qml_main_file;
    QmlReloader*            m_qml_reloader;
};


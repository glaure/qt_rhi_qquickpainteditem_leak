#pragma once

#include <QApplication>
#include <QObject>
#include <QQuickView>
#include "qml_reloader.h"


enum class RenderingMode
{
    Dynamic,
    Desktop_OpenGL,
    Desktop_OpenGL_RHI,
    Desktop_3D11_RHI,
    ANGLE_D3D9,
    ANGLE_D3D11,
    NullRhi,
};


class RHIApplicationData : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString renderingMode                READ getRenderingModeStr             CONSTANT)
public:

    RHIApplicationData()
        : m_rendering_mode(RenderingMode::Desktop_OpenGL_RHI)
    {}

    ~RHIApplicationData()
    {}


    QString getRenderingModeStr() const
    {
        switch (m_rendering_mode)
        {
        case RenderingMode::Dynamic:
            return "Dynamic";
        case RenderingMode::Desktop_OpenGL:
            return "Desktop_OpenGL";
        case RenderingMode::Desktop_OpenGL_RHI:
            return "Desktop_OpenGL_RHI";
        case RenderingMode::Desktop_3D11_RHI:
            return "Desktop_3D11_RHI";
        case RenderingMode::ANGLE_D3D9:
            return "ANGLE_D3D9";
        case RenderingMode::ANGLE_D3D11:
            return "ANGLE_D3D11";
        case RenderingMode::NullRhi:
            return "NullRhi";
        }

        return "Unknown mode";
    }

    void setRenderingMode(RenderingMode rendering_mode)
    {
        m_rendering_mode = rendering_mode;
    }

    RenderingMode getRenderingMode() const
    {
        return m_rendering_mode;
    }

private:
    RenderingMode m_rendering_mode;
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


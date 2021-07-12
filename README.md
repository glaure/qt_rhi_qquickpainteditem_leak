# qt_rhi_qquickpainteditem_leak

Reproduces a memory leak when using QML + RHI.


The qml windows uses QQuickPaintedItem for drawing a line using a painter.

Different graphical backends are configureable using the command line.

Following commandline arguments are possible:

 * OpenGLRhi
 * OpenGL
 * Direct3D11Rhi
 * ANGLE_D3D11
 * NullRhi


Only the older OpenGL and Angle backends do not leak.

All *Rhi backends (even NullRhi) leak memory.

This bug is not resolved in Qt 5.12.2

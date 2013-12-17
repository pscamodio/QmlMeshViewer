#include "meshview.h"

#include <QtQuick/qquickwindow.h>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QOpenGLContext>

MeshView::MeshView(QQuickItem *parent) :
    QQuickItem(parent),
    m_program(nullptr)
{
    connect(this, &QQuickItem::windowChanged, this, &MeshView::handleWindowChanged);
}

void MeshView::paint()
{
    if (!m_program) {
        m_program = new QOpenGLShaderProgram();
        m_program->addShaderFromSourceCode(QOpenGLShader::Vertex,
                                           "attribute highp vec4 vertices;"
                                           "varying highp vec2 coords;"
                                           "void main() {"
                                           "    gl_Position = vertices;"
                                           "    coords = vertices.xy;"
                                           "}");
        m_program->addShaderFromSourceCode(QOpenGLShader::Fragment,
                                           "uniform lowp float t;"
                                           "varying highp vec2 coords;"
                                           "void main() {"
                                           "    lowp float i = 1. - (pow(abs(coords.x), 4.) + pow(abs(coords.y), 4.));"
                                           "    i = smoothstep(t - 0.8, t + 0.8, i);"
                                           "    i = floor(i * 20.) / 20.;"
                                           "    gl_FragColor = vec4(coords * .5 + .5, i, i);"
                                           "}");

        m_program->link();

        connect(window()->openglContext(), SIGNAL(aboutToBeDestroyed()),
                this, SLOT(cleanup()), Qt::DirectConnection);
    }
//! [4] //! [5]
    m_program->bind();
    glViewport(0, 0, window()->width(), window()->height());
    glBegin(GL_TRIANGLES);
    glColor3f(0.1, 0.2, 0.3);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);
    glVertex3f(0, 1, 0);
    glEnd();

    m_program->release();
}

void MeshView::cleanup()
{

}

void MeshView::sync()
{

}

void MeshView::handleWindowChanged(QQuickWindow *win)
{
    if (win) {
        connect(win, &QQuickWindow::beforeRendering, this, &MeshView::paint, Qt::DirectConnection);
        connect(win, &QQuickWindow::beforeSynchronizing, this, &MeshView::sync, Qt::DirectConnection);
        win->setClearBeforeRendering(false);
    }
}



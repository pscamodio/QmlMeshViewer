#include "meshview.h"

#include <QtQuick/qquickwindow.h>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QOpenGLContext>
#include <QTimer>

MeshView::MeshView(QQuickItem *parent) :
    QQuickItem(parent), rot_x(0), rot_y(0)
{
    connect(this, &QQuickItem::windowChanged, this, &MeshView::handleWindowChanged);
    QTimer *t = new QTimer(this);
    connect(t, &QTimer::timeout, this, &MeshView::onTimer);
    t->start(10);
}

void MeshView::paint()
{
    glDisable(GL_DEPTH_TEST);

    glClearColor(0, 0, 0, 0.1);
    glClear(GL_COLOR_BUFFER_BIT);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    qreal ratio = window()->devicePixelRatio();
    int w = int(ratio * window()->width());
    int h = int(ratio * window()->height());
    glViewport(0, 0, w, h);
    glRotatef(thread_rot_x, 1, 0.0, 0.0);
    glRotatef(thread_rot_y, 0.0, 1, 0.0);

    glBegin(GL_QUADS);
    glColor3f( 1.0, 0.0, 0.0 );
    glVertex3f(  0.5, -0.5, -0.5 );      // P1 is red
    glVertex3f(  0.5,  0.5, -0.5 );      // P2 is green
    glVertex3f( -0.5,  0.5, -0.5 );      // P3 is blue
    glVertex3f( -0.5, -0.5, -0.5 );      // P4 is purple
    glEnd();

    // White side - BACK
    glBegin(GL_QUADS);
    glColor3f(   1.0,  1.0, 1.0 );
    glVertex3f(  0.5, -0.5, 0.5 );
    glVertex3f(  0.5,  0.5, 0.5 );
    glVertex3f( -0.5,  0.5, 0.5 );
    glVertex3f( -0.5, -0.5, 0.5 );
    glEnd();

    // Purple side - RIGHT
    glBegin(GL_QUADS);
    glColor3f(  1.0,  0.0,  1.0 );
    glVertex3f( 0.5, -0.5, -0.5 );
    glVertex3f( 0.5,  0.5, -0.5 );
    glVertex3f( 0.5,  0.5,  0.5 );
    glVertex3f( 0.5, -0.5,  0.5 );
    glEnd();

    // Green side - LEFT
    glBegin(GL_QUADS);
    glColor3f(   0.0,  1.0,  0.0 );
    glVertex3f( -0.5, -0.5,  0.5 );
    glVertex3f( -0.5,  0.5,  0.5 );
    glVertex3f( -0.5,  0.5, -0.5 );
    glVertex3f( -0.5, -0.5, -0.5 );
    glEnd();

    // Blue side - TOP
    glBegin(GL_QUADS);
    glColor3f(   0.0,  0.0,  1.0 );
    glVertex3f(  0.5,  0.5,  0.5 );
    glVertex3f(  0.5,  0.5, -0.5 );
    glVertex3f( -0.5,  0.5, -0.5 );
    glVertex3f( -0.5,  0.5,  0.5 );
    glEnd();

    // Red side - BOTTOM
    glBegin(GL_QUADS);
    glColor3f(   1.0,  0.0,  0.0 );
    glVertex3f(  0.5, -0.5, -0.5 );
    glVertex3f(  0.5, -0.5,  0.5 );
    glVertex3f( -0.5, -0.5,  0.5 );
    glVertex3f( -0.5, -0.5, -0.5 );
    glEnd();

}

void MeshView::cleanup()
{

}

void MeshView::sync()
{
    thread_rot_x = rot_x;
    thread_rot_y = rot_y;
}

void MeshView::handleWindowChanged(QQuickWindow *win)
{
    if (win) {
        connect(win, &QQuickWindow::beforeRendering, this, &MeshView::paint, Qt::DirectConnection);
        connect(win, &QQuickWindow::beforeSynchronizing, this, &MeshView::sync, Qt::DirectConnection);
        win->setClearBeforeRendering(false);
    }
}

void MeshView::onTimer()
{
    rot_x++;
    rot_y++;
    if (window())
        window()->update();
}



#ifndef MESHVIEW_H
#define MESHVIEW_H

#include <QQuickItem>
#include <QtGui/QOpenGLShaderProgram>

class MeshView : public QQuickItem
{
    Q_OBJECT
public:
    explicit MeshView(QQuickItem *parent = 0);

signals:

public slots:
    void paint();
    void cleanup();
    void sync();

private slots:
    void handleWindowChanged(QQuickWindow *win);

public slots:

private:
    QOpenGLShaderProgram *m_program;


};

#endif // MESHVIEW_H

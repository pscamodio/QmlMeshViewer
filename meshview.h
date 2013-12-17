#ifndef MESHVIEW_H
#define MESHVIEW_H

#include <QQuickItem>

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

protected:

private slots:
    void handleWindowChanged(QQuickWindow *win);

public slots:
    void onTimer();

private:
    int rot_x, thread_rot_x;
    int rot_y, thread_rot_y;


};

#endif // MESHVIEW_H

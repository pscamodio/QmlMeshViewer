#include <QtGui/QGuiApplication>

#include <QtQuick/QQuickView>
#include "qtquick2applicationviewer.h"

#include "meshview.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<MeshView>("QmlStlViewer", 1, 0, "MeshView");

    QtQuick2ApplicationViewer viewer;
    viewer.setMainQmlFile(QStringLiteral("qml/QmlStlViewer/main.qml"));
    viewer.showExpanded();

    return app.exec();
}

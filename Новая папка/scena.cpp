#include "scena.h"
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QPointF>
#include <iostream>
#ifdef WIN32
#include <QtPlugin>
Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin);
#endif
CustomScene::CustomScene(QObject* parent) : selecting(false) {
    QGraphicsScene();
    {   
        Q_UNUSED(parent);
    }
}

CustomScene::~CustomScene()
{
}
void CustomScene::setPixmap(QPixmap currentPixmap)
{
    pixmap = currentPixmap;
}
QPixmap CustomScene::getPixmap()
{
    return pixmap;
}
void CustomScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        selecting = true;
        startPoint = event->scenePos();
        releasePoint = event->scenePos();
        emit signalMousePressSelected(startPoint.toPoint());
    }
}
void CustomScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        selecting = false;
        QRectF selectedRect = QRectF(startPoint, releasePoint).normalized();
        std::cout << startPoint.x() << " " << releasePoint.x() << std::endl;
        std::cout << startPoint.y() << " " << releasePoint.y() << std::endl;
        if (!selectedRect.isEmpty() && startPoint!=releasePoint) {
            QPixmap selectedPixmap = pixmap.copy(selectedRect.toRect());
            emit signalSelectedArea(selectedPixmap);
            pixmap = selectedPixmap;
            startPoint = releasePoint;
        }
        emit signalMouseReleaseSelected();
    }
}
void CustomScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if (selecting) {
        releasePoint = event->scenePos();
        emit signalMouseMoveSelected(startPoint.toPoint(), (releasePoint.toPoint()));
    }
    emit signalTargetCoordinate(event->scenePos());
}

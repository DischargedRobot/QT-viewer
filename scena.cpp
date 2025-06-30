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
void CustomScene::setPixmap(QPixmap* currentPixmap)
{
    pixmap = *currentPixmap;
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
        //std::cout << startPoint.x() << " " << releasePoint.x() << std::endl;

        if (!selectedRect.isEmpty() && startPoint!=releasePoint && selectedRect.intersects(pixmap.rect())) {
            //std::cout << (selectedRect.intersected(pixmap.rect())).left()<<" " << startPoint.x() << " " << releasePoint.y() << std::endl;
            QPixmap selectedPixmap = pixmap.copy(selectedRect.toRect());
            emit signalSelectedArea(selectedPixmap, selectedRect.intersected(pixmap.rect()).left(), (selectedRect.intersected(pixmap.rect())).right(), (selectedRect.intersected(pixmap.rect())).top(), (selectedRect.intersected(pixmap.rect())).bottom());
            //pixmap = selectedPixmap;
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

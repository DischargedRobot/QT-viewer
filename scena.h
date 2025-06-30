#ifndef CUSTOMSCENE_H
#define CUSTOMSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPixmap>
#include <QPointF>
#include <QRubberBand>
class CustomScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit CustomScene(QObject* parent = 0);
    ~CustomScene();
    void setPixmap(QPixmap* currentPixmap);
    QPixmap getPixmap();
;
signals:
    // Сигнал для передачи координат положения курсора мыши
    void signalTargetCoordinate(QPointF point);  
    // Сигналы для выделения области
    void signalSelectedArea(QPixmap pixmap, int xStart, int xEnd, int yStart, int yEnd);
    void signalMousePressSelected(QPoint startPoint);
    void signalMouseMoveSelected(QPoint startPoint, QPoint currentPoint);
    void signalMouseReleaseSelected();
public slots:

private:
    QPointF startPoint;
    bool selecting;
    QPointF releasePoint;
    QPixmap pixmap;
    void ShowSelectedArea(const QPixmap& pixmap);
    // Функция, в которой производится отслеживание положения мыши
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
};
#endif 
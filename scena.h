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
    // ������ ��� �������� ��������� ��������� ������� ����
    void signalTargetCoordinate(QPointF point);  
    // ������� ��� ��������� �������
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
    // �������, � ������� ������������ ������������ ��������� ����
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
};
#endif 
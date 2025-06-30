#ifndef CUSTOMSVIEW_H
#define CUSTOMSVIEW_H

#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QScrollBar>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QPointF>
#include <iostream>

class CustomView : public QGraphicsView {
    Q_OBJECT

public:
    explicit CustomView(QWidget* parent = 0);
    ~CustomView();
    void conn();
private slots:
    void onHorizontalScrollValueChanged(int value);

    void onVerticalScrollValueChanged(int value);



signals:
    // Сигнал для передачи координат положения курсора мыши
    void signalMoveScrollBar();
};
#endif 
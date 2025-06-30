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
#include "view.h"
#ifdef WIN32
#include <QtPlugin>
Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin);
#endif

void CustomView::conn() {
            connect(horizontalScrollBar(), &QScrollBar::valueChanged, this, &CustomView::onHorizontalScrollValueChanged);
            connect(verticalScrollBar(), &QScrollBar::valueChanged, this, &CustomView::onVerticalScrollValueChanged);
    //   
}
CustomView::CustomView(QWidget* parent)
    : QGraphicsView(parent)
{
    connect(horizontalScrollBar(), &QScrollBar::valueChanged, this, &CustomView::onHorizontalScrollValueChanged);
    connect(verticalScrollBar(), &QScrollBar::valueChanged, this, &CustomView::onVerticalScrollValueChanged);
    //   
}
    CustomView::~CustomView()
    {
    }

    void CustomView::onHorizontalScrollValueChanged(int value) {
        emit signalMoveScrollBar();
    }

    void CustomView::onVerticalScrollValueChanged(int value) {
        emit signalMoveScrollBar();
    }



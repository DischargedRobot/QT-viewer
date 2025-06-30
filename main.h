#pragma once
#include <iostream>
#include <cstdio>
#include <cmath>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QWidget>
#include <QMouseEvent>
#include <QObject>
#include <QMenu>
#include <QAction>
#include <QMenuBar>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>
#include <QImage>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QMainWindow>
#include <QToolBar>
#include <QIcon>
#include <QPainter>
#include "BMP.h"
#include <map>
#include "scena.h"
#include "Histogram.h"
#include <QRubberBand>
#include <QRegion>
#include <QtGui>
#include "view.h"
#ifdef WIN32
#include <QtPlugin>
Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin);
#endif


class ImageViewer : public QMainWindow
{
public:
    ImageViewer();

private slots:
    void open();
    void saveAs();
    void normalSize();
    void fitToWindow();
    void zoomIn();
    void zoomOut();
    void moreInfoAboutImage();
    void returnImage();

private:
    void mouseMove(QPointF pos);
    void numberСolors(MathImage* mathImage, Returned* imgAndPixels);
    void selectedArea(QPixmap selectedPixmap, int xStart, int xEnd, int yStart, int yEnd);
    void select();
    CustomScene* scene;
    CustomView* view;
    QGraphicsPixmapItem* pixmapItem;
    QGraphicsPixmapItem* pixmapItemSelected;
    QImage image;
    QScrollArea* scrollArea;
    bool loadFile = false;
    QString fileName;
    QString fileNameChek = NULL;
    double scaleFactor = 1;
    QLabel* coordinatesLabel;
    Returned* loadedImgAndPixels;
    MathImage* mathLoadedImage = new MathImage();
    Histogram* histogram = nullptr;
    QPixmap pixmap;
    QPixmap selectedPixmap;
    //область выделения
    QRubberBand* rubberBand;
    QImage selectedImage;
    Returned* selectedImgAndPixels;
    MathImage* mathSelectedImage = new MathImage();
    BMPImageReader reader;
    int xStartSelect;
    int yStartSelect;
    QPointF itemPos;
    bool selected = false;
    bool connectScroll = false;
    float scale = 0;
    bool normalSizeFlag = false;
protected:
    void mousePressRubberBand(QPoint startPoint);
    void mouseMoveRubberBand(QPoint startPoint, QPoint currentPoint);
    void mouseReleaseRubberBand();
};

void ImageViewer::mousePressRubberBand(QPoint startPoint)
{
    rubberBand = new QRubberBand(QRubberBand::Rectangle, this->view);
    rubberBand->setGeometry(QRect(view->mapFromScene(startPoint), QSize()));
    rubberBand->show();
}

void ImageViewer::mouseMoveRubberBand(QPoint startPoint, QPoint currentPoint)
{
    rubberBand->setGeometry(QRect(view->mapFromScene(startPoint), view->mapFromScene(currentPoint)).normalized());
}

void ImageViewer::mouseReleaseRubberBand()
{

    //rubberBand->hide();
    rubberBand->deleteLater();
    rubberBand = nullptr;
}
ImageViewer::ImageViewer() {
    scene = new CustomScene(this);
    view = new CustomView(this);
    view->setScene(scene);
    this->setCentralWidget(view);
    // Заданиие toolBar
    QToolBar* toolBar = new QToolBar("Tools", this);
    this->addToolBar(Qt::RightToolBarArea, toolBar);
    toolBar->setIconSize(QSize(32, 32));
    toolBar->setMinimumWidth(85);

    // Создание menuBar
    QMenuBar* menuBar = new QMenuBar(this);
    this->setMenuBar(menuBar);

    // Создание ячеек для меню
    QMenu* fileMenu = new QMenu("File", menuBar);
    QMenu* viewMenu = new QMenu("View", menuBar);
    menuBar->addMenu(fileMenu);
    menuBar->addMenu(viewMenu);

    QAction* moreInfoAboutImageAction = new QAction("More info about image", menuBar);
    menuBar->addAction(moreInfoAboutImageAction);
    QObject::connect(moreInfoAboutImageAction, &QAction::triggered, this, &ImageViewer::moreInfoAboutImage);

    // Добавление "Open" в ячейку меню "File" и toolBar
    QAction* openAction = new QAction(QIcon(":/open.png"), "Open", fileMenu);
    fileMenu->addAction(openAction);
    toolBar->addAction(openAction);
    QObject::connect(openAction, &QAction::triggered, this, &ImageViewer::open);

    //  Добавление "Save" в ячейку меню "Save As" и toolBar
    QAction* saveAction = new QAction(QIcon(":/save.png"), "Save As", fileMenu);
    fileMenu->addAction(saveAction);
    toolBar->addAction(saveAction);
    QObject::connect(saveAction, &QAction::triggered, this, &ImageViewer::saveAs);

    // Добавление  "Normal Size" в ячейку меню  "View" и toolBar
    QAction* normalsizeAction = new QAction(QIcon(":/normalSize.png"), "Normal Size", viewMenu);
    viewMenu->addAction(normalsizeAction);
    toolBar->addAction(normalsizeAction);
    QObject::connect(normalsizeAction, &QAction::triggered, this, &ImageViewer::normalSize);

    // Добавление  "Fit To Window" в ячейку меню  "View" и toolBar
    QAction* fitToWindowAction = new QAction(QIcon(":/fitToWindow.png"), "Fit To Window", viewMenu);
    viewMenu->addAction(fitToWindowAction);
    toolBar->addAction(fitToWindowAction);
    QObject::connect(fitToWindowAction, &QAction::triggered, this, &ImageViewer::fitToWindow);

    // Добавление "Zoom In" в ячейку меню  "View" и toolBar
    QAction* zoomInAction = new QAction(QIcon(":/zoomIn.png"), "Zoom In", viewMenu);
    viewMenu->addAction(zoomInAction);
    toolBar->addAction(zoomInAction);
    QObject::connect(zoomInAction, &QAction::triggered, this, &ImageViewer::zoomIn);

    // Добавление "Zoom Out" в ячейку меню  "View" и toolBar
    QAction* zoomOutAction = new QAction(QIcon(":/zoomOut.png"), "Zoom Out", viewMenu);
    viewMenu->addAction(zoomOutAction);
    toolBar->addAction(zoomOutAction);
    QObject::connect(zoomOutAction, &QAction::triggered, this, &ImageViewer::zoomOut);

    // Добавление "Zoom Out" в ячейку меню  "View" и toolBar
    QAction* returnImageAction = new QAction(QIcon(":/cancle_selection.png"), "Cancel the selection", viewMenu);
    viewMenu->addAction(returnImageAction);
    toolBar->addAction(returnImageAction);
    QObject::connect(returnImageAction, &QAction::triggered, this, &ImageViewer::returnImage);

    // Отображение координат в toolBar
    coordinatesLabel = new QLabel("outside\nthe image", toolBar);
    toolBar->addWidget(coordinatesLabel);

    // Отслеживание мыши для view
    this->setMouseTracking(true);
    view->setMouseTracking(true);
    connect(scene, &CustomScene::signalTargetCoordinate, this, &ImageViewer::mouseMove);
    connect(scene, &CustomScene::signalSelectedArea, this, &ImageViewer::selectedArea);
    connect(scene, &CustomScene::signalMouseMoveSelected, this, &ImageViewer::mouseMoveRubberBand);
    connect(scene, &CustomScene::signalMousePressSelected, this, &ImageViewer::mousePressRubberBand);
    connect(scene, &CustomScene::signalMouseReleaseSelected, this, &ImageViewer::mouseReleaseRubberBand);
};

void ImageViewer::select() {
    if (loadFile) {

        QRectF visibleRect = view->mapToScene(view->viewport()->rect()).boundingRect();         // Преобразуем его в координаты сцены
        //QRectF visibleRect2 = view->mapToScene(visibleRect).boundingRect();
        QRectF rect = visibleRect.intersected(pixmapItem->boundingRect());

        scene->removeItem(pixmapItem);
        loadedImgAndPixels = reader.select(rect.left(), rect.right(), rect.top(), rect.bottom(), 1, true);

        //QPixmap selectedPixmap = QPixmap::fromImage(*loadedImgAndPixels->img);
        //scene->setPixmap(&selectedPixmap);
        if (pixmapItem != nullptr)
            delete pixmapItem;
        pixmapItem = new QGraphicsPixmapItem(QPixmap::fromImage(*loadedImgAndPixels->img));
        scene->addItem(pixmapItem);

    }
}
// Обработка выделенной области
void ImageViewer::selectedArea(QPixmap selectPixmap, int xStart, int xEnd, int yStart, int yEnd) {
    if (!selectPixmap.isNull()) {
        selectedPixmap = selectPixmap;
        //scene->removeItem(pixmapItem);
        //selectedPixmap = QPixmap::fromImage(*reader.select(xStart, xEnd, yStart, yEnd,1)->img);
        //scene->setPixmap(selectedPixmap);
        //pixmapItem = new QGraphicsPixmapItem(selectedPixmap);
        //scene->addItem(pixmapItem);

        //view->setSceneRect(pixmapItem->boundingRect());
        //scene->setPixmap(selectedPixmap);
        //fitToWindow();

        selected = true;
        //fileNameChek = nullptr;
    }
}
void ImageViewer::mouseMove(QPointF pos) {
    if (loadFile && pixmapItem) {
        // Получаем позицию курсора относительно сцены
        itemPos = pos;


        // Проверяем, находится ли курсор внутри изображения
        if (itemPos.x() >= 0 && itemPos.x() < pixmapItem->pixmap().width() &&
            itemPos.y() >= 0 && itemPos.y() < pixmapItem->pixmap().height()) {
            coordinatesLabel->setText(QString("Coordinate:\n x:%1,\n y:%2").arg(itemPos.x()).arg(itemPos.y()));
        }
        else {
            coordinatesLabel->setText("Outside\n the image");
        }
    }
    else {
        coordinatesLabel->setText("Image\n not loaded");
    }
}

void ImageViewer::returnImage() {
    selectedPixmap = pixmap;
    selected = false;
    }



void ImageViewer::saveAs()
{
    fileName = QFileDialog::getSaveFileName(this, "Image Save", "", "BMP files (*.bmp)");

    if (!fileName.isEmpty()) {
        if (loadFile) {
            if (!image.save(fileName)) {
                QMessageBox::warning(this, "warning", "File isn't save");
            }
        }
    }
}

void ImageViewer::moreInfoAboutImage() {
    if (loadFile) {

        if (selected) {
            selectedPixmap.save("selected.bmp");
            BMPImageReader f;
            selectedImgAndPixels = f.loadBMPFIle(QString("selected.bmp"),0);
            for (int i = 1; i < 5; i++) 
                selectedImgAndPixels = f.loadBMPFIle(QString("selected.bmp"), i);

            //selectedImage = *(selectedImgAndPixels->img);
            numberСolors(mathSelectedImage, selectedImgAndPixels);
            if (histogram != nullptr);
                delete histogram;
            histogram = new Histogram(mathSelectedImage, this);
            f.getFile()->close();
            remove("selected.bmp");
        }
        else {

            numberСolors(mathLoadedImage, loadedImgAndPixels);
            if (histogram != nullptr);
                delete histogram;
            histogram = new Histogram(mathLoadedImage, this);
        }
        histogram->setMinimumHeight(800);
        histogram->setMinimumWidth(900);
        histogram->setWindowTitle("Histogram");
        histogram->show();
    }
    else {
        QMessageBox::warning(this, "Warning", "The file is missing. Upload the file.");
    }
}

void ImageViewer::normalSize()
{
    if (loadFile) {
        scale = reader.getProrezh();
        view->resetTransform();
        normalSizeFlag = true;
        open();
        normalSizeFlag = false;
    }
}

void ImageViewer::fitToWindow() {
    if (loadFile) {
        if (connectScroll) {
            disconnect(view, &CustomView::signalMoveScrollBar, this, &ImageViewer::select);
        }
        view->fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio);
        connectScroll = false;
        select();
    }
}

void ImageViewer::zoomIn() {
    if ((loadFile)){
        if (scale>1&&scale <= 20) {
            if (connectScroll) {
                disconnect(view, &CustomView::signalMoveScrollBar, this, &ImageViewer::select);
            }
            QRectF visibleRect = view->mapToScene(view->viewport()->rect()).boundingRect();
            // Преобразуем его в координаты сцены
            //QRectF visibleRect2 = view->mapToScene(visibleRect).boundingRect();
            QRectF rect = visibleRect.intersected(pixmapItem->boundingRect());

            scene->removeItem(pixmapItem);
            loadedImgAndPixels = reader.select(std::max(qreal(0), rect.left()), rect.right(), std::max(qreal(0), rect.top()), rect.bottom(), 1.25, false);
            QPixmap selectedPixmap = QPixmap::fromImage(*loadedImgAndPixels->img);
            scene->setPixmap(&selectedPixmap);
            if (pixmapItem != nullptr)
                delete pixmapItem;
            pixmapItem = new QGraphicsPixmapItem(selectedPixmap);
            scene->addItem(pixmapItem);
            //view->scale(1.25, 1.25);
            scale = reader.getProrezh();

            view->setSceneRect(pixmapItem->boundingRect()); // Обновление области сцены
            connect(view, &CustomView::signalMoveScrollBar, this, &ImageViewer::select);
            connectScroll = true;
            select();
        }
        else {
            if (connectScroll) {
                disconnect(view, &CustomView::signalMoveScrollBar, this, &ImageViewer::select);
            }
            scale *= 1.25;

            view->scale(1.25, 1.25);
            view->setSceneRect(pixmapItem->boundingRect()); // Обновление области сцены
            connect(view, &CustomView::signalMoveScrollBar, this, &ImageViewer::select);
            connectScroll = true;
            select();
        }
    }
}

void ImageViewer::zoomOut() {
    if ((loadFile) && (scale < 30)) {
        if (scale >= 1 && scale < 20) {
            if (connectScroll) {
                disconnect(view, &CustomView::signalMoveScrollBar, this, &ImageViewer::select);
            }
            //view->scale(0.8, 0.8);
            scale = reader.getProrezh();

            QRectF visibleRect = view->mapToScene(view->viewport()->rect()).boundingRect();         // Преобразуем его в координаты сцены
            //QRectF visibleRect2 = view->mapToScene(visibleRect).boundingRect();
            QRectF rect = visibleRect.intersected(pixmapItem->boundingRect());
            scene->removeItem(pixmapItem);
            loadedImgAndPixels = reader.select(std::max(qreal(0), rect.left()), rect.right(), std::max(qreal(0), rect.top()), rect.bottom(), 0.8, false);
            QPixmap selectedPixmap = QPixmap::fromImage(*loadedImgAndPixels->img);
            if (pixmapItem != nullptr)
                delete pixmapItem;
            pixmapItem = new QGraphicsPixmapItem(selectedPixmap);
            scene->addItem(pixmapItem);
            scene->setPixmap(&selectedPixmap);
            view->setSceneRect(pixmapItem->boundingRect()); // Обновление области сцены

            connect(view, &CustomView::signalMoveScrollBar, this, &ImageViewer::select);
            connectScroll = true;
            select();
        }
        else {
            if (connectScroll) {
                disconnect(view, &CustomView::signalMoveScrollBar, this, &ImageViewer::select);
            }
            view->scale(0.8, 0.8);
            scale /=0.8;
            view->setSceneRect(pixmapItem->boundingRect()); // Обновление области сцены

            connect(view, &CustomView::signalMoveScrollBar, this, &ImageViewer::select);
            connectScroll = true;
            select();
        }
        //reader.select(rect.left(), rect.right(), rect.top(), rect.bottom());
    }
}

void ImageViewer::open() {
    if (!normalSizeFlag)
    fileName = QFileDialog::getOpenFileName(this, "Open Image", "", "Images (*.bmp)");
    if (connectScroll) {
        disconnect(view, &CustomView::signalMoveScrollBar, this, &ImageViewer::select);
    }
    connectScroll = false;

    if (!fileName.isEmpty()) {

        loadedImgAndPixels = reader.loadBMPFIle(fileName, 0);
        image = *(loadedImgAndPixels->img);
        if (image.isNull()) {
            coordinatesLabel->setText("Cannot load image");
            return;
        }


        if (loadFile) {
            scene->removeItem(pixmapItem);
            delete pixmapItem;
            pixmapItem = nullptr;
        }
        bool flag = false;
        reader.startSelect();
        for (int i = 1; i < 5; i++) {
            loadedImgAndPixels = reader.loadBMPFIle(fileName, i);
            image = *(loadedImgAndPixels->img);
            if (flag) {
                scene->removeItem(pixmapItem);
                delete pixmapItem;

            }
           
            pixmap = QPixmap::fromImage(image);
            pixmapItem = new QGraphicsPixmapItem(pixmap);


            scene->addItem(pixmapItem);
            flag = true;
            QCoreApplication::processEvents();
            view->setSceneRect(pixmapItem->boundingRect());
            view->fitInView(pixmapItem, Qt::KeepAspectRatio);

        }

        scene->setPixmap(&pixmap);
        selectedPixmap = pixmap;

            loadFile = true;
            scale = reader.getProrezh();
    }
}
void ImageViewer::numberСolors(MathImage* mathImage, Returned* imgAndPixels) {

    if (loadFile == true) {

            mathImage->averageColorsPixels[1] = 0;
            mathImage->averageColorsPixels[2] = 0;
            mathImage->averageColorsPixels[3] = 0;
            mathImage->squareAverageColorsPixels[1] = 0;
            mathImage->squareAverageColorsPixels[2] = 0;
            mathImage->squareAverageColorsPixels[3] = 0;
            mathImage->sumNumbersPixels[1] = 0;
            mathImage->sumNumbersPixels[2] = 0;
            mathImage->sumNumbersPixels[3] = 0;
            mathImage->numbersPixel[1] = &imgAndPixels->numbers->rgbNumbersBlue;
            mathImage->numbersPixel[2] = &imgAndPixels->numbers->rgbNumbersRed;
            mathImage->numbersPixel[3] = &imgAndPixels->numbers->rgbNumbersGreen;
            mathImage->maxNumbersPixels[1] = 0;
            mathImage->maxNumbersPixels[2] = 0;
            mathImage->maxNumbersPixels[3] = 0;
            for (int i = 1; i < 256; i++) {


                // Синий
                if ((*mathImage->numbersPixel[1])[i] > mathImage->maxNumbersPixels[1]) {
                    mathImage->maxNumbersPixels[1] = (*mathImage->numbersPixel[1])[i];
                }
                mathImage->averageColorsPixels[1] += (*mathImage->numbersPixel[1])[i] * i;
                mathImage->squareAverageColorsPixels[1] += (*mathImage->numbersPixel[1])[i] * i * i;
                mathImage->sumNumbersPixels[1] += (*mathImage->numbersPixel[1])[i];

                // Красный
                if ((*mathImage->numbersPixel[3])[i] > mathImage->maxNumbersPixels[3]) {
                    mathImage->maxNumbersPixels[3] = (*mathImage->numbersPixel[3])[i];
                };
                mathImage->averageColorsPixels[3] += (*mathImage->numbersPixel[3])[i] * i;
                mathImage->squareAverageColorsPixels[3] += ((*mathImage->numbersPixel[3])[i] * i * i);
                mathImage->sumNumbersPixels[3] += (*mathImage->numbersPixel[3])[i];
                // Зелёный
                if ((*mathImage->numbersPixel[2])[i] > mathImage->maxNumbersPixels[2]) {
                    mathImage->maxNumbersPixels[2] = (*mathImage->numbersPixel[2])[i];
                };
                mathImage->averageColorsPixels[2] += (*mathImage->numbersPixel[2])[i] * i;
                mathImage->squareAverageColorsPixels[2] += ((*mathImage->numbersPixel[2])[i] * i * i);
                mathImage->sumNumbersPixels[2] += (*mathImage->numbersPixel[2])[i];
            }
            //синий
            mathImage->averageColorsPixels[1] /= mathImage->sumNumbersPixels[1];
            mathImage->squareAverageColorsPixels[1] /= mathImage->sumNumbersPixels[1];
            mathImage->squareDeviation[1] = sqrt(mathImage->squareAverageColorsPixels[1] - mathImage->averageColorsPixels[1] * mathImage->averageColorsPixels[1]);
            //красный
            mathImage->averageColorsPixels[3] /= mathImage->sumNumbersPixels[3];
            mathImage->squareAverageColorsPixels[3] /= mathImage->sumNumbersPixels[3];
            mathImage->squareDeviation[3] = sqrt(mathImage->squareAverageColorsPixels[3] - mathImage->averageColorsPixels[3] * mathImage->averageColorsPixels[3]);
            //зелёный
            mathImage->averageColorsPixels[2] /= mathImage->sumNumbersPixels[2];
            mathImage->squareAverageColorsPixels[2] /= mathImage->sumNumbersPixels[2];
            mathImage->squareDeviation[2] = sqrt(mathImage->squareAverageColorsPixels[2] - mathImage->averageColorsPixels[2] * mathImage->averageColorsPixels[2]);


        
    }
}
#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QPixmap>
#include <QLabel>
#include <QVBoxLayout>
#include <QRubberBand>
#ifdef WIN32
#include <QtPlugin>
Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin);
#endif
// Объявление метода ShowSelectedArea
void ShowSelectedArea(const QPixmap& pixmap);

class ImageWidget : public QLabel
{


public:
    ImageWidget(QWidget* parent = nullptr)
        : QLabel(parent), rubberBand_(nullptr)
    {
        setScaledContents(true);
    }

    void setImage(const QString& path)
    {
        pixmap_.load(path);
        setPixmap(pixmap_.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }

protected:
    void mousePressEvent(QMouseEvent* event) override
    {
        if (event->button() == Qt::LeftButton) {
            startPoint_ = event->pos();
            rubberBand_ = new QRubberBand(QRubberBand::Rectangle, this);
            rubberBand_->setGeometry(QRect(startPoint_, QSize()));
            rubberBand_->show();
        }
    }

    void mouseMoveEvent(QMouseEvent* event) override
    {
        if (rubberBand_) {
            rubberBand_->setGeometry(QRect(startPoint_, event->pos()).normalized());
        }
    }

    void mouseReleaseEvent(QMouseEvent* event) override
    {
        if (event->button() == Qt::LeftButton && rubberBand_) {
            rubberBand_->hide();
            QRect selectedRect = rubberBand_->geometry();
            QPixmap selectedPixmap = pixmap_.copy(selectedRect);
            ShowSelectedArea(selectedPixmap);
            rubberBand_->deleteLater();
            rubberBand_ = nullptr;
        }
    }

private:
    QPixmap pixmap_;
    QPoint startPoint_;
    QRubberBand* rubberBand_;
};

// Определение метода ShowSelectedArea
void ShowSelectedArea(const QPixmap& pixmap)
{
    QWidget* window = new QWidget;
    window->setWindowTitle("Выделенная область");
    window->resize(800, 600); // Размер окна

    QLabel* label = new QLabel(window);
    label->setPixmap(pixmap.scaled(800, 600, Qt::KeepAspectRatio)); // Масштабируем pixmap
    label->setGeometry(0, 0, 800, 600);

    window->show();
}

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    QWidget window;
    QVBoxLayout* layout = new QVBoxLayout(&window);
    ImageWidget* imageWidget = new ImageWidget();

    imageWidget->setImage(":/open.png"); // Укажите путь к вашему изображению
    layout->addWidget(imageWidget);

    window.setWindowTitle("Image Selection Example");
    window.resize(800, 600);
    window.show();

    return app.exec();
}


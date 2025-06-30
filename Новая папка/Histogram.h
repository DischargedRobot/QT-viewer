#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <iostream>
struct MathImage {
    std::map<unsigned int, float> averageColorsPixels;
    std::map<unsigned int, float> squareAverageColorsPixels;
    std::map<unsigned int, unsigned int> sumNumbersPixels;
    std::map<unsigned int, std::map<int, unsigned int>*> numbersPixel;
    std::map<int, unsigned int> maxNumbersPixels;
    std::map<unsigned int, float> squareDeviation;
};
class Histogram : public QMainWindow 
{

public:
    MathImage* math;
    Histogram(MathImage* maths, QMainWindow* parent=nullptr) :  math(maths), QMainWindow(parent){}
       

protected:
    void paintEvent(QPaintEvent* event) {
        Q_UNUSED(event);
        
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        float koefWidth = (float)this->width() / 900;
        int maxBarHeight = 170;
        float barWidth = 3 * koefWidth;
        std::map<int, QColor> colors;
        colors[1] = Qt::blue;
        colors[2] = Qt::green;
        colors[3] = Qt::red;
        for (int j = 1; j <= 3; j++){
            int y = 230*j;
            unsigned int indent = QString("%1").arg(math->maxNumbersPixels[j]).size() * 3 + 30;
            for (int i = 1; i < 256; i++) {
                float procentotmaximumaheight = (float)(*math->numbersPixel[j])[i] / (math->maxNumbersPixels[j]);
                float barHeight = maxBarHeight * procentotmaximumaheight;
                float x = i * barWidth + indent;

               
                painter.fillRect(x, y, barWidth, -barHeight, colors[j]);
            painter.drawText(20, y + 30, QString("Average pixel brightness value: %1 square deviation: %2 number of pixels: %3").arg(math->averageColorsPixels[j]).arg(math->squareDeviation[j]).arg(math->sumNumbersPixels[j]));
            //painter.drawText(20, y + 20, QString("Average pixels: %1 square deviation: %2").arg(math->averageColorsPixels[j]).arg(math->squareDeviation[j]));
            painter.drawLine(barWidth + indent, y , barWidth * 256 + indent, y);
            //painter.drawText(, QString("255"));
            painter.drawText(barWidth * 256 + indent, y + 15, QString("255"));
            painter.drawText((barWidth * 256 + indent)*4/5, y + 15, QString("204"));
            painter.drawText((barWidth * 256 + indent) * 3 / 5, y + 15, QString("153"));
            painter.drawText((barWidth * 256 + indent) * 2 / 5, y + 15, QString("102"));
            painter.drawText((barWidth * 256 + indent) * 1 / 5, y + 15, QString("51"));
            painter.drawText(barWidth + indent, y + 15, QString("1"));
            //
            painter.drawLine(barWidth + indent, y, barWidth + indent, y - 180);
            painter.drawText(QRect(QPoint(barWidth, y - 180), QSize(barWidth + indent-5, indent)), Qt::AlignRight, QString("%1").arg(math->maxNumbersPixels[j]));
            painter.drawText(QRect(QPoint(barWidth, y - 180 * 4 / 5), QSize(barWidth + indent-5, indent)), Qt::AlignRight, QString("%1").arg(math->maxNumbersPixels[j]*4/5));
            painter.drawText(QRect(QPoint(barWidth, y - 180 * 3 / 5), QSize(barWidth + indent - 5, indent)), Qt::AlignRight, QString("%1").arg(math->maxNumbersPixels[j]*3/5));
            painter.drawText(QRect(QPoint(barWidth, y - 180 * 2 / 5), QSize(barWidth + indent - 5, indent)), Qt::AlignRight, QString("%1").arg(math->maxNumbersPixels[j]*2/5));
            painter.drawText(QRect(QPoint(barWidth, y - 180  / 5), QSize(barWidth + indent - 5, indent)), Qt::AlignRight, QString("%1").arg(math->maxNumbersPixels[j]/5));
            painter.drawText(QRect(QPoint(barWidth, y - 10), QSize(barWidth + indent - 5, indent)), Qt::AlignRight, QString("0"));
            }
        }
    }
};


#include <string>
#include <fstream>
#include <cstdint>
#include <QApplication>
#include <QWidget>
#include <QMouseEvent>
#include <QObject>
#include <QMenu>
#include <QAction>
#include <QMenuBar>
#include <QLabel>
#include <QMessageBox>
#include <iostream>
#include <QImage>
#include <QFileDialog>
#include <map>
// структура заголовка
struct RGBnumber {
    std::map<int, unsigned int> rgbNumbersBlue;
    std::map<int, unsigned int> rgbNumbersGreen;
    std::map<int, unsigned int> rgbNumbersRed;
};
struct Returned {
    QImage* img;
    RGBnumber* numbers;
};
class BMPImageReader {
    #pragma pack(push, 1)
    typedef struct BMPHeader {
        unsigned char format[2];
        unsigned int file_size;
        unsigned char unused[4];
        unsigned int pixel_offset;
    } BMPHeader;

    //структура информационной части
    typedef struct INFHeader {
        unsigned int beader_size;
        unsigned int width;
        unsigned int height;
        unsigned short color_planes;
        unsigned short bits_per_pixel;
        unsigned int compression;
        unsigned int data_size;
        unsigned int pwidth;
        unsigned int pheight;
        unsigned int colors_count;
        unsigned int imp_colors_count;
    } INFHeader;

    typedef struct RGB
    {
        unsigned char rgbBlue;
        unsigned char rgbGreen;
        unsigned char rgbRed;
    } RGB;

    // структура файла
    typedef struct BMPFile {
        BMPHeader bhdr;
        INFHeader infohdr;
    } BMPFile;
    #pragma pack(pop)
    public:
        ;
    // загрузка файла
    Returned* loadBMPFIle(const QString& file_name) {
        RGBnumber* rgbNumbers = new RGBnumber;
        BMPFile* bmp_file = (BMPFile*)malloc(sizeof(BMPFile));
        QFile file(file_name);
        file.open(QIODevice::ReadOnly);
        file.read(reinterpret_cast<char*>(&bmp_file->bhdr), sizeof(BMPHeader));
        file.read(reinterpret_cast<char*>(&bmp_file->infohdr), sizeof(INFHeader));
        
        int row_size = ((bmp_file->infohdr.bits_per_pixel * bmp_file->infohdr.width + 31) / 32) * 4;
        unsigned int width = bmp_file->infohdr.width;
        unsigned int height = bmp_file->infohdr.height;
        QImage* image = new QImage(width, height, QImage::Format_RGB888);

        if (image == nullptr) {
            free(bmp_file);
            file.close();
            //return nullptr;
        }
        for (int i = 1; i < 256; i++) {
            rgbNumbers->rgbNumbersBlue[i] = 0;
            rgbNumbers->rgbNumbersGreen[i] = 0;
            rgbNumbers->rgbNumbersRed[i] = 0;
        }
        file.seek(bmp_file->bhdr.pixel_offset);
        unsigned char* temp_buffer = (unsigned char*)malloc(row_size);
        for (int y = height-1; y >= 0; --y) {
            file.read(reinterpret_cast<char*>(temp_buffer), row_size);
            for (int x = width-1; x >= 0; --x) {
                RGB* rgb = (RGB*)(temp_buffer + x * 3);
                rgbNumbers->rgbNumbersBlue[rgb->rgbBlue] += 1;
                rgbNumbers->rgbNumbersGreen[rgb->rgbGreen] += 1;
                rgbNumbers->rgbNumbersRed[rgb->rgbRed] += 1;
                image->setPixelColor(x, y, QColor(rgb->rgbRed, rgb->rgbGreen, rgb->rgbBlue));
            }
        }
        Returned* returned = new Returned();
        returned->img = image;
        returned->numbers = rgbNumbers;
        file.close();
        free(temp_buffer);
        free(bmp_file);
        return returned;
    };

};

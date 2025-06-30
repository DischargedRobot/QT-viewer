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
        uint8_t  format[2];
        uint32_t  file_size;
        uint8_t  unused[4];
        uint32_t  pixel_offset;
    } BMPHeader;

    //структура информационной части
    typedef struct INFHeader {
        uint32_t  beader_size;
        int32_t    width;
        int32_t    height;
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
    private:
        int width;
        int height;
        //QFile file;
        QFile* file;
        RGBnumber* rgbNumbers;
        QImage* image = nullptr;
        BMPFile* bmp_file;
        Returned* returned;
        int prorezh;
        float prorezhF;
        int prorezhOld;
        int prorezhStart;
        int xStartSelect = 0;
        int yStartSelect = 0;
        unsigned int widthSelect;
        unsigned int heightSelect;
        bool loadFile = false;
    public:
        ;
    // загрузка файла
    Returned* loadBMPFIle(const QString& file_name, int section) {
        if (section == 0) {
            if (loadFile)
                delete rgbNumbers;
            rgbNumbers = new RGBnumber;
            bmp_file = (BMPFile*)malloc(sizeof(BMPFile));
            if (loadFile)
                delete file;
            file = new QFile(file_name);
            file->open(QIODevice::ReadOnly);
            file->read(reinterpret_cast<char*>(&bmp_file->bhdr), sizeof(BMPHeader));
            file->read(reinterpret_cast<char*>(&bmp_file->infohdr), sizeof(INFHeader));
            width = abs(bmp_file->infohdr.width);
            height = abs(bmp_file->infohdr.height);
            prorezh = std::max(std::min((int(width * height) / (1920 * 1080)),20), 1);
            prorezhStart = prorezh;
            prorezhOld = prorezh;
            prorezhF = prorezh;
            if (image != nullptr)
                delete image;
            image = new QImage(width/ prorezh, height/prorezh, QImage::Format_RGB888);
            if (image == nullptr) {
                free(bmp_file);
                file->close();

            }

            for (int i = 1; i < 256; i++) {
                rgbNumbers->rgbNumbersBlue[i] = 0;
                rgbNumbers->rgbNumbersGreen[i] = 0;
                rgbNumbers->rgbNumbersRed[i] = 0;
            }
            //int prorezh = 1;
            file->seek(bmp_file->bhdr.pixel_offset);
        }
        if (section < 5)
            load(section, file);
            
        if (loadFile)
            delete returned;
        returned = new Returned();
        returned->img = image;
        returned->numbers = rgbNumbers;
        loadFile = true;

        return returned;
    };
    QFile* getFile() {
        return file;
    }
    void load(int section, QFile* file) {
        section = abs(section - 4);
        prorezh = std::max(std::min((int(width * height) / (1920 * 1080)), 20), 1);
        prorezhStart = prorezh;

        int row_size = ((bmp_file->infohdr.bits_per_pixel * bmp_file->infohdr.width + 31) / 32) * 4;
        unsigned char* temp_buffer = (unsigned char*)malloc(row_size);
        if (bmp_file->infohdr.height < 0) {
            for (int y = (float(height - prorezh) / 5) * (section + 1); y >= int((float(height - prorezh) / 5) * section); y -= prorezh) {
                if (prorezh > 1)
                    file->seek(bmp_file->bhdr.pixel_offset + row_size * (height - prorezh - y));

                file->read(reinterpret_cast<char*>(temp_buffer), row_size);
                for (int x = 0; x <= (width - prorezh); x += prorezh) {
                    RGB* rgb = (RGB*)(temp_buffer + x * 3);
                    rgbNumbers->rgbNumbersBlue[rgb->rgbBlue] += 1;
                    rgbNumbers->rgbNumbersGreen[rgb->rgbGreen] += 1;
                    rgbNumbers->rgbNumbersRed[rgb->rgbRed] += 1;
                    image->setPixelColor(x / prorezh, (height - y) / prorezh, QColor(rgb->rgbRed, rgb->rgbGreen, rgb->rgbBlue));
                }

            }
        }
        else {
            for (int y = (float(height - prorezh) / 5) * (section + 1); y >= int((float(height - prorezh) / 5) * section); y -= prorezh) {
                if (prorezh > 1)
                    file->seek(bmp_file->bhdr.pixel_offset + row_size * (height - prorezh - y));

                file->read(reinterpret_cast<char*>(temp_buffer), row_size);
                for (int x = 0; x <= (width - prorezh); x += prorezh) {
                    RGB* rgb = (RGB*)(temp_buffer + x * 3);
                    rgbNumbers->rgbNumbersBlue[rgb->rgbBlue] += 1;
                    rgbNumbers->rgbNumbersGreen[rgb->rgbGreen] += 1;
                    rgbNumbers->rgbNumbersRed[rgb->rgbRed] += 1;
                    image->setPixelColor(x / prorezh, y / prorezh, QColor(rgb->rgbRed, rgb->rgbGreen, rgb->rgbBlue));
                }

            }
        }
    }
    void startSelect() {

        prorezh = prorezhStart;

    }
    int getProrezh() {
        return prorezh;
    }
    Returned* select(int xStart, int xEnd, int yStart, int yEnd, float scaleFactor, bool scroll) {

        if (!scroll) {
            //widthSelect = (abs(xEnd - xStart) * prorezh);
            //heightSelect = (abs(yEnd - yStart) * prorezh);

            prorezhF = std::max(prorezhF / scaleFactor, float(1));
            if (ceil(prorezhF) == 20) {
                xEnd = width / 20;
                yEnd = height / 20;
            }
            widthSelect = std::min(int(abs(xEnd - xStart) * prorezh), int(width));
            heightSelect = std::min(int(abs(yEnd - yStart) * prorezh), int(height));
            xStartSelect = std::min(xStart, xEnd) * prorezh;
            yStartSelect = height - std::max(yStart, yEnd) * prorezh;
            prorezh = std::max(int(floor(prorezhF)), 1);




            delete image; // необходимо вызвать этот код в деструкторе или другом методе для освобождения

            image = new QImage(width / prorezh, height / prorezh, QImage::Format_RGB888);
            int row_size = ((bmp_file->infohdr.bits_per_pixel * bmp_file->infohdr.width + 31) / 32) * 4;
            int row_size_select = ((bmp_file->infohdr.bits_per_pixel * (widthSelect)+31) / 32) * 4;
            unsigned char* temp_buffer = (unsigned char*)malloc(row_size_select);
            if (bmp_file->infohdr.height < 0) {
                int parent_rejection = row_size * (std::min(yStart, yEnd) * prorezhOld)+xStartSelect * 3;

                for (int y = heightSelect - prorezh; y >= 0; y -= prorezh) {
                    if (prorezh >= 1)
                        file->seek(bmp_file->bhdr.pixel_offset + parent_rejection + row_size * (y));

                    file->read(reinterpret_cast<char*>(temp_buffer), row_size_select);

                    for (int x = widthSelect - prorezh; x >= 0; x -= prorezh) {
                        RGB* rgb = (RGB*)(temp_buffer + x * 3);

                        image->setPixelColor(xStartSelect / prorezh + x / prorezh, std::min(yStart, yEnd) * prorezhOld / prorezh + y / prorezh, QColor(rgb->rgbRed, rgb->rgbGreen, rgb->rgbBlue));
                    }

                }
            }
            else {
                int parent_rejection = row_size * (yStartSelect)+xStartSelect * 3;

                for (int y = heightSelect - prorezh; y >= 0; y -= prorezh) {
                    if (prorezh >= 1)
                        file->seek(bmp_file->bhdr.pixel_offset + parent_rejection + row_size * (heightSelect - prorezh - y));

                    file->read(reinterpret_cast<char*>(temp_buffer), row_size_select);

                    for (int x = widthSelect - prorezh; x >= 0; x -= prorezh) {
                        RGB* rgb = (RGB*)(temp_buffer + x * 3);

                        image->setPixelColor(xStartSelect / prorezh + x / prorezh, std::min(yStart, yEnd) * prorezhOld / prorezh + y / prorezh, QColor(rgb->rgbRed, rgb->rgbGreen, rgb->rgbBlue));
                    }

                }
            }
            prorezhOld = prorezh;

            if (loadFile)
                delete returned;
            returned = new Returned();
            returned->img = image;
            returned->numbers = rgbNumbers;


            return returned;
        }
        else {
            
            if (round(prorezhF) > 20) {
                xEnd = width / 20;
                yEnd = height / 20;
            }
            widthSelect = std::min(int(abs(xEnd - xStart) * prorezh), int(width));
            heightSelect = std::min(int(abs(yEnd - yStart) * prorezh), int(height));
            xStartSelect = std::min(xStart, xEnd) * prorezh;
            yStartSelect = height - std::max(yStart, yEnd) * prorezh;

            int row_size = ((bmp_file->infohdr.bits_per_pixel * bmp_file->infohdr.width + 31) / 32) * 4;
            int row_size_select = ((bmp_file->infohdr.bits_per_pixel * (widthSelect)+31) / 32) * 4;
            unsigned char* temp_buffer = (unsigned char*)malloc(row_size_select);
            int parent_rejection = row_size * (yStartSelect)+xStartSelect * 3;
            if (bmp_file->infohdr.height < 0) {
                int parent_rejection = row_size * (std::min(yStart, yEnd) * prorezhOld) + xStartSelect * 3;

                for (int y = heightSelect - prorezh; y >= 0; y -= prorezh) {
                    if (prorezh >= 1)
                        file->seek(bmp_file->bhdr.pixel_offset + parent_rejection + row_size * (y));

                    file->read(reinterpret_cast<char*>(temp_buffer), row_size_select);

                    for (int x = widthSelect - prorezh; x >= 0; x -= prorezh) {
                        RGB* rgb = (RGB*)(temp_buffer + x * 3);

                        image->setPixelColor(xStartSelect / prorezh + x / prorezh, std::min(yStart, yEnd) * prorezhOld / prorezh + y / prorezh, QColor(rgb->rgbRed, rgb->rgbGreen, rgb->rgbBlue));
                    }

                }
            }
            else {
                int parent_rejection = row_size * (yStartSelect)+xStartSelect * 3;

                for (int y = heightSelect - prorezh; y >= 0; y -= prorezh) {
                    if (prorezh >= 1)
                        file->seek(bmp_file->bhdr.pixel_offset + parent_rejection + row_size * (heightSelect - prorezh - y));

                    file->read(reinterpret_cast<char*>(temp_buffer), row_size_select);

                    for (int x = widthSelect - prorezh; x >= 0; x -= prorezh) {
                        RGB* rgb = (RGB*)(temp_buffer + x * 3);

                        image->setPixelColor(xStartSelect / prorezh + x / prorezh, std::min(yStart, yEnd) * prorezhOld / prorezh + y / prorezh, QColor(rgb->rgbRed, rgb->rgbGreen, rgb->rgbBlue));
                    }

                }
            }
            if (loadFile)
                delete returned;
            returned = new Returned();
            returned->img = image;
            returned->numbers = rgbNumbers;


            return returned;
        }
    } 

};

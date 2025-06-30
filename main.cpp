#include "main.h"

int main(int argc, char* argv[]) {
    Q_INIT_RESOURCE(images);
    QApplication app(argc, argv);
    app.setAttribute(Qt::AA_DontCreateNativeWidgetSiblings);
    ImageViewer* dialog = new ImageViewer;
    dialog->setMinimumHeight(600);
    dialog->setMinimumWidth(800);
    dialog->show();

    return app.exec();
}
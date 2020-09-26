#include "filedialog.h"
#include <QApplication>
#include <QtDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FileDialog w;

    if (w.exec() == QDialog::Accepted)
        qDebug() << w.selectFiles();


    return 0;
}

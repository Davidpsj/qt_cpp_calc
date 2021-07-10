#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "Calc_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;

    w.setWindowState(
                w.windowState() &
                (~Qt::WindowMaximized | Qt::WindowActive)
    );

    Qt::WindowFlags windowFlags = (Qt::Dialog | Qt::CustomizeWindowHint);

    if (true) {
        windowFlags |= Qt::WindowCloseButtonHint;
    } else {
        windowFlags |= Qt::WindowMinimizeButtonHint;
        windowFlags |= Qt::WindowCloseButtonHint;
    }

    w.setWindowFlags(windowFlags);

    w.show();
    return a.exec();
}

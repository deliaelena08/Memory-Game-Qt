#include <QApplication>
#include "memorygame.h"

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    MemoryGame window;
    window.show();
    return a.exec();
}

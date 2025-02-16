#ifndef MEMORYGAME_H
#define MEMORYGAME_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QGridLayout>
#include <QMessageBox>
#include <QStringList>
#include <QDebug>
#include <algorithm>
#include <QRandomGenerator>
#include <QVector>
#include <QTimer>
#include <random>
#include <iostream>

class MemoryGame : public QWidget {
    Q_OBJECT

public:
    MemoryGame(QWidget* parent = nullptr);

private slots:
    void handleTileClick();
    void startNewGame();
    void addToHallOfFame();

private:
    void initializeGame();
    void resetGame();
    void checkForMatch();

    QVector<QPushButton*> tiles;
    QVector<int> tileValues;
    QPushButton* firstTile;
    QPushButton* secondTile;
    int clickCount;
    int matches;
    QLabel* clickLabel;
    QLabel* statusLabel;
    QLineEdit* nameInput;
    QListWidget* hallOfFame;
    QPushButton* newGameButton;
};

#endif // MEMORYGAME_H

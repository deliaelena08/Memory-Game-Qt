#include "memorygame.h"
#include <random>
#include <QApplication>

using namespace std;

MemoryGame::MemoryGame(QWidget* parent) : QWidget(parent), firstTile(nullptr), secondTile(nullptr), clickCount(0), matches(0) {
    // Initialize widgets
    clickLabel = new QLabel("Clicks: 0");
    statusLabel = new QLabel("Keep guessing...");
    nameInput = new QLineEdit;
    hallOfFame = new QListWidget;
    newGameButton = new QPushButton("New Game");

    // Create grid layout for tiles
    QGridLayout* gridLayout = new QGridLayout();
    for (int i = 0; i < 10; ++i) {
        QPushButton* tile = new QPushButton();
        tile->setFixedSize(50, 50);
        gridLayout->addWidget(tile, i / 5, i % 5);
        tiles.append(tile);
        connect(tile, &QPushButton::clicked, this, &MemoryGame::handleTileClick);
    }

    // Layouts for other UI elements
    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addWidget(clickLabel);
    mainLayout->addLayout(gridLayout);
    mainLayout->addWidget(statusLabel);
    mainLayout->addWidget(new QLabel("Enter your name:"));
    mainLayout->addWidget(nameInput);
    mainLayout->addWidget(new QLabel("Hall of Fame:"));
    mainLayout->addWidget(hallOfFame);
    mainLayout->addWidget(newGameButton);

    setLayout(mainLayout);
    setWindowTitle("Memory Game");

    // Connect signals and slots
    connect(newGameButton, &QPushButton::clicked, this, &MemoryGame::startNewGame);
    connect(nameInput, &QLineEdit::returnPressed, this, &MemoryGame::addToHallOfFame);

    initializeGame();
}

void MemoryGame::initializeGame() {
    tileValues.resize(10);
    for (int i = 0; i < 5; ++i) {
        tileValues[i] = i;
        tileValues[i + 5] = i;
    }
    random_device rd;
    mt19937 g(rd());
    shuffle(tileValues.begin(), tileValues.end(), g);
    resetGame();
}

void MemoryGame::resetGame() {
    for (auto tile : tiles) {
        tile->setText("");
        tile->setEnabled(true);
    }
    firstTile = nullptr;
    secondTile = nullptr;
    clickCount = 0;
    matches = 0;
    clickLabel->setText("Clicks: 0");
    statusLabel->setText("Keep guessing...");
}

void MemoryGame::handleTileClick() {
    QPushButton* clickedTile = qobject_cast<QPushButton*>(sender());
    if (!clickedTile || clickedTile == firstTile) return;

    int index = tiles.indexOf(clickedTile);
    clickedTile->setText(QString::number(tileValues[index]));
    clickedTile->setEnabled(false);

    if (!firstTile) {
        firstTile = clickedTile;
    }
    else {
        secondTile = clickedTile;
        ++clickCount;
        clickLabel->setText(QString("Clicks: %1").arg(clickCount));
        checkForMatch();
    }
}

void MemoryGame::checkForMatch() {
    int firstIndex = tiles.indexOf(firstTile);
    int secondIndex = tiles.indexOf(secondTile);
    if (tileValues[firstIndex] == tileValues[secondIndex]) {
        ++matches;
        if (matches == 5) {
            statusLabel->setText("You won!");
        }
        else {
            statusLabel->setText("Match found! Keep guessing...");
        }
        firstTile = nullptr;
        secondTile = nullptr;
    }
    else {
        statusLabel->setText("No match. Try again...");
        QTimer::singleShot(1000, [this]() {
            firstTile->setText("");
            secondTile->setText("");
            firstTile->setEnabled(true);
            secondTile->setEnabled(true);
            firstTile = nullptr;
            secondTile = nullptr;
            });
    }
}

void MemoryGame::startNewGame() {
    initializeGame();
}

void MemoryGame::addToHallOfFame() {
    QString name = nameInput->text();
    if (!name.isEmpty() && matches == 5) {
        hallOfFame->addItem(QString("%1 - %2 clicks").arg(name).arg(QString::number(clickCount)));
        nameInput->clear();
    }
}

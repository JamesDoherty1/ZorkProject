#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    game(new ZorkUL)
{
    ui->setupUi(this);

    connect(game, &ZorkUL::requestUserInput, this, &MainWindow::handleUserInputRequest);
    connect(game, &ZorkUL::setImage, this, &MainWindow::displayImage);
    connect(game, &ZorkUL::closeGameWindow, this, &MainWindow::onCloseGameWindow);
    connect(game, &ZorkUL::secondMessage, this, &MainWindow::displaySecondMessage);
    connect(game, &ZorkUL::firstMessage, this, &MainWindow::displayFirstMessage);
    connect(game, &ZorkUL::topMessage, this, &MainWindow::displayTopMessage);
    connect(game, &ZorkUL::scoreMessage, this, &MainWindow::displayScoreMessage);

    connect(ui->lineEdit, &QLineEdit::returnPressed, this, &MainWindow::processCommand);
    game->printWelcome();

    connect(ui->northButton, &QPushButton::clicked, this, &MainWindow::goNorth);
    connect(ui->southButton, &QPushButton::clicked, this, &MainWindow::goSouth);
    connect(ui->eastButton, &QPushButton::clicked, this, &MainWindow::goEast);
    connect(ui->westButton, &QPushButton::clicked, this, &MainWindow::goWest);
    connect(ui->takeButton, &QPushButton::clicked, this, &MainWindow::takeItem);
    connect(ui->actionButton, &QPushButton::clicked, this, &MainWindow::doAction);
}

MainWindow::~MainWindow() {
    delete ui;
    delete game;
}

void MainWindow::handleUserInputRequest(const QString& prompt) {
    ui->statusbar->showMessage(prompt);
    ui->lineEdit->clear();
    ui->lineEdit->setFocus();
}

void MainWindow::processCommand() {
    QString input = ui->lineEdit->text();
    if (!input.isEmpty()) {
        bool finished = game->update(input.toStdString());
        if (finished) {
            close();
        }
        ui->lineEdit->clear();
    }
}

void MainWindow::displaySecondMessage(const QString& message) {
    ui->label->setText(message);
}

void MainWindow::displayFirstMessage(const QString& message) {
    ui->label_2->setText(message);
}

void MainWindow::displayTopMessage(const QString& message) {
    ui->label_3->setText(message);
}

void MainWindow::displayScoreMessage(const QString& message) {
    ui->label_4->setText(message);
}

void MainWindow::displayImage(const QString& imageName) {
    QPixmap image("C:\\Users\\jkdoh\\QTProjects\\ZorkGame\\Images\\" + imageName + ".jpg");
    int w = ui->label_5->width();
    int h = ui->label_5->height();
    QPixmap scaledImage = image.scaled(w, h, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_5->setPixmap(scaledImage);
}

void MainWindow::onCloseGameWindow() {
    QApplication::quit();
}

void MainWindow::goNorth() {
    game->goRoom(Command("go", "north"));
    ui->lineEdit->setFocus();
}

void MainWindow::goSouth() {
    game->goRoom(Command("go", "south"));
    ui->lineEdit->setFocus();
}

void MainWindow::goEast() {
    game->goRoom(Command("go", "east"));
    ui->lineEdit->setFocus();
}

void MainWindow::goWest() {
    game->goRoom(Command("go", "west"));
    ui->lineEdit->setFocus();
}

void MainWindow::takeItem() {
    game->takeItem(game->getCurrentItem());
    ui->lineEdit->setFocus();
}
void MainWindow::doAction() {
    game->performAction();
    ui->lineEdit->setFocus();
}

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "AddAircraftDialog.h"
#include "src/CargoAircraft.h"
#include "src/WideBodyAircraft.h"
#include "src/NarrowBodyAircraft.h"
#include <QDebug>
#include "QMessageBox"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow), myAirline("Название", "Страна", 2026)
{
    ui->setupUi(this);
    ui->aircraftList->setWordWrap(true);
    connect(ui->btnAdd, &QPushButton::clicked, this, &MainWindow::on_btnAdd_clicked);
    connect(ui->btnClear, &QPushButton::clicked, this, &MainWindow::on_btnClear_clicked);
    connect(ui->btnDel, &QPushButton::clicked, this, &MainWindow::on_btnDel_clicked);

    this->setWindowTitle("AirlineApp");
}


void MainWindow::updateList() {
    ui->aircraftList->clear();
    for (auto plane : myAirline.GetFleet()) {
        QString info = formatAircraftInfo(plane);
        ui->aircraftList->addItem(info);
    }
}

QString MainWindow::formatAircraftInfo(Aircraft* plane) const {
    QString info = QString("Модель: %1 | Скор: %2 | Дальн: %3")
                       .arg(QString::fromStdString(plane->GetModel()))
                       .arg(plane->GetMaxSpeed())
                       .arg(plane->GetRange());

    if (auto cargo = dynamic_cast<CargoAircraft*>(plane)) {
        info += QString(" | [Грузовой] Вес: %1 кг, Объем: %2 м3")
                    .arg(cargo->GetMaxCargoWeight())
                    .arg(cargo->GetCargoVolumeCapacity());
    }
    else if (auto wide = dynamic_cast<WideBodyAircraft*>(plane)) {
        info += QString(" | [Широкофюзеляжный] Пасс: %1, Экипаж: %2, Палубы: %3, Мест 1-го класса: %4")
                    .arg(wide->GetPassengerCapacity())
                    .arg(wide->GetCabinCrewCount())
                    .arg(wide->GetDeckCount())
                    .arg(wide->GetFirstClassSeats());
    }
    else if (auto narrow = dynamic_cast<NarrowBodyAircraft*>(plane)) {
        info += QString(" | [Узкофюзеляжный] Пасс: %1, Экипаж: %2, Проходы: %3, Бизнес: %4")
                    .arg(narrow->GetPassengerCapacity())
                    .arg(narrow->GetCabinCrewCount())
                    .arg(narrow->GetAisleCount())
                    .arg(narrow->GetHasBusinessClass() ? "Да" : "Нет");
    }

    return info;
}


void MainWindow::updateTotalCapacity() {
    int total = 0;
    for (auto plane : myAirline.GetFleet()) {
        if (auto passPlane = dynamic_cast<PassengerAircraft*>(plane)) {
            total += passPlane->GetPassengerCapacity();
        }
    }
    ui->labelTotalCapacity->setText("Общая вместимость: " + QString::number(total));
}


void MainWindow::on_btnAdd_clicked() {
    AddAircraftDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        Aircraft* newPlane = dialog.createAircraft();
        if (newPlane) {
            myAirline.AddAircraft(newPlane);
            updateList();
            updateTotalCapacity();
        }
    }
}


void MainWindow::on_btnClear_clicked() {
    for (auto plane : myAirline.GetFleet()) {
        delete plane;
    }
    ui->aircraftList->clear();
}


void MainWindow::on_btnDel_clicked() {
    int currentRow = ui->aircraftList->currentRow();

    if (currentRow < 0) {
        QMessageBox::warning(this, "Внимание", "Выберите самолет для удаления!");
        return;
    }

    myAirline.RemoveAircraft(currentRow);

    updateList();
    updateTotalCapacity();
}


MainWindow::~MainWindow() {
    delete ui;
}
#include "AddAircraftDialog.h"
#include "ui_AddAircraftDialog.h"
#include "src/CargoAircraft.h"
#include "src/WideBodyAircraft.h"
#include "src/NarrowBodyAircraft.h"
#include <QMessageBox>

AddAircraftDialog::AddAircraftDialog(QWidget *parent) : QDialog(parent), ui(new Ui::AddAircraftDialog)
{
    ui->setupUi(this);

    connect(ui->comboBoxPassAircraftType, QOverload<int>::of(&QComboBox::currentIndexChanged),
            ui->stackedWidgetPassAircraftType, &QStackedWidget::setCurrentIndex);
    connect(ui->comboBoxAircraftType, QOverload<int>::of(&QComboBox::currentIndexChanged),
            ui->stackedWidgetAircraftType, &QStackedWidget::setCurrentIndex);

    ui->stackedWidgetPassAircraftType->setCurrentIndex(ui->comboBoxPassAircraftType->currentIndex());
    ui->stackedWidgetAircraftType->setCurrentIndex(ui->comboBoxAircraftType->currentIndex());

    this->setWindowTitle("Добавление самолета");
}

Aircraft* AddAircraftDialog::createAircraft() const {
    QString modelStr = ui->lineEditModel->text();
    int speed = ui->spinBoxSpeed->value();
    int range = ui->spinBoxRange->value();

    if (modelStr.isEmpty()) {
        QMessageBox::warning(nullptr, "Ошибка", "Модель самолета не может быть пустой!");
        return nullptr;
    }
    if (speed <= 0) {
        QMessageBox::warning(nullptr, "Ошибка", "Скорость должна быть больше 0!");
        return nullptr;
    }
    if (range <= 0) {
        QMessageBox::warning(nullptr, "Ошибка", "Дальность полета должна быть больше 0!");
        return nullptr;
    }

    std::string model = modelStr.toStdString();
    int mainType = ui->stackedWidgetAircraftType->currentIndex();

    if (mainType == 1) { // грузовой
        double weight = ui->doubleSpinBoxCargoWeight->value();
        double volume = ui->doubleSpinBoxCargoVolume->value();

        if (weight <= 0) {
            QMessageBox::warning(nullptr, "Ошибка", "Вес груза должен быть больше 0!");
            return nullptr;
        }
        if (volume <= 0) {
            QMessageBox::warning(nullptr, "Ошибка", "Объём грузового отсека должен быть больше 0!");
            return nullptr;
        }

        return new CargoAircraft(model, speed, range, weight, volume);
    }
    else {
        int passengers = ui->spinBoxPassCapacity->value();
        int crew = ui->spinBoxCabinCrew->value();

        if (passengers <= 0) {
            QMessageBox::warning(nullptr, "Ошибка", "Число пассажиров должно быть больше 0!");
            return nullptr;
        }
        if (crew <= 0) {
            QMessageBox::warning(nullptr, "Ошибка", "Число членов экипажа должно быть больше 0!");
            return nullptr;
        }

        int subType = ui->stackedWidgetPassAircraftType->currentIndex();
        if (subType == 0) {
            return new WideBodyAircraft(model, speed, range, passengers, crew,
                                        ui->comboBoxCountDecks->currentText().toInt(),
                                        ui->spinBoxCountFirstClass->value());
        } else {
            return new NarrowBodyAircraft(model, speed, range, passengers, crew,
                                          ui->comboBoxAisleCount->currentText().toInt(),
                                          ui->comboBoxBusinessClass->currentText() == "Да");
        }
    }
}


void AddAircraftDialog::on_pushButtonAdd_clicked() {
    Aircraft* newAircraft = createAircraft();
    if (newAircraft == nullptr) {
        return;
    }
    this->accept();
}

AddAircraftDialog::~AddAircraftDialog() {
    delete ui;
}
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
        return new CargoAircraft(
            model, speed, range,
            ui->doubleSpinBoxCargoWeight->value(),
            ui->doubleSpinBoxCargoVolume->value()
            );
    }
    else { // пассажирские
        int subType = ui->stackedWidgetPassAircraftType->currentIndex();

        if (subType == 0) { // широкий
            return new WideBodyAircraft(
                model, speed, range,
                ui->spinBoxPassCapacity->value(),
                ui->spinBoxCabinCrew->value(),
                ui->comboBoxCountDecks->currentText().toInt(),
                ui->spinBoxCountFirstClass->value()
                );
        } else { // узкий
            return new NarrowBodyAircraft(
                model, speed, range,
                ui->spinBoxPassCapacity->value(),
                ui->spinBoxCabinCrew->value(),
                ui->comboBoxAisleCount->currentText().toInt(),
                ui->comboBoxBusinessClass->currentText() == "Да"
                );
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
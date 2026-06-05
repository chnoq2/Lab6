#ifndef ADDAIRCRAFTDIALOG_H
#define ADDAIRCRAFTDIALOG_H

#include <QDialog>
#include "src/Aircraft.h" // Базовый класс

namespace Ui {
class AddAircraftDialog;
}

class AddAircraftDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddAircraftDialog(QWidget *parent = nullptr);
    ~AddAircraftDialog();

    Aircraft* createAircraft() const;

private slots:
    void on_pushButtonAdd_clicked();

private:
    Ui::AddAircraftDialog *ui;
};

#endif
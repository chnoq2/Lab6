#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "src/Airline.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
private:
    Ui::MainWindow *ui;
    std::vector<Airline> allAirlines;
    Airline myAirline;
    QString formatAircraftInfo(Aircraft* plane) const;

    void on_btnAdd_clicked();
    void on_btnClear_clicked();
    void on_btnDel_clicked();
    void updateTotalCapacity();
    void updateList();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};

#endif
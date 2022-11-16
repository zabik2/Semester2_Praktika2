#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QListWidgetItem>
#include "travelagency.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionEinlesen_triggered();

    void on_actionAusw_hlen_triggered();

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_actionJson_triggered();


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

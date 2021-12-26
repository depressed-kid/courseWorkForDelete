#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QListWidget>
#include <QSpacerItem>
#include <QDebug>
#include <Processor.h>
#include <dbtypes.h>
#include <vector>
#include <QTableWidget>
#include <QLabel>

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QWidget* widget;
    QVBoxLayout* mainLayout;
    QHBoxLayout* list_layout;
    QVBoxLayout* btnsLayout;
    QHBoxLayout* task1_layout;
    QHBoxLayout* task2_layout;
    QHBoxLayout* task3_layout;
    QHBoxLayout* task4_layout;
    QListWidget* listWgt;
    QComboBox* task1_comboBox;
    QPushButton* task1_btn;
    QComboBox* task2_comboBox;
    QPushButton* task2_btn;
    QTextEdit* task3_textEdit;
    QPushButton* task3_btn;
    QComboBox* task4_comboBox;
    QPushButton* task4_btn;
    QPushButton* add_btn;
    QPushButton* delete_btn;
    QSpacerItem* space;

    db::Processor* db;
    std::vector<DBTypes::DBEntry> data;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void updateInfo();
    void redraw();

private slots:
    void addBtn_clicked();
    void deleteBtn_clicked(const QString& value);
    void task1Btn_clicked(const QString& value);
    void task2Btn_clicked(const QString& value);
    void task3Btn_clicked(const QString& value);
    void task4Btn_clicked(const QString& value);
    void addGood(const QVariantList& data);
    void onUpdateInfo();
    void onRedraw();

};
#endif // MAINWINDOW_H

















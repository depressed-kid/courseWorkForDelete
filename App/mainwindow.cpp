#include "mainwindow.h"

#include <QDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    connect (this, &MainWindow::updateInfo, this, &MainWindow::onUpdateInfo);
    connect (this, &MainWindow::redraw, this, &MainWindow::onRedraw);

    db = new db::Processor;

    emit updateInfo();

    widget = new QWidget;

    mainLayout = new QVBoxLayout(widget);

    list_layout = new QHBoxLayout();
    btnsLayout = new QVBoxLayout();
    task1_layout = new QHBoxLayout();
    task2_layout = new QHBoxLayout();
    task3_layout = new QHBoxLayout();
    task4_layout = new QHBoxLayout();

    listWgt = new QListWidget(widget);
    for(const auto& item : data) {
        listWgt->addItem(item[1].toString());
    }
    listWgt->setMaximumSize (300, 300);

    task1_comboBox = new QComboBox;
    task1_comboBox->addItem ("");
    for(const auto& item : data) {
        task1_comboBox->addItem(item[1].toString());
    }
    task1_comboBox->setMinimumSize(300, 30);
    task1_btn = new QPushButton("Найти страны", widget);

    task2_comboBox = new QComboBox;
    task2_comboBox->addItem ("");
    for(const auto& item : data) {
        task2_comboBox->addItem(item[4].toString());
    }
    task2_comboBox->setMinimumSize (300, 30);
    task2_btn = new QPushButton("Найти товары", widget);

    task3_textEdit = new QTextEdit;
    task3_textEdit->setPlaceholderText("Введите начальную букву");
    task3_textEdit->setMinimumSize(300, 30);
    task3_textEdit->setMaximumSize(300, 30);
    task3_btn = new QPushButton("Найти товары", widget);

    task4_comboBox = new QComboBox;
    task4_comboBox->addItem ("");
    for(const auto& item : data) {
        task4_comboBox->addItem(item[2].toString());
    }
    task4_comboBox->setMinimumSize (300, 30);
    task4_btn = new QPushButton("Найти объем", widget);

    add_btn = new QPushButton("Добавить", widget);
    delete_btn = new QPushButton("Удалить", widget);

    space = new QSpacerItem(0, 20);

    mainLayout->addLayout(list_layout);
    mainLayout->addItem(space);
    mainLayout->addLayout(task1_layout);
    mainLayout->addLayout(task2_layout);
    mainLayout->addLayout(task3_layout);
    mainLayout->addLayout(task4_layout);

    btnsLayout->addWidget (add_btn);
    btnsLayout->addWidget (delete_btn);
    btnsLayout->setAlignment(Qt::AlignTop);

    list_layout->addWidget(listWgt);
    list_layout->addLayout (btnsLayout);

    task1_layout->addWidget(task1_comboBox);
    task1_layout->addWidget (task1_btn);

    task2_layout->addWidget(task2_comboBox);
    task2_layout->addWidget (task2_btn);

    task3_layout->addWidget(task3_textEdit);
    task3_layout->addWidget (task3_btn);

    task4_layout->addWidget(task4_comboBox);
    task4_layout->addWidget (task4_btn);

    setCentralWidget (widget);
    setContentsMargins(10, 10, 10, 10);

    // signals and slots
    connect(add_btn, &QPushButton::clicked, this, &MainWindow::addBtn_clicked);
    connect(delete_btn, &QPushButton::clicked, this, [this]{
        deleteBtn_clicked(listWgt->currentItem ()->text());
    });
    connect(task1_btn, &QPushButton::clicked, this, [this]{ task1Btn_clicked(task1_comboBox->currentText ()); });
    connect(task2_btn, &QPushButton::clicked, this, [this]{ task2Btn_clicked(task2_comboBox->currentText()); });
    connect(task3_btn, &QPushButton::clicked, this, [this]{ task3Btn_clicked(task3_textEdit->toPlainText()); });
    connect(task4_btn, &QPushButton::clicked, this, [this]{ task4Btn_clicked(task4_comboBox->currentText()); });



}

MainWindow::~MainWindow()
{
    delete widget;
    delete mainLayout;
    delete list_layout;
    delete btnsLayout;
    delete task1_layout;
    delete task2_layout;
    delete task3_layout;
    delete task4_layout;
    delete listWgt;
    delete task1_comboBox;
    delete task1_btn;
    delete task2_comboBox;
    delete task2_btn;
    delete task3_textEdit;
    delete task3_btn;
    delete task4_comboBox;
    delete task4_btn;
    delete add_btn;
    delete delete_btn;
    delete space;
}


// slots
void MainWindow::addBtn_clicked()
{
    QDialog* dialog = new QDialog();
    QVBoxLayout* layout = new QVBoxLayout(dialog);
    QHBoxLayout* btnsLayout = new QHBoxLayout();

    QTextEdit* goodsName = new QTextEdit(dialog);
    goodsName->setPlaceholderText("Наименование");
    goodsName->setMaximumSize (300, 30);
    QComboBox* goodsCountry = new QComboBox(dialog);
    goodsCountry->setMaximumSize (300, 30);
    goodsCountry->addItem ("");
    for(const auto& item : data) {
        goodsCountry->addItem(item[2].toString());
    }
    QTextEdit* goodsAmount = new QTextEdit(dialog);
    goodsAmount->setPlaceholderText("Количество");
    goodsAmount->setMaximumSize (300, 30);

    QComboBox* goodsManufacturerCountry = new QComboBox(dialog);
    goodsManufacturerCountry->setMaximumSize (300, 30);
    goodsManufacturerCountry->addItem ("");
    for(const auto& item : data) {
        goodsManufacturerCountry->addItem(item[4].toString());
    }
    QPushButton* addBtn = new QPushButton("Добавить", dialog);
    QPushButton* cancelBtn = new QPushButton("Отменить", dialog);
    QSpacerItem* space = new QSpacerItem(0, 20);

    btnsLayout->addWidget(addBtn);
    btnsLayout->addWidget(cancelBtn);

    layout->addWidget(goodsName);
    layout->addWidget(goodsCountry);
    layout->addWidget(goodsAmount);
    layout->addWidget(goodsManufacturerCountry);
    layout->addItem (space);
    layout->addLayout(btnsLayout);

    dialog->setContentsMargins(10, 10, 10, 10);

    // signals/slots
    connect (addBtn,  &QPushButton::clicked, this,  [&dialog, this, &goodsName, &goodsCountry, &goodsAmount, &goodsManufacturerCountry]{
        addGood({goodsName->toPlainText(), goodsCountry->currentText(), goodsAmount->toPlainText(), goodsManufacturerCountry->currentText()});
        dialog->close();
    });
    connect(cancelBtn, &QPushButton::clicked, dialog, &QDialog::close);

    dialog->exec();
}

void MainWindow::addGood(const QVariantList& data) {
    db->addTableData(DBTypes::DBTables::Export, data);
    emit updateInfo();
    emit redraw();
}

void MainWindow::onUpdateInfo()
{
    auto [DBResult, DBData] = db->requestTableData(DBTypes::DBTables::Export);

    if (DBResult == DBTypes::DBResult::FAIL) {
        qInfo() << "Не удалось получить данные из базы данных";
    } else {
        data = DBData;
    }
}

void MainWindow::onRedraw()
{
    listWgt->clear ();
    for(const auto& item : data) {
        listWgt->addItem(item[1].toString());
    }

    task1_comboBox->clear ();
    task1_comboBox->addItem ("");
    for(const auto& item : data) {
        task1_comboBox->addItem(item[1].toString());
    }

    task2_comboBox->clear ();
    task2_comboBox->addItem ("");
    for(const auto& item : data) {
        task2_comboBox->addItem(item[4].toString());
    }

    task4_comboBox->clear ();
    task4_comboBox->addItem ("");
    for(const auto& item : data) {
        task4_comboBox->addItem(item[2].toString());
    }
}

void MainWindow::deleteBtn_clicked(const QString& value)
{
    db->deleteTableData(DBTypes::DBTables::Export, value);
    emit updateInfo();
    emit redraw();
}

// найти страны, в которые экспортируется данный товар;
void MainWindow::task1Btn_clicked(const QString& value)
{
    // запрос (дождаться ответа)
    QStringList counties;
    for(const auto& item : data) {
        QString god = item[1].toString();
        if (god == value) {
            counties.push_back(item[2].toString ());
        }
    }

    // диалог
    QDialog* dialog = new QDialog();
    QVBoxLayout* layout = new QVBoxLayout(dialog);
    QListWidget* listWgt = new QListWidget(dialog);
    listWgt->addItems(counties);
    listWgt->setMaximumSize (300, 300);

    layout->addWidget (listWgt);

    dialog->exec();
}

// вывести список товаров, поставляемых указанной страной;
void MainWindow::task2Btn_clicked(const QString& value)
{
    // запрос (дождаться ответа)
    QStringList goods;
    for(const auto& item : data) {
        QString country = item[4].toString();
        if (country == value) {
            goods.push_back(item[1].toString ());
        }
    }

    // диалог
    QDialog* dialog = new QDialog();
    QVBoxLayout* layout = new QVBoxLayout(dialog);
    QListWidget* listWgt = new QListWidget(dialog);
    listWgt->addItems(goods);
    listWgt->setMaximumSize (300, 300);

    layout->addWidget (listWgt);

    dialog->exec();
}

// вывести наименование товаров, начинающихся с заданной буквы;
void MainWindow::task3Btn_clicked(const QString& value)
{
    // запрос (дождаться ответа)
    QStringList goods;
    for(const auto& item : data) {
        QString godFirstLetter = item[1].toString();
        if (godFirstLetter[0].toLower ()== value.toLower ()) {
            goods.push_back(item[1].toString());
        }
    }

    // диалог
    QDialog* dialog = new QDialog();
    QVBoxLayout* layout = new QVBoxLayout(dialog);
    QListWidget* listWgt = new QListWidget(dialog);
    listWgt->addItems(goods);
    listWgt->setMaximumSize (300, 300);

    layout->addWidget (listWgt);

    dialog->exec();
}

// вывести общий объем товаров, поставляемых в указанную страну
void MainWindow::task4Btn_clicked(const QString& value)
{
    // запрос (дождаться ответа)
    QStringList goods;
    QStringList size;
    int totalSize = 0;
    for(const auto& item : data) {
        QString country = item[2].toString();
        if (country == value) {
            goods.push_back (item[1].toString ());
            size.push_back(item[3].toString ());
            totalSize += item[3].toInt ();
        }
    }


    // диалог
    QDialog* dialog = new QDialog();
    QVBoxLayout* layout = new QVBoxLayout(dialog);
    QLabel* total = new QLabel(dialog);
    QTableWidget* tableWgt = new QTableWidget(goods.size (), 2, dialog);


    for(auto i = 0; i < goods.size(); i++) {
        tableWgt->setItem(i, 0, new QTableWidgetItem(goods[i]));
        tableWgt->setItem(i, 1, new QTableWidgetItem(size[i]));

    }

    total->setText("Итог: " + QString::number(totalSize));
    layout->addWidget(tableWgt);
    layout->addWidget(total);

    dialog->exec();
}




























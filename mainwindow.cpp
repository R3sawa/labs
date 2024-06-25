#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtMath>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , listModel(new QStringListModel(this))
{
    ui->setupUi(this);

    // Пример установки модели для QListView
    QStringList list;
    list << "meters" << "santimeters" << "miles"<<"kilometers"<<"inch";
    listModel->setStringList(list);
    ui->listView->setModel(listModel);

    ui->chooseValue->addItem("meters");
    ui->chooseValue->addItem("santimeters");
    ui->chooseValue->addItem("miles");
    ui->chooseValue->addItem("kilometers");
    ui->chooseValue->addItem("inch");

    val="meters";

    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::on_actionExit_triggered);
    connect(ui->button, &QPushButton::clicked, this, &MainWindow::on_buttonClicked);
    connect(ui->calculateButton, &QPushButton::clicked, this, &MainWindow::calculateLength);
    connect(ui->radioButton, &QRadioButton::toggled, this, &MainWindow::on_radioButton_toggled);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_buttonClicked()
{
    ui->sm->setText("");
    ui->m->setText("");
    ui->ml->setText("");
    ui->km->setText("");
    ui->inch->setText("");
    ui->lineEdit->setText("");

}

void MainWindow::calculateLength()
{
    qint16 value = ui->lineEdit->text().toDouble();
    if(val=="meters"){
        ui->sm->setText(QString::number(value*100));
        ui->m->setText(QString::number(value));
        ui->ml->setText(QString::number(value*0.000621371, 'f', 6));
        ui->km->setText(QString::number(value*0.001, 'f', 6));
        ui->inch->setText(QString::number(value*39.3701, 'f', 6));
    }else if(val=="santimeters"){
        ui->sm->setText(QString::number(value));
        ui->m->setText(QString::number(value*0.01, 'f', 6));
        ui->ml->setText(QString::number(value*6.21504039776258545680546923555e-6, 'f', 6));
        ui->km->setText(QString::number(value*0.00001, 'f', 6));
        ui->inch->setText(QString::number(value*0.39370079, 'f', 6));
    }else if(val=="miles"){
        ui->sm->setText(QString::number(value*160934));
        ui->m->setText(QString::number(value*1609.34, 'f', 6));
        ui->ml->setText(QString::number(value));
        ui->km->setText(QString::number(value*1.60934, 'f', 6));
        ui->inch->setText(QString::number(value*63360));
    }else if(val=="kilometers"){
        ui->sm->setText(QString::number(value*100000));
        ui->m->setText(QString::number(value*100));
        ui->ml->setText(QString::number(value*0.621371, 'f', 6));
        ui->km->setText(QString::number(value));
        ui->inch->setText(QString::number(value*39370.1, 'f', 6));
    }else if(val=="inch"){
        ui->sm->setText(QString::number(value*2.54, 'f', 6));
        ui->m->setText(QString::number(value*0.0254, 'f', 6));
        ui->ml->setText(QString::number(value*1.5782828282828282828282828282828e-5, 'f', 6));
        ui->km->setText(QString::number(value*2.5400050800101600203200406400813e-5, 'f', 6));
        ui->inch->setText(QString::number(value));
    }
}


void MainWindow::readFile(const QString &fileName)
{
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QStringList list;
        while (!in.atEnd()) {
            QString line = in.readLine();
            list << line;
        }
        listModel->setStringList(list);
        file.close();
    }
}

void MainWindow::writeFile(const QString &fileName, const QString &text)
{
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << text;
        file.close();
    }
}



void MainWindow::on_radioButton_toggled(bool checked)
{
    if(!checked) {
        ui->listView->show();
        ui->km->show();
        ui->m->show();
        ui->ml->show();
        ui->sm->show();
        ui->inch->show();
    }
    else {
        ui->listView->hide();
        ui->km->hide();
        ui->m->hide();
        ui->ml->hide();
        ui->sm->hide();
        ui->inch->hide();
    }
}








void MainWindow::on_chooseValue_activated(int index)
{
    if(index==0){
        val=ui->chooseValue->itemText(0);
    } else if(index==1){
        val=ui->chooseValue->itemText(1);
    }else if(index==2){
        val=ui->chooseValue->itemText(2);
    }else if(index==3){
        val=ui->chooseValue->itemText(3);
    }else if(index==4){
        val=ui->chooseValue->itemText(4);
    }
}


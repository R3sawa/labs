#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QListView>
#include <QComboBox>
#include <QStringListModel>
#include <QFile>
#include <QTextStream>
#include <QDialog>
#include <QString>
#include <QStringList>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    QString val;
    ~MainWindow();

private slots:
    void on_actionExit_triggered();
    void on_buttonClicked();
    void calculateLength();
    void on_radioButton_toggled(bool checked);
    void on_chooseValue_activated(int index);

private:
    Ui::MainWindow *ui;
    QStringListModel *listModel;

    // Пример методов для работы с файлами
    void readFile(const QString &fileName);
    void writeFile(const QString &fileName, const QString &text);
};

#endif // MAINWINDOW_H

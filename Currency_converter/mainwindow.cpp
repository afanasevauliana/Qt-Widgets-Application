#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QPropertyAnimation>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    exchangeRates["USD"] = 1.0;
    exchangeRates["EUR"] = 0.93;
    exchangeRates["GBP"] = 0.79;
    exchangeRates["JPY"] = 149.0;
    exchangeRates["RUB"] = 92.0;
    ui->fromCurrency->addItems(exchangeRates.keys());
    ui->toCurrency->addItems(exchangeRates.keys());
    QPropertyAnimation *anim = new QPropertyAnimation(ui->convertButton, "geometry");
    anim->setDuration(100);
    anim->setKeyValueAt(0, ui->convertButton->geometry());
    anim->setKeyValueAt(0.5, ui->convertButton->geometry().adjusted(-5, -5, 5, 5));
    anim->setKeyValueAt(1, ui->convertButton->geometry());
    connect(ui->convertButton, &QPushButton::clicked,
            this, &MainWindow::onConvertButtonClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onConvertButtonClicked()
{
    QString fromCurrency = ui->fromCurrency->currentText();
    QString toCurrency = ui->toCurrency->currentText();
    bool ok;
    double amount = ui->amountInput->text().toDouble(&ok);

    if (!ok || amount <= 0) {
        QMessageBox::warning(this, "Ошибка",
                           "Пожалуйста, введите корректную сумму");
        return;
    }
    if (exchangeRates.contains(fromCurrency) && exchangeRates.contains(toCurrency)) {
        double result = amount * (exchangeRates[toCurrency] / exchangeRates[fromCurrency]);
        ui->resultLabel->setText(QString::number(result, 'f', 2));
    } else {
        QMessageBox::warning(this, "Ошибка",
                           "Не удалось выполнить конвертацию");
    }
}

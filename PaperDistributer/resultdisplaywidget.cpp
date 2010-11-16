#include "resultdisplaywidget.h"
#include <QHBoxLayout>

ResultDisplayWidget::ResultDisplayWidget(QWidget *parent) :
    QWidget(parent)
{
    this->resultTable = new QTableWidget(this);
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(resultTable);
    this->setLayout(mainLayout);
}

void ResultDisplayWidget::displayResult(QVector<QVector<int> > result, QStringList hLabel, QStringList vLabel, QVector<int> amount)
{
    this->resultTable->reset();
    this->resultTable->clear();
    this->resultTable->setRowCount(result.size());
    this->resultTable->setColumnCount(result.size() + 1);
    for (int row = 0; row < result.size(); row++)
    {
        for (int col = 0; col < result[row].size(); col++)
        {
            this->resultTable->setItem(row, col, new QTableWidgetItem(QString().sprintf("%d", result[row][col])));
        }
    }

    this->resultTable->setHorizontalHeaderLabels(hLabel);
    this->resultTable->setVerticalHeaderLabels(vLabel);
    for (int col = 0; col < result.size(); col++)
    {
        this->resultTable->setColumnWidth(col, 32);
    }
    for (int row = 0; row < result.size(); row++)
    {
        this->resultTable->setItem(row, result.size(), new QTableWidgetItem(QString().sprintf("%d", amount[row])));
    }
}

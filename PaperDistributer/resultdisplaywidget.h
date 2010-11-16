#ifndef RESULTDISPLAYWIDGET_H
#define RESULTDISPLAYWIDGET_H

#include <QWidget>
#include <QTableWidget>

class ResultDisplayWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ResultDisplayWidget(QWidget *parent = 0);
private:
    QTableWidget *resultTable;
signals:

public slots:
    void displayResult(QVector< QVector<int> > result, QStringList hLabel, QStringList vLabel, QVector<int> amount);

};

#endif // RESULTDISPLAYWIDGET_H

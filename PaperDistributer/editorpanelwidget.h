#ifndef EDITORPANELWIDGET_H
#define EDITORPANELWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QVector>
#include "college.h"
class EditorPanelWidget : public QWidget
{
    Q_OBJECT
private:
    QTableWidget *mainTable;
    QPushButton *addRowBtn;
    QPushButton *addMultiRowBtn;
    QPushButton *deleteRowBtn;
    QPushButton *resetBtn;
    enum ColContent{name, number, is};
    const static int colCount = 3;
    const static int initRowCount = 1;
public:
    explicit EditorPanelWidget(QWidget *parent = 0);
    QVector<College> getColleges();
signals:

private slots:
    void addNewRow(int row);
    void addRowBtnClick();
    void deleteBtnClick();
    void autoSwitchEdit(QTableWidgetItem *item);
    void addMultiRowBtnClick();
    void resetBtnClick();
};

#endif // EDITORPANELWIDGET_H

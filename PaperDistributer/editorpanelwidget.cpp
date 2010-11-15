#include "editorpanelwidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QSpinBox>
#include <QInputDialog>

EditorPanelWidget::EditorPanelWidget(QWidget *parent) :
    QWidget(parent)
{


    this->mainTable = new QTableWidget(0, colCount, this);
    //this->mainTable->setAutoScroll(true);
    //this->addNewRow(0);

    this->addRowBtn = new QPushButton(tr("Add"), this);
    this->addMultiRowBtn = new QPushButton(tr("Add Multi"), this);
    this->deleteRowBtn = new QPushButton(tr("Delete"), this);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *buttonsLayout = new QHBoxLayout;

    buttonsLayout->addWidget(this->addRowBtn);
    buttonsLayout->addWidget(this->addMultiRowBtn);
    buttonsLayout->addWidget(this->deleteRowBtn);

    mainLayout->addWidget(this->mainTable);
    mainLayout->addLayout(buttonsLayout);
    this->setLayout(mainLayout);

    connect(this->addRowBtn, SIGNAL(clicked()), this, SLOT(addRowBtnClick()));
    connect(this->deleteRowBtn, SIGNAL(clicked()), this, SLOT(deleteBtnClick()));
    connect(this->addMultiRowBtn, SIGNAL(clicked()), this, SLOT(addMultiRowBtnClick()));
    //connect(this->mainTable, SIGNAL(itemActivated(QTableWidgetItem*)), this, SLOT(autoSwitchEdit(QTableWidgetItem*)));
}

void EditorPanelWidget::addNewRow(int row)
{
    this->mainTable->insertRow(row);
    this->mainTable->setCellWidget(row, number, new QSpinBox(this));
    this->mainTable->setCellWidget(row, is, new QCheckBox(this));
}

void EditorPanelWidget::addRowBtnClick()
{
    this->addNewRow(this->mainTable->rowCount());
}

void EditorPanelWidget::deleteBtnClick()
{
    int currentRow = this->mainTable->currentRow();
    if (currentRow >= 0 && currentRow < this->mainTable->rowCount())
    {
        this->mainTable->removeRow(currentRow);
    }
}

void EditorPanelWidget::autoSwitchEdit(QTableWidgetItem *item)
{
    exit(0);
    this->mainTable->editItem(item);
}

void EditorPanelWidget::addMultiRowBtnClick()
{
    bool ok;
    int rowNumberToAdd = QInputDialog::getInt(this, tr("Add Multi Rows"), tr("Rows To Add"), 2, -100, +100, 1, &ok);
    if (ok)
    {
        while (rowNumberToAdd--)
        {
            this->addNewRow(this->mainTable->rowCount());
        }
    }
}

QVector<College> EditorPanelWidget::getColleges()
{
    QVector<College> colleges;
    return colleges;
}

#include "editorpanelwidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QSpinBox>
#include <QInputDialog>
#include <QDebug>
#include <QIcon>
#include <QSpacerItem>
#include <QStringList>

EditorPanelWidget::EditorPanelWidget(QWidget *parent) :
    QWidget(parent)
{


    this->mainTable = new QTableWidget(0, colCount, this);
    this->mainTable->setColumnWidth(name, 128);
    this->mainTable->setColumnWidth(number, 64);
    this->mainTable->setColumnWidth(is, 64);
    this->mainTable->setMaximumWidth(128 + 64 + 64 + 32 + 16);
    this->setMaximumWidth(330);

    QStringList headerList;
    headerList.append(tr("name"));
    headerList.append(tr("number"));
    headerList.append(tr("is"));
    this->mainTable->setHorizontalHeaderLabels(headerList);

    QSize btnSize(32, 32);
    this->addRowBtn = new QPushButton(QIcon(":/icons/add.png"), tr(""), this);
    this->addRowBtn->setMaximumSize(btnSize);
    this->addRowBtn->setMinimumSize(btnSize);
    this->addRowBtn->setToolTip(tr("Add one College"));
    this->addMultiRowBtn = new QPushButton(QIcon(":/icons/addmulti.png"), tr(""), this);
    this->addMultiRowBtn->setMaximumSize(btnSize);
    this->addMultiRowBtn->setMinimumSize(btnSize);
    this->addMultiRowBtn->setToolTip(tr("Add multi College"));
    this->deleteRowBtn = new QPushButton(QIcon(":/icons/delete.png"), tr(""), this);
    this->deleteRowBtn->setMaximumSize(btnSize);
    this->deleteRowBtn->setMinimumSize(btnSize);
    this->deleteRowBtn->setToolTip(tr("Delete current College"));
    this->resetBtn = new QPushButton(QIcon(":/icons/reset.png"), tr(""), this);
    this->resetBtn->setMaximumSize(btnSize);
    this->resetBtn->setMinimumSize(btnSize);
    this->resetBtn->setToolTip(tr("Reset"));

    QSpacerItem *space = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);


    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *buttonsLayout = new QHBoxLayout;

    buttonsLayout->addWidget(this->addRowBtn);
    buttonsLayout->addWidget(this->addMultiRowBtn);
    buttonsLayout->addWidget(this->deleteRowBtn);
    buttonsLayout->addWidget(this->resetBtn);
    buttonsLayout->addSpacerItem(space);

    mainLayout->addWidget(this->mainTable);
    mainLayout->addLayout(buttonsLayout);
    this->setLayout(mainLayout);

    connect(this->addRowBtn, SIGNAL(clicked()), this, SLOT(addRowBtnClick()));
    connect(this->deleteRowBtn, SIGNAL(clicked()), this, SLOT(deleteBtnClick()));
    connect(this->addMultiRowBtn, SIGNAL(clicked()), this, SLOT(addMultiRowBtnClick()));
    connect(this->resetBtn, SIGNAL(clicked()), this, SLOT(resetBtnClick()));
    connect(this->mainTable, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(autoSwitchEdit(QTableWidgetItem*)));
}

void EditorPanelWidget::addNewRow(int row)
{
    this->mainTable->insertRow(row);
    this->mainTable->setItem(row, name, new QTableWidgetItem());
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
    this->mainTable->editItem(item);
}

void EditorPanelWidget::addMultiRowBtnClick()
{
    bool ok;
    int rowNumberToAdd = QInputDialog::getInt(this, tr("Add Multi Rows"), tr("Rows To Add"), 2, 0, +100, 1, &ok);
    if (ok)
    {
        while (rowNumberToAdd--)
        {
            this->addNewRow(this->mainTable->rowCount());
        }
    }
}

void EditorPanelWidget::resetBtnClick()
{
    while (this->mainTable->rowCount() > 0)
    {
        this->mainTable->removeRow(0);
    }
}

QVector<College> EditorPanelWidget::getColleges()
{
    QVector<College> colleges;
    for (int row = 0; row < this->mainTable->rowCount(); row++)
    {
        int collegeId = row + 1;
        QString collegeName = this->mainTable->item(row, name)->text().trimmed();
        int paperNumber = ((QSpinBox *)(this->mainTable->cellWidget(row, number)))->value();
        bool isJury = ((QCheckBox *)(this->mainTable->cellWidget(row, is)))->isChecked();
        College college = College(collegeId, collegeName, paperNumber, isJury);
        colleges.push_back(college);
    }
    return colleges;
}

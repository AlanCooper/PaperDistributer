#include "mainwindow.h"
#include <QHBoxLayout>
#include <QIcon>
#include <QPixmap>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    this->toolBar = this->addToolBar("");
    this->toolBar->setIconSize(QSize(iconSize, iconSize));
    this->goAction = new QAction(QIcon(":/icons/go.png"), tr("Go"), this);
    this->toolBar->addAction(goAction);
    this->exportAction = new QAction(QIcon(":/icons/export.png"), tr("Export"), this);
    this->toolBar->addAction(this->exportAction);
    this->exitAction = new QAction(QIcon(":/icons/exit.png"), tr("Exit"), this);
    this->toolBar->addAction(exitAction);

    editorPanel = new EditorPanelWidget(this);
    resultDisplayWidget = new ResultDisplayWidget(this);
    QWidget *centralWidget = new QWidget(this);
    QHBoxLayout *centralLayout = new QHBoxLayout(this);
    centralLayout->addWidget(editorPanel);
    centralLayout->addWidget(resultDisplayWidget);
    centralWidget->setLayout(centralLayout);
    this->setCentralWidget(centralWidget);
    this->connect(this->goAction, SIGNAL(triggered()), this, SLOT(process()));
    this->connect(this->exportAction, SIGNAL(triggered()), this, SLOT(exportCsv()));
    this->connect(this->exitAction, SIGNAL(triggered()), this, SLOT(close()));
    this->showMaximized();
}

void MainWindow::process()
{
    this->distributer.setColleges(this->editorPanel->getColleges());
    this->distributer.distribute();
    this->resultDisplayWidget->displayResult(distributer.getResult(), distributer.getHLabel(), distributer.getVLabel(), distributer.getAmount());
}

void MainWindow::exportCsv()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Open File"), "./", "*.csv");
    if (fileName.size() == 0)
    {
        return;
    }
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly))
    {
        file.write(this->distributer.csvString().toLocal8Bit());
        file.close();
    }
}

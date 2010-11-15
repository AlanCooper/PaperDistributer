#include "mainwindow.h"
#include "editorpanelwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    EditorPanelWidget *editorPanel = new EditorPanelWidget(this);
    this->setCentralWidget(editorPanel);
}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include <QAction>
#include "editorpanelwidget.h"
#include "resultdisplaywidget.h"
#include "distributer.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QToolBar *toolBar;
    QAction *goAction;
    QAction *exitAction;
    QAction *exportAction;

    EditorPanelWidget *editorPanel;
    ResultDisplayWidget *resultDisplayWidget;
    Distributer distributer;
    const static int iconSize = 48;
public:
    explicit MainWindow(QWidget *parent = 0);

signals:

public slots:
private slots:
    void process();
    void exportCsv();
};

#endif // MAINWINDOW_H

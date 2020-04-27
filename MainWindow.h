//
// Created by chasank on 18/04/2020.
//

#ifndef OPEN_CV_HELLO_WORLD_MAINWINDOW_H
#define OPEN_CV_HELLO_WORLD_MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QAction>
#include <QMenu>

#include "FacialRecognitionThread.h"
#include "CentralWidget.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent=nullptr);
    ~MainWindow();

    void initUI();

public slots:

    void updateFrame(const QImage &frame);

    void updateAverageFPS(const double &fps);

    void handleStream();

private slots:

    void quit();

    void about();

    void aboutQt();

private:

    void createMenus();

    void createActions();

    void createStatusBar();

protected:
    void closeEvent(QCloseEvent *event) override;

private:

    CentralWidget *centralWidget;

    FacialRecognitionThread *facialRecognitionThread;

    QMenu *fileMenu;
    QMenu *aboutMenu;

    QAction *quitAction;
    QAction *aboutAction;
    QAction *aboutQtAction;

};


#endif //OPEN_CV_HELLO_WORLD_MAINWINDOW_H

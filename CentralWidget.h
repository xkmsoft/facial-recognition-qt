//
// Created by chasank on 18/04/2020.
//

#ifndef OPEN_CV_HELLO_WORLD_CENTRALWIDGET_H
#define OPEN_CV_HELLO_WORLD_CENTRALWIDGET_H

#include <QWidget>
#include <QGroupBox>
#include <QRadioButton>
#include <QHBoxLayout>
#include <QComboBox>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <CameraWidget.h>


class CentralWidget : public QWidget {

    Q_OBJECT

public:

    explicit CentralWidget(QWidget *parent = nullptr);

    CameraWidget *getEntranceCameraWidget() const;

    QPushButton *getEntranceCameraStartButton() const;

    QGroupBox *getEntranceCameraGroupBox() const;

    QGridLayout *getEntranceCameraLayout() const;

    QLineEdit *getEntranceCameraUrl() const;

    QTextEdit *getEntranceLog() const;

    QGridLayout *getMainLayout() const;

    static const QMetaObject &getStaticMetaObject();

private:

    QGroupBox *entranceCameraGroupBox;

    QGridLayout *entranceCameraLayout;

    QLineEdit *entranceCameraURL;

    CameraWidget *entranceCameraWidget;

    QPushButton *entranceCameraStartButton;

    QTextEdit *entranceLog;

    QGridLayout *mainLayout;

};


#endif //OPEN_CV_HELLO_WORLD_CENTRALWIDGET_H

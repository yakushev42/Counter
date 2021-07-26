#ifndef MY_LABEL_H
#define MY_LABEL_H

#include <QObject>
#include <QLabel>
#include <QMouseEvent>
#include <QDebug>
#include<QEvent>
#include <QWheelEvent>
#include <QKeyEvent>

class my_label : public QLabel
{
    Q_OBJECT
public:
    int w; //колесо мыши
    int test;
    double xy;
    explicit my_label(QWidget *parent = nullptr);
    int Getint();
     int x,y,xx,lr;
     int tx,ty;
     int mx,my;
     void mousePressEvent(QMouseEvent *event);
     void mouseMoveEvent(QMouseEvent *event);
     void mouseReleaseEvent(QMouseEvent *event);
     void wheelEvent (QWheelEvent *event);
signals:
    void Mouse_Pressed();
    void Mouse_Pos();
    void Mouse_left();
    void Mouse_Release();
   void Wheel_Roll();


public slots:

protected:

};

#endif // LABEL_H

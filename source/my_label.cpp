#include "my_label.h"

my_label::my_label(QWidget *parent) : QLabel(parent)
{
    this->setMouseTracking(true);
}

int my_label::Getint()
{
    return xy;
}

void my_label::mousePressEvent(QMouseEvent *event)
{
    this->x=event->x();
    this->y=event->y();
    if(event->buttons()==Qt::LeftButton)xx=1;
       if(event->buttons()==Qt::RightButton){
           this->tx=event->x();
           this->ty=event->y();

            lr=1;
       };
    emit Mouse_Pressed();
}

void my_label::mouseMoveEvent(QMouseEvent *event)
{
    this->mx=event->x();
    this->my=event->y();
    emit Mouse_Pos();
}

void my_label::mouseReleaseEvent(QMouseEvent *event)
{

 if(xx==1){

     emit Mouse_Release();
      lr=0;
     xx=0;
 }


}
void my_label::wheelEvent(QWheelEvent *event){
   qDebug() << "Hello mouse: " << event->angleDelta().y();
   if(event->modifiers()==Qt::ControlModifier)w=event->angleDelta().y();
   else w=0;
   emit Wheel_Roll();
}











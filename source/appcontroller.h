#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H

#include <QObject>
#include <QMainWindow>
#include <QFile>
#include <QTextStream>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <vector>

class AppModel;
class MainWindow;

class AppController : QObject
{
    Q_OBJECT
public:
    AppController(AppModel* model, MainWindow* view, QObject* parent = 0);
    void OpenImage(QString);
    QPixmap GetResizeImage();
    QPixmap GetSourceImage();
    QPixmap GetBinarImage(int);
    QPixmap GetSegmentImage(int);
    void SetScale(int);
    int GetScale();
    void ReadSave(QString);
    void WriteSave();
    void UpdatePoints();
    void SetPoint(QPoint,int);
    void DeletePoint(QPoint);
    int GetCnt(int);
    int Segmentation(int,int&,int SegmentSize);
    void Binarization(int,int);
     void ChangeImgView(int);
     void InvertBinar();
     void MinFiltr(int count);
     void Calc_graph(QVector <double>&,QVector <double>&);
     void SWA();
     void CompareImage(QString,std::vector<std::vector<int>>,int);
public slots:


private:
    QImage  cvMatToQImage( const cv::Mat &inMat );
    QPixmap cvMatToQPixmap( const cv::Mat &inMat );




    AppModel* a_model;
    MainWindow* a_view;

};

#endif // APPCONTROLLER_H

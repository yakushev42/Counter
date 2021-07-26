#ifndef APPMODEL_H
#define APPMODEL_H

#include <QObject>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <map>
#include <vector>

struct FileData
{
    QString path;
    double Scale;
    int CntM,CntF,CntC;
    std::vector<cv::Point> Male;
    std::vector<cv::Point> Female;
    std::vector<cv::Point> Child;
};

class AppModel
{
public:
    AppModel();
    void OpenImage(QString);
    cv::Mat GetResizeImage();
    cv::Mat GetSourceImage();
    cv::Mat GetBinarImage(int);
    cv::Mat GetSegmentImage(int);
    void Binarization(int,int);
    int Segmentation(int type,int& OlCount,int SegmentSize);
    void SetScale(double);
    double GetScale();
    void LoadSave(FileData);
    FileData GetSave();
    void UpdatePoints();
    void SetPoint(cv::Point,int);
    void DeletePoint(cv::Point);
    void ChangeImgView(int);
    void InvertBinar();
    void MinFiltr(int count);

    void Calc_graph(QVector <double>&,QVector <double>&);
    void SWA();

private:
    QVector <int> g_segment_size;
    cv::Mat ReadImage(std::wstring filename);
    void MakePoint(cv::Point,int);

    void K_binarization();
    void HB_binarization();


    int dist(cv::Vec3b A, cv::Vec3b B);


    cv::Mat original_img;
    cv::Mat original_true_image;
    cv::Mat resize_img;
    cv::Mat binar_img;
    cv::Mat binar_mask;
    cv::Mat segment_img;
    cv::Mat points_mask;
    double scale;
    FileData Save;
    int img_state=0;
    int binar_view=0;
};


#endif // APPMODEL_H

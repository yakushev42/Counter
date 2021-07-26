#include "appmodel.h"

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


using namespace cv;
using namespace std;
AppModel::AppModel()
{

}

void AppModel::OpenImage(QString A)
{
    original_img= ReadImage(A.toStdWString());
    points_mask=Mat::zeros(original_img.rows,(original_img.cols),CV_8UC3);
    original_img.copyTo(resize_img);
    original_img.copyTo(original_true_image);
}

Mat AppModel::GetResizeImage()
{
    Mat temp;
    switch (img_state) {
        case 0:
          cv::resize(original_img,temp,Size(),scale,scale,2);
            break;
        case 1:
            cv::resize(binar_img,temp,Size(),scale,scale,2);
            if(binar_view){
                Mat temp2;
                cv::resize(original_img,temp2,temp.size(),0,0);
                add(temp,temp2,temp);
            }
            break;
        case 2:
            cv::resize(segment_img,temp,Size(),scale,scale,2);
            break;
        }
    Mat temp2;
    resize(points_mask,temp2,temp.size(),0,0);
    add(temp,temp2,temp);
    return temp;
}

Mat AppModel::GetSourceImage()
{
    return original_img;
}

Mat AppModel::GetBinarImage(int type)
{

    Mat temp;
    img_state=type;

    return temp;
}



void AppModel::Binarization(int type,int viev)
{
    switch (type) {
        case 0:
            HB_binarization();
            break;
        case 1:
            K_binarization();
            break;
    }
    binar_view=viev;

}

void AppModel::SetScale(double s)
{
    scale=s;
}

double AppModel::GetScale()
{
 return scale;
}

void AppModel::LoadSave(FileData Data)
{
    Save=Data;
    SetScale(Data.Scale);

}

FileData AppModel::GetSave()
{
    Save.Scale=scale;
    return Save;
}

void AppModel::UpdatePoints()
{
    //cv::resize(original_img,resize_img,Size(),scale,scale,2);
    for(int k=0;k<3;k++){
        switch (k) {
        case 0:
            if(!(Save.Male.size()==0)){
                for(int i=0;i<Save.Male.size();i++){
                     MakePoint(Save.Male[i],0);
                }
            }
            break;
        case 1:
            if(!(Save.Female.size()==0)){
                for(int i=0;i<Save.Female.size();i++){
                    MakePoint(Save.Female[i],1);
                }
             }
            break;
        case 2:
            if(!(Save.Child.size()==0)){
                for(int i=0;i<Save.Child.size();i++){
                    MakePoint(Save.Child[i],2);
                }
            }
            break;
        }
    }
}

void AppModel::SetPoint(Point P, int type)
{
    MakePoint(P/scale,type);
    switch (type) {
    case 0:
        Save.CntM++;
        Save.Male.push_back(P/scale);
        break;
    case 1:
        Save.CntF++;
        Save.Female.push_back(P/scale);
        break;
    case 2:
        Save.CntC++;
        Save.Child.push_back(P/scale);
        break;
    case 3:
        DeletePoint(P);
        break;

    }
}

void AppModel::DeletePoint(Point Point)
{
    Point/=scale;
    int ky=15,kx=15;
    for(int i=0;i<3;i++){
        switch (i) {
        case 0:
            for(int j=0;j<Save.Male.size();j++){
                if(fabs(Point.x-Save.Male[j].x)<kx&&fabs(Point.y-Save.Male[j].y)<ky){
                   Save.Male.erase(Save.Male.begin()+j);
                   Save.CntM--;
                }
            }
            break;
        case 1:
            for(int j=0;j<Save.Female.size();j++){
                if(fabs(Point.x-Save.Female[j].x)<kx&&fabs(Point.y-Save.Female[j].y)<ky){
                   Save.Female.erase(Save.Female.begin()+j);
                   Save.CntF--;
                }
            }
            break;
        case 2:
            for(int j=0;j<Save.Child.size();j++){
                if(fabs(Point.x-Save.Child[j].x)<kx&&fabs(Point.y-Save.Child[j].y)<ky){
                   Save.Child.erase(Save.Child.begin()+j);
                   Save.CntC--;
                }
            }
            break;

        }
    }
    UpdatePoints();
}

void AppModel::ChangeImgView(int View)
{
    img_state=View;
}

void AppModel::InvertBinar()
{
    for (int j=0;j<binar_img.cols;j++){
        for (int i=0;i<binar_img.rows;i++){
        if(binar_img.at<Vec3b>(i,j)[0]<50){binar_img.at<Vec3b>(i,j)=Vec3b(253, 253,253);}else
        if(binar_img.at<Vec3b>(i,j)[0]>125)binar_img.at<Vec3b>(i,j)=Vec3b(0, 0,0);
        }
        }
}

Mat AppModel::ReadImage(wstring filename)
{
    const wchar_t* szName = filename.c_str();
    FILE* fp = _wfopen(szName, L"rb");
        if (!fp)
        {
            return  Mat::zeros(1,1,CV_8U);
        }
        fseek(fp, 0, SEEK_END);
        long sz = ftell(fp);
        char* buf = new char[sz];
        fseek(fp, 0, SEEK_SET);
        long n = fread(buf, 1, sz, fp);
        _InputArray arr(buf, sz);
        Mat img = imdecode(arr, 1);
        delete[] buf;
        fclose(fp);
        return img;
}

void AppModel::MakePoint(Point P, int type)
{
    int radius=13;
    Mat temp;
    for(int k=-0;k<radius;k++){
        for(int t=-1;t<radius;t++){
            if((P.y+k)>0&&(P.x+t)>0&&(P.x+t)<points_mask.cols&&(P.y+k)<points_mask.rows){
            if(type==0)points_mask.at<Vec3b>(P.y+k, P.x+t) = Vec3b(255, 0, 0);
            if(type==1)points_mask.at<Vec3b>(P.y+k, P.x+t) = Vec3b(0, 0, 255);
            if(type==2)points_mask.at<Vec3b>(P.y+k, P.x+t) = Vec3b(0, 255, 255);
            }
        }
    }

}

int AppModel::Segmentation(int type,int &OlCount,int SegmentSize)
{

    std::vector<std::vector<int>> segments;
    Mat img=binar_img;
    int segment_number=1;
    segments.assign(img.rows, vector<int>(img.cols));
    int temp;
    g_segment_size.clear();
    for (int i=1;i<img.rows-2;i++){
           for (int j=1;j<img.cols-2;j++){
                if(img.at<Vec3b>(i,j)[0]>125){
                    if(img.at<Vec3b>(i,j-1)[0]<50&&img.at<Vec3b>(i-1,j)[0]<50){
                         segments[i][j]=segment_number;
                         segment_number++;
                    }else if(img.at<Vec3b>(i,j-1)[0]>125&&img.at<Vec3b>(i-1,j)[0]<50){
                        segments[i][j]= segments[i][j-1];
                    }else if(img.at<Vec3b>(i,j-1)[0]<50&&img.at<Vec3b>(i-1,j)[0]>125){
                         segments[i][j]= segments[i-1][j];
                    }else if(img.at<Vec3b>(i,j-1)[0]>125&&img.at<Vec3b>(i-1,j)[0]>125){
                       if(segments[i][j-1]==segments[i-1][j])segments[i][j]=segments[i-1][j];
                       else{
                           segments[i][j]=segments[i-1][j];
                           if(segments[i][j-1]!=0){
                                temp=segments[i][j-1];
                                int flag=1;
                                for(int g=i;g>=0;g--){
                                    if(!flag)break;
                                    flag=0;
                                    for(int t=img.cols;t>=0;t--){
                                        if(img.at<Vec3b>(g,t)[0]>125&&temp==segments[g][t]){
                                            segments[g][t]=segments[i][j];
                                            flag=1;
                                        }
                                    }
                               }
                           }
                       }
                    }
                }
            }
     }

    map <int,vector<int>> color;
    map <int,vector<int>> ::iterator iterator;
    map <int,int> segments_size;
    map <int,int> ::iterator segments_size_iterator;
    Mat img_for_segm;
    for (int j=0;j<img.cols-1;j++){
       for (int i=0;i<img.rows-1;i++){
           segments_size_iterator=segments_size.find(segments[i][j]);
           if(segments_size_iterator==segments_size.end()){
               segments_size.insert(make_pair(segments[i][j],1));
           }
           else {
               segments_size_iterator->second++;
           }
       }
    }
    std::vector<int> kkk;
    int min=100000,max=1;
    segments_size_iterator=segments_size.begin();
    segments_size_iterator=segments_size.erase(segments_size_iterator);
    do {
        if (segments_size_iterator->second<SegmentSize) segments_size_iterator=segments_size.erase(segments_size_iterator);
        else{
            g_segment_size.push_back(segments_size_iterator->second);
            segments_size_iterator++;
        }
    } while (segments_size_iterator!=segments_size.end());
    segments_size_iterator=segments_size.begin();

    int average;
    do {
        color.insert(make_pair(segments_size_iterator->first,vector<int> {rand()%255,rand()%255,rand()%255}));
        average+=segments_size_iterator->second;
         segments_size_iterator++;
    } while (segments_size_iterator!=segments_size.end());
    average/=segments_size.size();

    if(type==0){//чб
        img.copyTo(img_for_segm);
        for (int j=1;j<img.cols-2;j++){
          for (int i=1;i<img.rows-2;i++){
             if(segments[i][j]){
                 if(segments_size.find(segments[i][j])==segments_size.end()){
                     img_for_segm.at<Vec3b>(i,j)=Vec3b(0, 0,0);
                 }else{
                    iterator=color.find(segments[i][j]);
                    img_for_segm.at<Vec3b>(i,j)=Vec3b(iterator->second[0], iterator->second[1],iterator->second[2]);
                    }
                 }
             }
          }
        }

    if(type==1){//поверх оригинала
        img.copyTo(img_for_segm);
        for (int j=1;j<img.cols-2;j++){
          for (int i=1;i<img.rows-2;i++){
             if(segments[i][j]){
                 if(segments_size.find(segments[i][j])==segments_size.end()){
                     img_for_segm.at<Vec3b>(i,j)=Vec3b(0, 0,0);
                 }else{
                    iterator=color.find(segments[i][j]);
                    img_for_segm.at<Vec3b>(i,j)=Vec3b(iterator->second[0], iterator->second[1],iterator->second[2]);
                    }
                 }
             }
          }
    }



     OlCount=segments_size.size();
     for(int i=0;i<segments_size.size();i++){
        if(segments_size[i]>average*2){
            OlCount+=segments_size[i]/average;
        }
    }


    img_for_segm.copyTo(segment_img);


    return g_segment_size.size();

}

void AppModel::K_binarization()
{
    //Функция бинаризации методом К-средних
    Mat img=resize_img;
    std::vector<std::vector<int>> segm;
    segm.assign(img.rows, vector<int>(img.cols));
    for (int j=0;j<img.cols;j++){
      for (int i=0;i<img.rows;i++){
          segm[i][j]=-1;
      }
    }
    int P1[2],P2[2];
    int y=img.cols,x=img.rows;
    P1[0]=x/4;
    P1[1]=y/4;
    P2[0]=x/2;
    P2[1]=y/2;
    Vec3b C1,C2;
    C1=img.at<Vec3b>(P1);
    C2=img.at<Vec3b>(P2);
    int flag=1;
    int D=dist(img.at<Vec3b>(P1),img.at<Vec3b>(P2));
    while(flag){
        flag=0;
        for (int j=0;j<img.cols;j++){
          for (int i=0;i<img.rows;i++){
               if(dist(img.at<Vec3b>(i,j),C1)<dist(img.at<Vec3b>(i,j),C2)){
                   if(segm[i][j]==1)flag=1;
                   segm[i][j]=0;
               }else{
                   if(segm[i][j]==0)flag=1;
                   segm[i][j]=1;
               }
          }
        }
        Vec3b S1,S2;
        int k1,k2;
        for (int j=0;j<img.cols;j++){
          for (int i=0;i<img.rows;i++){
                  if(segm[i][j]){
                      S1+=img.at<Vec3b>(i,j);
                      k1++;
                  }
                  else {
                      S1+=img.at<Vec3b>(i,j);
                      k2++;
                  }
          }
        }
        C1=S1/k1;
        C2=S2/k2;
    }
    Mat temp;
    img.copyTo(temp);
    for (int j=0;j<temp.cols;j++){
      for (int i=0;i<temp.rows;i++){
          if(segm[i][j])temp.at<Vec3b>(i,j)=Vec3b(0,0,0);
          else temp.at<Vec3b>(i,j)=Vec3b(255,255,255);
      }
    }
    temp.copyTo( binar_img );
    // return temp;
}

void AppModel::HB_binarization()
{
    //Функция пороговой бинаризации
    Mat img=resize_img;
    Mat hsv ;
    int balance[2];
    long Bsum=0,Bsum2=0,Hsum=0,Hsum2=0;
    int D=0,HD=0;
    if(img.data!=0){
    cvtColor(img,hsv,COLOR_BGR2HSV);
   int seg=1;
   int SegCols=hsv.cols/seg;
   int SegRows=hsv.rows/seg;
   int tcols=hsv.cols,trows=hsv.rows;
   for(int c=0;c<seg;c++){
        for(int r=0;r<seg;r++){
            Bsum=0,Bsum2=0,Hsum=0,Hsum2=0;
            D=0,HD=0;
            for (int j=c*SegCols+1;j<=(c+1)*SegCols;j++){
                if(j>=hsv.cols-1)break;
                for (int i=r*SegRows+1;i<=(r+1)*SegRows;i++){

                    if(i>=hsv.rows-1)break;


           D=max(abs(hsv.at<Vec3b>(i+1,j)[2]-hsv.at<Vec3b>(i-1,j)[2]),abs(hsv.at<Vec3b>(i,j+1)[2]-hsv.at<Vec3b>(i,j-1)[2]));
            Bsum+=D*hsv.at<Vec3b>(i,j)[2];
            Bsum2+=D;
            HD=max(abs(hsv.at<Vec3b>(i+1,j)[0]-hsv.at<Vec3b>(i-1,j)[0]),abs(hsv.at<Vec3b>(i,j+1)[0]-hsv.at<Vec3b>(i,j-1)[0]));
             Hsum+=HD*hsv.at<Vec3b>(i,j)[0];
             Hsum2+=HD;
        }
    }
    float T=Bsum/Bsum2;
    float HT=Hsum/Hsum2;
    for (int j=c*SegCols+1;j<=(c+1)*SegCols;j++){
        for (int i=r*SegRows+1;i<=(r+1)*SegRows;i++){
            if(j==hsv.cols)continue;
            if(i==hsv.rows)continue;
        if(hsv.at<Vec3b>(i,j)[2]<T || hsv.at<Vec3b>(i,j)[0]<HT){
            hsv.at<Vec3b>(i,j)=Vec3b(0, 0,255);
            balance[0]++;
        }else{
            hsv.at<Vec3b>(i,j)=Vec3b(0, 0,0 );
            balance[1]++;
        }
        }
        }
        }
   }
    Mat rgb;
    cvtColor(hsv,rgb,COLOR_HSV2BGR);


    rgb.copyTo(binar_img);
    }
}

void AppModel::MinFiltr(int count)
{
    //минимальный фильтр
    //закрашивает пиксель, если в единичном радиусе есть пиксель фона
    Mat temp_img;
    while (count) {
        binar_img.copyTo(temp_img);
        for (int j=1;j<binar_img.cols-2;j++){
          for (int i=1;i<binar_img.rows-2;i++){
             if(binar_img.at<Vec3b>(i,j)[0]>125){
                int flag=0;
                for(int k=-1;k<2;k++){
                    for(int t=-1;t<2;t++){
                        if(k==0&&t==0)continue;
                        if(binar_img.at<Vec3b>(i+k,j+t)[0]<125){
                            flag=1;
                            break;
                        }
                    }
                }
                if(flag)temp_img.at<Vec3b>(i,j)=Vec3b(0,0,0);
             }
          }
        }
        temp_img.copyTo(binar_img);
        count--;
    }

}

void AppModel::Calc_graph(QVector <double> &X, QVector <double> &Y)
{
    X.resize(11);
    Y.resize(10);

    int average=0;
    qSort(g_segment_size);

    for(int i=0;i<g_segment_size.size();i++){
        average+=g_segment_size[i];
    }
    average/=g_segment_size.size();
    int min=g_segment_size[0],max=g_segment_size[g_segment_size.size()-1];
    int step=(average-min)/5;
    int step2=(max-average)/4;
    X[0]=min;
    for(int i=1;i<X.size();i++){
        if(i<6){
            X[i]=X[i-1]+step;
        }
        else X[i]=X[i-1]+step2;
    }
    int x=1;
    X[10]=10000000;
    for(int i=0;i<g_segment_size.size();){
        if(g_segment_size[i]<X[x]){
            Y[x-1]++;
            i++;
        }
        else x++;
    }
    X.pop_back();

}

void AppModel::SWA()
{
    vector<vector<int>> graph;
    Mat hsv ;
    Mat graph1(hsv.rows*2-1,hsv.cols*2-1,resize_img.type());
    cvtColor(resize_img,hsv,COLOR_BGR2HSV);
    graph.resize(hsv.rows*2-1);
    for(int i=0;i<graph.size();i++)graph[i].resize(hsv.cols*2-1);

    for (int i=0;i<hsv.rows;i++){
        for (int j=0;j<hsv.cols;j++){

            if((j+1)<hsv.cols){
                graph[i*2][j*2+1]=abs(hsv.at<Vec3b>(i,j)[2]-hsv.at<Vec3b>(i,j+1)[2]);
                graph1.at<Vec3b>(i*2,j*2+1)=Vec3b(graph[i*2][j*2+1], graph[i*2][j*2+1],graph[i*2][j*2+1]);
            }
            if((i+1)<hsv.rows){
                graph[i*2+1][j*2]=abs(hsv.at<Vec3b>(i,j)[2]-hsv.at<Vec3b>(i+1,j)[2]);
                graph1.at<Vec3b>(i*2+1,j*2)=Vec3b(graph[i*2+1][j*2], graph[i*2+1][j*2],graph[i*2+1][j*2]);
            }
        }
    }
     int max=0,min=1000;
    for(int i=0;i<graph.size();i++){
        for(int j=0;j<graph[i].size();j++){
            if(graph[i][j]>max)max=graph[i][j];
            if(graph[i][j]<min)min=graph[i][j];
        }
    }
    int x=0;
    x++;
}

int AppModel::dist(Vec3b A, Vec3b B)
{
    //евклидово растояние между 2умя трёхмерными точками
      return sqrt(pow((A[0]-B[0]),2)+pow((A[1]-B[1]),2)+pow((A[2]-B[2]),2));
}

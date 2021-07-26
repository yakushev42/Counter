#include "appcontroller.h"
#include "appmodel.h"
AppController::AppController(AppModel* model, MainWindow* view, QObject* parent):
    QObject(parent), a_model( model ), a_view( view )
{

}

 QImage  AppController::cvMatToQImage( const cv::Mat &inMat )
{
    switch ( inMat.type() )
    {
    // 8-bit, 4 channel
    case CV_8UC4:
    {
        QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_RGB32 );

        return image;
    }

        // 8-bit, 3 channel
    case CV_8UC3:
    {
        QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_RGB888 );

        return image.rgbSwapped();
    }

        // 8-bit, 1 channel
    case CV_8UC1:
    {
        static QVector<QRgb>  sColorTable;

        // only create our color table once

        QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_Indexed8 );
        return image;
    }

    default:
    {
       break;
    }

    }

    return QImage();
}

 QPixmap AppController::cvMatToQPixmap( const cv::Mat &inMat )
{
    return QPixmap::fromImage( cvMatToQImage( inMat ) );
}


void AppController::OpenImage(QString A)
{
    a_model->OpenImage(A);
}

QPixmap AppController::GetResizeImage()
{
    cv::Mat img = a_model->GetResizeImage();
    return cvMatToQPixmap(img);
}

QPixmap AppController::GetSourceImage()
{
    cv::Mat img = a_model->GetSourceImage();
    return cvMatToQPixmap(img);
}

QPixmap AppController::GetBinarImage(int type)
{
    return cvMatToQPixmap(a_model->GetBinarImage(type));
}

void AppController::SetScale(int s)
{
    a_model->SetScale(floor(s)/100);

}

int AppController::GetScale()
{
    return a_model->GetScale()*100;
}

void AppController::ReadSave(QString path)
{
    FileData Data;
    Data.path=path;
    QFile file(path);
    int type=0;
    if ((file.exists())&&(file.open(QIODevice::ReadOnly)))
    {

       QTextStream in(&file);
       QString line = in.readLine();
       Data.Scale=line.toDouble();
       while(!in.atEnd()) {
           line = in.readLine();
           if(line.contains('M'))type=0;
           if(line.contains('F'))type=1;
           if(line.contains('Y'))type=2;
           if(line.contains(':'))
           {
              QStringList list = line.split(':');
              if(list[0].contains("Male"))Data.CntM=list[1].toInt();
              if(list[0].contains("Female"))Data.CntF=list[1].toInt();
              if(list[0].contains("Young"))Data.CntC=list[1].toInt();
           }
           if(line.contains(','))
           {
              QStringList list = line.split(',');
              switch (type) {
              case 0:
                  Data.Male.push_back(cv::Point (list[0].toInt(),list[1].toInt()));
                  break;
              case 1:
                  Data.Female.push_back(cv::Point (list[0].toInt(),list[1].toInt()));
                  break;
              case 2:
                  Data.Child.push_back(cv::Point (list[0].toInt(),list[1].toInt()));
                  break;
              }

            }
        }

    }
    else{
        Data.Scale=1;
        Data.CntC=Data.CntF=Data.CntM=0;
    }
    file.close();
    a_model->LoadSave(Data);
}

void AppController::WriteSave()
{
    FileData Save=a_model->GetSave();
    QFile file(Save.path);
    if (file.open(QIODevice::WriteOnly))
    {
        QTextStream writeStream(&file);
        writeStream<<Save.Scale<<endl;
        writeStream<<"all:"<<Save.CntM+Save.CntF+Save.CntC<<endl;
        writeStream<<"Male:"<<Save.CntM<<endl;
        writeStream<<"Female:"<<Save.CntF<<endl;
        writeStream<<"Young:"<<Save.CntC<<endl;
        for(int k=0;k<3;k++){
            switch (k) {
            case 0:
                writeStream<<"M"<<endl;
                for(int i=0;i<Save.Male.size();i++)
                {
                     writeStream<<Save.Male[i].x<<','<<Save.Male[i].y<<endl;
                }
                break;
            case 1:
                writeStream<<"F"<<endl;
                for(int i=0;i<Save.Female.size();i++)
                {
                     writeStream<<Save.Female[i].x<<','<<Save.Female[i].y<<endl;
                }
                break;
            case 2:
                writeStream<<"Y"<<endl;
                for(int i=0;i<Save.Child.size();i++)
                {
                     writeStream<<Save.Child[i].x<<','<<Save.Child[i].y<<endl;
                }
                break;

            }

        }
    }
    file.close();
}

void AppController::UpdatePoints()
{
    a_model->UpdatePoints();
}

void AppController::SetPoint(QPoint P,int type)
{
    a_model->SetPoint(cv::Point (P.x(),P.y()),type);
}

void AppController::DeletePoint(QPoint QPoint)
{
    cv::Point Point(QPoint.x(),QPoint.y());
    a_model->DeletePoint(Point);
}

int AppController::GetCnt(int type)
{
    FileData file = a_model->GetSave();
    switch (type) {
    case 0:
        return file.CntM+file.CntF+file.CntC;
    case 1:
        return file.CntM;
    case 2:
        return file.CntF;
    case 3:
        return file.CntC;

    }
}

int AppController::Segmentation(int type,int &OlCount,int SegmentSize)
{
  return a_model->Segmentation(type, OlCount,SegmentSize);


}

void AppController::Binarization(int type,int view)
{

    a_model->Binarization(type,view);
}

void AppController::ChangeImgView(int view)
{
    a_model->ChangeImgView(view);
}

void AppController::InvertBinar()
{
    a_model->InvertBinar();
}

void AppController::MinFiltr(int count)
{
    a_model->MinFiltr(count);
}

void AppController::Calc_graph(QVector<double> &X, QVector<double> &Y)
{
    a_model->Calc_graph(X,Y);
}

void AppController::SWA()
{
    a_model->SWA();
}

void AppController::CompareImage(QString dir, std::vector<std::vector<int>> sets, int)
{
   /* a_model->OpenImage(dir);
    a_model->SetScale(floor(sets[0][0])/100);
    a_model->Binarization(sets[0][1],sets[0][1]);
    if(sets[0][8])a_model->InvertBinar();
    a_model->Segmentation(sets[0][4], 0,sets[0][3]);
    if(sets[0][5])a_model->MinFiltr(sets[0][5]);
*/
}




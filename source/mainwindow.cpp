#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdlib.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    a_controller = new AppController ( &a_model, this, this );

    QStringList list={"всего","самец","самка","телёнок"};
    ui->comboBox->addItems(list);

    //сигналы мыши
    connect(ui->label_main,SIGNAL(Mouse_pos()),this,SLOT(Mouse_current_pos()));
    connect(ui->label_main,SIGNAL(Mouse_Pressed()),this,SLOT(Mouse_Pressed()));
    connect(ui->label_main,SIGNAL(Mouse_Release()),this,SLOT(Mouse_Release()));
    connect(ui->label_main,SIGNAL(Wheel_Roll()),this,SLOT(slotWheel_Roll()));

    ui->label_main->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->label_main, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slotCustomMenuRequested(QPoint)));

    //хоткеи
    keyF11 = new QShortcut(this);
    keyF11->setKey(Qt::Key_F11);
    connect(keyF11, SIGNAL(activated()), this, SLOT(slotShortcutF11()));
    keyCtrlD = new QShortcut(this);
    keyCtrlD->setKey(Qt::Key_Delete);
    connect(keyCtrlD, SIGNAL(activated()), this, SLOT(sltdeletePoint()));
    keyCtrlO = new QShortcut(this);
    keyCtrlO->setKey(Qt::CTRL+Qt::Key_O);
    connect(keyCtrlO, SIGNAL(activated()), this, SLOT(slotShortcutO()));
    keyCtrlS = new QShortcut(this);
    keyCtrlS->setKey(Qt::CTRL+Qt::Key_S);
    connect(keyCtrlS, SIGNAL(activated()), this, SLOT(slotShortcutS()));
    keyCtrlZ = new QShortcut(this);
    keyCtrlZ->setKey(Qt::CTRL+Qt::Key_Z);
    connect(keyCtrlZ, SIGNAL(activated()), this, SLOT(slotShortcutZ()));
    keySM = new QShortcut(this);
    keySM->setKey(Qt::Key_1);
    connect(keySM, SIGNAL(activated()), this, SLOT(slotmale()));
    keySF = new QShortcut(this);
    keySF->setKey(Qt::Key_2);
    connect(keySF, SIGNAL(activated()), this, SLOT(slotfemale()));
    keySY = new QShortcut(this);
    keySY->setKey(Qt::Key_3);
    connect(keySY, SIGNAL(activated()), this, SLOT(slotyoung()));
    ui->label_cnt->setText("");
    ui->segmentation->setEnabled(false);
    ui->binarization->setEnabled(false);
    ui->save->setEnabled(false);
    ui->pushButton->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    ui->pushButton_4->setEnabled(false);
    ui->pushButton_5->setEnabled(false);
    ui->pushButton_6->setEnabled(false);
    ui->apply->setEnabled(false);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_cancel_clicked()
{

}

void MainWindow::slotShortcutF11(){

    if(this->isMaximized()){
            this->showNormal();
        } else {

        this->showMaximized();
        }
}
void MainWindow::slotShortcutS(){
    on_save_clicked();
}
void MainWindow::slotShortcutO(){
    on_open_clicked();
}

void MainWindow::slotShortcutZ(){
    on_cancel_clicked();
}

void MainWindow::on_open_clicked()
{
    //открыть изображение и загрузить сохранённые данные

    QString A=QFileDialog::getOpenFileName(this,"open","","*.jpg");
    if(A!=nullptr)
    {
        a_controller->OpenImage(A);
        QFileInfo file(A);
        QString name = file.baseName();
        QString FileDir = file.path();
        a_controller->ReadSave(FileDir+'/'+name+".txt");
        a_controller->UpdatePoints();
        ui->label_main->setScaledContents(false);
        ui->label_main->setPixmap(a_controller->GetResizeImage());
        ui->label_dir->setText(A);
        ui->Slider->setValue(a_controller->GetScale());
        ui->label_cnt->setNum(a_controller->GetCnt(ui->comboBox->currentIndex()));
        ui->Slider->setValue(a_controller->GetScale());//не факт что правильно
        ui->scale->setNum(1/(double(ui->Slider->value())/100));
        ui->save->setEnabled(true);
        ui->apply->setEnabled(true);
        ui->pushButton->setEnabled(true);
        ui->pushButton_2->setEnabled(true);
        ui->pushButton_6->setEnabled(true);
     }
     
     
     
}

void MainWindow::slotWheel_Roll()
{
    if(ui->label_main->w>0){
        if(ui->Slider->value()<195) ui->Slider->setValue( ui->Slider->value()+5);
        else  ui->Slider->setValue(200);
    }else{
        if(ui->label_main->w<0){
            if(ui->Slider->value()>6)ui->Slider->setValue( ui->Slider->value()-5);
            else  ui->Slider->setValue(1);
        }
    }
    a_controller->SetScale(ui->Slider->value());
    a_controller->UpdatePoints();
    ui->label_main->setPixmap(a_controller->GetResizeImage());
    ui->scale->setNum(1/(double(ui->Slider->value())/100));
}

void MainWindow::Mouse_Release()
{
    if(ui->checkBox->checkState())
    {
        a_controller->SetPoint(QPoint (ui->label_main->x,ui->label_main->y),State);
        ui->label_main->setPixmap(a_controller->GetResizeImage());
         ui->label_cnt->setNum(a_controller->GetCnt(ui->comboBox->currentIndex()));
    }
}


void MainWindow::on_save_clicked()
{
    //сохранить
    a_controller->WriteSave();

}

void MainWindow::slotCustomMenuRequested(QPoint pos)
{
    QAction * Selectmale = new QAction("Выделение самца", this);
    QAction * Selectfemale = new QAction("Выделение самки", this);
    QAction * Selectyong = new QAction("Выделение телёнка", this);
    QAction * deletePoint = new QAction("Удалить точку", this);
    QMenu * menu = new QMenu(this);
    menu->addAction(Selectmale);
    menu->addAction(Selectfemale);
    menu->addAction(Selectyong);
    menu->addAction(deletePoint);
    menu->popup(ui->label_main->mapToGlobal(pos));
    connect(Selectmale, SIGNAL(triggered()), this, SLOT(slotmale()));
    connect(Selectfemale, SIGNAL(triggered()), this, SLOT(slotfemale()));
    connect(Selectyong, SIGNAL(triggered()), this, SLOT(slotyoung()));
    connect(deletePoint, SIGNAL(triggered()), this, SLOT(sltdeletePoint()));
}

void MainWindow::slotmale()
{
    State=0;
    ui->checkBox->setCheckState(Qt::Checked);
    ui->checkBox->setText("самец");
}

void MainWindow::slotfemale()
{
    State=1;
    ui->checkBox->setCheckState(Qt::Checked);
    ui->checkBox->setText("самка");

}

void MainWindow::slotyoung()
{
    State=2;
    ui->checkBox->setCheckState(Qt::Checked);
    ui->checkBox->setText("телёнок");

}

void MainWindow::sltdeletePoint()
{
    State=3;
    ui->checkBox->setCheckState(Qt::Checked);
    ui->checkBox->setText("удаление");
    a_controller->DeletePoint(QPoint (ui->label_main->tx,ui->label_main->ty));
    ui->label_main->setPixmap(a_controller->GetResizeImage());
}



void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    ui->label_cnt->setNum(a_controller->GetCnt(index));
}

void MainWindow::on_apply_clicked()
{
    a_controller->SetScale(ui->Slider->value());
    a_controller->UpdatePoints();
    ui->label_main->setPixmap(a_controller->GetResizeImage());
    ui->scale->setNum(1/(double(ui->Slider->value())/100));

}

void MainWindow::on_segmentation_clicked()
{
    ImgViev=2;
    a_controller->ChangeImgView(ImgViev);
   ui->label_main->setPixmap(a_controller->GetResizeImage());
}

void MainWindow::on_binarization_clicked()
{
    ImgViev=1;
     a_controller->ChangeImgView(ImgViev);
    ui->label_main->setPixmap(a_controller->GetResizeImage());

}

void MainWindow::on_source_clicked()
{
    ImgViev=0;
    a_controller->ChangeImgView(ImgViev);
   ui->label_main->setPixmap(a_controller->GetResizeImage());
}

void MainWindow::on_pushButton_clicked()
{
    a_controller->SetScale(ui->horizontalSlider->value());
    a_controller->UpdatePoints();
    ui->label_main->setPixmap(a_controller->GetResizeImage());
    ui->scale->setNum(1/(double(ui->horizontalSlider->value())/100));
}

void MainWindow::on_pushButton_2_clicked()
{

    a_controller->Binarization(ui->comboBox_3->currentIndex(),ui->comboBox_2->currentIndex());
    ui->pushButton_3->setEnabled(true);
    ui->pushButton_4->setEnabled(true);
    ui->pushButton_5->setEnabled(true);
    ui->binarization->setEnabled(true);

}

void MainWindow::on_pushButton_3_clicked()
{
    a_controller->InvertBinar();
    ui->label_main->setPixmap(a_controller->GetResizeImage());
}

void MainWindow::on_pushButton_4_clicked()
{
    a_controller->MinFiltr(ui->lineEdit->text().toUInt());
    ui->label_main->setPixmap(a_controller->GetResizeImage());
}

void MainWindow::on_pushButton_5_clicked()
{
    int C=0;
   ui->label_5->setNum( a_controller->Segmentation(ui->comboBox_4->currentIndex(),C,ui->lineEdit_2->text().toUInt()));
   ui->label_7->setNum(C);
    Graph_view();
    ui->segmentation->setEnabled(true);
}

void MainWindow::Graph_view()
{

    QVector<double> X,Y;
    a_controller->Calc_graph(X,Y);
    // set dark background gradient:
    QLinearGradient gradient(0, 0, 0, 400);
    gradient.setColorAt(0, QColor(90, 90, 90));
    gradient.setColorAt(0.38, QColor(105, 105, 105));
    gradient.setColorAt(1, QColor(70, 70, 70));
    ui->customPlot->setBackground(QBrush(gradient));

    // create empty bar chart objects:
    QCPBars *regen = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
    regen->setAntialiased(false); // gives more crisp, pixel aligned bar borders
    regen->setStackingGap(1);
    // set names and colors:
    regen->setName("segments");
    regen->setPen(QPen(QColor(0, 168, 140).lighter(130)));
    regen->setBrush(QColor(0, 168, 140));

    QVector<double> ticks;
    QVector<QString> labels;
    ticks << 1 << 2 << 3 << 4 << 5 << 6 << 7<< 8 << 9 << 10;
    labels << QString::number(X[0]) << QString::number(X[1]) << QString::number(X[2]) << QString::number(X[3]) <<QString::number(X[4]) <<QString::number(X[5])
           << QString::number(X[6]) << QString::number(X[7]) << QString::number(X[8]) <<QString::number(X[9]) ;
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    ui->customPlot->xAxis->setTicker(textTicker);
    ui->customPlot->xAxis->setTickLabelRotation(60);
    ui->customPlot->xAxis->setSubTicks(false);
    ui->customPlot->xAxis->setTickLength(0, 4);
    ui->customPlot->xAxis->setRange(0, 8);
    ui->customPlot->xAxis->setBasePen(QPen(Qt::white));
    ui->customPlot->xAxis->setTickPen(QPen(Qt::white));
    ui->customPlot->xAxis->grid()->setVisible(true);
    ui->customPlot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    ui->customPlot->xAxis->setTickLabelColor(Qt::white);
    ui->customPlot->xAxis->setLabelColor(Qt::white);

    // prepare y axis:
    ui->customPlot->yAxis->setRange(0, 12.1);
    ui->customPlot->yAxis->setPadding(5); // a bit more space to the left border
    ui->customPlot->yAxis->setLabel("Count");
    ui->customPlot->yAxis->setBasePen(QPen(Qt::white));
    ui->customPlot->yAxis->setTickPen(QPen(Qt::white));
    ui->customPlot->yAxis->setSubTickPen(QPen(Qt::white));
    ui->customPlot->yAxis->grid()->setSubGridVisible(true);
    ui->customPlot->yAxis->setTickLabelColor(Qt::white);
    ui->customPlot->yAxis->setLabelColor(Qt::white);
    ui->customPlot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    ui->customPlot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

    regen->setData(ticks, Y);

    // setup legend:
    ui->customPlot->legend->setVisible(true);
    ui->customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
    ui->customPlot->legend->setBrush(QColor(255, 255, 255, 100));
    ui->customPlot->legend->setBorderPen(Qt::NoPen);
    QFont legendFont = font();
    legendFont.setPointSize(10);
    ui->customPlot->legend->setFont(legendFont);
    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}

void MainWindow::on_pushButton_7_clicked()
{
    a_controller->SWA();
}

void MainWindow::on_pushButton_13_clicked()
{
    std::vector<std::vector<int>> sets(3);
    sets[0].resize(9);
    sets[1].resize(9);
    sets[2].resize(9);

    sets[0][0]=ui->Slider2_2->value();
    sets[0][1]=ui->comboBox_7->currentIndex();
    sets[0][2]=ui->comboBox_6->currentIndex();
    sets[0][3]=ui->line2_2->text().toUInt();
    sets[0][4]=ui->comboBox_9->currentIndex();
    sets[0][5]=ui->line3_2->text().toUInt();
    sets[0][6]=ui->checkBox_3->checkState();
    sets[0][7]=ui->checkBox_4->checkState();
    sets[0][8]=ui->checkBox_9->checkState();
    if(ui->checkBox_10->checkState()){
        sets[1][0]=ui->Slider2_3->value();
        sets[1][1]=ui->comboBox_8->currentIndex();
        sets[1][2]=ui->comboBox_10->currentIndex();
        sets[1][3]=ui->line2_3->text().toUInt();
        sets[1][4]=ui->comboBox_11->currentIndex();
        sets[1][5]=ui->line3_3->text().toUInt();
        sets[1][6]=ui->checkBox_5->checkState();
        sets[1][7]=ui->checkBox_6->checkState();
        sets[1][8]=ui->checkBox_13->checkState();
    }else{
        for(int i=9;i<17;i++){
            sets[1][i]=-1;
        }
    }
    if(ui->checkBox_11->checkState()){
        sets[2][0]=ui->Slider2_4->value();
        sets[2][1]=ui->comboBox_12->currentIndex();
        sets[2][2]=ui->comboBox_13->currentIndex();
        sets[2][3]=ui->line2_4->text().toUInt();
        sets[2][4]=ui->comboBox_14->currentIndex();
        sets[2][5]=ui->line3_4->text().toUInt();
        sets[2][6]=ui->checkBox_7->checkState();
        sets[2][7]=ui->checkBox_8->checkState();
        sets[2][8]=ui->checkBox_14->checkState();
    }else{
        for(int i=16;i<24;i++){
            sets[2][i]=-1;
        }
    }
    int inv=ui->checkBox_12->checkState();
    //if(sets[0][7]||sets[1][7]&&ui->checkBox_10->checkState()||sets[2][7]&&ui->checkBox_11->checkState())Stat=load_stat();
}

void MainWindow::on_pushButton_14_clicked()
{
    folder=QFileDialog::getOpenFileName(this,"z","","*.jpg");
    ui->label_37->setText(folder);
    ui->label_15->setText("");
}

void MainWindow::on_pushButton_12_clicked()
{
    folder=QFileDialog::getExistingDirectory();
    ui->label_15->setText(folder);
     ui->label_37->setText("");
}

void MainWindow::on_manual_clicked()
{
    QMessageBox mess(this);
        mess.setText("Программа предназначена для подсчета поголовья северных оленей на аэрофотоснимке."
                     "\n\nПрограмма позволяет ставить на фото три разных по цвету метки для самца, самки и теленка.,"
                     "На дисплее отображается число поставленных меток каждого цвета и их сумма.");
        mess.open();
        mess.exec();
}

void MainWindow::on_pushButton_6_clicked()
{
    on_pushButton_2_clicked();
    if(ui->checkBox_3->checkState())on_pushButton_3_clicked();
    on_pushButton_4_clicked();
    on_pushButton_5_clicked();
    ui->segmentation->setEnabled(true);
    ui->binarization->setEnabled(true);
    ui->pushButton_3->setEnabled(true);
    ui->pushButton_4->setEnabled(true);
    ui->pushButton_5->setEnabled(true);
}

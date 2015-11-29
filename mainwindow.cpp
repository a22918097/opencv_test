#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "stereo_vision.h"

#include <QLabel>
using namespace cv;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // Pseudo color table ======================

    ui->setupUi(this);

    TopView tv(20, 200, 3000, 19.8, 1080, 750, 270, 125, 100);
    tv.pseudoColorTable();
    cv::Mat src = this->qimage_to_mat_cpy(*tv.color_table,CV_8UC3);
    cv::resize(src,src,cv::Size(300,15));
    //imshow("color",src);
    ui->label_color_table->setPixmap(QPixmap::fromImage(QImage((uchar*) src.data, src.cols, src.rows, src.step, QImage::Format_RGB888)));
    //    bm = cv::StereoBM::create(16, 9);
    //ui->label_color_table->setScaledContents(true) ;
    //disp_pseudo = cv::Mat::zeros(IMG_H, IMG_W, CV_8UC3);

}
MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::on_pushButton_Read_clicked()
{


    cap.open(0);
    capp.open(1);
    stereo_vision sv;
//    ui->label_color_table->setPixmap(QPixmap::fromImage(sv->color_table));

    sv.matchParamInitialize();



    if(!cap.isOpened() || !capp.isOpened())  // check if we succeeded
    {

        qDebug() << "camera is not open!";
        return;
    }
    fg_proc=true;
    while(fg_proc==true&&fg_pause==false)
    {
        //        Mat image;
        cap >> image;
        capp >> image2;
        cvtColor(image, dest,CV_BGR2RGB);
        cvtColor(image2, dest2,CV_BGR2RGB);
        image1 = QImage((uchar*) dest.data, dest.cols, dest.rows, dest.step, QImage::Format_RGB888);
        image3 = QImage((uchar*) dest2.data, dest2.cols, dest2.rows, dest2.step, QImage::Format_RGB888);
        //BM
        cv::Mat destGray,dest2Gray;
        cvtColor(dest,destGray,CV_RGB2GRAY);
        cvtColor(dest2,dest2Gray,CV_RGB2GRAY);
        sv.compute(destGray,dest2Gray,disp_raw);
        disp_raw.convertTo(disp,CV_8UC1);
        //sv.depthCalculation();
        ui->label_cam_L->setPixmap(QPixmap::fromImage(image1));
        ui->label_cam_R->setPixmap(QPixmap::fromImage(image3));
        ui->label_disp->setPixmap(QPixmap::fromImage(QImage::QImage(disp.data, disp.cols, disp.rows, disp.step, QImage::Format_Indexed8)));
        //ui->label_disp_2->setPixmap(QPixmap::fromImage(QImage::QImage(sv.disp_pseudo.data, sv.disp_pseudo.cols, sv.disp_pseudo.rows, sv.disp_pseudo.step, QImage::Format_Indexed8)));
        qApp->processEvents();
        waitKey(33);

    }

}

void MainWindow::on_pushButton_close_clicked()
{
    fg_proc=false;
    this->cap.release();
    this->capp.release();
    close();
    //    bm.release();
}

void MainWindow::on_actionClose_triggered()
{

    fg_proc=false;
    this->cap.release();
    this->capp.release();
    close();
}
void MainWindow::closeEvent(QCloseEvent *event)
{
    fg_proc=false;
    this->cap.release();
    this->capp.release();
    close();
}

void MainWindow::on_pushButton_pause_clicked()
{
    fg_pause=true;
    ui->save_L->setPixmap(QPixmap::fromImage(image1));
    ui->save_R->setPixmap(QPixmap::fromImage(image3));

}

void MainWindow::on_pushButton_play_clicked()
{
    fg_pause=false;
    ui->pushButton_Read->click();
}
void MainWindow::on_pushButton_save_clicked()
{

    QString fileName = QFileDialog::getSaveFileName(this,tr("Save Left image"), "G:", tr("Image Files (*.jpg )"));
    if(fileName=="")
        return;
    else
    {
        imwrite( fileName.toStdString(), image);//left
        //imwrite( fileName.toStdString(), image2);//right
    }
    QString fileName2 = QFileDialog::getSaveFileName(this,tr("Save right image"), "G:", tr("Image Files (*.jpg )"));
    if(fileName=="")
        return;
    else
    {
        imwrite( fileName2.toStdString(), image2);

    }
}
void MainWindow::svDisplay(cv::Mat *img_L, cv::Mat *img_R,cv::Mat *disp_pseudo)
{
    ui->label_cam_L->setPixmap(QPixmap::fromImage(QImage::QImage(img_L->data, img_L->cols, img_L->rows, img_L->step, QImage::Format_RGB888)).scaled(IMG_DIS_W, IMG_DIS_H));
    ui->label_cam_R->setPixmap(QPixmap::fromImage(QImage::QImage(img_R->data, img_R->cols, img_R->rows, img_R->step, QImage::Format_RGB888)).scaled(IMG_DIS_W, IMG_DIS_H));
    //    if (si->sv->input_mode == SV::INPUT_SOURCE::VIDEO) {
    //        ui->label_sv_frame_count->setText(QString::number(current_frame_count) + " / " + QString::number(sv_frame_count) + " frames");
    //        ui->label_sv_frame_count_2->setText(QString::number(current_frame_count) + " / " + QString::number(sv_frame_count) + " frames");
    //    }
    //    else if (si->sv->input_mode == SV::INPUT_SOURCE::CAM) {
    //        ui->label_sv_frame_count->setText(QString::number(current_frame_count) + " frames");
    //        ui->label_sv_frame_count_2->setText(QString::number(current_frame_count) + " frames");
    //    }
    ui->label_disp->setPixmap(QPixmap::fromImage(QImage::QImage(disp_pseudo->data, disp_pseudo->cols, disp_pseudo->rows, disp_pseudo->step, QImage::Format_RGB888)).scaled(IMG_DIS_DISP_W, IMG_DIS_DISP_H));


    // update topview
    //        if (ui->checkBox_sv_topview->isChecked()) {
    //            ui->label_top_view_sv->setPixmap(QPixmap::fromImage(QImage::QImage(topview->data, topview->cols, topview->rows, topview->step, QImage::Format_RGBA8888)).scaled(270, 750));
    //            ui->label_sv_detected->setPixmap(QPixmap::fromImage(QImage::QImage(img_detected->data, img_detected->cols, img_detected->rows, img_detected->step, QImage::Format_RGB888)).scaled(IMG_DIS_W, IMG_DIS_H));
    //        }
    //        lock_sv.unlock();
    //    }
    //    ui->label_sv_proc->setText(QString::number(si->sv->time_proc));

    //  ui->label_cam_L->update();
    //  ui->label_cam_R->update();
    // ui->label_disp->update();

    // qApp->processEvents();
}



Mat MainWindow::qimage_to_mat_cpy(const QImage img, int format)
{
    return cv::Mat(img.height(), img.width(), format,
                   const_cast<uchar*>(img.bits()),
                   img.bytesPerLine()).clone();
}

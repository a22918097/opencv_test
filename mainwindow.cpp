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
    // SV
    fg_capturing = false;
    // COM port
    for (int i = 0; i < 6; i++) {
        ui->comboBox_cam_device_index_L->addItem(QString::number(i));
        ui->comboBox_cam_device_index_R->addItem(QString::number(i));
    }
    // focal length
    ui->comboBox_camera_focal_length->addItem("16");
    ui->comboBox_camera_focal_length->addItem("12");
    ui->comboBox_camera_focal_length->addItem("4");
    fin_cam_param = new stereo_vision::camParam;
    fin_BM = new stereo_vision::matchParamBM;
    sv = new stereo_vision();

    paramRead();
    TopView tv(20, 200, 3000, 19.8, 1080, 750, 270, 125, 100);
    tv.pseudoColorTable();
    cv::Mat src = this->qimage_to_mat_cpy(*tv.color_table,CV_8UC3);
    cv::resize(src,src,cv::Size(300,15));
    // Initialization
    retrieveMatchParam();
    ui->label_color_table->setPixmap(QPixmap::fromImage(QImage((uchar*) src.data, src.cols, src.rows, src.step, QImage::Format_RGB888)));
    QObject::connect(sv, SIGNAL(updateGUI(cv::Mat *, cv::Mat *, cv::Mat *, cv::Mat *)), this, SLOT(svDisplay(cv::Mat *, cv::Mat *, cv::Mat *, cv::Mat *)));
    ui->checkBox_do_calibration->click();
    ui->checkBox_do_depth->click();
    //    bm = cv::StereoBM::create(16, 9);
    //ui->label_color_table->setScaledContents(true) ;
    //disp_pseudo = cv::Mat::zeros(IMG_H, IMG_W, CV_8UC3);

}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::camOpen()
{
    int L = ui->comboBox_cam_device_index_L->currentIndex();
    int R = ui->comboBox_cam_device_index_R->currentIndex();
    if (!sv->open(L, R)) {
        qDebug() <<"sv", "Error!", "Camera can NOT be opened.";
        sv->close();
        return;
    }
    else {
        qDebug() <<"Port's opened.";
    }
}
void MainWindow::on_pushButton_Read_clicked()
{
    camOpen();
    qDebug() << "read done";

    while(1){
    sv->dataExec();

    qApp->processEvents();
    waitKey(33);
    }

    //    }

}

void MainWindow::on_pushButton_close_clicked()
{
    fg_proc=false;
    sv->cam_L.release();
    sv->cam_R.release();
    //delete sv;
    close();
}

void MainWindow::on_actionClose_triggered()
{
    fg_proc=false;
    sv->cam_L.release();
    sv->cam_R.release();
    close();
}
void MainWindow::closeEvent(QCloseEvent *event)
{
    fg_proc=false;
    sv->cam_L.release();
    sv->cam_R.release();
    qDebug() << "closed";
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
Mat MainWindow::qimage_to_mat_cpy(const QImage img, int format)
{
    return cv::Mat(img.height(), img.width(), format,
                   const_cast<uchar*>(img.bits()),
                   img.bytesPerLine()).clone();
}

void MainWindow::on_checkBox_do_calibration_clicked(bool checked)
{
    if (checked) {
        // load camera calibration files
        if (!sv->loadRemapFile(ui->comboBox_camera_focal_length->currentText().toInt(), ui->lineEdit_base_line->text().toDouble())) {
            qDebug("cc", "Error!", "Calibration files can NOT be imported.");
            ui->checkBox_do_calibration->setChecked(false);
        }
        sv->fg_calib = true;
    }
    else
        sv->fg_calib = false;
}
bool MainWindow::cwdIsProjectFolder()
{
    project_path = QDir::current();
    QString current_folder = project_path.currentPath().section("/", -1, -1);
    if (current_folder == "release" || current_folder == "debug") {
        project_path.cdUp();
    }
    if (project_path.path().section("/", -1, -1) == "Fusion") {
        return true;
    }

    return false;
}
void MainWindow::paramRead()
{
    QFile fout(project_path.path() + "/basic_param.yml");
    if (!fout.exists()) {
        qDebug() <<("path", "Error!", "basic_param.yml is NOT existed.");
        return;
    }

    cv::FileStorage fs(project_path.path().toStdString() + "/basic_param.yml", cv::FileStorage::READ);

    cv::FileNode n;
    n = fs["stereoVision"];
    fin_cam_param->port_L = (int) n["port_L"];
    fin_cam_param->port_R = (int) n["port_R"];
    fin_cam_param->cam_focal_length = (int) n["cam_focal_length"];
    fin_cam_param->base_line = (double) n["base_line"];
    fin_cam_param->rig_height = (double) n["rig_height"];
    fin_cam_param->focal_length = (double) n["focal_length"];
    ui->comboBox_cam_device_index_L->setCurrentIndex(fin_cam_param->port_L);
    ui->comboBox_cam_device_index_R->setCurrentIndex(fin_cam_param->port_R);
    ui->comboBox_camera_focal_length->setCurrentIndex(fin_cam_param->cam_focal_length);
    ui->label_sv_rig_height->setText(QString::number(fin_cam_param->rig_height));//立體視覺系統架設的高度 110 cm
    ui->lineEdit_base_line->setText(QString::number(fin_cam_param->base_line));
    ui->label_sv_focal_length->setText(QString::number(fin_cam_param->focal_length));//校正用的焦距跟平常的光學焦距不太一樣

    //    n = fs["topView"];
    //    ui->spinBox_topview_r->setValue((int) n["row_interval"]);
    //    ui->spinBox_topview_c->setValue((int) n["col_interval"]);
    //    ui->spinBox_radar_topview_r->setValue((int) n["row_interval_radar"]);
    //    ui->spinBox_radar_topview_c->setValue((int) n["col_interval_radar"]);
    n = fs["stereoParamBM"];
    fin_BM->pre_filter_size = (int)(n["pre_filter_size"]);
    fin_BM->pre_filter_cap = (int)(n["pre_filter_cap"]);
    fin_BM->SAD_window_size = (int)(n["SAD_window_size"]);
    fin_BM->min_disp = (int)(n["min_disp"]);
    fin_BM->num_of_disp = (int)(n["num_of_disp"]);
    fin_BM->texture_thresh = (int)(n["texture_thresh"]);
    fin_BM->uniquenese_ratio = (int)(n["uniquenese_ratio"]);
    fin_BM->speckle_window_size = (int)(n["speckle_window_size"]);
    fin_BM->speckle_range = (int)(n["speckle_range"]);

    fs.release();
    fg_param_loaded = true;
}
void MainWindow::svDisplay(cv::Mat *img_L, cv::Mat *img_R, cv::Mat *disp, cv::Mat *disp_pseudo)
{
    ui->label_cam_img_L->setPixmap(QPixmap::fromImage(QImage::QImage(img_L->data, img_L->cols, img_L->rows, img_L->step, QImage::Format_RGB888)).scaled(IMG_DIS_W, IMG_DIS_H));
    ui->label_cam_img_R->setPixmap(QPixmap::fromImage(QImage::QImage(img_R->data, img_R->cols, img_R->rows, img_R->step, QImage::Format_RGB888)).scaled(IMG_DIS_W, IMG_DIS_H));
    //ui->label_sv_detected_obj->setText(QString::number(detected_obj));
    //    if (si->sv->input_mode == SV::INPUT_SOURCE::VIDEO) {
    //        ui->label_sv_frame_count->setText(QString::number(current_frame_count) + " / " + QString::number(sv_frame_count) + " frames");
    //        ui->label_sv_frame_count_2->setText(QString::number(current_frame_count) + " / " + QString::number(sv_frame_count) + " frames");
    //    }
    //    else if (si->sv->input_mode == SV::INPUT_SOURCE::CAM) {
    //        ui->label_sv_frame_count->setText(QString::number(current_frame_count) + " frames");
    //        ui->label_sv_frame_count_2->setText(QString::number(current_frame_count) + " frames");
    //    }

    if (ui->checkBox_do_depth->isChecked()) {
        //lock_sv.lockForRead();
        if (ui->checkBox_pseudo_color->isChecked()) {
            ui->label_disp->setPixmap(QPixmap::fromImage(QImage::QImage(disp_pseudo->data, disp_pseudo->cols, disp_pseudo->rows, disp_pseudo->step, QImage::Format_RGB888)).scaled(IMG_DIS_DISP_W, IMG_DIS_DISP_H));
        }
        else {
            ui->label_disp->setPixmap(QPixmap::fromImage(QImage::QImage(disp->data, disp->cols, disp->rows, disp->step, QImage::Format_Indexed8)).scaled(IMG_DIS_DISP_W, IMG_DIS_DISP_H));
        }

        // update topview
        //        if (ui->checkBox_sv_topview->isChecked()) {
        //            ui->label_top_view_sv->setPixmap(QPixmap::fromImage(QImage::QImage(topview->data, topview->cols, topview->rows, topview->step, QImage::Format_RGBA8888)).scaled(270, 750));
        //            ui->label_sv_detected->setPixmap(QPixmap::fromImage(QImage::QImage(img_detected->data, img_detected->cols, img_detected->rows, img_detected->step, QImage::Format_RGB888)).scaled(IMG_DIS_W, IMG_DIS_H));
        //        }
        //        lock_sv.unlock();
    }
    //    ui->label_sv_proc->setText(QString::number(si->sv->time_proc));

    ui->label_cam_img_L->update();
    ui->label_cam_img_R->update();
    //    ui->label_sv_detected_obj->update();
    //    ui->label_sv_frame_count->update();
    //    ui->label_sv_frame_count_2->update();
    ui->label_disp->update();
    //    ui->label_top_view_sv->update();
    //    ui->label_sv_detected->update();
    //    ui->label_sv_detected_display->update();
    //    ui->label_sv_proc->update();
    qApp->processEvents();
}
void MainWindow::on_checkBox_do_depth_clicked(bool checked)
{

    if (checked) {
        // Though disparity is scaled by 16, GUI takes scaled pixels. If not, the topview looks weird.
        sv->cam_param->param_r = sv->cam_param->focal_length * sv->cam_param->base_line;

        ui->checkBox_pseudo_color->setEnabled(true);
        //ui->checkBox_sv_topview->setEnabled(true);
        //ui->checkBox_sv_reproject->setEnabled(true);
        sv->fg_stereoMatch = true;
    }
    else {
        ui->checkBox_pseudo_color->setEnabled(false);
        //ui->checkBox_sv_topview->setEnabled(false);
        //ui->checkBox_sv_reproject->setEnabled(false);
        sv->fg_stereoMatch = false;
    }
}
void MainWindow::retrieveMatchParam()
{

    sv->cam_param->cam_focal_length     = fin_cam_param->cam_focal_length;
    sv->cam_param->base_line            = fin_cam_param->base_line;
    sv->cam_param->focal_length         = fin_cam_param->focal_length;
    sv->cam_param->rig_height           = fin_cam_param->rig_height;
    sv->param_bm->pre_filter_size     = fin_BM->pre_filter_size;
    sv->param_bm->pre_filter_cap      = fin_BM->pre_filter_cap;
    sv->param_bm->SAD_window_size     = fin_BM->SAD_window_size;
    sv->param_bm->min_disp            = fin_BM->min_disp;
    sv->param_bm->num_of_disp         = fin_BM->num_of_disp;
    sv->param_bm->texture_thresh      = fin_BM->texture_thresh;
    sv->param_bm->uniquenese_ratio    = fin_BM->uniquenese_ratio;
    sv->param_bm->speckle_window_size = fin_BM->speckle_window_size;
    sv->param_bm->speckle_range       = fin_BM->speckle_range;

    //sv->updateParamsSmp();
}

void MainWindow::on_checkBox_pseudo_color_clicked(bool checked)
{
    if (checked)
        sv->fg_pseudo = true;
    else
        sv->fg_pseudo = false;

}

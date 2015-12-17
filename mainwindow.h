#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define IMG_W 640
#define IMG_H 480
#define IMG_W_HALF 320
#define IMG_H_HALF 240
#define IMG_DIS_W 320
#define IMG_DIS_H 240
#define IMG_DIS_DISP_W 320
#define IMG_DIS_DISP_H 240
#include <QMainWindow>
#include "opencv2/opencv.hpp"
#include <QFileDialog>
#include <QString>
#include <QCameraInfo>
#include <QList>
#include <QDebug>
#include <QLabel>
#include <stereo_vision.h>

namespace Ui {
class MainWindow;
}

class MainWindow :public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    // disparity image
    cv::Mat disp_raw;
    cv::Mat disp;
    cv::Mat disp_pseudo;
    stereo_vision *sv;
    //QImage *color_table;                // psuedo-color table

private slots:
    void on_pushButton_close_clicked();

    void on_actionClose_triggered();
    void on_pushButton_pause_clicked();

    void on_pushButton_Read_clicked();

    void on_pushButton_play_clicked();

    void on_pushButton_save_clicked();
//    void svDisplay(cv::Mat *img_L, cv::Mat *img_R, cv::Mat *disp, cv::Mat *disp_pseudo, cv::Mat *topview, cv::Mat *img_detected, int detected_obj, int current_frame_count);
    void svDisplay(cv::Mat *img_L, cv::Mat *img_R, cv::Mat *disp, cv::Mat *disp_pseudo);
    /*
    // BM ===========================
    void change_bm_pre_filter_size(int value);

    void change_bm_pre_filter_cap(int value);

    void change_bm_sad_window_size(int value);

    void change_bm_min_disp(int value);

    void change_bm_num_of_disp(int value);

    void change_bm_texture_thresh(int value);

    void change_bm_uniqueness_ratio(int value);

    void change_bm_speckle_window_size(int value);

    void change_bm_speckle_range(int value);
    // BM =========================== End
*/

    void on_checkBox_do_calibration_clicked(bool checked);

    void on_checkBox_do_depth_clicked(bool checked);

    void on_checkBox_pseudo_color_clicked(bool checked);

private:
    void closeEvent(QCloseEvent *);
    Ui::MainWindow *ui;
    cv::Mat image;
    cv::Mat image2;
    bool fg_proc;
    bool fg_pause=false;
    cv::VideoCapture cap;
    cv::VideoCapture capp;
    cv::Mat dest;
    cv::Mat dest2;
    QImage image3;
    QImage image1;
    void camOpen();
    bool fg_capturing;
//    cv::Ptr<cv::StereoBM> bm;
   // void matchParamInitialize();

    cv::Mat qimage_to_mat_cpy(const QImage img, int format);
    bool cwdIsProjectFolder();               // find the project folder for loading files
    //確認當前dir是不是專案資料夾 因為我引用校正檔案的路徑是採相對路徑

    // Read params ============
    bool fg_param_loaded;               // check wether the paramerters are loaded

    // file in & out
    stereo_vision::camParam* fin_cam_param;
    stereo_vision::matchParamBM* fin_BM;
    int fin_lrf_port, fin_lrf_baud_rate, fin_lrf_scale, fin_lrf_res;

    void paramRead();                   // read params from basic_param.yml

    void paramWrite(); //param是為了記住我每次BM SGBM或UI上微調的參數

    void paramUpdate();
    // Stereo vision param ====
    //stereoMatchParamForm *form_smp;

    bool fg_form_smp_alloc;

    void retrieveMatchParam();
};

#endif // MAINWINDOW_H

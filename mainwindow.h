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


    //QImage *color_table;                // psuedo-color table

private slots:
    void on_pushButton_close_clicked();

    void on_actionClose_triggered();
    void closeEvent(QCloseEvent *event);


    void on_pushButton_pause_clicked();

    void on_pushButton_Read_clicked();

    void on_pushButton_play_clicked();

    void on_pushButton_save_clicked();


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

private:
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
    void MainWindow::svDisplay(cv::Mat *img_L, cv::Mat *img_R,cv::Mat *disp_pseudo);
//    cv::Ptr<cv::StereoBM> bm;
   // void matchParamInitialize();

    cv::Mat qimage_to_mat_cpy(const QImage img, int format);
};

#endif // MAINWINDOW_H

#ifndef STEREO_VISION_H
#define STEREO_VISION_H

#include "QObject"
#include <opencv2/opencv.hpp>
#include <QTime>
#include <QDebug>
// topview
#include "topview.h"
// Sensor base
#include "sensorbase.h"
#include <QDir>
extern QDir project_path;
#define IMG_W 640
#define IMG_H 480
#define IMG_W_HALF 320
#define IMG_H_HALF 240
#define IMG_DIS_W 320
#define IMG_DIS_H 240
#define IMG_DIS_DISP_W 320
#define IMG_DIS_DISP_H 240

#define GROUND_RANGE 20
namespace SV {
enum STATUS {
    OK = 0,
    NO_INPUT = -1,
    NO_UPDATE = -2,
    NO_RECTIFYIMAGE = -3
};

enum STEREO_MATCH {
    SGBM,
    BM
};

enum INPUT_SOURCE {
    CAM,
    VIDEO,
    IMG
};
}
class stereo_vision : public QObject,public TopView, protected SensorBase
{
    Q_OBJECT

public:
    explicit stereo_vision();

    ~stereo_vision();
    //    stereo_vision();
    void guiUpdate();
    int match_mode;
    void close();
    void matchParamInitialize();
    bool open(int device_index_L, int device_index_R);
    bool loadRemapFile(int cam_focal_length, double base_line);
    // status
    int input_mode;
    bool fg_calib;                      // check whether the calibration button is checked
    bool fg_stereoMatch;                // check whether do the correspondence matching
    bool fg_pseudo;                     // checK whether pesudo the disparity image
    bool fg_topview;                    // check whether project to topview
    bool fg_reproject;                  // check whether re-project detected objects to image
    bool fg_tracking;                   // it's true when object tracking is activated
    bool fg_topview_plot_points;        // check wethere to plot each points on the topview
    bool fg_ground_filter;
    void compute(cv::Mat& dest,cv::Mat& dest2,cv::Mat& disp_raw);
    void depthCalculation();
    void closecam();
    void opencam();
    // capture from camera =========
    int device_index_L;
    int device_index_R;
    cv::VideoCapture cam_L;
    cv::VideoCapture cam_R;
    // capture from camera ========= End
    // calibrated images
    cv::Mat img_r_L;
    cv::Mat img_r_R;
    // RGB images for displaying
    cv::Mat img_L;
    cv::Mat img_R;
    // cv::Mat type capture image ==
    cv::Mat cap_L;
    cv::Mat cap_R;
    // status ======================
    // disparity image
    cv::Mat disp_raw;
    cv::Mat disp;
    cv::Mat disp_pseudo;
    // depth estimatiom
    struct camParam
    {
        int port_L;
        int port_R;
        double param_r;
        double focal_length;
        int cam_focal_length;
        double base_line;
        double rig_height;
    };
    camParam* cam_param;


    // data - stereo vision ========
    struct StereoData
    {
        // IMAGE -------------
        float disp;

        // World coordinate system (WCS) (cm)
        int X;
        int Y;
        int Z;

        bool ground_cand;               // recognized as ground by v-disparity algorithm

        // GRIDMAP -----------
        std::pair<int, int> grid_id;    // located cell in topview

        StereoData() {
            disp = -1;
            X = -1;
            Y = -1;
            Z = -1;
            ground_cand = false;
            grid_id = std::pair<int, int>(-1, -1);
        }
    };

    StereoData** data;
    struct matchParamBM
    {
        int pre_filter_size;
        int pre_filter_cap;
        int SAD_window_size;
        int min_disp;
        int num_of_disp;
        int texture_thresh;
        int uniquenese_ratio;
        int speckle_window_size;
        int speckle_range;
    };
    matchParamBM* param_bm;
    int dataExec();
    //int guiUpdate();
private:


    int* LUT_grid_row;                  // depth -> grid map row
    int* LUT_grid_col;                  // image col -> grid map col
    int* LUT_depth;                     // grid map row -> depth
    int* LUT_img_col;                   // grid map col -> image col
    void updateDataForDisplay();
    void createLUT();
    int corrGridRow(int k);
    int corrGridCol(int k);

    void resetOpen(int device_index_L, int device_index_R);

    bool camCapture();


    bool dataIn();

    bool rectifyImage();
    bool fg_proc;
    bool fg_pause;

    bool vDispCalculation();

    float point2Line(cv::Point pt, cv::Point line_1, cv::Point line_2);

    void stereoMatch();

    QTime t_p;                          // process time of all exec.


    bool fg_cam_L, fg_cam_R;            // open or not
    bool fg_cam_opened;                 // check if cams are opened
    bool fg_calib_loaded;               // load the calibration files or not
    QTime t;                            // control gui not to update too fast
    int time_gap;
    // status ====================== End
    cv::Mat img_match_L;
    cv::Mat img_match_R;
    cv::Ptr<cv::StereoBM> bm;

    // stereo calibration stuffs ===
    QDir remap_path;
    QString remap_folder;
    QString remap_file;
    cv::Mat rmapLx, rmapLy, rmapRx, rmapRy;
    cv::Rect calibROI[2];
private slots:
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
signals:
    void updateGUI(cv::Mat *img_L, cv::Mat *img_R, cv::Mat *disp, cv::Mat *disp_pseudo);
    //void updateGUI(cv::Mat *img_L, cv::Mat *img_R, cv::Mat *disp, cv::Mat *disp_pseudo, cv::Mat *topview, cv::Mat *img_detected, int detected_obj, int current_frame_count);

};




#endif // STEREO_VISION_H

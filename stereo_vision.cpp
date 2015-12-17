#include "stereo_vision.h"
stereo_vision::stereo_vision():TopView(20, 200, 3000, 19.8, 1080, 750, 270, 125, 100)
{
    device_index_L = -1;
    device_index_R = -1;
    fg_cam_L = false;
    fg_cam_R = false;
    fg_cam_opened = false;
    fg_calib_loaded = false;
    fg_calib = false;
    fg_stereoMatch = false;
    fg_reproject = false;
    fg_tracking = true;
    fg_topview_plot_points = false;
    fg_ground_filter = true;
    data = new StereoData *[IMG_H];
    for (int r = 0; r < IMG_H; r++) {
        data[r] = new StereoData[IMG_W];
    }
    cam_param = new camParam;
    param_bm = new matchParamBM;
    img_L = cv::Mat::zeros(IMG_H, IMG_W, CV_8UC3);
    img_R = cv::Mat::zeros(IMG_H, IMG_W, CV_8UC3);
    disp_pseudo = cv::Mat::zeros(IMG_H, IMG_W, CV_8UC3);
    bm = cv::StereoBM::create(16, 9);
    cam_param = new camParam;

    matchParamInitialize();

}
bool stereo_vision::camCapture()
{
    if (cam_L.isOpened()) {
        cam_L >> cap_L;
        cv::cvtColor(cap_L, img_L, cv::COLOR_BGR2RGB);
        imshow("img_L",img_L);
    }
    else
        return false;
    if (cam_R.isOpened()) {
        cam_R >> cap_R;
        cv::cvtColor(cap_R, img_R, cv::COLOR_BGR2RGB);
        imshow("img_R",img_R);
    }
    else
        return false;

    return true;
}
void stereo_vision::resetOpen(int device_index_L, int device_index_R)
{
    if (this->device_index_L != device_index_L) {
        cam_L.release();
        fg_cam_L = false;
    }
    if (this->device_index_R != device_index_R) {
        cam_R.release();
        fg_cam_R = false;
    }

}
bool stereo_vision::open(int device_index_L, int device_index_R)
{
    resetOpen(device_index_L, device_index_R);
    if (fg_cam_L && fg_cam_R)
        return true;
    if (device_index_L == device_index_R || device_index_L < 0 || device_index_R < 0)
        return false;
    if (!cam_L.isOpened()) {
        if (cam_L.open(device_index_L)) {
            if (cam_L.isOpened()) {
                cam_L.set(cv::CAP_PROP_FRAME_WIDTH, IMG_W);
                cam_L.set(cv::CAP_PROP_FRAME_HEIGHT, IMG_H);
                fg_cam_L = true;
                this->device_index_L = device_index_L;
                qDebug()<<"open L";
            }
        }
        else {
            qDebug()<<"fail L";
        }
    }
    if (!cam_R.isOpened()) {
        if (cam_R.open(device_index_R)) {
            if (cam_R.isOpened()) {
                cam_R.set(cv::CAP_PROP_FRAME_WIDTH, IMG_W);
                cam_R.set(cv::CAP_PROP_FRAME_HEIGHT, IMG_H);
                fg_cam_R = true;
                this->device_index_R = device_index_R;
                qDebug()<<"open R";
            }
        }
        else {
                qDebug()<<"fail R";
        }
    }
    if (fg_cam_L && fg_cam_R)
        fg_cam_opened = true;
    else
        fg_cam_opened = false;

    return fg_cam_opened;
}
void stereo_vision::closecam()
{
    if (cam_L.isOpened())
        cam_L.release();
    if (cam_R.isOpened())
        cam_R.release();
}
bool stereo_vision::loadRemapFile(int cam_focal_length, double base_line)
{

    // The folder of calibration files should be placed under project's folder
    // check whether the file has been loaded
    if (fg_calib_loaded && this->cam_param->cam_focal_length == cam_focal_length && this->cam_param->base_line == base_line)
        return fg_calib_loaded;

    // find files under which folder and find the folder with calibration files
    remap_folder = "calibrationImgs";
    remap_file = QString("My_Data_" + QString::number(cam_focal_length) + "_" + QString::number(base_line) + ".yml");
    remap_path = project_path;
    if (!remap_path.exists(remap_folder))
        return fg_calib_loaded;
    remap_path.cd(remap_folder);

#ifdef debug_info_sv
    qDebug()<<"path exist: "<<remap_path.exists()<<"path: "<<remap_path.path();
#endif
    if (!remap_path.exists())
        return fg_calib_loaded;

    cv::FileStorage fs(QString(remap_path.path() + "/" + remap_file).toStdString().c_str(), cv::FileStorage::READ);

    if (!fs.isOpened())
        return fg_calib_loaded;

    // rewrite params
    fs["reMapLx"] >> rmapLx;
    fs["reMapLy"] >> rmapLy;
    fs["reMapRx"] >> rmapRx;
    fs["reMapRy"] >> rmapRy;
    fs["ROI0x"] >> calibROI[0].x;
    fs["ROI0y"] >> calibROI[0].y;
    fs["ROI0w"] >> calibROI[0].width;
    fs["ROI0h"] >> calibROI[0].height;
    fs["ROI1x"] >> calibROI[1].x;
    fs["ROI1y"] >> calibROI[1].y;
    fs["ROI1w"] >> calibROI[1].width;
    fs["ROI1h"] >> calibROI[1].height;
    fs.release();
    //qDebug() << fg_calib_loaded;
    this->cam_param->cam_focal_length = cam_focal_length;
    this->cam_param->base_line = base_line;
    fg_calib_loaded = true;
    //qDebug() << fg_calib_loaded;
    return fg_calib_loaded;
}
bool stereo_vision::dataIn()
{
//    switch (input_mode) {
//    // camera capturing
//    case SV::INPUT_SOURCE::CAM:
        if (!camCapture())
            return false;

//        if (re.vr->fg_record) {
//            cv::Mat img_merge = cv::Mat(IMG_H, 2 * IMG_W, CV_8UC3);
//            re.vr->combineTwoImages(&img_merge, img_L, img_R, cv::Size(img_L.cols, img_L.rows));
//            re.recordData(img_merge);
//        }
//        break;
//    case SV::INPUT_SOURCE::VIDEO:
//        // For synchronization replay
//        if (re.tr->fg_loaded && re.vr->fg_loaded)
//            if (!re.tr->fg_data_end && re.tr->current_frame_count < re.vr->current_frame_count) {
////                std::cout<<re.tr->fg_data_end<<" "<<re.tr->current_frame_count<<" "<<re.vr->current_frame_count;
//                return false;
//            }
//        if (!re.vr->segmentTwoImages(&img_L, &img_R, cv::Size(IMG_W, IMG_H))) {
//            emit videoEnd();
//            return false;
//        }
//        break;
//    case SV::INPUT_SOURCE::IMG:
////        img_L = ;
////        img_R = ;
//        break;
//    }

//    re.vr->current_frame_count++;

    return true;
}
bool stereo_vision::rectifyImage()
{
    if (fg_calib_loaded) {
        cv::remap(img_L, img_r_L, rmapLx, rmapLy, cv::INTER_LINEAR);
        cv::remap(img_R, img_r_R, rmapRx, rmapRy, cv::INTER_LINEAR);
        return true;
    }

    return false;
}
void stereo_vision::stereoMatch()
{
// qDebug () << "stereoMatch";
    // pre-processing
    cv::cvtColor(img_r_L, img_match_L, cv::COLOR_BGR2GRAY);
    cv::cvtColor(img_r_R, img_match_R, cv::COLOR_BGR2GRAY);

    cv::equalizeHist(img_match_L, img_match_L);
    cv::equalizeHist(img_match_R, img_match_R);

    cv::GaussianBlur(img_match_L, img_match_L, cv::Size(7, 7), 0, 0);
    cv::GaussianBlur(img_match_R, img_match_R, cv::Size(7, 7), 0, 0);
    //imshow("img_match_L",img_match_L);
    //imshow("img_match_R",img_match_R);

    bm->compute(img_match_L, img_match_R, disp_raw);
    disp_raw.convertTo(disp, CV_8UC1);
    //imshow("disp",disp);

//     depth calculation of points from disp [merge into stereo_vision::depthCalculation]
}
void stereo_vision::depthCalculation ()
{
    //qDebug() << "depthCalculation";
    disp_raw.convertTo(disp,CV_8UC1);
    //imshow("disp",disp);

    if (fg_pseudo)
        disp_pseudo.setTo(0);
    uchar* ptr_color = color_table->scanLine(0);
    //lock_sv_data.lockForWrite();
    for (int r = 0; r < IMG_H; r++) {
        short int* ptr_raw = (short int*)(disp_raw.data + r * disp_raw.step);
        uchar* ptr = (uchar*)(disp_pseudo.data + r * disp_pseudo.step);
        for (int c = 0; c < IMG_W; c++) {
            // non-overlapping part
            if (c < param_bm->num_of_disp / 2)
                continue;
            // Depth calculation
            float val = ptr_raw[c];

            data[r][c].disp = val / 16.0;

            if (data[r][c].disp > 0) {
                data[r][c].Z = cam_param->param_r / data[r][c].disp;
                data[r][c].X = (c - IMG_W_HALF) * data[r][c].Z / cam_param->focal_length;
                data[r][c].Y = (IMG_H_HALF - r) * data[r][c].Z / cam_param->focal_length + cam_param->rig_height;

                // pseudo color transform
                if (fg_pseudo) {
                    int z_est;
                    z_est = data[r][c].Z;
                    //                        std::cout<<z_est<<" ";
                    if (z_est >= min_distance && z_est <= max_distance) {
                        int jj = z_est - min_distance;
                        ptr[3 * c + 0] = ptr_color[3 * jj + 0];
                        ptr[3 * c + 1] = ptr_color[3 * jj + 1];
                        ptr[3 * c + 2] = ptr_color[3 * jj + 2];
                    }
                    // out of max_distance
                    else if (z_est > max_distance) {
                        ptr[3 * c + 0] = 140;
                        ptr[3 * c + 1] = 0;
                        ptr[3 * c + 2] = 168;
                    }
                    // below the min_distance
                    else {
                        ptr[3 * c + 0] = 0;
                        ptr[3 * c + 1] = 0;
                        ptr[3 * c + 2] = 0;
                    }
                }
            }
            // unmatched
            else {
                data[r][c].Z = -1;
                data[r][c].X = -1;
                data[r][c].Y = -1;
                ptr[3 * c + 0] = 100;
                ptr[3 * c + 1] = 100;
                ptr[3 * c + 2] = 100;
                //                    std::cout<<"0 ";
            }
        }
        //            std::cout<<std::endl;
    }
    //lock_sv_data.unlock();
    //imshow("disp_pseudo",disp_pseudo);
}

int stereo_vision::dataExec()
{

    if (!dataIn()) {
    return SV::STATUS::NO_INPUT;
    }
//    qDebug () << "dataExec";
    // camera calibration
    if (fg_calib) {
        if (!rectifyImage())
            return SV::STATUS::NO_RECTIFYIMAGE;
    }
    else {
        img_r_L = img_L.clone();
        img_r_R = img_R.clone();
    }

    // stereo matching
    if (fg_stereoMatch) {
        stereoMatch();
          depthCalculation();

    }

    else {
        disp.setTo(0);
        disp_pseudo.setTo(0);
        //img_detected.setTo(0);
    }
    //updateDataForDisplay();

    return SV::STATUS::OK;
}
void stereo_vision::change_bm_pre_filter_size(int value)
{
    bm->setPreFilterSize(value);
    param_bm->pre_filter_size = value;
#ifdef debug_info_sv_param
    qDebug()<<bm->getPreFilterSize();
#endif
}

void stereo_vision::change_bm_pre_filter_cap(int value)
{
    bm->setPreFilterCap(value);
    param_bm->pre_filter_cap = value;
#ifdef debug_info_sv_param
    qDebug()<<bm->getPreFilterCap();
#endif
}

void stereo_vision::change_bm_sad_window_size(int value)
{
    bm->setBlockSize(value);
    param_bm->SAD_window_size = value;
#ifdef debug_info_sv_param
    qDebug()<<bm->getBlockSize();
#endif
}

void stereo_vision::change_bm_min_disp(int value)
{
    bm->setMinDisparity(value);
    param_bm->min_disp = value;
#ifdef debug_info_sv_param
    qDebug()<<bm->getMinDisparity();
#endif
}

void stereo_vision::change_bm_num_of_disp(int value)
{
    bm->setNumDisparities(value);
    param_bm->num_of_disp = value;
#ifdef debug_info_sv_param
    qDebug()<<bm->getNumDisparities();
#endif
}

void stereo_vision::change_bm_texture_thresh(int value)
{
    bm->setTextureThreshold(value);
    param_bm->texture_thresh = value;
#ifdef debug_info_sv_param
    qDebug()<<bm->getTextureThreshold();
#endif
}

void stereo_vision::change_bm_uniqueness_ratio(int value)
{
    bm->setUniquenessRatio(value);
    param_bm->uniquenese_ratio = value;
#ifdef debug_info_sv_param
    qDebug()<<bm->getUniquenessRatio();
#endif
}

void stereo_vision::change_bm_speckle_window_size(int value)
{
    bm->setSpeckleWindowSize(value);
    param_bm->speckle_window_size = value;
#ifdef debug_info_sv_param
    qDebug()<<bm->getSpeckleWindowSize();
#endif
}

void stereo_vision::change_bm_speckle_range(int value)
{
    bm->setSpeckleRange(value);
    param_bm->speckle_range = value;
#ifdef debug_info_sv_param
    qDebug()<<bm->getSpeckleRange();
#endif
}

stereo_vision::~stereo_vision()
{
    delete cam_param;
    delete param_bm;

    for (int i = 0; i < IMG_H; i++) {
        delete[] data[i];
    }
    delete[] data;

//    //delete[] objects;
//    //delete[] objects_display;

//    delete[] LUT_grid_row;
//    delete[] LUT_grid_col;

//    delete[] LUT_depth;
//    delete[] LUT_img_col;

//    close();

    bm.release();
}
void stereo_vision::close()
{
    if (cam_L.isOpened())
        cam_L.release();
    if (cam_R.isOpened())
        cam_R.release();
}
void stereo_vision::matchParamInitialize()
{
    // default initialization
    int SAD_window_size = 0, number_disparity = 128;  // 0

    //        bm->setROI1(roi1);
    //        bm->setROI2(roi2);
    //設定參數
    bm = cv::StereoBM::create(16, 9);
    bm->setPreFilterCap(31);
    bm->setBlockSize(SAD_window_size > 0 ? SAD_window_size : 9);
    bm->setMinDisparity(0);
    bm->setNumDisparities(number_disparity);
    bm->setTextureThreshold(10);
    bm->setUniquenessRatio(15);
    bm->setSpeckleWindowSize(100);
    bm->setSpeckleRange(32);
    bm->setDisp12MaxDiff(1);

}
//int stereo_vision::guiUpdate()
void stereo_vision::guiUpdate()
{
    //if (t.elapsed() > time_gap) {
        //emit updateGUI(&img_r_L, &img_r_R, &disp, &disp_pseudo, &topview, &img_detected, detected_obj, re.vr->current_frame_count);
    emit updateGUI(&img_r_L, &img_r_R, &disp, &disp_pseudo);
        //t.restart();
        //time_proc = t_p.restart();
        //return SV::STATUS::OK;
    //}
    //return SV::STATUS::NO_UPDATE;
}

#include "stereo_vision.h"

stereo_vision::stereo_vision():TopView(20, 200, 3000, 19.8, 1080, 750, 270, 125, 100)
{
    img_L = cv::Mat::zeros(IMG_H, IMG_W, CV_8UC3);
    img_R = cv::Mat::zeros(IMG_H, IMG_W, CV_8UC3);
    disp_pseudo = cv::Mat::zeros(IMG_H, IMG_W, CV_8UC3);
}
void stereo_vision::stereoMatch()
{
    // pre-processing
    cv::cvtColor(img_r_L, img_match_L, cv::COLOR_BGR2GRAY);
    cv::cvtColor(img_r_R, img_match_R, cv::COLOR_BGR2GRAY);

    cv::equalizeHist(img_match_L, img_match_L);
    cv::equalizeHist(img_match_R, img_match_R);

    cv::GaussianBlur(img_match_L, img_match_L, cv::Size(7, 7), 0, 0);
    cv::GaussianBlur(img_match_R, img_match_R, cv::Size(7, 7), 0, 0);
    bm->compute(img_match_L, img_match_R, disp_raw);
    disp_raw.convertTo(disp, CV_8UC1);

    // depth calculation of points from disp [merge into stereo_vision::depthCalculation]
}
void stereo_vision::depthCalculation ()
{

    //compute(destGray,dest2Gray,disp_raw);
            disp_raw.convertTo(disp,CV_8UC1);
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
}
int stereo_vision::dataExec()
{
    //if (!dataIn()) {
    return SV::STATUS::NO_INPUT;
    //}

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
bool stereo_vision::rectifyImage()
{
    if (fg_calib_loaded) {
        cv::remap(img_L, img_r_L, rmapLx, rmapLy, cv::INTER_LINEAR);
        cv::remap(img_R, img_r_R, rmapRx, rmapRy, cv::INTER_LINEAR);
        return true;
    }

    return false;
}
stereo_vision::~stereo_vision()
{
//    delete cam_param;
//    delete param_bm;

//    for (int i = 0; i < IMG_H; i++) {
//        delete[] data[i];
//    }
//    delete[] data;

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

void stereo_vision::compute(cv::Mat &dest, cv::Mat &dest2, cv::Mat &disp_raw)
{

    bm->compute(dest,dest2,disp_raw);

}
void stereo_vision::GUIdispaly(){

}

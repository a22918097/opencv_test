#ifndef SENSORINFO_H
#define SENSORINFO_H

#include <opencv2/opencv.hpp>

#include <QReadWriteLock>
// Stereo vision
#include "stereo_vision.h"
//#include "stereomatchparamform.h"
namespace SENSOR {
enum {
    SV,
    RADAR,
    LRF
};
}
class SensorInfo : public QObject
{
    Q_OBJECT
public:
    SensorInfo();

    ~SensorInfo();

    stereo_vision* sv;
// Status =================
    bool fg_proc;
    bool fg_sv;
    bool fg_sv_each_pixel;
    bool fg_radar;
    bool fg_data_update;
    bool fg_fusion;
    bool fg_ot;
    bool fg_ot_trajectory;
    bool fg_ot_trajectory_raw;
    bool fg_ot_trajectory_kalman;
    bool fg_ot_vel;
    bool fg_ot_kf;
    bool fg_ot_pf;
    bool fg_ca_astar;
    bool fg_ca_vfh;
    bool fg_fused_region_display_only;
    bool fg_display_literature_mode;
    // Status ================= End

    // Sensors' information ===
    //!
    //! \brief Retrieving data from stereo vision.
    //! \return int status
    //!
    int svDataExec();
void dataExec();
private:
    // sensor location
    struct sensorLocation {
        // sensor's position based on the center of vehicle. (cm) forward is x+, lateral right is y+.
        cv::Point2f pos;

        // Orientation of sensor (degree). Forward is set as zero and counting clockwisely.
        float theta;
    };
// Information of objects detected by different sensors
    // Based on fused topview
    struct sensorInformation {
        sensorLocation location;                    // Sensor location

        cv::Point pos_pixel;                        // (pixel)

        float angle_half_fov;                       // the half fov for displaying (degree)

        cv::Scalar color;                           // color of different sensors on the fused topview

        cv::Scalar color_fov;                       // color of fov lines

        sensorInformation() {
            pos_pixel = cv::Point(-1, -1);

            angle_half_fov = -1.0;

            color = cv::Scalar(0, 0, 0);

            color_fov = cv::Scalar(200, 200, 200, 255);
        }
    };

    sensorInformation *sensors;

    struct vehicleInfo {
        cv::Point VCP;                              // fused topview vehicle current position (pixel)

        double width;                               // average vehicle's size (cm)

        double length;                              // (cm)

        int width_pixel;                            // (pixel)

        int length_pixel;                           // (pixel)

        double head_pos;                            // (cm)

        int head_pos_pixel;                         // (pixel)

        cv::Rect rect;                              // (pixel)

        cv::Scalar color;                           // vehicle color
    } vehicle;

    int gap = 500;

    enum {
        CT_WCS2SCS,
        CT_SCS2WCS
    };
//! \brief coordinateTransform. The transformation of coordinates system
    //! \param int type
    //! \param cv::Point sensor_pos
    //! \param SensorBase::PC pc_in
    //! \return SensorBase::PC pc_out
    //!
    SensorBase::PC coordinateTransform(int type, cv::Point sensor_pos, SensorBase::PC pc_in);
signals:
    void updateGUI(cv::Mat *fused_topview, cv::Mat *img_detected_display);

    void guiDisplay(int type, bool fg_on);
};

#endif // SENSORINFO_H


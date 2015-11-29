#include "sensorinfo.h"

SensorInfo::SensorInfo()
{
    //**// You may CRASH if you add lots of sensors but you don't revise the number of the array
    // sensor information
    sensors = new sensorInformation[3];

    // Initialization
    sv = new stereo_vision();
}
SensorInfo::~SensorInfo()
{
    delete sv;
}
/*void SensorInfo::chooseVehicle(int vehicle_type)
{
    switch (vehicle_type) {
    case VEHICLE::CART:
        // choose cart
        vehicle.width = 43;
        vehicle.length = 43;
        vehicle.head_pos = vehicle.length / 2;

        sensors[SENSOR::SV].location.pos = cv::Point2f(0, 29.5);
        sensors[SENSOR::SV].location.theta = 0.0;
        sensors[SENSOR::RADAR].location.pos = cv::Point2f(0, vehicle.head_pos);
        sensors[SENSOR::RADAR].location.theta = 0.0;
        break;
    case VEHICLE::CAR:
        // choose car: TOYOTA Camry
        vehicle.width = 183;
        vehicle.length = 485;
        vehicle.head_pos = vehicle.length / 2;

        sensors[SENSOR::SV].location.pos = cv::Point2f(0, 75);
        sensors[SENSOR::SV].location.theta = 0.0;
        sensors[SENSOR::RADAR].location.pos = cv::Point2f(0, vehicle.head_pos);
        sensors[SENSOR::RADAR].location.theta = 0.0;
        break;
    case VEHICLE::TRACTOR:
        vehicle.width = 125;
        vehicle.length = 295;
        vehicle.head_pos = vehicle.length / 2;

        sensors[SENSOR::SV].location.pos = cv::Point2f(-16.5, 302 - vehicle.length / 2);
        sensors[SENSOR::SV].location.theta = 0.0;
        sensors[SENSOR::RADAR].location.pos = cv::Point2f(0, 301 - vehicle.length / 2);
        sensors[SENSOR::RADAR].location.theta = 0.0;
        break;
    }

    vehicle.width_pixel = vehicle.width * ratio;
    vehicle.length_pixel = vehicle.length * ratio;
    // find max & min detection range in all sensors, so this function shall be called after initialization of all sensors
    max_detection_range = rc->max_distance;
    min_detection_range = rc->min_distance + sqrt(pow(0.5 * vehicle.length, 2) + pow(0.5 * vehicle.width, 2));

    updateFusedTopView();
}*/



SensorBase::PC SensorInfo::coordinateTransform(int type, cv::Point sensor_pos, SensorBase::PC pc_in)
{
    double range = pc_in.range;
    double angle = pc_in.angle;
    SensorBase::PC pc_out;
    switch (type) {
    case CT_SCS2WCS:
        double x_world, z_world; // (cm)
        x_world = (double)(range * sin(angle * CV_PI / 180.0) + sensor_pos.x);
        z_world = (double)(range * cos(angle * CV_PI / 180.0) + sensor_pos.y - vehicle.head_pos_pixel);

        pc_out.angle = atan(x_world / z_world) * 180.0 / CV_PI;
        pc_out.range = sqrt(pow(x_world, 2) + pow(z_world, 2));
        break;
    case CT_WCS2SCS:
        break;
    }

    return pc_out;
}

/*int SensorInfo::svDataExec()
{
    int stat = sv->dataExec();

    if (stat == SV::STATUS::OK)
        stat = sv->guiUpdate();

    return stat;
}*/

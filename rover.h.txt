#include "dop_f.h"
#include "field.h"

class Rover {
    friend class Processor;
    int direction;
    int length_in_pixels = 3;
    int width_in_pixels = 3;
    int radius_of_wheels_in_pixels;
    int straight_speed = 1;
    Point center_gravity_location;
    const Field* rover_field;
    double left_tilt, right_tilt;
    double tilt_to_the_side;
    double tilt_along;
    double critical_side_tilt;
    double critical_along_tilt;
    Point first_pixels_row_to_rover[5];
    Point second_pixels_row_to_rover[7];
    Point third_pixels_row_to_rover[9];
    Point first_pixels_corner_to_rover[7];
    Point second_pixels_corner_to_rover[9];
    Point third_pixels_corner_to_rover[11];

public:
    Rover(const int& dir, const int& rad, const double& crit_slope_side, const double& crit_slope_along, const double& start_point_x, const double& start_point_y, const Field* surf);

    bool check_condition();
    double get_max_side_tilt();
    double get_max_along_tilt();

    bool turn_45_clockwise();
    bool turn_45_counterclockwise();
    bool turn_90_clockwise();
    bool turn_90_counterclockwise();
    void turn_180();

    bool drive_forward_speed_1();
    bool moveTowardsDestination(Point Final_Destination);
    void navigateAndMoveForward();
    Point get_location();
    void change_cords(const int& dx, const int& dy);
    void Lose();
    void fill_sensor();
    bool sensor_check();
    Point get_point_centerdxdy(const int& dx, const int& dy);
    bool moveTowardsFinalDestination(Point Final_Destination);
};
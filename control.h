#include "rover.h"

class Control {
    ofstream control_log_file;
    ofstream surf_gnu_file;
    ofstream rover_gnu_file;
    string gnu_load_filename;
    Field* ptr_field;
    Rover* rover;
    bool is_date = true;
    Cursor control_cursor;
public:
    Control(bool date, string log_filename, string gnu_surf_filename, string gnu_rover_filename, string gnu_load);
    ~Control();

    bool field_create(const double& surf_length, const double& surf_width, const double& surf_unevennes);
    bool set_cursor(const double& x, const double& y);
    bool field_set_random_hills(const double& num);
    bool field_set_random_stones(const double& num);
    bool field_set_random_logs(const double& num);
    bool field_create_hill(const double& height, const double& sigma_x, const double& sigma_y, const double& rotation);
    bool field_create_log(const double& x1, const double& y1, const double& x2, const double& y2, const double& radius);
    bool field_create_stone(const double& radius);
    bool field_count();
    void field_delete();
    void rover_create(const int& dir, const int& rad, const double& crit_slope_side, const double& crit_slope_along, const double& start_point_x, const double& start_point_y);
    bool rover_drive_forward_1();
    bool rover_turn_45_clock();
    bool rover_turn_45_counterclock();
    bool rover_turn_90_clock();
    bool rover_turn_90_counterclock();
    void rover_turn_180();
    void rover_print_current_loc();
    void close_files();
    void print_message_in_log(string message);
    void route() {
        rover->moveTowardsFinalDestination(Point(70, 80, 0));
    }
};

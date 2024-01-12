#include "dop_f.h"
#include "Log_Hill_Stone.h"
#include "cursor.h"

class Point
{
    friend class Field;
    friend class Rover;
    friend class Control;
protected:
    double x_cord;
    double y_cord;
    double z_cord;
public:
    Point(const double& x = 0, const double& y = 0, const double& z = 0) {
        x_cord = x, y_cord = y, z_cord = z;
    };
};

class Field {
    friend class Rover;
    friend class Log;
    friend class Stone;
    friend class Hill;
    friend class Control;
    double unevenness_degree;
    vector<Hill> hills;
    vector<Stone> stones;
    vector<Log> logs;
    Cursor cursor;
    Point** pixels;
public:
    double length;
    double width;
    Field(const double& f_len = 10, const double& f_wid = 10, const double& f_uneven = 0.1);
    double Gauss(const double& x, const double& y);
    void Print_in_file(ofstream& file);
    void count_field();
    ~Field();
    bool add_hill(const double& x = 0.0, const double& y = 0.0, const double& z = 0.0, const double& sig_x = 1.0, const double& sig_y = 1.0, const double& ax_rotat_angle = 0);
    bool add_stone(const double& x = 0.0, const double& y = 0.0, const double& radius = 0);
    bool add_log(const double& x1 = 0.0, const double& y1 = 0.0, const double& x2 = 0.0, const double& y2 = 0.0, const double& radius = 0.0);
};

 
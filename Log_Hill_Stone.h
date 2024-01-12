#include "dop_f.h"

class Hill{
    friend class Field;
    double x, y;
    double sigma_x;     // ����������� ���������� �� X ��� ������� ������.
    double sigma_y;     // ����������� ���������� �� Y ��� ������� ������.
    double height;      // ������ ����� ��� ������� ������.
    double angle;       // ���� �������� � ��������.

public:
    Hill(const double& x0 = 0, const double& y0 = 0, const double& z0 = 0, const double& sig_x = 1, const double& sig_y = 1, const double& ax_rotat_angle = 0);
    double hill_Gauss(const double& x, const double& y);
};

class Stone {
    friend class Field;
    double x, y;
    double R;
public:
    Stone(const double& x0 = 0.0, const double& y0 = 0, const double& radius = 0);
    double stone_Gauss(const double& x = 0.0, const double& y = 0.0);
};

class Log {
    friend class Field;
    double x1;
    double x2;
    double y1;
    double y2;
    double R;
public:
    Log(const double& x10 = 0.0, const double& y10 = 0.0, const double& x20 = 0.0, const double& y20 = 0.0, const double& radius = 0.0);
    double log_Gauss(const double& x = 0.0, const double& y = 0.0);
};

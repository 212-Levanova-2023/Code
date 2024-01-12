#include "Log_Hill_Stone.h"

Hill::Hill(const double& x0, const double& y0, const double& z0, const double& sig_x, const double& sig_y, const double& angle0) {
    sigma_x = sig_x;
    sigma_y = sig_y;
    height = z0;
    angle = angle0;
}

double Hill::hill_Gauss(const double& x0, const double& y0) {
    double e_x = pow((x - x0) * cos(angle) - (y - y0) * sin(angle), 2) / (2 * sigma_x * sigma_x);
    double e_y = pow((x - x0) * sin(angle) + (y - y0) * cos(angle), 2) / (2 * sigma_y * sigma_y);
    double normalization = 1.0 / (2 * acos(-1) * sigma_x * sigma_y);

    return height * normalization * exp(-(e_x + e_y));
}


Stone::Stone(const double& x0, const double& y0, const double& radius) {
    x = x0;
    y = y0;
    R = radius;
}

double Stone::stone_Gauss(const double& x0, const double& y0) {
    double dx = x0 - x;
    double dy = y0 - y;
    double distanceSquared = dx * dx + dy * dy;
    if (distanceSquared <= R * R) {
        double height = sqrt(R * R - distanceSquared);
        return height;
    }
    return 0.0;
}

Log::Log(const double& x10, const double& y10, const double& x20, const double& y20, const double& radius) {
    x1 = x10;
    x2 = x20;
    y1 = y10;
    y2 = y20;
    R = radius;
}

double Log::log_Gauss(const double& x0, const double& y0) {
    double t;
    double z;
    t = pow((R), 2) - pow((y0 - (x0 - x1) * (y2 - y1) / (x2 - x1) - y1), 2);
    if (t >= 0 && abs(y0 - ((x1 - x2) * x0 / (y2 - y1)) - (y1 + y2) / 2 + (x1 - x2) * (x1 + x2) / (2 * (y2 - y1))) <= sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2)) / 2) {
        z = sqrt(t);
    }
    else {
        z = 0;
    }
    return z;
}
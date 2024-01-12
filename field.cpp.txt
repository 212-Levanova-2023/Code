#include "field.h"
#include "dop_f.h"

size_t _max_rand_hills;
size_t _max_rand_logs;
size_t _max_rand_stones;

Field::Field(const double& f_len, const double& f_wid, const double& f_uneven) {
    length = f_len;
    width = f_wid;
    unevenness_degree = f_uneven;
    pixels = new Point * [int(length / NET_STEP) + 1];
    for (int i = 0; i <= int(length / NET_STEP); i++)
    {
        pixels[i] = new Point[int(width / NET_STEP) + 1];
    }
    srand(static_cast<unsigned>(time(0))); 
    for (int i = 0; i < _max_rand_hills; i++) {
        double x0 = static_cast<double>(rand()) / static_cast<double>(RAND_MAX) * (length - width) + width;
        double y0 = static_cast<double>(rand()) / static_cast<double>(RAND_MAX) * (length - width) + width;
        double sigmax0 = static_cast<double>(rand()) / static_cast<double>(RAND_MAX) * unevenness_degree;
        double sigmay0 = static_cast<double>(rand()) / static_cast<double>(RAND_MAX) * unevenness_degree;
        double height0 = static_cast<double>(rand()) / static_cast<double>(RAND_MAX) * 50 - 25;
        double angle0 = static_cast<double>(rand()) / static_cast<double>(RAND_MAX) * 2 * 3.1415926;
        hills.push_back(Hill(x0, y0, height0, sigmax0, sigmay0, angle0));
    }

    for (int i = 0; i < _max_rand_stones; i++) {
        double x0 = static_cast<double>(rand()) / static_cast<double>(RAND_MAX) * length;
        double y0 = static_cast<double>(rand()) / static_cast<double>(RAND_MAX) * width;
        double radius = static_cast<double>(rand()) / static_cast<double>(RAND_MAX) + 0.7;
        stones.push_back(Stone(x0, y0, radius));
    }

    for (int i = 0; i < _max_rand_logs; i++) {
        double x1 = static_cast<double>(rand()) / static_cast<double>(RAND_MAX) * length;
        double y1 = static_cast<double>(rand()) / static_cast<double>(RAND_MAX) * width;
        double x2 = static_cast<double>(rand()) / static_cast<double>(RAND_MAX) * length;
        double y2 = static_cast<double>(rand()) / static_cast<double>(RAND_MAX) * width;
        double radius = static_cast<double>(rand()) / static_cast<double>(RAND_MAX) + 0.7;
        logs.push_back(Log(x1, y1, x2, y2, radius));
    }
}

Field:: ~Field() {
    for (int i = 0; i < int(length / NET_STEP); i++) {
        delete[] pixels[i];
    }
    delete[] pixels;
}

bool Field::add_hill(const double& x, const double& y, const double& z, const double& sig_x, const double& sig_y, const double& ax_rotat_angle) {
    if (x >= 0.0 && y >= 0.0 && x <= length && y <= width) {
        hills.push_back(Hill(x, y, z, sig_x, sig_y, ax_rotat_angle));
        return true;
    }
    return false;
}

bool Field::add_log(const double& x1, const double& y1, const double& x2, const double& y2, const double& radius) {
    if (x1 >= 0.0 && y1 >= 0.0 && x1 <= length && y1 <= width && x2 >= 0.0 && y2 >= 0.0 && x2 <= length && y2 <= width) {
        logs.push_back(Log(x1, y1, x2, y2, radius));
        return true;
    }
    return false;
}

bool Field::add_stone(const double& x, const double& y, const double& radius) {
    if (x >= 0.0 && y >= 0.0 && x <= length && y <= width) {
        stones.push_back(Stone(x, y, radius));
        return true;
    }
    return false;
}

double Field::Gauss(const double& x, const double& y) {
    double z = 0;
    for (size_t i = 0; i < hills.size(); i++) {
        z += hills[i].hill_Gauss(x, y);
    }
    for (size_t i = 0; i < stones.size(); i++) {
        z += stones[i].stone_Gauss(x, y);
    }
    for (size_t i = 0; i < logs.size(); i++) {
        z += logs[i].log_Gauss(x, y);
    }
    return z;
}

void Field::count_field() {
    for (int i = 0; i <= int(length / NET_STEP); i++)
    {
        for (int j = 0; j <= int(width / NET_STEP); j++)
        {
                pixels[i][j] = Point(i * NET_STEP, j * NET_STEP, Gauss(i * NET_STEP, j * NET_STEP));
            
        }
    }

}


void Field::Print_in_file(ofstream& file) {
    for (double i = 0.0; i <= length; i += 1) {
        for (double j = 0.0; j <= width; j += 1) {
            file << i << " " << j << " " << Gauss(i, j) << "\n";
        }
    }
}

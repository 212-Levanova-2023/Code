#include "rover.h"

Rover::Rover(const int& dir, const int& rad, const double& crit_slope_side, const double& crit_slope_along, const double& start_point_x, const double& start_point_y, const Field* surf) {
    radius_of_wheels_in_pixels = rad;
    critical_along_tilt = crit_slope_along;
    critical_side_tilt = crit_slope_side;
    rover_field = surf;
    
    center_gravity_location = Point(start_point_x, start_point_y, rover_field->pixels[int(start_point_x / NET_STEP)][int(start_point_y / NET_STEP)].z_cord);
    direction = dir;

   
    if (dir != 10 && dir != 1 && dir != -10 && dir != -1) {
        cout << "Incorrect direction value \n";
        exit(-1);
    }
    if (crit_slope_along > M_PI_2 || crit_slope_side > M_PI_2 || crit_slope_along < EPS || crit_slope_side < EPS) {
        cout << "Incorrect critical slope value";
        exit(-1);
    }
}

bool Rover::check_condition() {
    
    if (center_gravity_location.x_cord - NET_STEP < 0 || center_gravity_location.y_cord - NET_STEP < 0 || center_gravity_location.x_cord + NET_STEP > rover_field->length || center_gravity_location.y_cord + NET_STEP > rover_field->width) return 0;

    double max_z = center_gravity_location.z_cord, min_z = center_gravity_location.z_cord;
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (get_point_centerdxdy(i, j).z_cord <= min_z) {
                min_z = get_point_centerdxdy(i, j).z_cord;
            }
            if (get_point_centerdxdy(i, j).z_cord >= max_z) {
                max_z = get_point_centerdxdy(i, j).z_cord;
            }
        }
    }
    
    if (fabs(min_z - max_z) >= radius_of_wheels_in_pixels * NET_STEP) return 0;
    return 1;
}

double Rover::get_max_side_tilt() {
    if (direction == 1 || direction == -1) {
        left_tilt = acos(fabs((1 * NET_STEP) / (1 * sqrt(get_sqr(NET_STEP) + get_sqr(center_gravity_location.z_cord - get_point_centerdxdy(1, 0).z_cord)))));
        right_tilt = acos(fabs((-1 * NET_STEP) / (1 * sqrt(get_sqr(NET_STEP) + get_sqr(center_gravity_location.z_cord - get_point_centerdxdy(-1, 0).z_cord)))));
    }
    else if (direction == 10 || direction == -10) {
        left_tilt = acos(fabs((1 * NET_STEP) / (1 * sqrt(get_sqr(NET_STEP) + get_sqr(center_gravity_location.z_cord - get_point_centerdxdy(0, 1).z_cord)))));
        right_tilt = acos(fabs((-1 * NET_STEP) / (1 * sqrt(get_sqr(NET_STEP) + get_sqr(center_gravity_location.z_cord - get_point_centerdxdy(0, -1).z_cord)))));
        
    }
    else if (direction == 11 || direction == 101) {
        left_tilt = acos(fabs((2 * NET_STEP) / (sqrt(2 * get_sqr(NET_STEP) + get_sqr(center_gravity_location.z_cord - get_point_centerdxdy(1, -1).z_cord)) * sqrt(2))));
        right_tilt = acos(fabs((-2 * NET_STEP) / (sqrt(2 * get_sqr(NET_STEP) + get_sqr(center_gravity_location.z_cord - get_point_centerdxdy(-1, 1).z_cord)) * sqrt(2))));
        
    }
    else if (direction == -11 || direction == 1101) {
        left_tilt = acos(fabs((2 * NET_STEP) / (sqrt(2 * get_sqr(NET_STEP) + get_sqr(center_gravity_location.z_cord - get_point_centerdxdy(-1, -1).z_cord)) * sqrt(2))));
        right_tilt = acos(fabs((-2 * NET_STEP) / (sqrt(2 * get_sqr(NET_STEP) + get_sqr(center_gravity_location.z_cord - get_point_centerdxdy(1, 1).z_cord)) * sqrt(2))));
        
    }
    if (fabs(left_tilt) > fabs(right_tilt)) return fabs(left_tilt);
    else return fabs(right_tilt);
}

double Rover::get_max_along_tilt() {
    double left_tilt, right_tilt;
    if (direction == 10 || direction == -10) {
        left_tilt = acos(fabs((1 * NET_STEP) / (1 * sqrt(get_sqr(NET_STEP) + get_sqr(center_gravity_location.z_cord - rover_field->pixels[int(center_gravity_location.x_cord / NET_STEP + 1)][int(center_gravity_location.y_cord / NET_STEP)].z_cord)))));
        right_tilt = acos(fabs((-1 * NET_STEP) / (1 * sqrt(get_sqr(NET_STEP) + get_sqr(center_gravity_location.z_cord - rover_field->pixels[int(center_gravity_location.x_cord / NET_STEP - 1)][int(center_gravity_location.y_cord / NET_STEP)].z_cord)))));
    }
    else if (direction == 1 || direction == -1) {
        left_tilt = acos(fabs((1 * NET_STEP) / (1 * sqrt(get_sqr(NET_STEP) + get_sqr(center_gravity_location.z_cord - rover_field->pixels[int(center_gravity_location.x_cord / NET_STEP)][int(center_gravity_location.y_cord / NET_STEP + 1)].z_cord)))));
        right_tilt = acos(fabs((-1 * NET_STEP) / (1 * sqrt(get_sqr(NET_STEP) + get_sqr(center_gravity_location.z_cord - rover_field->pixels[int(center_gravity_location.x_cord / NET_STEP)][int(center_gravity_location.y_cord / NET_STEP - 1)].z_cord)))));
    }
    else if (direction == -11 || direction == 1101) {
        left_tilt = acos(fabs((2 * NET_STEP) / (sqrt(2 * get_sqr(NET_STEP) + get_sqr(center_gravity_location.z_cord - get_point_centerdxdy(1, 1).z_cord)) * sqrt(2))));
        right_tilt = acos(fabs((-2 * NET_STEP) / (sqrt(2 * get_sqr(NET_STEP) + get_sqr(center_gravity_location.z_cord - get_point_centerdxdy(-1, -1).z_cord)) * sqrt(2))));
       
    }
    else if (direction == 11 || direction == 101) {
        left_tilt = acos(fabs((2 * NET_STEP) / (sqrt(2 * get_sqr(NET_STEP) + get_sqr(center_gravity_location.z_cord - get_point_centerdxdy(-1, -1).z_cord)) * sqrt(2))));
        right_tilt = acos(fabs((-2 * NET_STEP) / (sqrt(2 * get_sqr(NET_STEP) + get_sqr(center_gravity_location.z_cord - get_point_centerdxdy(1, 1).z_cord)) * sqrt(2))));
        
    }

    if (fabs(left_tilt) > fabs(right_tilt)) return fabs(left_tilt);
    else return fabs(right_tilt);
}

bool Rover::turn_90_clockwise() {
    switch (direction)
    {
    case 1:
        direction = 10;
        break;
    case 10:
        direction = -1;
        break;
    case -1:
        direction = -10;
        break;
    case -10:
        direction = 1;
        break;
    case 11:
        direction = 1101;
        break;
    case 1101:
        direction = 101;
        break;
    case 101:
        direction = -11;
        break;
    case -11:
        direction = 11;
        break;
    default:
        break;
    }
    if (check_condition() == 0) {
        Lose();
        return 0;
    }
    else return 1;
}

bool Rover::turn_45_counterclockwise() {
    switch (direction) {
    case 1:
        direction = -11;
        break;
    case -11:
        direction = -10;
        break;
    case -10:
        direction = 101;
        break;
    case 101:
        direction = -1;
        break;
    case -1:
        direction = 1101;
        break;
    case 1101:
        direction = 10;
        break;
    case 10:
        direction = 11;
        break;
    case 11:
        direction = 1;
        break;
    default:
        break;
    }
    return 1;
}

bool Rover::turn_45_clockwise() {
    switch (direction)
    {
    case 1:
        direction = 11;
        break;
    case 11:
        direction = 10;
        break;
    case 10:
        direction = 1101;
        break;
    case 1101:
        direction = -1;
        break;
    case -1:
        direction = 101;
        break;
    case 101:
        direction = -10;
        break;
    case -10:
        direction = -11;
        break;
    case -11:
        direction = 1;
        break;
    default:
        break;
    }
    if (check_condition() == 0) {
        Lose();
        return 0;
    }
    else return 1;
}

bool Rover::turn_90_counterclockwise() {
    switch (direction)
    {
    case 1:
        direction = -10;
        break;
    case -10:
        direction = -1;
        break;
    case -1:
        direction = 10;
        break;
    case 10:
        direction = 1;
        break;
    case 11:
        direction = -11;
        break;
    case -11:
        direction = 101;
        break;
    case 101:
        direction = 1101;
        break;
    case 1101:
        direction = 11;
        break;
    default:
        break;
    }
    if (check_condition() == 0) {
        Lose();
        return 0;
    }
    else return 1;
}

void Rover::turn_180() {
    if (direction == 1 || direction == -1 || direction == 10 || direction == -10) {
        direction = -direction;
    }
    else {
        switch (direction)
        {
        case -11:
            direction = 1101;
            break;
        case 1101:
            direction = -11;
            break;
        case 11:
            direction = 101;
            break;
        case 101:
            direction = 11;
            break;
        default:
            break;
        }
    }
}

bool Rover::drive_forward_speed_1() {
    switch (direction)
    {
    case 1:
        change_cords(0, straight_speed);
        
        break;
    case -1:
        change_cords(0, -straight_speed);
        break;
    case 10:
        change_cords(straight_speed, 0);
        break;
    case -10:
        change_cords(-straight_speed, 0);
        break;
    case -11:
        change_cords(-straight_speed, straight_speed);
        break;
    case 101:
        change_cords(-straight_speed, -straight_speed);
        break;
    case 1101:
        change_cords(straight_speed, -straight_speed);
        break;
    case 11:
        change_cords(straight_speed, straight_speed);
        break;
    default:
        break;
    }
    cout << center_gravity_location.x_cord << " " << center_gravity_location.y_cord << " " << center_gravity_location.z_cord << "\n";//" ����� ������ -  " << left_tilt << " ������ ������ - " << right_tilt << " ������ ������ - " << tilt_along << "\n";
    if (check_condition() == 0) {
        Lose();
        return 0;
    }
    else return 1;
}

void Rover::Lose() {
    cout << "\nLose\n";
}

Point Rover::get_location() {
    return center_gravity_location;
}

void Rover::change_cords(const int& dx, const int& dy) {
    center_gravity_location.y_cord += NET_STEP * dy;
    center_gravity_location.x_cord += NET_STEP * dx;
    center_gravity_location.z_cord = rover_field->pixels[int(center_gravity_location.x_cord / NET_STEP) + dx][int(center_gravity_location.y_cord / NET_STEP) + dy].z_cord;
}

void Rover::fill_sensor() {
    switch (direction) {
    case 1:
        for (int i = -2; i <= 2; i++)
        {
            first_pixels_row_to_rover[i + 2] = get_point_centerdxdy(i, 2);
        }
        for (int i = -3; i <= 3; i++)
        {
            second_pixels_row_to_rover[i + 3] = get_point_centerdxdy(i, 3);
        }
        for (int i = -4; i <= 4; i++)
        {
            third_pixels_row_to_rover[i + 4] = get_point_centerdxdy(i, 4);
        }
        break;
    case -1:
        for (int i = -2; i <= 2; i++)
        {
            first_pixels_row_to_rover[i + 2] = get_point_centerdxdy(i, -2);
        }
        for (int i = -3; i <= 3; i++)
        {
            second_pixels_row_to_rover[i + 3] = get_point_centerdxdy(i, -3);
        }
        for (int i = -4; i <= 4; i++)
        {
            third_pixels_row_to_rover[i + 4] = get_point_centerdxdy(i, -4);
        }
        break;
    case 10:
        for (int i = -2; i <= 2; i++)
        {
            first_pixels_row_to_rover[i + 2] = get_point_centerdxdy(2, i);
        }
        for (int i = -3; i <= 3; i++)
        {
            second_pixels_row_to_rover[i + 3] = get_point_centerdxdy(3, i);
        }
        for (int i = -4; i <= 4; i++)
        {
            third_pixels_row_to_rover[i + 4] = get_point_centerdxdy(4, i);
        }
        break;
    case -10:
        for (int i = -2; i <= 2; i++)
        {
            first_pixels_row_to_rover[i + 2] = get_point_centerdxdy(-2, i);
        }
        for (int i = -3; i <= 3; i++)
        {
            second_pixels_row_to_rover[i + 3] = get_point_centerdxdy(-3, i);
        }
        for (int i = -4; i <= 4; i++)
        {
            third_pixels_row_to_rover[i + 4] = get_point_centerdxdy(-4, i);
        }
        break;
    case 11:
        for (int i = 0; i <= 2; i++) first_pixels_corner_to_rover[i] = get_point_centerdxdy(i - 1, 2);
        for (int i = 0; i <= 3; i++) second_pixels_corner_to_rover[i] = get_point_centerdxdy(i - 1, 3);
        for (int i = 0; i <= 4; i++) third_pixels_corner_to_rover[i] = get_point_centerdxdy(i - 1, 4);

        for (int i = 3; i <= 6; i++) first_pixels_corner_to_rover[i] = get_point_centerdxdy(2, i - 4);
        for (int i = 4; i <= 8; i++) second_pixels_corner_to_rover[i] = get_point_centerdxdy(3, i - 5);
        for (int i = 5; i <= 10; i++) third_pixels_corner_to_rover[i] = get_point_centerdxdy(4, i - 6);
        break;
    case -11:
        for (int i = 0; i <= 2; i++) first_pixels_corner_to_rover[i] = get_point_centerdxdy(i - 1, 2);
        for (int i = 0; i <= 3; i++) second_pixels_corner_to_rover[i] = get_point_centerdxdy(i - 2, 3);
        for (int i = 0; i <= 4; i++) third_pixels_corner_to_rover[i] = get_point_centerdxdy(i - 3, 4);

        for (int i = 3; i <= 6; i++) first_pixels_corner_to_rover[i] = get_point_centerdxdy(-2, i - 4);
        for (int i = 4; i <= 8; i++) second_pixels_corner_to_rover[i] = get_point_centerdxdy(-3, i - 5);
        for (int i = 5; i <= 10; i++) third_pixels_corner_to_rover[i] = get_point_centerdxdy(-4, i - 6);
        break;
    case 101:
        for (int i = 0; i <= 2; i++) first_pixels_corner_to_rover[i] = get_point_centerdxdy(i - 1, -2);
        for (int i = 0; i <= 3; i++) second_pixels_corner_to_rover[i] = get_point_centerdxdy(i - 2, -3);
        for (int i = 0; i <= 4; i++) third_pixels_corner_to_rover[i] = get_point_centerdxdy(i - 3, -4);

        for (int i = 3; i <= 6; i++) first_pixels_corner_to_rover[i] = get_point_centerdxdy(-2, i - 5);
        for (int i = 4; i <= 8; i++) second_pixels_corner_to_rover[i] = get_point_centerdxdy(-3, i - 7);
        for (int i = 5; i <= 10; i++) third_pixels_corner_to_rover[i] = get_point_centerdxdy(-4, i - 9);
        break;
    case 1101:
        for (int i = 0; i <= 2; i++) first_pixels_corner_to_rover[i] = get_point_centerdxdy(i - 1, -2);
        for (int i = 0; i <= 3; i++) second_pixels_corner_to_rover[i] = get_point_centerdxdy(i - 1, -3);
        for (int i = 0; i <= 4; i++) third_pixels_corner_to_rover[i] = get_point_centerdxdy(i - 1, -4);

        for (int i = 3; i <= 6; i++) first_pixels_corner_to_rover[i] = get_point_centerdxdy(2, i - 5);
        for (int i = 4; i <= 8; i++) second_pixels_corner_to_rover[i] = get_point_centerdxdy(3, i - 7);
        for (int i = 5; i <= 10; i++) third_pixels_corner_to_rover[i] = get_point_centerdxdy(4, i - 9);
        break;
    default:
        break;
    }
}

bool Rover::moveTowardsDestination(Point Final_Destination) {
    if (center_gravity_location.y_cord > Final_Destination.y_cord && center_gravity_location.x_cord > Final_Destination.x_cord) {
        direction = 101;
        if (sensor_check() == false) return false;
        while (center_gravity_location.y_cord > Final_Destination.y_cord && center_gravity_location.x_cord > Final_Destination.x_cord) {
            if (drive_forward_speed_1() == 0) {
                return 1;
            }
            if (sensor_check() == false) return false;
        }
        while (center_gravity_location.y_cord > Final_Destination.y_cord) {
            direction = -1;
            if (sensor_check() == false) return false;
            if (drive_forward_speed_1() == 0) {
                return 1;
            }
            if (sensor_check() == false) return false;
        }
        while (center_gravity_location.x_cord > Final_Destination.x_cord)
        {
            direction = -10;
            if (sensor_check() == false) return false;
            if (drive_forward_speed_1() == 0) {
                return 1;
            }
            if (sensor_check() == false) return false;
        }
    }
    else if (center_gravity_location.y_cord > Final_Destination.y_cord && center_gravity_location.x_cord < Final_Destination.x_cord) {
        
        direction = 1101;
        if (sensor_check() == false) return false;
        while (center_gravity_location.y_cord > Final_Destination.y_cord && center_gravity_location.x_cord < Final_Destination.x_cord) {
            if (drive_forward_speed_1() == 0) {
                return 1;
            }
            if (sensor_check() == false) return false;
        }
        while (center_gravity_location.y_cord > Final_Destination.y_cord) {
            direction = -1;
            if (sensor_check() == false) return false;
            if (drive_forward_speed_1() == 0) {
                return 1;
            }
            if (sensor_check() == false) return false;
        }
        while (center_gravity_location.x_cord < Final_Destination.x_cord)
        {
            direction = 10;
            if (sensor_check() == false) return false;
            if (drive_forward_speed_1() == 0) {
                return 1;
            }
            if (sensor_check() == false) return false;
        }
    }
    else if (center_gravity_location.y_cord > Final_Destination.y_cord && center_gravity_location.x_cord == Final_Destination.x_cord) {
        // cout << "C\n";
        while (center_gravity_location.y_cord > Final_Destination.y_cord) {
            direction = -1;
            if (sensor_check() == false) return false;
            if (drive_forward_speed_1() == 0) {
                return 1;
            }
            if (sensor_check() == false) return false;
        }
    }
    else if (center_gravity_location.y_cord < Final_Destination.y_cord && center_gravity_location.x_cord < Final_Destination.x_cord) {
        // cout << "D\n";
        direction = 11;
        if (sensor_check() == false) return false;
        while (center_gravity_location.y_cord < Final_Destination.y_cord && center_gravity_location.x_cord < Final_Destination.x_cord) {
            if (drive_forward_speed_1() == 0) {
                return 1;
            }
            if (sensor_check() == false) return false;
        }
        while (center_gravity_location.y_cord < Final_Destination.y_cord) {
            direction = 1;
            if (sensor_check() == false) return false;
            if (drive_forward_speed_1() == 0) {
                return 1;
            }
            if (sensor_check() == false) return false;
        }
        while (center_gravity_location.x_cord < Final_Destination.x_cord)
        {
            direction = 10;
            if (sensor_check() == false) return false;
            if (drive_forward_speed_1() == 0) {
                return 1;
            }
            if (sensor_check() == false) return false;
        }
    }
    else if (center_gravity_location.y_cord < Final_Destination.y_cord && center_gravity_location.x_cord > Final_Destination.x_cord) {
        
        direction = -11;
        if (sensor_check() == false) return false;
        while (center_gravity_location.y_cord < Final_Destination.y_cord && center_gravity_location.x_cord > Final_Destination.x_cord) {
            
            if (drive_forward_speed_1() == 0) {
                return 1;
            }
            if (sensor_check() == false) return false;
        }
        while (center_gravity_location.y_cord < Final_Destination.y_cord) {
            
            direction = 1;
            if (sensor_check() == false) return false;
            if (drive_forward_speed_1() == 0) {
                return 1;
            }
            if (sensor_check() == false) return false;
        }
        while (center_gravity_location.x_cord > Final_Destination.x_cord)
        {
           
            direction = -10;
            if (sensor_check() == false) return false;
            if (drive_forward_speed_1() == 0) {
                return 1;
            }
            if (sensor_check() == false) return false;
        }
    }
    else if (center_gravity_location.y_cord < Final_Destination.y_cord && center_gravity_location.x_cord == Final_Destination.x_cord) {
        
        direction = 1;
        if (sensor_check() == false) return false;
        while (center_gravity_location.y_cord < Final_Destination.y_cord) {
            if (drive_forward_speed_1() == 0) {
                return 1;
            }
            if (sensor_check() == false) return false;
        }
    }
    else if (center_gravity_location.y_cord == Final_Destination.y_cord && center_gravity_location.x_cord > Final_Destination.x_cord) {
        
        direction = -10;
        if (sensor_check() == false) return false;
        while (center_gravity_location.x_cord > Final_Destination.x_cord) {
            if (drive_forward_speed_1() == 0) {
                return 1;
            }
            if (sensor_check() == false) return false;
        }
    }
    else if (center_gravity_location.y_cord == Final_Destination.y_cord && center_gravity_location.x_cord < Final_Destination.x_cord) {
        
        direction = 10;
        if (sensor_check() == false) return false;
        while (center_gravity_location.x_cord < Final_Destination.x_cord) {
            if (drive_forward_speed_1() == 0) {
                return 1;
            }
            if (sensor_check() == false) return false;
        }
    }
    else if (Final_Destination.x_cord == center_gravity_location.x_cord && Final_Destination.y_cord == center_gravity_location.y_cord) {
        
        return 1;
    }
    else {
        cout << "��� ���������!" << " " "\n";
    }

    return 1;
}

bool Rover::sensor_check() {
    fill_sensor();
    double max_z = center_gravity_location.z_cord, min_z = center_gravity_location.z_cord;
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (get_point_centerdxdy(i, j).z_cord <= min_z) {
                min_z = get_point_centerdxdy(i, j).z_cord;
            }
            if (get_point_centerdxdy(i, j).z_cord >= max_z) {
                max_z = get_point_centerdxdy(i, j).z_cord;
            }
        }

    }
    if (direction == 1 || direction == -1 || direction == 10 || direction == -10) {
        for (size_t i = 0; i < 5; i++)
        {
            if (min_z + radius_of_wheels_in_pixels * NET_STEP < first_pixels_row_to_rover[i].z_cord) return 0;
            if (max_z - radius_of_wheels_in_pixels * NET_STEP > first_pixels_row_to_rover[i].z_cord) return 0;
        }
        for (size_t i = 0; i < 7; i++)
        {
            if (min_z + radius_of_wheels_in_pixels * NET_STEP < second_pixels_row_to_rover[i].z_cord) return 0;
            if (max_z - radius_of_wheels_in_pixels * NET_STEP > second_pixels_row_to_rover[i].z_cord) return 0;
        }
        for (size_t i = 0; i < 9; i++)
        {
            if (min_z + radius_of_wheels_in_pixels * NET_STEP < third_pixels_row_to_rover[i].z_cord) return 0;
            if (max_z - radius_of_wheels_in_pixels * NET_STEP > third_pixels_row_to_rover[i].z_cord) return 0;
        }
    }
    else {
        for (size_t i = 0; i < 8; i++)
        {
            if (min_z + radius_of_wheels_in_pixels * NET_STEP < first_pixels_corner_to_rover[i].z_cord) return 0;
            if (max_z - radius_of_wheels_in_pixels * NET_STEP > first_pixels_corner_to_rover[i].z_cord) return 0;
        }
        for (size_t i = 0; i < 10; i++)
        {
            if (min_z + radius_of_wheels_in_pixels * NET_STEP < second_pixels_corner_to_rover[i].z_cord) return 0;
            if (max_z - radius_of_wheels_in_pixels * NET_STEP > second_pixels_corner_to_rover[i].z_cord) return 0;
        }
        for (size_t i = 0; i < 12; i++)
        {
            if (min_z + radius_of_wheels_in_pixels * NET_STEP < third_pixels_corner_to_rover[i].z_cord) return 0;
            if (max_z - radius_of_wheels_in_pixels * NET_STEP > third_pixels_corner_to_rover[i].z_cord) return 0;
        }
    }
    return true;
}

void Rover::navigateAndMoveForward() {
    int i = 0;
    
    while (sensor_check() == 0) {
        i++;
        turn_45_clockwise();
       
    }
   
    drive_forward_speed_1();
    drive_forward_speed_1();
    drive_forward_speed_1();

    for (int j = 0; j < i % 8; j++)
    {
        turn_45_counterclockwise();
        
    }
    if (sensor_check() == 0) {
        while (sensor_check() == 0)
        {
            for (int j = 0; j < i % 8; j++)
            {
                turn_45_clockwise();
            }
            if (sensor_check() == 0) return;
            drive_forward_speed_1();
            drive_forward_speed_1();
            drive_forward_speed_1();
            for (int j = 0; j < i % 8; j++)
            {
                turn_45_counterclockwise();
                
            }
        }
        drive_forward_speed_1();
        drive_forward_speed_1();
        drive_forward_speed_1();
    }
}

bool Rover::moveTowardsFinalDestination(Point Final_Destination) {
    if (center_gravity_location.x_cord == Final_Destination.x_cord && center_gravity_location.y_cord == Final_Destination.y_cord) return true;
    while (moveTowardsDestination(Final_Destination) == false) {
        navigateAndMoveForward();
        if (center_gravity_location.x_cord == Final_Destination.x_cord && center_gravity_location.y_cord == Final_Destination.y_cord) return true;
    }
    return true;
}

Point Rover::get_point_centerdxdy(const int& dx, const int& dy) {
    
    return Point(center_gravity_location.x_cord + NET_STEP * dx, center_gravity_location.y_cord + NET_STEP * dy, rover_field->pixels[int(center_gravity_location.x_cord / NET_STEP) + dx][int(center_gravity_location.y_cord / NET_STEP) + dy].z_cord);
}
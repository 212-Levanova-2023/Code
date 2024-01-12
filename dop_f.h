#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>
#include <chrono>
#define _USE_MATH_DEFINES
#define EPS 1e-14
#define NET_STEP 0.1
#define M_PI_2 1.57079632679489661923
using namespace std;

bool is_extra_symbol_after_semicolon(string str);
double get_sqr(const double& num);
bool can_double_to_int(const double& num);
bool is_substr(string str, string substr);
void printer_with_time(string message, ofstream& file);

extern size_t _max_rand_hills;
extern size_t _max_rand_stones;
extern size_t _max_rand_logs;

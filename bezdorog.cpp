#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

class Point
{
private:
    double x;           // Координата X точки.
    double y;           // Координата Y точки.
    double sigma_x;     // Стандартное отклонение по X для функции Гаусса.
    double sigma_y;     // Стандартное отклонение по Y для функции Гаусса.
    double height;      // Высота точки для функции Гаусса.

public:
    Point(double x0, double y0, double sigmax0, double sigmay0, double height0)//Конструктор 
        : x(x0), y(y0), height(height0)
    {
        sigma_x = abs(sigmax0);  // Инициализируем sigma_x, беря абсолютное значение sigmax0.
        sigma_y = abs(sigmay0);  // Инициализируем sigma_y, беря абсолютное значение sigmay0.
    }
    double Gauss(double x0, double y0) const
    {
        double e_x = (x - x0) * (x - x0) / (2 * sigma_x * sigma_x); // Вычисляем e_x.
        double e_y = (y - y0) * (y - y0) / (2 * sigma_y * sigma_y); // Вычисляем e_y.
        double normalization = 1.0 / (2 * acos(-1) * sigma_x * sigma_y); // Вычисляем нормализацию.

        return height * normalization * exp(-(e_x + e_y)); // Вычисляем функцию Гаусса.
    }
    friend ostream& operator<<(ostream& os, const Point& p)
    {
        os << p.x << " " << p.y << " " << p.sigma_x << " " << p.sigma_y << " " << p.height << endl;
        return os;
    }
};

class Field
{
private:
    double size_x;            // Размер поля по X.
    double size_y;            // Размер поля по Y.
    vector<Point> hills; // Вектор холмов на поле.

public:
    Field(double x, double y, int count) : size_x(x), size_y(y)
    {
        std::srand(std::time(nullptr)); // Инициализируем генератор случайных чисел текущим временем.
        for (int i = 0; i < count; i++)
        {
            double x0 = (rand() / static_cast<double>(RAND_MAX)) * x - x / 2; // Генерируем случайное значение x0.
            double y0 = (rand() / static_cast<double>(RAND_MAX)) * y - y / 2; // Генерируем случайное значение y0.
            double sigmax0 = (rand() / static_cast<double>(RAND_MAX)) * 1.9 + 0.1; // Генерируем случайное значение sigmax0.
            double sigmay0 = (rand() / static_cast<double>(RAND_MAX)) * 1.9 + 0.1; // Генерируем случайное значение sigmay0.
            double height0 = (rand() / static_cast<double>(RAND_MAX)) * 10 - 5; // Генерируем случайное значение height0.
            hills.push_back(Point(x0, y0, sigmax0, sigmay0, height0)); // Добавляем точку (холм) в вектор холмов.
        }
    }
    friend ofstream& operator<<(ofstream& file, const Field& field)
    {
        for (double i = -field.size_x / 2; i <= field.size_x / 2; i += field.size_x / 40)
        {
            for (double j = -field.size_y / 2; j <= field.size_y / 2; j += field.size_y / 40)
            {
                double z = 0;
                for (const Point& point : field.hills) // Проходим по всем холмам (точкам) в поле и суммируем значения функции Гаусса для текущей точки (i, j).
                {
                    z += point.Gauss(i, j);
                }
                file << i << " " << j << " " << z << "\n"; // Записываем координаты i, j и значение z в файл.
            }
            file << "\n";
        }
        return file;
    }
    friend ostream& operator<<(ostream& os, const Field& f)
    {
        for (int i = 0; i < f.hills.size(); i++)
        {
            os << i << " point " << endl;
            os << f.hills[i];// Выводим информацию о каждой точке (холме) в поле.
        }
        return os;
    }
};

int main()
{
    Field my_field(20, 20, 50); // Создаем объект класса Field с размерами 20x20 и 30 случайно сгенерированными холмами.
    ofstream outputFile("output.txt"); // Создаем объект для записи в файл "output.txt".
    outputFile << my_field; // Выводим информацию о поле в файл.
    outputFile.close(); // Закрываем файл.
    return 0; // Возвращаем 0, чтобы указать успешное завершение программы.
}

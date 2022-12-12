

#include <vector>
#include <cmath>

#include <iostream>

#include <typeinfo>


class Curve
{
    public:
    
        // returns 3d point
        virtual std::vector<double> get_point(double angle){}

        // returns gradient
        virtual std::vector<double> gradient_at_point(double angle){}

};

/*
equation: x^2 + y^2 = r^2
*/
class Circle : Curve
{
    public:
        Circle(double _radius): radius(_radius){}

        double radius;

        std::vector<double> get_point(double angle)
        {
            // z = 0
            // x = r * cos(theta)
            // y = r * sin(theta)

            double x = radius * cos(angle);
            double y = radius * sin(angle);
            double z = 0.0;
            std::vector<double> point_3d = {x,y,z};

            return point_3d;
        }

        std::vector<double> gradient_at_point(double angle)
        {
            double x = radius * cos(angle);
            double y = radius * sin(angle);

            double grad_x = 2 * x;
            double grad_y = 2 * y;
            double grad_z = 0.0;

            std::vector<double> grad_3d = {grad_x, grad_y, grad_z};
        }
};

/*
equation: x^2/a^2 + y^2/b^2 = 1
a,b - corresponding radii
*/
class Ellipse : Curve
{
    public:
        Ellipse(double _radius_x, double _radius_y) : radius_x(_radius_x), radius_y(_radius_y) {}

        double radius_x;
        double radius_y;

        std::vector<double> get_point(double angle)
        {
            double x = radius_x * cos(angle);
            double y = radius_y * sin(angle);
            double z = 0.0;
            std::vector<double> point_3d = {x,y,z};

            return point_3d;
        }

        std::vector<double> gradient_at_point(double angle)
        {
            double x = radius_x * cos(angle);
            double y = radius_y * sin(angle);

            double grad_x = (2 * x) / (radius_x*radius_x);
            double grad_y = (2 * y) / (radius_y*radius_y);
            double grad_z = 0.0;

            std::vector<double> grad_3d = {grad_x, grad_y, grad_z};
        }

};


int random_int(int offset, int range)
{
    return offset + (rand() % range);
}

class Helix : Curve
{
    public:
        Helix(double _radius, double _step) : radius(_radius), step(_step){}

        double radius;
        double step;

        std::vector<double> get_point(double angle)
        {
            double x = radius * cos(angle);
            double y = radius * sin(angle);
            double z = step * angle;
            std::vector<double> point_3d = {x,y,z};

            return point_3d;

        }

        std::vector<double> gradient_at_point(double angle)
        {
            double x = radius * cos(angle);
            double y = radius * sin(angle);

            double grad_x = 2 * x;
            double grad_y = 2 * y;
            double grad_z = step;

            std::vector<double> grad_3d = {grad_x, grad_y, grad_z};
        }
};






int main()
{
    std::vector<double> angles = {0.0, 1.57, 3.14, 6.28};

    Circle circle1(5);
    Circle circle2(15);
    Ellipse ellipse1(2,3);

    Helix helix1(1,2);

    std::vector<double> cur_point;
    for(const auto &angle : angles)
    {
        cur_point = circle1.get_point(angle);
        std::cout << "circle | angle: " << angle << " cur_point.x: " << cur_point[0] << " cur_point.y: " << cur_point[1] << " cur_point.z: " << cur_point[2] << std::endl;   
    }

    for(const auto &angle : angles)
    {
        cur_point = ellipse1.get_point(angle);
        std::cout << "ellipse | angle: " << angle << " cur_point.x: " << cur_point[0] << " cur_point.y: " << cur_point[1] << " cur_point.z: " << cur_point[2] << std::endl;   
    }

    for(const auto &angle : angles)
    {
        cur_point = helix1.get_point(angle);
        std::cout << "helix | angle: " << angle << " cur_point.x: " << cur_point[0] << " cur_point.y: " << cur_point[1] << " cur_point.z: " << cur_point[2] << std::endl;   
    }



    return 0;
}

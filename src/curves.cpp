#include <vector>
#include <cassert>
#include <cmath>

// TASK1. creating 3 different classes of curves

class Curve
{
    public:
        Curve(){}
        Curve(double _radius) : radius(_radius){
            assert(_radius > 0.0);
        }
    
        // returns 3d point
        virtual std::vector<double> get_point(double angle)
        {
            std::vector<double> zero_vec = {0.0,0.0,0.0};
            return zero_vec;
        }

        // returns gradient
        virtual std::vector<double> gradient_at_point(double angle){ return {0.0};}

        int type = 0;

        double radius = 1;

        
};

/*
equation: x^2 + y^2 = r^2
*/
class Circle : public Curve
{
    public:
        Circle()
        {
            type = 0;
        }

        Circle(double _radius): Curve{_radius}
        {
            type = 0;
        }


        // double radius;

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

            return grad_3d;
        }

    private:
        
};

/*
equation: x^2/a^2 + y^2/b^2 = 1
a,b - corresponding radii
*/
class Ellipse : public Curve
{
    public:
        Ellipse()
        {
            type = 1;
        }

        Ellipse(double _radius_x, double _radius_y) : Curve{_radius_x}, radius_2(_radius_y) 
        {
            type = 1;
        }

        // double radius_x;
        double radius_2;

        std::vector<double> get_point(double angle)
        {
            double x = radius * cos(angle);
            double y = radius_2 * sin(angle);
            double z = 0.0;
            std::vector<double> point_3d = {x,y,z};

            return point_3d;
        }

        std::vector<double> gradient_at_point(double angle)
        {
            double x = radius * cos(angle);
            double y = radius_2 * sin(angle);

            double grad_x = (2 * x) / (radius*radius);
            double grad_y = (2 * y) / (radius_2*radius_2);
            double grad_z = 0.0;

            std::vector<double> grad_3d = {grad_x, grad_y, grad_z};

            return grad_3d;
        }

    private:
         
};


class Helix : public Curve
{
    public:
        Helix()
        {
            type = 2;
        }

        Helix(double _radius, double _step) : Curve{_radius}, step(_step)
        {
            type = 2;
        }

        // double radius;
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

            return grad_3d;
        }

    private:
};
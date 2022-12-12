#define _USE_MATH_DEFINES
#define THREAD_NUM 4

#include <vector>

#include <iostream>

#include <memory>

#include <algorithm>

#include <cassert>

#include "curves.cpp"
#include <omp.h>




// random integer generator which generates values in range = (offset, offset + range)
int random_int(int offset, int range)
{
    return offset + (rand() % range);
}


/*
function for fillind a vector with random curves with random parameters
1. generates type of curve: (0 - circle, 1 - ellipse, 2 - helix)
2. creates corresponding curve by calling constructor with random parameters
*/
void populate_vector(std::vector<std::shared_ptr<Curve>> &curve_vec, const int &n_samples)
{
    int max_radius = 20;
    int max_step = 30;
    for(size_t i = 0; i<n_samples; i++)
    {
        int subclass = random_int(0,3);

        if(subclass == 0)
        {
            std::shared_ptr<Circle> circle_current(new Circle(random_int(1,max_radius+1)));
            curve_vec.push_back(circle_current);
        }
        else if(subclass == 1)
        {
            std::shared_ptr<Ellipse> ellipse_current(new Ellipse(random_int(1,max_radius+1), random_int(1,max_radius+1)));

            curve_vec.push_back(ellipse_current);
        }
        else if(subclass == 2)
        {
            std::shared_ptr<Helix> helix_current(new Helix(random_int(1,max_radius+1), random_int(1,max_step+1)));

            curve_vec.push_back(helix_current);
        }
    }
}

/*
extracts curves of a given type from curve_vec and puts them into spec_curve_vec
*/
void extract_types(const std::vector<std::shared_ptr<Curve>> &curve_vec, std::vector<std::shared_ptr<Curve>> &spec_curve_vec, const int &type)
{
    for(size_t i = 0; i < curve_vec.size(); i++)
    {
        if(curve_vec[i]->type == type)
        {
            spec_curve_vec.push_back(curve_vec[i]);
        }
    }
}




int main()
{
    srand(time(0));


    // TASK2. creating container with random curves and random parameters
    int N_SAMPLES = 20;
    std::vector<std::shared_ptr<Curve>> random_curve_vector;
    populate_vector(random_curve_vector, N_SAMPLES);


    // TASK3. printing coordinates of point and derivatives at t = pi/4
    double angle = M_PI/4;

    std::vector<double> cur_point;
    std::vector<double> cur_gradient;
    std::cout << "_________GENERATING RANDOM CURVES_________ " << std::endl;
    for(size_t i = 0; i < random_curve_vector.size(); i++)
    {
        std::cout << "i: " << i << " type: " << random_curve_vector[i]->type << "\t";
        cur_point = random_curve_vector[i]->get_point(angle);
        cur_gradient = random_curve_vector[i]->gradient_at_point(angle);

        std::cout << "point| x: " << cur_point[0] << " y: " << cur_point[1] << " z: " << cur_point[2] << std::endl;
        std::cout << "gradient| x: " << cur_gradient[0] << " y: " << cur_gradient[1] << " z: " << cur_gradient[2] << std::endl;
    }


    // TASK 4. extracting circles from curve vector
    std::vector<std::shared_ptr<Curve>> circle_vec;
    int chosen_type = 0;
    extract_types(random_curve_vector, circle_vec, chosen_type);

    // check that there are only circles(type = 0)
    for(size_t i = 0; i < circle_vec.size(); i++)
    {
        assert(circle_vec[i]->type == chosen_type);
    }


    // TASK 5. sorting circles in the ascending order of radii
    std::sort(circle_vec.begin(),circle_vec.end(), [](const std::shared_ptr<Curve> &c1, const std::shared_ptr<Curve> &c2)
    {
        return c1->radius < c2->radius;
    });

    // check radii of all circles, their order should be ascending(smallest to highest radii)
    std::cout << "_________SORTED CIRCLES_________" << std::endl;
    for(size_t i = 0; i < circle_vec.size(); i++)
    {
        std::cout << "radius: " << circle_vec[i]->radius << std::endl;
        if(i>1)
        {
            assert(circle_vec[i]->radius >= circle_vec[i-1]->radius);
        }
    }


    // TASK 6. computing total sum of radii of all curves
    double total_sum = 0.0;
    omp_set_num_threads(THREAD_NUM);
    #pragma omp parallel for
    for(size_t i = 0; i < circle_vec.size(); i++)
    {
        // std::cout << "radius: " << circle_vec[i]->radius << std::endl;
        total_sum += circle_vec[i]->radius;
    }
    std::cout << "_________TOTAL SUM OF RADII_________" << std::endl;
    std::cout << "total_sum: " << total_sum << std::endl;



    return 0;
}

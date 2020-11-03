#ifndef BODY_HPP
#define BODY_HPP
#include "Vec3.hpp"
#include "structs.hpp"
#include "Ray.hpp"
#include <utility>
#include <tuple>
#include <vector>

/*

?? 

What is correct color_rem type?

Triangle point order? Is triangle normal calculated right?

*/

class Body {

    public:

        Body(double gloss, Vec3 color_rem, double luminosity, RGB_color light_color) 
            : gloss_(gloss), color_rem_(color_rem), luminosity_(luminosity), light_color_(light_color) { }

        double gloss_;
        Vec3 color_rem_;

        double luminosity_;
        RGB_color light_color_;

        std::pair<double, double> x_range_;
        std::pair<double, double> y_range_;
        std::pair<double, double> z_range_;



        virtual bool FindCollision(Ray &Ray) = 0;


    private:



};

class Triangle : public Body {

    public:

        Triangle(std::tuple<Vec3, Vec3, Vec3> corners, double gloss, Vec3 color_rem, double luminosity, RGB_color light_color) :
        Body(gloss, color_rem, luminosity, light_color), 
        corners_(corners), 
        normal_((std::get<1>(corners) - std::get<0>(corners)).cross_product(std::get<2>(corners) - std::get<0>(corners)).normalize()) { }

        std::tuple<Vec3, Vec3, Vec3> corners_;
        Vec3 normal_;

        bool FindCollision(Ray &Ray); 

    private:

};

class TriBody : public Body {

    public:

        TriBody(std::vector<Triangle> triangles, double gloss, Vec3 color_rem, double luminosity, RGB_color light_color) : Body(gloss, color_rem, luminosity, light_color),
        triangles_(triangles), n_triangles_(triangles.size()) { }

        std::vector<Triangle> triangles_;
        int n_triangles_;

        bool FindCollision(Ray &Ray);

    private:

};

class Ball : public Body {

    public:

        Ball(Vec3 center, double radius, double gloss, Vec3 color_rem, double luminosity, RGB_color light_color) : Body(gloss, color_rem, luminosity, light_color), center_(center), radius_(radius) { }

        Vec3 center_;
        double radius_;

        bool FindCollision(Ray &Ray);

    private:

};

#endif
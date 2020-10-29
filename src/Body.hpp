#include "Vec3.hpp"
#include <utility>
#include <tuple>
#include <vector>

class Body {

    public:

        Body(double gloss, Vec3 color_rem, double luminosity, Vec3 light_color) : gloss_(gloss), color_rem_(color_rem), luminosity_(luminosity), light_color_(light_color) { }

        double gloss_;
        Vec3 color_rem_;

        double luminosity_;
        Vec3 light_color_;

        std::pair<double, double> x_range_;
        std::pair<double, double> y_range_;
        std::pair<double, double> z_range_;



        //virtual bool FindCollision(Ray &Ray) = 0; //Needs Ray-Class


    private:



};

/* To do Triangle:
    - constructor definition?
*/

class Triangle : public Body {

    public:

        Triangle(std::tuple<Vec3, Vec3, Vec3> corners, double gloss, Vec3 color_rem);

        std::tuple<Vec3, Vec3, Vec3> corners_;
        Vec3 normal_;

        //bool FindCollision(Ray &Ray); //Needs Ray-Class       

    private:

};

/* To do TriBody:
    - constructor definition?
*/

class TriBody : public Body {

    public:

        TriBody(std::vector<Triangle> triangles, double gloss, Vec3 color_rem);

        std::vector<Triangle> triangles_;
        int n_triangles_;

        //bool FindCollision(Ray &Ray); //Needs Ray-Class

    private:

};


/* To do Ball:
    - constructor definition?
*/

class Ball : public Body {

    public:

        Ball(Vec3 center, double radius, double gloss, Vec3 color_rem);

        Vec3 center_;
        double radius_;

        //bool FindCollision(Ray &Ray); //Needs Ray-Class

    private:

};


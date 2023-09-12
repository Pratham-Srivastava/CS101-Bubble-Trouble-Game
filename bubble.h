#include <simplecpp>
#include "variables.h"

/* Bubble Variables */
const int BUBBLE_START_X = 250;
const int BUBBLE_START_Y = 50;
const int BUBBLE_DEFAULT_RADIUS = 40;
const int BUBBLE_RADIUS_THRESHOLD = 10;
const int BUBBLE_DEFAULT_VX = 100;
const int BUBBLE_DEFAULT_VY = 0;
const int BUBBLE_DEFAULT_ACCELERATION = 40;

class Bubble{
    private:
        Circle circle;  // the circle representing the bubble
        double vx, vy, g;  // velocity in x and y direction
        Color color;    // color of the bubble
        unsigned int stage; // denotes if the bubble is large(1), medium (2) or small(3)

    public:

        Bubble(double cx, double cy, double r, double vx_=BUBBLE_DEFAULT_VX, unsigned int stage_=1){
            // Bubble constructor
            stage=stage_;
            circle = Circle(cx, cy, r);

            // Different color of the bubble according to its size
            if(stage==1) circle.setColor(COLOR(255,0,0));
            else if(stage==2) circle.setColor(COLOR(204,0,204));
            else if(stage==3) circle.setColor(COLOR(0,0,255));

            circle.setFill(true);

            vx = vx_;
            vy = BUBBLE_DEFAULT_VY;
            g = BUBBLE_DEFAULT_ACCELERATION;
        }

        void reflect_x(){
            // reflect the bubble only in X-direction
            vx=-vx;
        }

        void reflect_y(){
            // reflect the bubble only in Y-direction
            vy=-vy;
        }

        void reflect_x_y(){
            // reflect the bubble in both X and Y-directions
            vx=-vx;
            vy=-vy;
        }

        void nextStep(double t){
            // move the bubble
            double new_x = circle.getX() + vx*t;
            double new_y = circle.getY() + vy*t + 0.5*g*t*t;

            if ((vx < 0 && new_x < (0 + circle.getRadius())) // bounce along X direction at left border
                ||
                (vx > 0 && new_x > (WINDOW_X - circle.getRadius()))){ // bounce along X direction at right border

                vx = -vx;
                new_x = circle.getX() + vx*t;
            }

            circle.moveTo(new_x, new_y);
            vy=vy+g*t;
        }

        double get_radius(){
            // return the radius of the bubble
            return circle.getRadius();
        }

        double get_center_x(){
            // return the x coordinate of the center of the bubble
            return circle.getX();
        }

        double get_center_y(){
            // return the y coordinate of the center of the bubble
            return circle.getY();
        }

        double get_vx(){
            // return the x velocity of the bubble
            return vx;
        }

        double get_vy(){
            // return the y velocity of the bubble
            return vy;
        }

        unsigned int get_stage(){
            return stage;
        }
};

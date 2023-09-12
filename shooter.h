#include <simplecpp>
#include "bullet.h"
#include "variables.h"

/* Shooter Variables */
const int SHOOTER_START_X = 250;
const int SHOOTER_START_Y = 434;
const int SHOOTER_VX = 400;
const int SHOOTER_BODY_HEIGHT = 30;
const int SHOOTER_BODY_WIDTH = 18;
const int SHOOTER_HEAD_RADIUS = 8;

class Shooter{
    private:
        Rectangle body; // the body of the shooter
        Circle head;    // the head of the shooter
        double vx;      // the velocity in x-direction of the shooter

    public:
        Shooter(double position_x, double position_y){
            // Shooter constructor

            // body (represented by a rectangle)
            body = Rectangle(position_x, position_y, SHOOTER_BODY_WIDTH, SHOOTER_BODY_HEIGHT);
            body.setColor(COLOR(0, 0, 153));
            body.setFill(true);

            // head (represented by a circle)
            head = Circle(position_x, position_y - SHOOTER_BODY_HEIGHT/2. - SHOOTER_HEAD_RADIUS, SHOOTER_HEAD_RADIUS);
            head.setColor(COLOR(0, 0, 153));
            head.setFill(true);

            // initial velocity
            vx = SHOOTER_VX;
        }

        Bullet shoot(){
            // shoot a bullet
            return Bullet(head.getX(), head.getY());
        }

        void move(double t, bool is_moving_left){
            // move the shooter
            double vel = vx;
            if (is_moving_left) {
                vel = -vel;
            }

            double new_body_x = body.getX() + vel*t;
            double new_head_x = head.getX() + vel*t;

            if (vel < 0 && new_body_x < (0 + body.getWidth()/2.0)){ // stop moving along X-direction at left border (if pressed A)
                new_body_x = 0 + body.getWidth()/2.0;
                new_head_x = 0 + body.getWidth()/2.0;
            }
            else if (vel > 0 && new_body_x > (WINDOW_X - body.getWidth()/2.0)){ // stop moving along X-direction at right border (if pressed D)
                new_body_x = WINDOW_X - body.getWidth()/2.0;
                new_head_x = WINDOW_X - body.getWidth()/2.0;
            }

            body.moveTo(new_body_x, body.getY());
            head.moveTo(new_head_x, head.getY());
        }

        double get_head_center_x(){
            // return the x coordinate of the center of the head
            return head.getX();
        }

        double get_head_center_y(){
            // return the y coordinate of the center of the head
            return head.getY();
        }

        double get_head_radius(){
            // return the radius of the head
            return head.getRadius();
        }

        double get_body_center_x(){
            // return the x coordinate of the center of the body
            return body.getX();
        }

        double get_body_center_y(){
            // return the y coordinate of the center of the body
            return body.getY();
        }

        double get_body_width(){
            // return the width of the body
            return body.getWidth();
        }

        double get_body_height(){
            // return the height of the body
            return body.getHeight();
        }

        void hide(){
            head.hide();
            body.hide();
        }
};

#include <simplecpp>

/* Bullet Varaibles */
const int BULLET_WIDTH = 10;
const int BULLET_HEIGHT = 10;
const int BULLET_VELOCITY = 200;

class Bullet{
    private:
        Rectangle rect; // the rectangle representing the bullet
        double vy; // the velocity in y direction of the bullet

    public:
        Bullet(double center_x, double center_y){
            // Bullet constructor
            rect = Rectangle(center_x, center_y, BULLET_WIDTH, BULLET_HEIGHT);
            rect.setColor(COLOR(153, 76, 0));
            rect.setFill(true);
            vy = BULLET_VELOCITY;
        }

        bool nextStep(double t){
            // move the bullet
            double new_y = rect.getY() - vy*t;
            if(new_y < (0-rect.getHeight()/2.0))   // out of canvas, so delete the bullet
            {
                return false;
            }
            rect.moveTo(rect.getX(), new_y);
            return true;
        }

        double get_width(){
            // return the width of the bullet
            return rect.getWidth();
        }

        double get_height(){
            // return the height of the bullet
            return rect.getHeight();
        }

        double get_center_x(){
            // return the x coordinate of the center of the bullet
            return rect.getX();
        }

        double get_center_y(){
            // return the y coordinate of the center of the bullet
            return rect.getY();
        }
};

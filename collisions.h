#include <simplecpp>
#include "shooter.h"
#include "bubble.h"
#include "background.h"

// A header file containg all the functions checking collision between different entities in the game
// Since this file is included only once (in the main.cpp) and hence, there is no issue of multiple definitions

bool check_collision(Bullet &bullet, Background &background){
    // checks if a bullet collides with obstacles in level 3
    bool collision =
    (((bullet.get_center_x()+ bullet.get_width()/2 >= background.get_center_x_obstacle1()-background.get_width_obstacle1()/2)
    &&(bullet.get_center_x()- bullet.get_width()/2 <= background.get_center_x_obstacle1()+ background.get_width_obstacle1()/2))
    &&(bullet.get_center_y()-bullet.get_height()/2 < background.get_center_y_obstacle1()+ background.get_height_obstacle1()/2))
    ||(((bullet.get_center_x()+ bullet.get_width()/2 >= background.get_center_x_obstacle2()-background.get_width_obstacle2()/2)
    &&(bullet.get_center_x()- bullet.get_width()/2 <= background.get_center_x_obstacle2()+ background.get_width_obstacle2()/2))
    &&(bullet.get_center_y()-bullet.get_height()/2 < background.get_center_y_obstacle2()+ background.get_height_obstacle2()/2));

    // return true if collision occurs, else false
    if(collision) return true;
    return false;
}

void bullet_obstacle_collison(vector<Bullet> &bullets, Background &background){
    // goes over all the bullets and calls a function for checking if collison occurs
    // if collision occurs, destroy the bullet
    for(unsigned int i=0; i<bullets.size(); i++){
        if(check_collision(bullets[i], background)){
            bullets.erase(bullets.begin()+i);
        }
    }
}

void bubble_ground_collision(vector<Bubble> &bubbles){
    // checks if any bubble hits the ground
    // if collision occurs, bubble bounces back
    for(unsigned int i=0; i<bubbles.size(); i++){
        if ((bubbles[i].get_center_y() + bubbles[i].get_radius())>=PLAY_Y_HEIGHT){
                bubbles[i].reflect_y();
        }
    }
}

void check_collision(Bubble &bubble, Background &background){
    // checks collision between the bubbles and the obstacles in level 3
    // if the bubble hits an obstacle, it bouces back

    // the bool statements check collision about different edges and corners of the obstacle
    // we use the 8 cardinal directions to make it easy to understand which statement checks collision about which edge or corner
    bool collision_north_south =
    (((bubble.get_center_x()>=background.get_center_x_obstacle1()-background.get_width_obstacle1()/2)
    &&(bubble.get_center_x()<=background.get_center_x_obstacle1()+ background.get_width_obstacle1()/2))
    &&(std::abs(background.get_center_y_obstacle1()-bubble.get_center_y())<=bubble.get_radius()+background.get_height_obstacle1()/2))
    ||(((bubble.get_center_x()>=background.get_center_x_obstacle2()-background.get_width_obstacle2()/2)
    &&(bubble.get_center_x()<=background.get_center_x_obstacle2()+ background.get_width_obstacle2()/2))
    &&(std::abs(background.get_center_y_obstacle2()-bubble.get_center_y())<=bubble.get_radius()+background.get_height_obstacle2()/2));

	bool collision_east_west =
	(((bubble.get_center_y()>=background.get_center_y_obstacle1()- background.get_height_obstacle1()/2)
	&&(bubble.get_center_y()<=background.get_center_y_obstacle1()+ background.get_height_obstacle1()/2))
    &&(std::abs(bubble.get_center_x()-background.get_center_x_obstacle1())<=bubble.get_radius()+background.get_width_obstacle1()/2))
    ||(((bubble.get_center_y()>=background.get_center_y_obstacle2()- background.get_height_obstacle2()/2)
    &&(bubble.get_center_y()<=background.get_center_y_obstacle2()+ background.get_height_obstacle2()/2))
    &&(std::abs(bubble.get_center_x()-background.get_center_x_obstacle2())<=bubble.get_radius()+background.get_width_obstacle2()/2));

	bool collision_NW =
	(pow(bubble.get_center_x()-(background.get_center_x_obstacle1()-background.get_width_obstacle1()/2), 2)
	+ pow(bubble.get_center_y()-(background.get_center_y_obstacle1()-background.get_height_obstacle1()/2), 2)
	<= pow(bubble.get_radius(), 2))
    ||(pow(bubble.get_center_x()-(background.get_center_x_obstacle2()-background.get_width_obstacle2()/2), 2)
    + pow(bubble.get_center_y()-(background.get_center_y_obstacle2()-background.get_height_obstacle2()/2), 2)
    <= pow(bubble.get_radius(), 2));

	bool collision_NE = (
	pow(bubble.get_center_x()-(background.get_center_x_obstacle1()+background.get_width_obstacle1()/2), 2)
	 + pow(bubble.get_center_y()-(background.get_center_y_obstacle1()-background.get_height_obstacle1()/2), 2)
	  <= pow(bubble.get_radius(), 2))
    ||(pow(bubble.get_center_x()-(background.get_center_x_obstacle2()+background.get_width_obstacle2()/2), 2)
     + pow(bubble.get_center_y()-(background.get_center_y_obstacle2()-background.get_height_obstacle2()/2), 2)
     <= pow(bubble.get_radius(), 2));

	bool collision_SW =
	(pow(bubble.get_center_x()-(background.get_center_x_obstacle1()-background.get_width_obstacle1()/2), 2)
	+ pow(bubble.get_center_y()-(background.get_center_y_obstacle1()+background.get_height_obstacle1()/2), 2)
	<= pow(bubble.get_radius(), 2))
    ||(pow(bubble.get_center_x()-(background.get_center_x_obstacle2()-background.get_width_obstacle2()/2), 2)
    + pow(bubble.get_center_y()-(background.get_center_y_obstacle2()+background.get_height_obstacle2()/2), 2)
    <= pow(bubble.get_radius(), 2));


	bool collision_SE =
	(pow(bubble.get_center_x()-(background.get_center_x_obstacle1()+background.get_width_obstacle1()/2), 2)
	+ pow(bubble.get_center_y()-(background.get_center_y_obstacle1()+background.get_height_obstacle1()/2), 2)
	<= pow(bubble.get_radius(), 2))
    ||(pow(bubble.get_center_x()-(background.get_center_x_obstacle2()+background.get_width_obstacle2()/2), 2)
    + pow(bubble.get_center_y()-(background.get_center_y_obstacle2()+background.get_height_obstacle2()/2), 2)
    <= pow(bubble.get_radius(), 2));


	// following statements rebound the bubble if they hit an edge or a corner accordingly
	if(collision_north_south){
        bubble.reflect_y();
    }
    else if(collision_east_west){
        bubble.reflect_x();
    }
    else if(collision_NW||collision_NE||collision_SW||collision_SE){
        bubble.reflect_x_y();
    }
}

void bubble_obstacle_collision(vector<Bubble> &bubbles, Background &background){
    // goes over the entire vector contating the bubbles, and calls a function for checking collision for each bubble
    for(unsigned int i=0; i<bubbles.size(); i++){
        check_collision(bubbles[i], background);
    }
}

void split(vector<Bubble> &bubbles, unsigned int i, unsigned int level){
    // this function adds two more smaller bubbles depending upon the stage of the bubble that was hit with the bullet
    // if the level is 2 and the stage of bubble is 1, or the level is 3 and the stage of bubble is 1 or 2,
    // then only two new bubbles are added
    if((bubbles[i].get_stage()==1)&&(bubbles[i].get_stage()<level)){
        bubbles.push_back(Bubble(bubbles[i].get_center_x(), bubbles[i].get_center_y(), bubbles[i].get_radius()/2 ,
                                    -bubbles[i].get_vx(), 2));

        bubbles.push_back(Bubble(bubbles[i].get_center_x(), bubbles[i].get_center_y(), bubbles[i].get_radius()/2 ,
                                    bubbles[i].get_vx(), 2));
    }

    else if((bubbles[i].get_stage()==2)&&(bubbles[i].get_stage()<level)){
        bubbles.push_back(Bubble(bubbles[i].get_center_x(), bubbles[i].get_center_y(), bubbles[i].get_radius()/2 ,
                        -bubbles[i].get_vx(), 3));

        bubbles.push_back(Bubble(bubbles[i].get_center_x(), bubbles[i].get_center_y(), bubbles[i].get_radius()/2 ,
                        bubbles[i].get_vx(), 3));
    }
}

bool check_collision(Bubble &bubble, Bullet &bullet){
    // checks collision between the bubbles and the bullets

    // the bool statements check collision about different edges and corners of the bullet
    // we use the 8 cardinal directions to make it easy to understand which statement checks collision about which edge or corner
    bool collision_north_south =((bubble.get_center_x()>=bullet.get_center_x()-bullet.get_width()/2)
                                &&(bubble.get_center_x()<=bullet.get_center_x()+ bullet.get_width()/2))
                            &&(std::abs(bullet.get_center_y()-bubble.get_center_y())<=bubble.get_radius()+bullet.get_height()/2);

    bool collision_east_west = ((bubble.get_center_y()>=bullet.get_center_y()- bullet.get_height()/2)
                                &&(bubble.get_center_y()<=bullet.get_center_y()+ bullet.get_height()/2))
                            &&(std::abs(bubble.get_center_x()-bullet.get_center_x())<=bubble.get_radius()+bullet.get_width()/2);

    bool collision_NW = pow(bubble.get_center_x()-(bullet.get_center_x()-bullet.get_width()/2), 2)
                    + pow(bubble.get_center_y()-(bullet.get_center_y()-bullet.get_height()/2), 2) <= pow(bubble.get_radius(), 2);

    bool collision_NE = pow(bubble.get_center_x()-(bullet.get_center_x()+bullet.get_width()/2), 2)
                    + pow(bubble.get_center_y()-(bullet.get_center_y()-bullet.get_height()/2), 2) <= pow(bubble.get_radius(), 2);

    bool collision_SW = pow(bubble.get_center_x()-(bullet.get_center_x()-bullet.get_width()/2), 2)
                    + pow(bubble.get_center_y()-(bullet.get_center_y()+bullet.get_height()/2), 2) <= pow(bubble.get_radius(), 2);

    bool collision_SE = pow(bubble.get_center_x()-(bullet.get_center_x()+bullet.get_width()/2), 2)
                    + pow(bubble.get_center_y()-(bullet.get_center_y()+bullet.get_height()/2), 2) <= pow(bubble.get_radius(), 2);

    // returns true if bullet hits a bubble, else false
    if(collision_north_south||collision_east_west||collision_NW||collision_NE||collision_SW||collision_SE) return true;
    return false;
}

bool bubble_bullet_collision(vector<Bubble> &bubbles, vector<Bullet> &bullets, unsigned int &score, unsigned int level){
    // goes over all possible pairs of bubbles and bullets and calls the function to check collision
    // if collision occurs, returns true, else false
    for(unsigned int i=0; i<bubbles.size(); i++){
        for(unsigned int j=0; j<bullets.size(); j++){
            if(check_collision(bubbles[i], bullets[j])){ // if collision occurs
                split(bubbles, i, level); // split the bubble

                // appends the score depending upon the stage of the bubble
                if(bubbles[i].get_stage()==1) score+=10; // if large bubble is hit
                else if (bubbles[i].get_stage()==2) score+=20; // if medium bubble is hit
                else if (bubbles[i].get_stage()==3) score+=30; // if small bubble is hit

                // after collision, the participating bubble and bullet are erased
                bullets.erase(bullets.begin()+j);
                bubbles.erase(bubbles.begin()+i);
                return true;
            }
        }
    }
    return false;
}

bool check_collision(Bubble &bubble, Shooter &shooter){
    // checks collision between the bubbles and the shooter

    // the bool statements check collision about different edges and corners of the body of the shooter
    // we use the 8 cardinal directions to make it easy to understand which statement checks collision about which edge or corner
    // we do not check for the lower edge and corners of the shooter body, because it is on the ground and bubble will never hit that part
    bool collision_north =((bubble.get_center_x()>=shooter.get_body_center_x()-shooter.get_body_width()/2)
                        &&(bubble.get_center_x()<=shooter.get_body_center_x()+ shooter.get_body_width()/2))
                        &&(shooter.get_body_center_y()-bubble.get_center_y()<=bubble.get_radius()+shooter.get_body_height()/2);

    bool collision_east_west = ((bubble.get_center_y()>=shooter.get_body_center_y()- shooter.get_body_height()/2)
                             &&(bubble.get_center_y()<=shooter.get_body_center_y()+ shooter.get_body_height()/2))
                &&(std::abs(bubble.get_center_x()-shooter.get_body_center_x())<=bubble.get_radius()+shooter.get_body_width()/2);

    bool collision_NW = pow(bubble.get_center_x()-(shooter.get_body_center_x()-shooter.get_body_width()/2), 2)
                      + pow(bubble.get_center_y()-(shooter.get_body_center_y()-shooter.get_body_height()/2), 2)
                     <= pow(bubble.get_radius(), 2);

    bool collision_NE = pow(bubble.get_center_x()-(shooter.get_body_center_x()+shooter.get_body_width()/2), 2)
                      + pow(bubble.get_center_y()-(shooter.get_body_center_y()-shooter.get_body_height()/2), 2)
                     <= pow(bubble.get_radius(), 2);

    // checks collision between the head of the shooter and the bubble
    bool collision_head_bubble = pow(bubble.get_center_x()-shooter.get_head_center_x(), 2) + pow(bubble.get_center_y()-shooter.get_head_center_y(), 2) <= pow(bubble.get_radius()+shooter.get_head_radius(), 2);

    // following statements check if the collision occurs, and rebound the bubble accordingly
    // returns true if collision occurs, else false
    if(collision_north){
        bubble.reflect_y();
        return true;
    }
    else if(collision_east_west){
        bubble.reflect_x();
        return true;
    }
    else if(collision_NW||collision_NE||collision_head_bubble){
        bubble.reflect_x_y();
        return true;
    }
    return false;
}

bool bubble_shooter_collision(vector<Bubble> &bubbles, Shooter &shooter){
    // goes over all the bubbles and checks if they have collisded with the shooter
    // returns true if collision occurs, else false
    for(unsigned int i=0; i<bubbles.size(); i++){
        if(check_collision(bubbles[i], shooter))return true;
    }
    return false;
}

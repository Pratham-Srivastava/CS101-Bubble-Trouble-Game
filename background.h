#include <simplecpp>
#include "variables.h"

/* A class which contains all the entities for the background of the game window */
class Background{
    private:
        //Gameplay Entities: The entities which make up the background when the user is playing a level

        // first four variables are background gameplay entities
        Rectangle sky;
        Rectangle ground;

        // obstacles introduced in level 3 of the game
        Rectangle obstacle1;
        Rectangle obstacle2;

        Rectangle game_begin_end; // background for beginning and ending of the game
        Rectangle interval; // background for transition screen between different levels
        Rectangle game_over; // background when game overs

        void hide_environment(){
            // hides all the gameplay entities when the level ends
            sky.hide();
            ground.hide();
            obstacle1.hide();
            obstacle2.hide();
        }

    public:
        Background(){
            // Background constructor

            // defining the sizes and colors of all the rectangles representing background entities
            // only one background (which indicates the start of the game) is visible and all the rest are hidden
            game_begin_end.reset(WINDOW_X/2, WINDOW_Y/2, WINDOW_X, WINDOW_Y);
            game_begin_end.setColor(COLOR(234, 40, 247));
            game_begin_end.setFill(true);

            interval.reset(WINDOW_X/2, WINDOW_Y/2, WINDOW_X, WINDOW_Y);
            interval.setColor(COLOR(253, 68, 167));
            interval.setFill(true);
            interval.hide();

            sky.reset(WINDOW_X/2, WINDOW_Y/2, WINDOW_X, WINDOW_Y);
            sky.setColor(COLOR(81, 216, 255));
            sky.setFill(true);
            sky.hide();

            ground.reset(WINDOW_X/2, PLAY_Y_HEIGHT + GROUND_HEIGHT/2, WINDOW_X, GROUND_HEIGHT);
            ground.setColor(COLOR(0, 255, 0));
            ground.setFill(true);
            ground.hide();

            obstacle1.reset(LEFT_MARGIN + LENGTH/2, WINDOW_Y/2 , LENGTH, WIDTH);
            obstacle1.setColor(COLOR(204, 102, 0));
            obstacle1.setFill(true);
            obstacle1.hide();

            obstacle2.reset(RIGHT_MARGIN - LENGTH/2, WINDOW_Y/2 , LENGTH, WIDTH);
            obstacle2.setColor(COLOR(204, 102, 0));
            obstacle2.setFill(true);
            obstacle2.hide();
        }

        void game_starts(){
            // before a level starts, a transition screen is made visible indicating that the level is going to commence
            game_begin_end.hide();
            interval.show();
        }

        void level_starts(unsigned int level){
            // when the level starts, hidden gameplay entities are made visible
            interval.hide();
            sky.show();
            ground.show();
            if(level==3){  // obstacles are present only in level 3
                obstacle1.show();
                obstacle2.show();
            }
        }

        void game_ends(unsigned int level){
            // when the game ends, all gamepplay entities are hidden and a clean transition screen is made visible
            // indicating that next level is going to commence
            interval.show();
            hide_environment();
        }

        void end_game_bg(){
            // when the game ends (when the user completes all levels or presses Q, not game over)
            // all gamepplay entities are hidden and a clean background appears indicating that the game has ended
            hide_environment();
            game_begin_end.show();
        }

        void game_over_bg(){
            // when the game is over (due to time running out or dead shooter),
            //all gamepplay entities are hidden and a clean background appears indicating that the game has ended
            hide_environment();
            game_over.reset(WINDOW_X/2, WINDOW_Y/2, WINDOW_X, WINDOW_Y);
            game_over.setColor(COLOR(247, 81, 40));
            game_over.setFill(true);
        }

        double get_width_obstacle1(){
            // return the width of the obstacle1
            return obstacle1.getWidth();
        }

        double get_height_obstacle1(){
            // return the height of the obstacle1
            return obstacle1.getHeight();
        }

        double get_center_x_obstacle1(){
            // return the x coordinate of the center of the obstacle1
            return obstacle1.getX();
        }

        double get_center_y_obstacle1(){
            // return the y coordinate of the center of the obstacle1
            return obstacle1.getY();
        }

        double get_width_obstacle2(){
            // return the width of the obstacle2
            return obstacle2.getWidth();
        }

        double get_height_obstacle2(){
            // return the height of the obstacle2
            return obstacle2.getHeight();
        }

        double get_center_x_obstacle2(){
            // return the x coordinate of the center of the obstacle2
            return obstacle2.getX();
        }

        double get_center_y_obstacle2(){
            // return the y coordinate of the center of the obstacle2
            return obstacle2.getY();
        }
};

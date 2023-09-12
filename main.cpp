/*
	CS 101 Project: Bubble Trouble
    Name: Pratham Srivastava
    Roll No.: 210100121
    Section: D3

    LIST OF FILES:
        bullet.h
        bubble.h
        shooter.h
        variables.h
        background.h
        text.h
        collisions.h
        main.cpp

*/

#include <simplecpp>
#include "collisions.h"
#include "text.h"

//    In the entire program, I have used "Game ends" and "Game over" in many comments, functions and variables.
//  	Game Ends: The player presses 'q' or the player succesfully completes all the levels.
//      Game Over: The shooter is dead ot the time runs out.


unsigned int TOTAL_SCORE=0; // a variable storing the cumulative score of the user since the beginning of game

void erase_environment(vector<Bubble> &bubbles, vector<Bullet> &bullets, Shooter &shooter){
    // erases the bubbles, shooter and the bullets from the game window
    bubbles.clear();
    bullets.clear();
    shooter.hide();
}

void end_game(Background &background, GameText &game_text){
    // when the game ends, a new clean background appears with a congratulatory message and the total score
    game_text.hide_level();
    game_text.hide_text();
    background.end_game_bg();
    game_text.end_game_text(TOTAL_SCORE);

    if(TOTAL_SCORE==MAXIMUM_SCORE) game_text.show_max_score();

    wait(2);
}

void game_over(Background &background, GameText &game_text){
    // when the game is over, a new clean background appears with a message and the total score
    game_text.hide_level();
    game_text.hide_text();
    background.game_over_bg();
    game_text.over_text(TOTAL_SCORE);

    wait(2);
}


void move_bullets(vector<Bullet> &bullets){
    // move all bullets
    for(unsigned int i=0; i<bullets.size(); i++){
        if(!bullets[i].nextStep(STEP_TIME)){
            bullets.erase(bullets.begin()+i);
        }
    }
}

void move_bubbles(vector<Bubble> &bubbles){
    // move all bubbles
    for (unsigned int i=0; i < bubbles.size(); i++)
    {
        bubbles[i].nextStep(STEP_TIME);
    }
}

vector<Bubble> create_bubbles()
{
    // create initial bubbles in the game
    vector<Bubble> bubbles;
    bubbles.push_back(Bubble(WINDOW_X/2.0, BUBBLE_START_Y, BUBBLE_DEFAULT_RADIUS, -BUBBLE_DEFAULT_VX, 1));
    bubbles.push_back(Bubble(WINDOW_X/4.0, BUBBLE_START_Y, BUBBLE_DEFAULT_RADIUS, BUBBLE_DEFAULT_VX, 1));
    return bubbles;
}


int main()
{
    initCanvas("Bubble Trouble", WINDOW_X, WINDOW_Y); // create game window

    Background background; // intialise background for the game
    GameText game_text; // intialise text that appears on the game window
    //a colored background appears with a message "Game Begins!!!"

    wait(2);

    unsigned int level; // a variable that stores on which level is the user

    for(level=1; level<=3; level++){ //  a loop that loops through three levels

        // intialise score, health and time to default values at the beginning of each level
        unsigned int score=0, time=60, health=3;

        // a new colored background appears and shows the level at which the user is currently in
        background.game_starts();
        game_text.show_level(level);
        game_text.update_level(level);

        wait(2);

        // the gameplay background appears with sky, ground (and obstacles) along with user statistics
        background.level_starts(level);
        game_text.initialise_text(score, time, health);

        // intialize the shooter
        Shooter shooter(SHOOTER_START_X, SHOOTER_START_Y);

        // initialize the bubbles
        vector<Bubble> bubbles = create_bubbles();

        // initialize the bullets (empty)
        vector<Bullet> bullets;

        XEvent event;

        int count_loop=0; // a variable that counts the number of iterations that occur during one level

        // Main game loop
        while (!bubbles.size()==0)
        {
            bool pendingEvent = checkEvent(event);
            if (pendingEvent)
            {
                // Get the key pressed and display it on the window
                char c = charFromEvent(event);
                game_text.update_cmd(c);

                // Update the shooter
                if(c == 'a')
                    shooter.move(STEP_TIME, true);
                else if(c == 'd')
                    shooter.move(STEP_TIME, false);
                else if(c == 'w')
                    bullets.push_back(shooter.shoot());
                else if(c == 'q'){
                    //user wants to end the game
                    //so erase all gameplay entities and show the total score with a congratulatory message
                    TOTAL_SCORE+=score;
                    erase_environment(bubbles, bullets, shooter);
                    end_game(background, game_text);
                    return 0;
                };

            }

            // Update the bubbles
            move_bubbles(bubbles);

            // Update the bullets
            move_bullets(bullets);

            bubble_ground_collision(bubbles); // check if any bubble hits the ground

            // in level 3, check collision between the bubble and the obstacles (rebound them on hitting)
            //or bullets and the obstacles (destroy the bullet on hitting)
            if(level==3) {
                bubble_obstacle_collision(bubbles, background);
                bullet_obstacle_collison(bullets, background);
            }

            // check if a bullet hits a bubble
            // if collision occurs, update the score and display it on window
            if(bubble_bullet_collision(bubbles, bullets, score, level)){
                game_text.update_score(score);
            }

            // check if any bubble hits the shooter
            // if collision occurs, decrement the health by 1 unit and display it on window
            if(bubble_shooter_collision(bubbles, shooter)){
                health--;
                game_text.update_health(health);
                if(health==0){ // if health becomes zero, the shooter is dead and game overs
                    erase_environment(bubbles, bullets, shooter);
                    game_over(background, game_text);
                    return 0;
                };
            }

            count_loop++;
            // if UNIT_TIME_INVERSE number of iterations have occured, decrement the time left by 1 second
            if(count_loop%UNIT_TIME_INVERSE==0){
                time--;
                game_text.update_time(time);
                if(time==0){ // if the time finishes, the game is over
                    erase_environment(bubbles, bullets, shooter);
                    game_over(background, game_text);
                    return 0;
                };
            }
            wait(STEP_TIME);
        }
        // if the user finsihes the level succesfully, erase all the entities present on the screen,
        // for a fresh start for the next level
        erase_environment(bubbles, bullets, shooter);
        game_text.hide_text();
        background.game_ends(level);

        TOTAL_SCORE+=score; // update the total score at the end of each level
    }

    // if the user finishes all the levels succesfully,
    // end the game with a congratulatory message and total score
    end_game(background, game_text);
}

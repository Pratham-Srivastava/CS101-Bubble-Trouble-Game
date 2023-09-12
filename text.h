#include <simplecpp>

/* A class that manages all the text that appears on the game window */
class GameText{
    private:
        // text indicating level at which the user is
        string level_text="Level _";
        Text game_level;

        // text indicating the command which the user has given
        string msg_cmd="Cmd: _";
        Text charPressed;

        // text indicating the current score in that particular level
        string score_text="Score: ";
        Text game_score_1;
        Text game_score_2;

        // text indicating the time left
        string time_text="Time Left: ";
        Text time_left_1;
        Text time_left_2;

        // text indicating the health of the shooter
        // in each level, shooter gets 3 lives
        string health_text="Health: 3";
        Text shooter_health;

        // text indicating the cumulative score across all levels
        string total_score_text="Total Score: ";
        Text game_total_score_1;
        Text game_total_score_2;

        string maximum_score="Well Done! You have earned the maximum score!";
        Text max_score;

        Text game_begins_text; // text saying that the game has begun
        Text game_ends_text; // text saying that the game has ended
        Text game_over_text; // text saying that the game is over



    public:
        GameText(){
            // GameText constructor
            game_begins_text.reset(WINDOW_X/2 , WINDOW_Y/2 , "Game Begins!!!");
        }

        void initialise_text(unsigned int score, unsigned int time, unsigned int health){
            // at the beginning of each level, this function makes all the necessary information visible
            game_level.reset(WINDOW_X/2 , TOP_MARGIN , level_text);

            charPressed.reset(LEFT_MARGIN, BOTTOM_MARGIN, msg_cmd);

            game_score_1.reset(WINDOW_X/2 , BOTTOM_MARGIN, score_text);
            game_score_2.reset(WINDOW_X/2 + textWidth(score_text)/2 + SPACE, BOTTOM_MARGIN, score);

            time_left_1.reset(RIGHT_MARGIN , BOTTOM_MARGIN, time_text);
            time_left_2.reset(RIGHT_MARGIN + textWidth(time_text)/2 + SPACE, BOTTOM_MARGIN, time);

            shooter_health.reset(RIGHT_MARGIN, TOP_MARGIN, health_text);
        }

        void show_level(unsigned int level){
            // the text indicating the level appears on the transition screen
            game_begins_text.hide();
            game_level.reset(WINDOW_X/2 , WINDOW_Y/2 , level_text);
        }

        void update_level(unsigned int level){
            // updates the level, after the previous level ends
            char l=level+48;
            level_text[level_text.length() - 1] = l;
            game_level.setMessage(level_text);
        }

        void update_cmd(char c){
            // shows the character pressed by the user at the instant
            msg_cmd[msg_cmd.length() - 1] = c;
            charPressed.setMessage(msg_cmd);
        }

        void show_total_score(unsigned int total_score){
            // shows the total score of the user
            game_total_score_1.reset(WINDOW_X/2, WINDOW_Y/2, total_score_text);
            game_total_score_2.reset(WINDOW_X/2 + textWidth(total_score_text)/2 + SPACE/2, WINDOW_Y/2, total_score);
        }

        void show_max_score(){
            // shows a congratulatory message if the user has earned the maximum score possible
            max_score.reset(WINDOW_X/2, WINDOW_Y/2 - SPACE, maximum_score);
        }

        void end_game_text(unsigned int total_score){
            // when the game ends, a congratulatory message appears along with the total score
            game_ends_text.reset(WINDOW_X/2 , WINDOW_Y/2 + SPACE, "Well Played!!!");
            show_total_score(total_score);
        }

        void over_text(unsigned int total_score){
            // when the game is over, a text showing "Game Over" and total score appears
            game_over_text.reset(WINDOW_X/2 , WINDOW_Y/2 + SPACE, "Game Over!!!");
            show_total_score(total_score);

        }

        void update_score(unsigned int score){
            // updates the score on window
            game_score_2.reset(WINDOW_X/2 + textWidth(score_text)/2 +SPACE, BOTTOM_MARGIN, score);
        }

        void update_health(unsigned int health){
            // updates the health on window
            char c=health+48;
            health_text[health_text.length() - 1] = c;
            shooter_health.setMessage(health_text);
        }

        void update_time(unsigned int time){
            // updates the time left on window
            time_left_2.reset(RIGHT_MARGIN + textWidth(time_text)/2 + SPACE, BOTTOM_MARGIN, time);
        }

        void hide_text(){
            // hides all the text entities when the level ends
            charPressed.hide();
            game_score_1.hide();
            game_score_2.hide();
            time_left_1.hide();
            time_left_2.hide();
            shooter_health.hide();
        }

        void hide_level(){
            // hides all the level text when the game ends or game is over
            game_level.hide();
        }
};

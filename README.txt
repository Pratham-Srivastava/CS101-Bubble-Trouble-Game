CS 101 Project: Bubble Trouble
Name: Pratham Srivastava
Roll No.: 210100121
Section: D3

LIST OF FILES:
	bullet.h		->	defines the class 'Bullet' and corresponding variables
	bubble.h		->  defines the class 'Bubble' and corresponding variables
	shooter.h		->  defines the class 'Shooter' and corresponding variables
	variables.h		->	defines the main game variables 
	background.h	->  defines the class 'Background' and corresponding variables (to manage all the background elements)
	text.h			->  defines the class 'GameText' and corresponding variables (to manage all the text elements appearing)
	collisions.h	->	defines the functions responsible for checking collisions between different entities
	main.cpp		->  main program
	
LINK TO THE VIDEO: Both the files contain the same video.
	.webm extension ->  https://drive.google.com/file/d/1rQoppvvy0gPgdySObIP4miZ1vK5qMysW/view?usp=sharing
	 .mp4 extension ->  https://drive.google.com/file/d/1GTBTN0rIH6Szpk_QBrBkPM6JBCAn6Xl4/view?usp=sharing
		
FEATURES:
	(a) Bubbles move in vertical parabolic path (i.e. perform projectile motion).
		When the bubble hits the ground, it rebounds with the same vertical velocity.
		
	(b) There are three kinds of bubbles in the game:
			Large: Radius R
			Medium: Radius R/2
			Small: Radius R/4	

	(c) There are five statistic elements displayed on the screen:
			(i)   An element which shows the level at which the user is currently in
			(ii)  An element which shows the health of the shooter
			(iii) An element which shows the character corresponding to the key pressed by the user on the keyboard
			(iv)  An element which shows the cuurent score of the user in that particular level
			(v)   An element which shows the time left for the level to end
		Additionally, there is an element which shows the total cumulative score of the user across all the levels played
		whenever the game ends or the game is over.
		
	(d) When a bullet hits a bubble:
			(i)   if level=1; bubble bursts (or is destroyed)
			(ii)  if level=2; if bubble is a large bubble, it splits into two medium bubbles
							  if bubble is a medium bubble, it bursts
			(iii) if level=3; if bubble is a large bubble, it splits into two medium bubbles
							  if bubble is a medium bubble, it splits into two small bubbles
							  if bubble is a small bubble, it bursts
			
		When a parent bubble splits, the daughter bubbles move in horizontally opposite directions 
		with magnitude of horizontal velocity equal to that of the parent bullet and with vertical velocity zero.
				
		Bullet is destroyed in all the cases.
			
		If bullet hits a large bubble, score is increased by 10 units.
		If bullet hits a medium bubble, score is increased by 20 units.
		If bullet hits a small bubble, score is increased by 30 units.
			
		Maximum score possible is 460;			
								 
	(e) When a bubble hits the shooter, the bubble rebounds. 
		The health of the shooter is reduced by 1 unit.
		The shooter gets 3 lives at the beginning of each level.
		When the shooter has 0 lives left, the game is over.
			
	(f) For each level, the user gets 60 seconds to burst all the bubbles.
		If the time runs out, the game is over.
		
	(g) In Level 3 of the game, obsctacles are introduced.
		When a bubble hits the obstacles, it rebounds.
		When a bullet fired by the shooter hits the obstacles, it is destroyed (i.e. the bullet cannot pass through the obstacles).
	
	(h) Collisions:
			When a bubble hits the shooter's head, it rebounds with both the components of its velocity made negative.
				
			When a bubble hits any corners (shooter body or obstacles), 
			it rebounds with both the components of its velocity made negative.
				
			When a bubble hits any edge (shooter body, obstacles, walls or ground), 
			it rebounds with the component of velocity perpendicular to the edge made negative
			but the other component remains unchanged.
		
	(i) Certain features involving the different backgrounds used will be mentioned in the gameplay.
		
GAMEPLAY:
	(1) Game window is created.
	(2) A colored background appears with "Game Begins!!!" message. Wait 2 seconds.
	(3) A new colored background appears with "Level 1" message. Wait 2 seconds.
	(4) -> A new background (blue sky and green ground) appears. 
		-> The statistic elements appear.
		-> Bubbles appear and start moving.
		-> Shooter appears.
	(5) On succesful completion of the level, STEP 2 happens with "Level 2" message. Wait 2 seconds.
	(6) Level 2 begins (similar to STEP 4).
	(7) On succesful completion of the level, STEP 2 happens with "Level 3" message. Wait 2 seconds.
	(8) Level 3 begins (similar to STEP 4).
		-> This time, two brown colored obstacles appear.
	(9) On succesful completion of the level, a new background appears.
		-> A message "Well PLayed!!!" and the total score appears.
		-> A congratulatory message appears as the player has scored the maximum possible score.
		-> Wait 2 seconds.
	(10) Game window closes.
		
	(11) If the player presses 'q', the player is taken to STEP 9 (but the congratulatory message is not displayed).
		 -> The total score till the moment the player pressed 'q' appears.
	(12) If the shooter is dead or the time runs out, the player is taken to a new background.
		-> A message "Game Over!!!" .Wait 2 seconds. Game window closes.
		-> The total score till the moment the player pressed 'q' appears.
	
NOTE:
	In the entire program, I have used "Game ends" and "Game over" in many comments, functions and variables.
	Game Ends: The player presses 'q' or the player succesfully completes all the levels. (STEP 9 or STEP 11)
	Game Over: The shooter is dead or the time runs out. (STEP 12)
				
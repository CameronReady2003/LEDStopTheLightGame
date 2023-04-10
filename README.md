# LEDStopTheLightGame(WIP)
# Description:
A program for a game using Arduino. Similiar to Stop the Light Games in an arcade/casino.
The game involves pressing a button to stop  blinking LED lights on a particular LED, accumulating points based on the LED's pin. The game has two difficulty levels, and the speed of the LEDs changes accordingly.

The program sets up the digital pins for the LEDs, button, and switch input with pull-up resistors. It also sets variables for the LED pins and their sequence, time limit, score, and delay time.

In the loop() function, the program first checks the elapsed time since the game started and resets the LEDs and score if the time limit is reached.

Next, it checks if the button is pressed. If it is, the program enters a loop that lights up the LED sequence at a speed determined by the difficulty level and waits for the button to be pressed again. When the button is pressed, the program calculates the score based on the last LED lit and displays it. If the score is a multiple of 20, it doubles the score and flashes all LEDs, and if the score is a multiple of 100, it flashes a pattern on the LEDs and restarts the game, decreasing your score to 0 and retarting . If the score reaches 1000, it displays a message and enters an infinite loop to signify the end of the game.

If the button is not pressed, the program continues to loop through the LED sequence.

# Components & Devices:
Arduino Uno R3, Breadboard, Slideswitch, Press Button, 6 LED's, Use of Serial Monitor .

# Instructions in code

# Improvememnts:
Use of loops and conditional statments will be adjusted to lower line count and redundant conditions, use of functions will implimented. I will add an 16x2 LCD screen to output all the messages/string that the serial monitor is outputting, will also include future special characters on it to indicate to player how close they are to winning or losing. 


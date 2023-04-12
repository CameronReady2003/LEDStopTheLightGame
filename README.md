
# StopTheLightGame(UpdatedVersion)
# Description:
A program for a game using Arduino. Similiar to Stop the Light Games in an arcade/casino.
The game involves pressing a button to stop  blinking LED lights on a particular LED, accumulating points based on the LED's pin. The game has two difficulty levels, and the speed of the LEDs changes accordingly.

The program sets up the digital pins for the NeoPixel Ring, button, and switch input with pull-up resistors. It also sets variables for the NeoPixel pixel's and their sequence, time limit, score, and delay time.

In the loop() function, the program first checks the elapsed time since the game started and resets the pixels and score if the time limit is reached.

The program simultaniously turns on and off each pixel in clockwise order with random colours each cycle.  Depending on the state of the SlideSwitch, the monitor will print out which level the user is on, Easy difficulty or Medium difficulty. The former is slower than the latter. Can be switched any point during the initial pixel sequence.

Next, it checks if the button is pressed.  When the button is pressed, the program calculates the score based on the last pixel lit and displays it. If the score is a multiple of 20, it doubles the score and flashes all pixels, with the last lit pixel being green while the rest are red, and if the score is a multiple of 100, it flashes a half red half green pattern on the pixels and restarts the game, decreasing your score to 0 and retarting . If the score reaches 1000, it displays a message and enters an infinite loop to signify the end of the game.

If the button is not pressed, the program continues to loop through the LED sequence.

# Components & Devices:
Arduino Uno R3, Breadboard, Slideswitch, Press Button, NeoPixel 12 LED, Use of Serial Monitor .

# Instructions in code

# Improvememnts:
Looking to increase size with an added lcd 16x2 screen to output all future messages.


![arduinoproject](https://user-images.githubusercontent.com/130194724/231319061-81fc557b-8423-4dfc-878c-953ba26e3e37.png)

**Check previous commits to see progression of project**

#include <Adafruit_NeoPixel.h>
/*/
INSTRUCTIONS:
Score per PIXEL
12 total
starting pixel = 0
+1 score clockwise up to 11
When the button is clicked the pixel that was lit will stay on
while the rest turn off. 
You will be provided and displayed a score based on that pixel(See above), 
the loop will continue after the button is pressed again,
i.e the main loop.
Every consecutive pixel chosen will add to your score. 
GAME OVER when any multiple of 100 up to 900 is the total score.
GAME WON when total score reaches 1000 or higher, 
the game pauses permenantly.
EVERY Multiple of 20 multiplies the total score by 2, 
(Helpful, considering the timer).
WHEN the time played hits 5 minutes the game restarts 
and the timer and score starts at zero again.
Click the switch to change the difficulty
(The speed of the pixel changing).
Good luck/*/
int redP = 0;
int greenP = 0;
int blueP = 0;
int pixelPin = 5;
int pixelCount = 12;
int swIN = 6;
int button = 3;
int lastLED = 0;
bool switchKeyHigh = false;
bool switchKeyLow = false;
bool scoreKey = false;
int delayChange = 0;
int score = 895;
unsigned long timeLimit = 100000;  // 5 minute in milliseconds
unsigned long startTime = 0;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(pixelCount, pixelPin, NEO_GRB + NEO_KHZ800);
void colourChange() {
  redP = random(0, 255);
  greenP = random(0, 255);
  blueP = random(0, 255);
}
void setup() {
  //all digital pins, button and led circle
  pinMode(pixelPin, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  pinMode(swIN, INPUT_PULLUP);
  startTime = millis();
  Serial.begin(9600);
  strip.begin();
}
void loop() {
  colourChange();
  int swValue = digitalRead(swIN);
  int pbValue = digitalRead(button);
  unsigned long currentTime = millis();
  unsigned long elapsedTime = currentTime - startTime;
  if (elapsedTime >= timeLimit) {
    Serial.println("The time limit was reached.");
    Serial.println("Restarting...");
    for (int i = 0; i < pixelCount; i++) {
      strip.setPixelColor(i, strip.Color(0, 0, 0));
    }
    strip.show();
    delay(5000);
    score = 0;
    startTime = millis();
  }
  if (pbValue == LOW) {
    for (int i = 0; i < pixelCount; i++) {
      if (swValue == LOW) {
        if (switchKeyHigh == false) {
          Serial.print("LEVEL ONE EASY DIFFICULTY\n");
          switchKeyHigh = true;
          switchKeyLow = false;
        }
        delayChange = 100;
      } else {
        if (switchKeyLow == false) {
          Serial.print("LEVEL TWO MEDIUM DIFFICULTY\n");
          switchKeyLow = true;
          switchKeyHigh = false;
        }
        delayChange = 35;
      }
      strip.setPixelColor(i, strip.Color(redP, greenP, blueP));
      strip.show();
      delay(delayChange);
      strip.setPixelColor(i, strip.Color(0, 0, 0));
      delay(delayChange);
      lastLED = i;
      pbValue = digitalRead(button);
      if (pbValue == HIGH) {
        break;
      }
    }
    delay(100);
  } else {
    scoreKey = false;
    delay(2000);
    pbValue = digitalRead(button);
    while (pbValue == LOW) {
      for (int i = 0; i < pixelCount; i++) {
        if (i != lastLED) {
          strip.setPixelColor(i, strip.Color(150, 0, 0));
        } else {
          strip.setPixelColor(lastLED, strip.Color(0, 150, 0));
        }
      }
      strip.show();
      delay(1000);
      if (lastLED >= 0 && scoreKey == false) {
        score = lastLED + score;
        Serial.print("Score = ");
        Serial.println(lastLED);
        scoreKey = true;
        Serial.print("Total score: ");
        Serial.println(score);
        delay(3000);
        if (score % 20 == 0 && score % 100 != 0) {
          for (int i = 0; i < pixelCount; i++) {
            strip.setPixelColor(i, strip.Color(0, 150, 0));
            strip.show();
          }
          delay(1000);
          for (int i = 0; i < pixelCount; i++) {
            strip.setPixelColor(i, strip.Color(0, 0, 0));
            strip.show();
          }
          score = score * 2;
          Serial.print("LUCKY SCORE REACHED, WINNER\n");
          Serial.print("Score multiplied by Two\n");
          Serial.print("Total score: ");
          Serial.println(score);
        }
        if (score % 100 == 0 && score % 1000 != 0) {
          for (int i = 0; i < 6; i++) {
            strip.setPixelColor(i, strip.Color(0, 0, 0));
            strip.show();
            delay(300);
            strip.setPixelColor(i, strip.Color(0, 150, 0));
            strip.show();
            delay(300);
          }
          Serial.print("Limit Reached, GAME OVER\n");
          Serial.print("Resetting\n");
          delay(2000);
          score = 0;
          break;
        }
        if (score >= 1000) {
          for (int i = 0; i < pixelCount; i++) {
            strip.setPixelColor(i, strip.Color(0, 0, 0));
            strip.show();
            delay(50);
            Serial.print("GAME WON, CONGRATS\n");
            delay(50);
            while (1) {}
          }
        }
      }
      pbValue = digitalRead(button);
      if (pbValue == HIGH) {
        Serial.print("Button Clicked");
        delay(1000);
        Serial.print(" Restarting\n");
        delay(3000);
        for (int i = 0; i < pixelCount; i++) {
          strip.setPixelColor(i, strip.Color(0, 0, 0));
        }
        strip.show();
        break;
      }
    }
  }
}

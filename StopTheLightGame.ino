#include <Adafruit_NeoPixel.h>
#include <LiquidCrystal.h>
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
int score = 0;
unsigned long timeLimit = 100000;
unsigned long startTime = 0;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(pixelCount, pixelPin, NEO_GRB + NEO_KHZ800);
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

void colourChange() {
  redP = random(0, 255);
  greenP = random(0, 255);
  blueP = random(0, 255);
}

void setup() {
  pinMode(pixelPin, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  pinMode(swIN, INPUT_PULLUP);
  startTime = millis();
  strip.begin();
  lcd.begin(16, 2);
}

void loop() {
  lcd.clear();
  lcd.print("Press Button Now");

  colourChange();
  int swValue = digitalRead(swIN);
  int pbValue = digitalRead(button);
  unsigned long currentTime = millis();
  unsigned long elapsedTime = currentTime - startTime;
  if (elapsedTime >= timeLimit) {
    lcd.setCursor(0, 1);
    lcd.print("Time limit reached");
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
          lcd.clear();
          lcd.print("LEVEL ONE");
          lcd.setCursor(0, 1);
          lcd.print("EASY DIFFICULTY");

          delay(2000);
          switchKeyHigh = true;
          switchKeyLow = false;
        }
        delayChange = 100;

      } else {
        if (switchKeyLow == false) {
          lcd.clear();
          lcd.print("LEVEL TWO");
          lcd.setCursor(0, 1);
          lcd.print("HARD DIFFICULTY");
          delay(2000);
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
  }

  else {
    lcd.clear();
    lcd.print("Button Pressed");
    lcd.setCursor(0, 1);
    lcd.print("Great Job");
    scoreKey = false;
    delay(5000);
    lcd.clear();
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

        lcd.print("Score=");
        lcd.setCursor(6, 0);
        lcd.print(lastLED);
        scoreKey = true;
        lcd.setCursor(0, 1);
        lcd.print("Total Score=");
        lcd.setCursor(12, 1);
        lcd.print(score);
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
          lcd.clear();
          lcd.print("LUCKY SCORE");
          lcd.setCursor(0, 1);
          lcd.print("SCORE X2");
          delay(2000);
          lcd.clear();
          lcd.print("Total Score=");
          lcd.setCursor(12, 0);
          lcd.print(score);
          delay(2000);
        }

        if (score % 100 == 0 && score % 1000 != 0) {
          for (int i = 0; i < pixelCount; i++) {
            strip.setPixelColor(i, strip.Color(150, 0, 0));
            strip.show();
            delay(300);
          }
          lcd.clear();
          lcd.print("GAME OVER");
          lcd.setCursor(0, 1);
          lcd.print("Resetting");
          delay(2000);
          score = 0;
          break;
        }

        if (score >= 1000) {
          for (int i = 0; i < pixelCount; i++) {
            strip.setPixelColor(i, strip.Color(0, 0, 0));
            strip.show();
          }
          delay(50);
          lcd.clear();
          lcd.print("GAME WON!!!");
          delay(50);
          while (1) {}
        }
      }
      lcd.clear();
      lcd.print("Press Button");
      lcd.setCursor(0, 1);
      lcd.print("to try again");

      pbValue = digitalRead(button);
      if (pbValue == HIGH) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Button Clicked");
        delay(1000);
        lcd.setCursor(0, 1);
        lcd.print("Restarting");
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
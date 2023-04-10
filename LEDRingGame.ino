/*/
INSTRUCTIONS:
6 Total LED's, each LED is worth points (Left to right):
LED1 13
LED2 12
LED3 11
LED4 10
LED5 9
LED6 8
When the button is clicked the LED that was lit will stay on
while the rest turn off. 
You will be provided and displayed a score based on that LED(See above), 
the loop will continue after the button is pressed again,
i.e the main loop.
Every consecutive LED chosen will add to your score. 
GAME OVER when any multiple of 100 up to 900 is the total score.
GAME WON when total score reaches 1000 or higher, 
the game pauses permenantly.
EVERY Multiple of 20 multiplies the total score by 2, 
(Helpful, considering the timer).
WHEN the time played hits 5 minutes the game restarts 
and the timer and score starts at zero again.
Click the switch to change the difficulty
(The speed of the LED's changing).
Good luck/*/

int firstLED = 13;
int secondLED = 12;
int thirdLED = 11;
int fourthLED = 10;
int fifthLED = 9;
int sixthLED = 8;
int swIN = 6;
int button = 3;
int lastLED = 0;
bool switchKeyHigh = false;
bool switchKeyLow = false;
bool scoreKey = false;
int delayChange = 0;
int score = 0;
int pins[6] = { firstLED, secondLED, thirdLED, fourthLED, fifthLED, sixthLED };
unsigned long timeLimit = 100000;  // 5 minute in milliseconds
unsigned long startTime = 0;
void setup() {
  //all digital pins, button and led circle
  pinMode(firstLED, OUTPUT);
  pinMode(secondLED, OUTPUT);
  pinMode(thirdLED, OUTPUT);
  pinMode(fourthLED, OUTPUT);
  pinMode(fifthLED, OUTPUT);
  pinMode(sixthLED, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  pinMode(swIN, INPUT_PULLUP);
  startTime = millis();
  Serial.begin(9600);
}
void loop() {
  unsigned long currentTime = millis();
  unsigned long elapsedTime = currentTime - startTime;
  int swValue = digitalRead(swIN);
  int pbValue = digitalRead(button);
  if (elapsedTime >= timeLimit) {
    Serial.print("The time limit was reached\n");
    delay(500);
    Serial.print("Restarting\n");
    score = 0;
    digitalWrite(firstLED, LOW);
    digitalWrite(secondLED, LOW);
    digitalWrite(thirdLED, LOW);
    digitalWrite(fourthLED, LOW);
    digitalWrite(fifthLED, LOW);
    digitalWrite(sixthLED, LOW);
    delay(5000);
    startTime = millis();
  }
  if (pbValue == LOW) {
    for (int i = 0; i <= 5; i++) {
      if (swValue == LOW) {
        if (switchKeyHigh == false) {
          Serial.print("LEVEL ONE EASY DIFFICULTY\n");
          switchKeyHigh = true;
          switchKeyLow = false;
        }
        delayChange = 200;
      } else {
        if (switchKeyLow == false) {
          Serial.print("LEVEL TWO MEDIUM DIFFICULTY\n");
          switchKeyLow = true;
          switchKeyHigh = false;
        }
        delayChange = 50;
      }
      digitalWrite(pins[i], HIGH);
      delay(delayChange);
      digitalWrite(pins[i], LOW);
      delay(delayChange);
      lastLED = pins[i];
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
      digitalWrite(pins[6], LOW);
      digitalWrite(lastLED, HIGH);
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
          for (int i = 0; i < 6; i++) {
            digitalWrite(pins[i], HIGH);
          }
          delay(1000);
          for (int i = 0; i < 6; i++) {
            digitalWrite(pins[i], LOW);
          }
          score = score * 2;
          Serial.print("LUCKY SCORE REACHED, WINNER\n");
          Serial.print("Score multiplied by Two\n");
          Serial.println(score);
        }
        if (score % 100 == 0 && score % 1000 != 0) {
          for (int i = 0; i < 6; i++) {
            digitalWrite(pins[i], LOW);
            delay(300);
            digitalWrite(i, HIGH);
            delay(300);
          }
          Serial.print("Limit Reached, GAME OVER\n");
          Serial.print("Resetting\n");
          delay(2000);
          score = 0;
          break;
        }
        if (score >= 1000) {
          for (int i = 0; i < 6; i++) {
            digitalWrite(pins[i], LOW);
            digitalWrite(lastLED, LOW);
            delay(300);
            Serial.print("GAME WON, CONGRATS\n");
            delay(2000);
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
        digitalWrite(lastLED, LOW);
        break;
      }
    }
  }
}

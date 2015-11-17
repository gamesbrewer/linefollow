#include <ArduinoRobot.h>
#include <Wire.h>
#include <SPI.h>

#define echoPin TKD3
#define trigPin TKD4

#define BotReady 0
#define BotLine 1
#define BotMaze 2
int state = 0; //0=ready, 1=line, 2=maze

void setup() {
  // initialize the robot
  Robot.begin();

  // initialize the sound library
  Robot.beginSpeaker();

  //initialize ultrasonics
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  //check kep pressed
  switch (state) {
     case BotReady:
        keyboardControl();
        break;
     case BotLine:
        //todo
        break;
     case BotMaze:
        detectWall(3);
        break;
     default:
        //todo
        break;
  }
}

void keyboardControl() {
  //Use buttons to control the gallery
  while (true) {
    int keyPressed = Robot.keyboardRead(); // read the button values
    switch (keyPressed) {
      case BUTTON_UP:  // play song
        playLineFollowSong();
        return;
      case BUTTON_DOWN:  // line follow
        lineFollow();
        return;
      case BUTTON_LEFT:  // maze
        //
        return;
      case BUTTON_RIGHT:  // test
        state = BotMaze;
        return;
      case BUTTON_MIDDLE:  // clear
        state = BotReady;
        return;
    }
  }
}

/* We want to detect based on distance (d) in cm */
void detectWall(int targetDistance) {
  long duration, distance;

  Robot.digitalWrite(TKD3, HIGH);

  Robot.digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  Robot.digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // Added this line
  Robot.digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;

  logDistanceToSerial(distance);
  delay(200);
}

void lineFollow() {
  //Robot.lineFollowConfig(14, 9, 50, 10);
  Robot.lineFollowConfig(11, 7, 60, 5);


  //set the motor board into line-follow mode
  Robot.setMode(MODE_LINE_FOLLOW);
}

void playLineFollowSong() {
  // array containing the melody
  char aTinyMelody[] = "6mm-m-nm-o---s---n--s--t--u-w-vu-smor-qo-m-npw--n--s--t--u-w,-vu-smor-qo-m-npw------------------";

  // play the melody
  Robot.playMelody(aTinyMelody);
}

/* What to do when wall is detected? */
void obstacleDetected() {
  Serial.println("Detected");
}

void noWall() {
  Serial.println("No wall");
}

void logDistanceToSerial(int distance) {
  Serial.print(distance);
  Serial.println(" cm");
}

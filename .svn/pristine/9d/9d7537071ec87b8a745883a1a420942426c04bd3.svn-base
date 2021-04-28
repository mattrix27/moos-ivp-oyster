

/*

	Mokai - MOOS Interface
	Emily Dunne and Alon Yaari
	MIT LAMSS
	April, 2014

*/

#define JOY_THRUST_MIN      0
#define JOY_THRUST_MAX   1023
#define JOY_RUDDER_MIN      0
#define JOY_RUDDER_MAX   1023
#define JOY_CORNER_THRESH 100
#define JOY_BOTTOM_THRESH 100
#define JOY_CORNER_TIME    15
#define JOY_CENTER_TIME   100
#define HEARTBEAT_FROM_BACKSEAT 1000
#define HEARTEAT_TO_BACKSEAT 750
#define SERVO_THRUST_MIN    0
#define SERVO_THRUST_MAX  180
#define SERVO_RUDDER_MIN    0
#define SERVO_RUDDER_MAX  180
#define SERVO_RUDDER_HALF  90


#include <Servo.h>

float   rudderLookup[32] = { 0.00, -1.00, -0.86, -0.66, -0.51, -0.40, -0.32, -0.26, -0.21, -0.17, -0.14, -0.11, -0.09, -0.07, -0.04, -0.02,
                            0.00,  0.02,  0.04,  0.07,  0.09,  0.11,  0.14,  0.17,  0.21,  0.26,  0.32,  0.40,  0.51,  0.66,  0.86,  1.00 };

Servo   servoThrust;
Servo   servoRudder;

// Heartbeat
unsigned long   lastHeartbeatTime = 0;
char            lastHeartbeat     = '\0';

// States
char    stateControl = '?';
char    stateEngine  = '?';
char    lastStateCtl = '?';
char    lastStateEng = '?';

// Control Values
float   cmdPctRudder =  0.0;
float   cmdPctThrust =  0.0;
int     bit5Thrust   =  0;
int     bit5Rudder   =  0;
bool    cmdEngine    = false;


// Joystick Details
int     joyPinRudder = A1;
int     joyPinThrust = A0;
int     joyValRudder = 0;
int     joyValThrust = 0;
int     joyLeft      = JOY_RUDDER_MIN + JOY_CORNER_THRESH;
int     joyRight     = JOY_RUDDER_MAX - JOY_CORNER_THRESH;
int     joyBottom    = JOY_THRUST_MAX - JOY_BOTTOM_THRESH;
char    joyCorner    = '?';     // Corner joystick is definitely in
char    joyDebounce  = '?';     // Might be in this corner, waiting for debounce
int     joyDebounceT = 0;       // Waiting for debounce, been in this corner for this long
char    joyLastCorner= '?';     // Last corner stick was definitely in

/*

   0     512    1024
    ______ ______     0       'A' stick above threshold line, corner irrelevant
   |      |      |            'L' stick below threshold line, now in L or in between corners
   |    A | A    |            'R' stick below threshold line, now in R or in between corners
   |      |      |            'C' stick below threshold line, not in corner for some time
   |______|______|X 512
   |    A | A    |        joyBottom
   |__ ___|___ __| __________/
   |L | C | C |R |
   |__|___|___|__| 1024
     /    Y    \ 
joyLeft       joyRight

*/

void ReadJoystickAxes()
{
 // Read the joystick values
 joyValRudder = analogRead(joyPinRudder);
 joyValThrust = analogRead(joyPinThrust);

 // Above the bottom threshold means no corner
 if (joyValThrust < joyBottom) {
   joyLastCorner = '?';
   joyCorner = 'A';
   return; }

 // Joystick is below threshold, check if left, right, or center
 char curCorner = 'C';
 if (joyValRudder < joyLeft) {
   curCorner = 'L'; }
 else if (joyValRudder > joyRight) {
   curCorner = 'R'; }

 // If we're already in this corner, nothing changes
 if (curCorner == joyCorner) {
   return; }

 // Are we debouncing?
 if (curCorner == joyDebounce) {
   joyDebounceT++;
   int timeCompare = JOY_CORNER_TIME;
   if (curCorner == 'C') {
       timeCompare = JOY_CENTER_TIME; }
   if (joyDebounceT > timeCompare) {

     // Debounce time elapsed, solidly in the corner or centered
     joyDebounceT  = 0;
     joyLastCorner = joyCorner;
     joyCorner     = joyDebounce;
     joyDebounce   = '?';
     return; } }

 // Reaching here means we need to start debouncing a new corner
 else {
   joyDebounceT = 0;
   joyDebounce  = curCorner; }
}

void ReadSerialIn()
{
 while (Serial.available() > 0) {
   int serialByte = Serial.read();

   // Thrust byte
   if (B10000000 & serialByte) {
     bit5Thrust = B00011111 & serialByte; }

   // Rudder byte (includes desired engine statys)
   else {
     bit5Rudder = B00011111 & serialByte;
     cmdEngine  = B00100000 & serialByte; } }
}

/*
 Control States

 'M' Manual Control
     Transition to '1' when joystick is bottom-left

 '1' Manual control - Joystick in bottom-left
     Transition to '2' if joystick changes to BR
     Transition to 'M' if joystick centers or goes above y-axis threshold

 '2' Manual control - Joystick was BL but is now bottom-right
     Transition to '3' if joystick changes to BL
     Transition to 'M' if joystick centers or goes above y-axis threshold

 '3' Manual control - Joystick was BL, BR, and is now bottom-left
     Transition to '4' if joystick changes to BR
     Transition to 'M' if joystick centers or goes above y-axis threshold

 '4' Manual control - Joystick was BL, BR, BL, and is now bottom-right
     Transition to 'A' if joystick changes to center
     Transition to 'M' if joystick changes to BL or goes above y-axis threshold

 'A' Autonomous control - Joystick was BL, BR, BL, BR, and is now centered
     Transition to 'M' if joystick changes to BL, BR, or goes above y-axis threshold
     Transition to 'M' if watchdog doesn't receive heartbeat from autonomy within time threshold
*/
void ManageControlState()
{
 // If no change in joystick then state doesn't have reason to change
 if (joyCorner == joyLastCorner) {
   return; }

 // Any movement above y-axis threshold means manual
 if (joyCorner == 'A') {
   stateControl = 'M';
   return; }

 if (stateControl == 'M') {
   if (joyCorner == 'L') {
     stateControl = '1'; } }

 else if (stateControl == '1') {
   if (joyCorner == 'R') {
     stateControl = '2'; }
   else if (joyCorner == 'C') {
     stateControl = 'M'; } }

 else if (stateControl == '2') {
   if (joyCorner == 'L') {
     stateControl = '3'; }
   else if (joyCorner == 'C') {
     stateControl = 'M'; } }

 else if (stateControl == '3') {
   if (joyCorner == 'R') {
     stateControl = '4'; }
   else if (joyCorner == 'C') {
     stateControl = 'M'; } }

 else if (stateControl == '4') {
   if (joyCorner == 'C') {
     stateControl = 'A';
     lastHeartbeat = millis(); }
   else if (joyCorner == 'L') {
     stateControl = 'M'; } }

 else if (stateControl == 'A') {
   unsigned long timeDiff = millis() - lastHeartbeat;
   if (joyCorner != 'C' || timeDiff > HEARTBEAT_FROM_BACKSEAT) {
     stateControl = 'M'; } }
}

/*
 Engine States
     - ONLY IN AUTONOMOUS MODE

     0  Engine off
     1  Engine on
     S  Engine being started
*/

void ManageEngineState()
{
 stateEngine = '1';
}

void ManualControlValues()
{
 // Joystick values have already been read into joyValRudder and joyValThrust
 // TODO: Add dead zones

 cmdPctThrust = joyValThrust / JOY_THRUST_MAX;

 int tmpRudder = joyValRudder - 512;
 if (tmpRudder == 0) {
   cmdPctRudder = 0; }
 else {
   cmdPctRudder = joyValRudder / JOY_RUDDER_MAX; }
}

void AutonomousControlValues()
{
 // ALLSTOP, FULLSTOP, and invalid values all result in no thrust
 if (bit5Thrust  < 2 || bit5Thrust > 20) {
   cmdPctThrust = 0.0; }
 else {
   cmdPctThrust = (float) ((bit5Thrust - 1) * 5); }

 cmdPctRudder = rudderLookup[bit5Rudder];
}

void DetermineControlValues()
{
 if (stateControl == 'A') {
    AutonomousControlValues(); }
 else {
   ManualControlValues(); }
}

void CommandTheServos()
{
 float fltThrust = cmdPctThrust * SERVO_THRUST_MAX;
 int commandThrust = (int) fltThrust;
 servoThrust.write(commandThrust);

 float fltRudder = cmdPctRudder * SERVO_RUDDER_HALF;
 int commandRudder = SERVO_RUDDER_HALF + (int) fltRudder;
 servoRudder.write(commandRudder);
}

void SendHeartbeat()
{
 bool autonomous = false;
 if (stateControl == 'A')
   autonomous = true;

 bool engine = false;
 if (stateEngine == '1')
   engine = true;

 char hb = '?';
 if (autonomous) {
   if (engine) {
     hb = 'B'; }
   else {
     hb = 'b'; } }
 else {
   if (engine) {
     hb = 'F'; }
   else {
     hb = 'f'; } }

 bool publish = false;
 if (hb != lastHeartbeat) {
   publish = true; }
 if (millis() - lastHeartbeatTime > HEARTEAT_TO_BACKSEAT) {
   publish = true; }

 if (publish) {
   Serial.write(hb);
   Serial.write(13);
   Serial.write(10);
   lastHeartbeat = hb;
   lastHeartbeatTime = millis(); }
}


void setup() {
 servoThrust.attach(5);
 servoRudder.attach(6);
 Serial.begin(57600);
}

void loop() {

 ReadJoystickAxes();
 ReadSerialIn();
 ManageControlState();
 ManageEngineState();
 DetermineControlValues();
 CommandTheServos();
 SendHeartbeat();
}

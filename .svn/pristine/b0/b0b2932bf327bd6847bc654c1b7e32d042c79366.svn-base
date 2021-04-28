
/*

	Mokai - MOOS Interface
	Emily Dunne and Alon Yaari
	MIT LAMSS
       MAY, 2014

*/

#define JOY_THRUST_MIN             0
#define JOY_THRUST_MAX          1023
#define JOY_RUDDER_MIN             0
#define JOY_RUDDER_MAX          1023
#define JOY_RUDDER_HALF        512.0
#define JOY_CORNER_THRESH        100
#define JOY_BOTTOM_THRESH        100
#define JOY_CORNER_TIME           15
#define JOY_CENTER_TIME          100
#define HEARTBEAT_FROM_BACKSEAT 5000
#define HEARTBEAT_TO_BACKSEAT    750
#define SERVO_THRUST_MIN          30
#define SERVO_THRUST_MAX         150
#define SERVO_THRUST_EXTENT    120.0
#define SERVO_RUDDER_MIDDLE     90.0
#define SERVO_RUDDER_EXTENT     45.0


#include <Servo.h>

float   rudderPctLookup[32] = {   0.0, -1.00, -0.80, -0.60, -0.50, -0.40, -0.30, -0.20, -0.14, -0.11, -0.08, -0.06, -0.04, -0.03, -0.02, -0.01,
                                  0.0,  0.01,  0.02,  0.03,  0.04,  0.06,  0.08,  0.11,  0.14,  0.20,  0.30,  0.40,  0.50,  0.60,  0.80,  1.00 };
Servo   servoThrust;
Servo   servoRudder;

// Heartbeat
unsigned long   lastHeartbeatTime = 0;
char            lastHeartbeat     = '\0';
unsigned long   lastIncomingHB    = 0;

// States
char    stateControl = 'A';
char    stateEngine  = '?';
char    lastStateCtl = 'A';
char    lastStateEng = '?';

// Control Values
float   cmdPctRudder =  0.0;
float   cmdPctThrust =  0.0;
int     bit5Thrust   =  0;
int     bit5Rudder   =  0;
bool    cmdEngine    = false;

// Smoothing
int     lastPctRudder = 0.0;
int     lastPctThrust = 0.0;

// Joystick Details
int     joyPinRudder = A0;
int     joyPinThrust = A1;
int     joyValRudder = 0;
int     joyValThrust = 0;
int     joyLeft      = JOY_RUDDER_MIN + JOY_CORNER_THRESH;
int     joyRight     = JOY_RUDDER_MAX - JOY_CORNER_THRESH;
int     joyBottom    = JOY_THRUST_MAX - JOY_BOTTOM_THRESH;
char    joyCorner    = '?';     // Corner joystick is definitely in
char    joyDebounce  = '?';     // Might be in this corner, waiting for debounce
int     joyDebounceT = 0;       // Waiting for debounce, been in this corner for this long
char    joyLastCorner = '?';    // Last corner stick was definitely in

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
    // Any char from computer resets the incoming heartbeat
    lastIncomingHB = millis();

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
    stateControl = 'A';
    return; }

  if (stateControl == 'A') {
    if (joyCorner == 'L') {
      stateControl = '1'; } }

  else if (stateControl == '1') {
    if (joyCorner == 'R') {
      stateControl = '2'; } }

  else if (stateControl == '2') {
    if (joyCorner == 'L') {
      stateControl = '3'; } }

  else if (stateControl == '3') {
    if (joyCorner == 'R') {
      stateControl = '4'; } }

  else if (stateControl == '4') {
    if (joyCorner == 'C') {
      stateControl = 'A';
      lastIncomingHB = millis(); }
    else if (joyCorner == 'L') {
      stateControl = 'A'; } }

  else if (stateControl == 'A') {
    unsigned long timeDiff = millis() - lastIncomingHB;
    if (joyCorner != 'C' || timeDiff > HEARTBEAT_FROM_BACKSEAT) {
      stateControl = 'A'; } }
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

/*
Control Values
    
    cmdPctThrust
      - Percent thrust for the throttle
        FULL STOP  =   0%  =   0 degrees
        FULL SPEED = 100%  = 135 degrees
        
    cmdPctRudder
      - Percent rudder angle
        FULL LEFT  = -100% =  45 degrees
        CENTERED   =    0% =  90 degrees
        FULL RIGHT =  100% = 135 degrees
*/

// DetermineControlValues()
//    - Determine whether to use manual or autonomous inputs for control
void DetermineControlValues()
{
  if (stateControl == 'A') {
    AutonomousControlValues(); }
  else {
    ManualControlValues(); }
}

// ManualControlValues()
//    - Set cmdPctThrust and cmdPctRudder based on joystick position
void ManualControlValues()
{
  // Joystick values have already been read into joyValRudder and joyValThrust
  // TODO: Add dead zones
  char test       = 't';
  cmdPctThrust    = (float) joyValThrust / (float) JOY_THRUST_MAX;
  cmdPctThrust    = 1.0 - cmdPctThrust;
  
  float tmpRudder = (float) joyValRudder - JOY_RUDDER_HALF;
  cmdPctRudder    = tmpRudder / JOY_RUDDER_HALF; 
  if (cmdPctRudder < -0.95)
    cmdPctRudder  = -1.0;
  if (cmdPctRudder > 0.95)
    cmdPctRudder  = 1.0;
}

// AutonomousControlValues()
//    - Set cmdPctThrust and cmdPctRudder based on input from PC that arrived via serial
void AutonomousControlValues()
{
  // ALLSTOP, FULLSTOP, and invalid values all result in no thrust
  if (bit5Thrust  < 2) {
    cmdPctThrust = 0.0; }
  else {
    cmdPctThrust = (float) ((bit5Thrust - 1) * 5) / 100.0; }
    
  cmdPctRudder = rudderPctLookup[bit5Rudder];
}

// CommandTheServos()
//    - Command the servos based on current value of cmdPctRudder and cmdPctThrust
void CommandTheServos()
{
  // cmdPctThrust contains the percent throttle, 0% to 100%
  //    Convert to proper angle for servo
  //        thrMagnitude is the amount of the extent the throttle servo can travel
  float thrMagnitude = cmdPctThrust * SERVO_THRUST_EXTENT;
  //        fltThrust is the actual throttle servo angle, the magnitude added to the min throttle angle
  float fltThrust   = thrMagnitude + (float) SERVO_THRUST_MIN;
  //        commandThrust is the integer version of the angle being sent to the servo
  int commandThrust = (int) fltThrust;
  
  // cmdPctRudder contains the percent rudder angle, -100% to 100%
  //    Convert to proper angle for servo
  //    SERVO_RUDDER_EXTENT is the extent of the servo's travel from center to one side
  //    rudMagntitude is the amount of the extent to one side of centered
  //        Negative means that distance to the left, positive to the right
  float rudMagnitude = cmdPctRudder * SERVO_RUDDER_EXTENT;
  //        fltRudder is the actual rudder angle, the magnitude added to (or subtracted from) the center
  float fltRudder = (float) SERVO_RUDDER_MIDDLE + rudMagnitude;
  //        commandRudder is the integer version of the angle to be sent to the servo
  int commandRudder = (int) fltRudder;
  // Now commandRudder holds what we instantaneously want thrust to be


  // Code that smooths out the transition between commanded angles
  //    - Currently not used
  //    - To use it, uncomment this section
//  if (stateControl == 'X') {
//    if (commandThrust > lastPctThrust)
//      commandThrust = lastPctThrust + 1;
//    if (commandThrust < lastPctThrust)
//      commandThrust = lastPctThrust - 1;
//    if (commandRudder > lastPctRudder)
//    commandRudder = lastPctRudder + 1;
//  if (commandRudder < lastPctRudder)
//    commandRudder = lastPctRudder - 1; }
    
  // Send commands to the servos
  servoThrust.write(commandThrust);
  lastPctThrust = commandThrust;
  
  servoRudder.write(commandRudder);
  lastPctRudder = commandRudder;
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
      hb = 'B';}
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
  unsigned long timeDiff = millis() - lastHeartbeatTime;
  if (timeDiff > HEARTBEAT_TO_BACKSEAT) {
    publish = true; }
  if (publish) {
    Serial.write(hb);
    Serial.write(13);
    //Serial.write(10);
    lastHeartbeat = hb;
    lastHeartbeatTime = millis(); }
}


void setup()
{
  servoThrust.attach(6);
  servoRudder.attach(5);
  Serial.begin(115200);
}

void loop()
{
  ReadJoystickAxes();
  ReadSerialIn();
  ManageControlState();
  stateControl == 'A';
  ManageEngineState();
  stateControl == 'A';
  DetermineControlValues();
  stateControl == 'A';
  CommandTheServos();
  SendHeartbeat();
  Serial.println(stateControl);
  delay(1);
}



#include <iterator>
#include "math.h"
#include "ActMokai.h"
#include "MBUtils.h"

using namespace std;


ActMokai::ActMokai()
{
    bDebug               = DEBUG_MODE;
    bVerbose             = !bDebug;
    serial_port          = "";
    baudRate             = 115200;
    streaming            = true;
    desiredRudder        = 0.0;
    desiredThrust        = 0.0;
    maxThrust            = 100.0;                   // Desired thrust that maps to 100% of possible thrust
    fullRudder           = 45.0;                    // Rudder in degrees that maps to rudder 100% turned
    lastToMokaiTime      = 1.0;
    lastLocalDesiredTime = 1.0;
    lastFrontseatTime    = 1.0;
    localThrust          = 0.0;
    localRudder          = 0.0;
    heartbeatToMokai     = HEARTBEAT_TIME;          // Publish hearbeat this many seconds apart
    watchdogLocalHelm    = LOCALSILENCE_TIME;       // If we don't receive desired_* values in this timeout,
                                                    // then go to allstop
    watchdogFromMokai    = FRONTSEATSILENCE_TIME;   // If we don't receive heartbeat from frontseat in this timeout,
                                                    // then go to allstop
    frontSeatStatus      = '?';
    lastFromFront        = '?';
    lastByteRudder       = (uint8_t) '\0';
    lastByteThrust       = (uint8_t) '\0';
    needPublishOwnHeartbeat = true;
    toMokaiRudder        = (uint8_t) 0;
    toMokaiThrust        = (uint8_t) 0;
    toMokaiEngine        = false;

    /*      Steering:

        bits    int  commands this   degrees  10bit joystick equivalent
        00000     0  ALLSTOP              0   none
        00001     1  100% LEFT           45      0
        00010     2   80% LEFT           48     34
        00011     3   60% LEFT           51     68
        00100     4   50% LEFT           54    102
        00101     5   40% LEFT           57    137
        00110     6   30% LEFT           60    171
        00111     7   20% LEFT           63    205
        01000     8   14% LEFT           66    239
        01001     9   11% LEFT           69    273
        01010    10    8% LEFT           72    307
        01011    11    6% LEFT           75    341
        01100    12    4% LEFT           78    375
        01101    13    3% LEFT           81    410
        01110    14    2% LEFT           83    444
        01111    15    1% LEFT           87    478
        10000    16   CENTERED           90    512
        10001    17   1% RIGHT           93    546
        10010    18   2% RIGHT           96    580
        10011    19   3% RIGHT           99    614
        10100    20   4% RIGHT          102    649
        10101    21   6% RIGHT          105    683
        10110    22   8% RIGHT          108    717
        10111    23  11% RIGHT          111    751
        11000    24  14% RIGHT          114    785
        11001    25  20% RIGHT          117    819
        11010    26  30% RIGHT          120    853
        11011    27  40% RIGHT          123    887
        11100    28  50% RIGHT          126    922
        11101    29  60% RIGHT          129    956
        11110    30  80% RIGHT          132    990
        11111    31 100% RIGHT          135   1024 */

    pctIndex[0]  = 0.01;
    pctIndex[1]  = 0.02;
    pctIndex[2]  = 0.03;
    pctIndex[3]  = 0.04;
    pctIndex[4]  = 0.06;
    pctIndex[5]  = 0.08;
    pctIndex[6]  = 0.11;
    pctIndex[7]  = 0.14;
    pctIndex[8]  = 0.20;
    pctIndex[9]  = 0.30;
    pctIndex[10] = 0.40;
    pctIndex[11] = 0.50;
    pctIndex[12] = 0.60;
    pctIndex[13] = 0.80;
    pctIndex[14] = 1.00;     // All the way to full rudder
    pctIndex[15] = 1.00;

    cmdLeft[15]  = (uint8_t)  1;   // 100% left rudder
    cmdLeft[14]  = (uint8_t)  1;
    cmdLeft[13]  = (uint8_t)  2;
    cmdLeft[12]  = (uint8_t)  3;
    cmdLeft[11]  = (uint8_t)  4;
    cmdLeft[10]  = (uint8_t)  5;
    cmdLeft[9]   = (uint8_t)  6;
    cmdLeft[8]   = (uint8_t)  7;
    cmdLeft[7]   = (uint8_t)  8;
    cmdLeft[6]   = (uint8_t)  9;
    cmdLeft[5]   = (uint8_t) 10;
    cmdLeft[4]   = (uint8_t) 11;
    cmdLeft[3]   = (uint8_t) 12;
    cmdLeft[2]   = (uint8_t) 13;
    cmdLeft[1]   = (uint8_t) 14;
    cmdLeft[0]   = (uint8_t) 15;
    cmdCenter    = (uint8_t) 16;
    cmdRight[0]  = (uint8_t) 17;
    cmdRight[1]  = (uint8_t) 18;
    cmdRight[2]  = (uint8_t) 19;
    cmdRight[3]  = (uint8_t) 20;
    cmdRight[4]  = (uint8_t) 21;
    cmdRight[5]  = (uint8_t) 22;
    cmdRight[6]  = (uint8_t) 23;
    cmdRight[7]  = (uint8_t) 24;
    cmdRight[8]  = (uint8_t) 25;
    cmdRight[9]  = (uint8_t) 26;
    cmdRight[10] = (uint8_t) 27;
    cmdRight[11] = (uint8_t) 28;
    cmdRight[12] = (uint8_t) 29;
    cmdRight[13] = (uint8_t) 30;
    cmdRight[14] = (uint8_t) 31;
    cmdRight[15] = (uint8_t) 31;  // 100% right rudder
}


bool ActMokai::OnNewMail(MOOSMSG_LIST &NewMail)
{
    MOOSMSG_LIST::reverse_iterator p;
    for (p = NewMail.rbegin(); p != NewMail.rend(); p++) {
        CMOOSMsg &msg = *p;
        string key   = msg.GetKey();
        string sVal  = msg.GetString();
        double dVal  = msg.GetDouble();
        if (MOOSStrCmp(key, "MOOS_MANUAL_OVERIDE") || MOOSStrCmp(key, "MOOS_MANUAL_OVERRIDE")) {
            if (!sVal.empty())
                char c = sVal.at(0); }
        if (MOOSStrCmp(key, "DESIRED_THRUST")) {
            lastLocalDesiredTime = MOOSTime();
            desiredThrust = dVal;
            SetDesiredThrust(); }
        if (MOOSStrCmp(key, "DESIRED_RUDDER")) {
            lastLocalDesiredTime = MOOSTime();
            desiredRudder = dVal;
            SetDesiredRudder(); } }
    return true;
}

void ActMokai::SetDesiredThrust()
{
    // Something is seriously wrong if desired thrust is negative
    if (desiredThrust < 0.0) {
        if (bVerbose)
            MOOSTrace("%s: Min thrust is 0. Desired thrust of %d was requested. Setting thrust to 0.\n",
                    GetAppName().c_str(), desiredThrust);
        desiredThrust = 0.0; }
    ConvertThrustToMokai5bit();
}

void ActMokai::SetDesiredRudder()
{
    // Check that rudder isn't completely invalid
    if (desiredRudder > fullRudder) {
        if (bVerbose)
            MOOSTrace("%s: Max rudder angle is +/- 180.0. Desired rudder of %d was requested. Capping rudder value.\n",
                    GetAppName().c_str(), desiredRudder);
        desiredRudder = fullRudder; }
    if (desiredRudder < -1.0 * fullRudder) {
        if (bVerbose)
            MOOSTrace("%s: Max rudder angle is +/- 180.0. Desired rudder of %d was requested. Capping rudder value.\n",
                    GetAppName().c_str(), desiredRudder);
        desiredRudder = -1.0 * fullRudder; }
    ConvertRudderToMokai5bit();
}

bool ActMokai::OnConnectToServer()
{
    RegisterVariables();
    return true;
}

void ActMokai::RegisterVariables()
{
    m_Comms.Register("DESIRED_THRUST", 0);
    m_Comms.Register("DESIRED_RUDDER", 0);
    m_Comms.Register("MOOS_MANUAL_OVERIDE", 0);
    m_Comms.Register("MOOS_MANUAL_OVERRIDE", 0);
}


bool ActMokai::Iterate()
{
    double now   = MOOSTime();
    double delta = 0.0;

    // Haven't received DESIRED_THRUST or DESIRED_RUDDER in a while?
    //      - Stop the motors!
    delta        = now - lastLocalDesiredTime;
    if (!(delta < watchdogLocalHelm)) {
        desiredRudder = 0.0;
        desiredThrust = 0.0; }

    // Haven't heard from the vehicle in a while?
    //      - Stop the motors, just in case
    delta        = now - lastFrontseatTime;
    if (!(delta > watchdogFromMokai)) {
            desiredRudder = 0.0;
            desiredThrust = 0.0; }

    // Have we sent anything to the mokai in a while?
    //      - Send a heartbeat so it knows we're ok
    delta        = now - lastToMokaiTime;
    needPublishOwnHeartbeat = (delta > heartbeatToMokai);

    PublishToMokai();
    ReceiveFromMokai();
    return true;
}

void ActMokai::ReceiveFromMokai()
{
    // Check incoming bytes from Arduino
    char c;
    while (m_serial.serialport_read_one_char(c)) {
        lastFrontseatTime = MOOSTime();
        if (bDebug)
            MOOSTrace("%c", c);
            if (bVerbose) {
                if (c != lastFromFront) {
                    lastFromFront = c;
                    MOOSTrace("%s: From mokai (int) %d 0x%x '%c'\n", GetAppName().c_str(),(int) c, (int) c, c); } }
        ParseDataFromArduino(c); }
}


bool ActMokai::OnStartUp()
{
    STRING_LIST sParams;
    m_MissionReader.GetConfiguration(GetAppName(), sParams);

    STRING_LIST::iterator p;
    for (p = sParams.begin(); p != sParams.end(); p++) {
        string sLine     = *p;
        string sVarName  = MOOSChomp(sLine, "=");
        sLine = stripBlankEnds(sLine);

        if (!bDebug) {
            if (MOOSStrCmp(sVarName, "VERBOSE")) {
                if (!sLine.empty()) {
                    char c = sLine.c_str()[0];
                    bVerbose = !(c == 'F' || c == 'f'); } } }

        if (MOOSStrCmp(sVarName, "PORT")) {
            if (!sLine.empty())
                serial_port = sLine; }

        if (MOOSStrCmp(sVarName, "BAUDRATE")) {
            if (!sLine.empty())
                baudRate = atoi(sLine.c_str()); }

        if (MOOSStrCmp(sVarName, "MAX_THRUST")) {
            if (!sLine.empty())
                maxThrust = strtod(sLine.c_str(), NULL); }
        if (maxThrust > 100.0)
            maxThrust = 100.0;
        if (maxThrust <= 0.0) {
            MOOSTrace("%s: ERROR- MAX_THRUST must be greater than 0.0. Quitting.",
                    GetAppName().c_str());
            return false; }

        if (MOOSStrCmp(sVarName, "FULL_RUDDER")) {
            if (!sLine.empty())
                fullRudder = strtod(sLine.c_str(), NULL); }
        if (fullRudder > 180.0 || fullRudder <= 0.0) {
            MOOSTrace("%s: ERROR- FULL_RUDDER must be greater than 0.0 and less than or equal to 180.0. Quitting.",
                    GetAppName().c_str());
            return false; }

        if (MOOSStrCmp(sVarName, "HBEAT_TO_MOKAI")) {
            if (!sLine.empty())
                heartbeatToMokai = strtod(sLine.c_str(), NULL); }

        if (MOOSStrCmp(sVarName, "WDOG_LOCAL_HELM")) {
            if (!sLine.empty())
                watchdogLocalHelm = strtod(sLine.c_str(), NULL); }

        if (MOOSStrCmp(sVarName, "WDOG_FROM_MOKAI")) {
            if (!sLine.empty())
                watchdogFromMokai = strtod(sLine.c_str(), NULL); } }

    MOOSTrace("%s: Verbose mode is %s.\n",
            GetAppName().c_str(), (bVerbose ? "ON" : "OFF"));
    MOOSTrace("%s: Serial port set to %s.\n",
            GetAppName().c_str(), serial_port.c_str());
    MOOSTrace("%s: Serial baud rate set to %d.\n",
            GetAppName().c_str(), baudRate);
    MOOSTrace("%s: Thrust will be normalized to a maximum of %f.\n",
            GetAppName().c_str(), maxThrust);
    MOOSTrace("%s: Full rudder on the vehicle is %f degrees.\n",
            GetAppName().c_str(), fullRudder);
    MOOSTrace("%s: Commands or heartbeat to Mokai will publish faster than %f seconds.\n",
            GetAppName().c_str(), heartbeatToMokai);
    MOOSTrace("%s: Watchdog expects local DESIRED_* publications within each %f seconds.\n",
            GetAppName().c_str(), watchdogLocalHelm);
    MOOSTrace("%s: Watchdog expects Mokai to publish status within each %f seconds.\n",
            GetAppName().c_str(), watchdogFromMokai);

    m_serial.serialport_init(serial_port.c_str(), baudRate);
    RegisterVariables();

    //m_Comms.Notify("DIRECT_THRUST_CONTROL", "TRUE");
    return true;
}

void ActMokai::ConvertThrustToMokai5bit()
{
/*      bits    intVal commands this   10bit joystick equivalent
        00000      0   ALLSTOP         none
        00001      1   FULL STOP          0
        00010      2    5                51
        00011      3   10               102
        00100      4   15               154
        00101      5   20               205
        00110      6   25               256
        00111      7   30               307
        01000      8   35               358
        01001      9   40               410
        01010     10   45               461
        01011     11   50               512
        01100     12   55               563
        01101     13   60               614
        01110     14   65               666
        01111     15   70               717
        10000     16   75               768
        10001     17   80               819
        10010     18   85               870
        10011     19   90               922
        10100     20   95               973
        10101     21   FULL THRUST     1024  */

    // Thrust arrives as a double between 0.0 and 100.0, inclusive
    // Need to round it to the nearest 5
    double toRound = desiredThrust + 2.5;
    int interimThrust = (int) toRound;
    localThrust = interimThrust - (interimThrust % 5);
    if (localThrust < 0)
        localThrust = 0;
    if (localThrust > 100)
        localThrust = 100;
    toMokaiThrust = (1 + (localThrust / 5));
    if (toMokaiThrust > (uint8_t) 21) {
            MOOSTrace("%s: Internal error- 5-bit thrust value is greater than max value!\n", GetAppName().c_str());
            toMokaiThrust = (uint8_t) 0; }
}

void ActMokai::ConvertRudderToMokai5bit()
{
    // Rudder arrives as -angle to +angle
    // Fullrudder = greatest angle the rudder can acheive = 100%
    // Normalize rudder between 0 and fullrudder then account for sign
    bool isLeft = (desiredRudder < 0.0);
    double absRudder = (isLeft ? -1.0 * desiredRudder : desiredRudder);
    if (absRudder > fullRudder)
        absRudder = fullRudder;

    double absRudderPct = absRudder / fullRudder;

    // Cycle through look-ups to find correct rudder number
    if (absRudderPct < pctIndex[0])
        toMokaiRudder = cmdCenter;
    else {
        for (int i = RUDDER_SLICES - 1; i >= 0; i--) {
            if (absRudderPct >= pctIndex[i]) {
                localRudder = (100 * pctIndex[i]) * (isLeft ? -1 : 1);
                toMokaiRudder = (isLeft ? cmdLeft[i] : cmdRight[i]);
                break; } } }

    if (toMokaiRudder > (uint8_t) 31) {
        MOOSTrace("%s: Internal error- 5-bit rudder value is greater than max value!\n", GetAppName().c_str());
        toMokaiRudder = (uint8_t) 0; }
}

void ActMokai::PublishToMokai()
{
    // Byte 1
    //  - Bit 8 always 0
    //  - Bit 7 irrelevant (reserved for future use)
    //  - Bit 6 engine status (0 engine off, 1 engine on)
    //  - Bits 5 to 1 steering position
    uint8_t byteRudder = (uint8_t) 0;
    byteRudder = toMokaiRudder;
    // TODO: Add engine status back into byte1
    //byte1 += (toMokaiEngine ? (uint8_t) 32 : (uint8_t) 0);

    // Byte 2
    //  - Bit 8 always 1
    //  - Bits 7 and 6 irrelevant (reserved for future use)
    //  - Bits 5 to 1 thrust percent
    uint8_t byteThrust = (uint8_t) 0;
    byteThrust = 128 | toMokaiThrust;

    if (bVerbose)
        MOOSTrace("%s: To Mokai  Rudder %d%%  toMokaiRudder %d  command bytes 1: %d  2: %d\n",
            GetAppName().c_str(), localRudder, (int) toMokaiRudder, (int) byteRudder, (int) byteThrust);

    // No point in just sending the same thing to the front seat again and again
    bool publishByteRudder = true; //(needPublishOwnHeartbeat || (byteRudder == lastByteRudder));
    bool publishByteThrust = true; //(needPublishOwnHeartbeat || (byteThrust == lastByteThrust));
    bool ok = true;
    if (publishByteRudder) {
        heartbeatToMokai = MOOSTime();
        lastToMokaiTime = MOOSTime();
        lastByteRudder = byteRudder;
        ok &= m_serial.serialport_writebyte(byteRudder); }
    if (publishByteThrust) {
        heartbeatToMokai = MOOSTime();
        lastToMokaiTime = MOOSTime();
        lastByteThrust = byteThrust;
        ok &= m_serial.serialport_writebyte(byteThrust); }
    if (!ok)
        MOOSTrace("%s: ERROR sending commands to the Mokai.\n", GetAppName().c_str());
}


void ActMokai::ParseDataFromArduino(char c)
{
    // Don't reprocess if front seat status hasn't changed
    if (c == frontSeatStatus)
        return;
    frontSeatStatus = c;

    // Something changed - process it!
    string msg = "";
    switch (c) {
        case MOKAI_ENGINE_ON_FRONT_CONTROL:
            msg = "Frontseat in control, engine is running."; break;
        case MOKAI_ENGINE_OFF_FRONT_CONTROL:
            msg = "Frontseat in control, engine is stopped."; break;
        case MOKAI_ENGINE_ON_BACK_CONTROL:
            msg = "Backseat in control, engine is running."; break;
        case MOKAI_ENGINE_OFF_BACK_CONTROL:
            msg = "Backseat in control, engine is stopped."; break;
        case 'M':
            msg = "MANUAL joystick control"; break;
        case '1':
        case '2':
        case '3':
        case '4':
            msg = "Transition from manual to autonomous, state %c."; break;
        case 'A':
            msg = "Mokai under MOOS control."; break;
        case '?':
        default:
            msg = "Mokai state is unknown."; break; }
    if (bVerbose)
        MOOSTrace("%s: %s\n", GetAppName().c_str(), msg.c_str());
}










//



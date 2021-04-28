

#ifndef I_ActMokai_HEADER
#define I_ActMokai_HEADER

#include "MOOS/libMOOS/MOOSLib.h"

#ifdef USE_KAESS_SERIAL
#include "KaessSerial.h"
#else
#include "arduinoSerial.h"
#endif

#define HEARTBEAT_TIME 1.0
#define LOCALSILENCE_TIME 1.0
#define FRONTSEATSILENCE_TIME 1.0
#define RUDDER_SLICES 15

#define MOKAI_ENGINE_ON_FRONT_CONTROL   'F'
#define MOKAI_ENGINE_OFF_FRONT_CONTROL  'f'
#define MOKAI_ENGINE_ON_BACK_CONTROL    'B'
#define MOKAI_ENGINE_OFF_BACK_CONTROL  'b'
#define MOKAI_STATE_UNKNOWN             '?'

#define DEBUG_MODE true

/*
    Mokai Frontseat Embedded Arduino Wire Protocol

    TO frontseat is encoded in two alternating bytes:

        Byte 1: 0rESSSSS
            0       Most significant bit ALWAYS 0
            r       reserved for future use
            E       0 - engine should be turned off
                    1 - engine should be turned on
            SSSSS   5 bits to encode steering position
        Byte 2: most significant bit ALWAYS 1 (1rrTTTTT)
            1       Most significant bit ALWAYS 1
            rr      reserved for future use
            TTTTT   5 bits to encode thrust percent

    FROM mokai is encode in one byte:
                Engine      Controlled by
           F     ON            front
           f     OFF           front
           B     ON            back
           b     OFF           back
           ?     State unknown

    Steering:

        bits    int  commands this   degrees  10bit joystick equivalent
        00000     0  ALLSTOP          0    0   none
        00001     1  100% LEFT      -45   45      0
        00010     2   80% LEFT      -36   48     34
        00011     3   60% LEFT      -27   51     68
        00100     4   50% LEFT      -23   54    102
        00101     5   40% LEFT      -18   57    137
        00110     6   30% LEFT      -14   60    171
        00111     7   20% LEFT       -9   63    205
        01000     8   14% LEFT       -6   66    239
        01001     9   11% LEFT       -5   69    273
        01010    10    8% LEFT       -4   72    307
        01011    11    6% LEFT       -3   75    341
        01100    12    4% LEFT     -1.8   78    375
        01101    13    3% LEFT     -1.4   81    410
        01110    14    2% LEFT     -0.9   83    444
        01111    15    1% LEFT     -0.5   87    478
        10000    16   CENTERED        0   90    512
        10001    17   1% RIGHT      0.5   93    546
        10010    18   2% RIGHT      0.9   96    580
        10011    19   3% RIGHT      1.4   99    614
        10100    20   4% RIGHT      1.8  102    649
        10101    21   6% RIGHT        3  105    683
        10110    22   8% RIGHT        4  108    717
        10111    23  11% RIGHT        5  111    751
        11000    24  14% RIGHT        6  114    785
        11001    25  20% RIGHT        9  117    819
        11010    26  30% RIGHT       14  120    853
        11011    27  40% RIGHT       18  123    887
        11100    28  50% RIGHT       23  126    922
        11101    29  60% RIGHT       27  129    956
        11110    30  80% RIGHT       36  132    990
        11111    31 100% RIGHT       45  135   1024

    Thrust:

        bits    int  commands this  degrees 10bit joystick equivalent
        00000     0    ALLSTOP            0    none
        00001     1  FULL STOP            0
        00010     2         5%            7      51
        00011     3        10%           14     102
        00100     4        15%           20     154
        00101     5        20%           27     205
        00110     6        25%           34     256
        00111     7        30%           41     307
        01000     8        35%           47     358
        01001     9        40%           54     410
        01010    10        45%           61     461
        01011    11        50%           68     512
        01100    12        55%           74     563
        01101    13        60%           81     614
        01110    14        65%           88     666
        01111    15        70%           95     717
        10000    16        75%          101     768
        10001    17        80%          108     819
        10010    18        85%          115     870
        10011    19        90%          122     922
        10100    20        95%          128     973
        10101    21 FULL SPEED          135    1024

 */

class ActMokai : public CMOOSInstrument
{
public:
    ActMokai();
    virtual ~ActMokai() {};

    bool OnNewMail(MOOSMSG_LIST &NewMail);
    bool Iterate();
    bool OnConnectToServer();
    bool OnStartUp();
    void RegisterVariables();
    void ParseDataFromArduino(char c);

protected:

    void        ConvertThrustToMokai5bit();
    void        ConvertRudderToMokai5bit();

    bool        bVerbose;
    bool        bDebug;

    // Safety

    double      lastToMokaiTime;         // Last time we sent a message or heartbeat to the Mokai
    double      heartbeatToMokai;        // HBEAT_TO_MOKAI
                                         //     Time in seconds between when we publish heartbeats to the frontseat

    double      lastLocalDesiredTime;    // Last time we received a DESIRED_* moos message
    double      watchdogLocalHelm;       // WDOG_LOCAL_HELM
                                         //     If we don't hear receive desired rudder or thrust in this
                                         //     time period, go to allstop

    double      lastFrontseatTime;       // Last time we received heartbeat from the Mokai
    double      watchdogFromMokai;       // WDOG_FROM_MOKAI
                                         //     If we don't receive heartbeat from frontseat in this
                                         //     timeperiod, go to allstop

    // Serial port setup
    std::string serial_port;             // OS reference to the serial port (e.g. /dev/ttyUSB0)
    int         baudRate;                // serial port baud rate
    bool        streaming;               // should port be in streaming mode?
    Serial      m_serial;                // object to reference the serial port

    // Data TO the Mokai frontseat
    bool        needPublishOwnHeartbeat; // true when enough time has elapsed
    uint8_t     lastByteRudder;          // Last rudder byte published to the mokai
    uint8_t     lastByteThrust;          // Last thrust byte published to the mokai
    uint8_t     toMokaiRudder;           // Stores rudder to push out via serial
    uint8_t     toMokaiThrust;           // Stores thrust to push out via serial
    bool        toMokaiEngine;           // One-bit decision for whether engine should be on or not
    double      desiredRudder;           // Latest received DESIRED_RUDDER value
    double      desiredThrust;           // Latest received DESIRED_THRUST value
    int         localRudder;             // rudder value after locally enhanced
    int         localThrust;             // thrust value after locally enhanced
    double      maxThrust;               // MAX_THRUST
                                         //     Des. thrust at or above this maps to 100%
    double      fullRudder;              // FULL_RUDDER
                                         //     Des. rudder angle +/- maps to 100%

    // Data FROM the Mokai frontseat
    char        frontSeatStatus;         // 'M' Manual mode, engine is running
                                         // 'm' Manual mode, engine is stopped
                                         // 'A' Autonomous mode, engine is running
                                         // 'a' Autonomous mode, engine is stopped
                                         // '?' Unknown status
    char        lastFromFront;

    // Data mappings for steering
    double      pctIndex[RUDDER_SLICES + 1];
    uint8_t     cmdLeft[RUDDER_SLICES + 1];
    uint8_t     cmdRight[RUDDER_SLICES + 1];
    uint8_t     cmdCenter;

    void PublishToMokai();
    void SetDesiredThrust();
    void SetDesiredRudder();
    void ReceiveFromMokai();
};

#endif

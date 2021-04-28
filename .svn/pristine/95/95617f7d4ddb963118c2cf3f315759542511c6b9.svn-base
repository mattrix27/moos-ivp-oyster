Code to run on an Arduino embedded on a Mokai.
Allows MOOS to operate as back seat with the Arduino as front seat.
MOOS runs on a PC (laptop, Raspi, etc.) and connects to the Arduino via its USB port.

Operation
  - Arduino publishes heartbeat to back seat at 1hz
  - PC publishes commands to front seat
  - Heartbeat ensures 'I'm alive' sent to front seat at least 1hz
  - PC sends one of two bytes:
        Byte 1: most significant bit ALWAYS 0
                0rESSSSS
            0       Most significant bit ALWAYS 0
            r       reserved for future use
            E       0 - engine should be turned off
                    1 - engine should be turned on
            SSSSS   5 bits to encode steering position
        Byte 2: most significant bit ALWAYS 1
                1rrTTTTT
            1       Most significant bit ALWAYS 1
            rr      reserved for future use
            TTTTT   5 bits to encode thrust percent
   - Ardunio sends one status byte:
        Engine      Controlled by
           F     ON            front
           f     OFF           front
           B     ON            back
           b     OFF           back
           ?     State unknown

Rev A
Initial version of README file. 



#define FALSE 0
#define TRUE 1
#define StartChar "<"
#define EndChar ">"
#define SeparatorChar ","
//#define LogSeparatorChar ":"
#define LogSeparatorChar ","
#define NullArgument "0"

#define StartCharAscii 60    // "<"
#define EndCharAscii 62        // ">"
#define SeparatorCharAscii 44  // ","
#define NullArgumentAscii 48   // "0"
//#define LogSeparatorCharAscii 58 // ":"
#define LogSeparatorCharAscii 44 // ","
#define Ascii0 48 //"0"
#define Ascii9 57 //"9"

//Command Definitions
    #define ReqAck 0                   //Request Acknowledgement
    #define SndAck 1                   //Send Acknowledgement
    #define Ack 2                      //Confirm Acknowledged
    #define Nack 3                     //Negative Acknowledged
    #define GetAnalogIps 4             //Request remote end to send Analog Input values
    #define GetDigitalIps 5            //Request remote end to send Digital Input values
    #define GetAnalogOps 6             //Request remote end to send Analog Output values
    #define GetDigitalOps 7            //Request remote end to send Digital Output values
    #define StartSendingLogRecords 8   //Request remote end to send Digital Output values
    #define StopSendingLogRecords 9    //Request remote end to send Digital Output values

    #define SetA0value 10      //Set value of Analog0
    #define SetA1value 11      //Set value of Analog1
    #define SetA2value 12      //Set value of Analog2
    #define SetA3value 13      //Set value of Analog3
    #define SetA4value 14      //Set value of Analog4
    #define SetA5value 15      //Set value of Analog5
    #define SetA6value 16      //Set value of Analog6
    #define SetA7value 17      //Set value of Analog7
    #define SetLcounter 18     //Set value of Left Distance Counter
    #define SetRcounter 19     //Set value of Right Distance Counter

    #define SetS2value 20      //Set value of Switch 2
    #define SetS4_1value 21    //Set value of Switch 4-1
    #define SetS4_2value 22    //Set value of Switch 4-2
    #define SetS4_3value 23    //Set value of Switch 4-3
    #define SetS4_4value 24    //Set value of Switch 4-4

    #define SetLPWMvalue 30    //Set value of Left Motor PWM
    #define SetRPWMvalue 31    //Set value of Right Motor PWM

    #define SetLDIRbit 40      //Set value of Left Motor direction bit
    #define SetRDIRbit 41      //Set value of Right Motor direction bit
    #define SetEmAbit 42       //Set value of Emitter A bit
    #define SetEmBbit 43       //Set value of Emitter B bit
    #define SetUserIObit 44    //Set value of User I/O bit
    #define SetLampbit 45      //Set the value of the on-board lamp bit

    #define SetLogvalues 50    //Set values for a log record
    #define StartLogging 51    //Request remote end starts sending log values
    #define StopLogging 52     //Request remote end stops sending log values
    
    #define RemoteStart 253    //Remote start the robot
    #define RemoteStop 254     //Remote stop the robot
    #define DebugMessage 255   //Send a message to be displayed

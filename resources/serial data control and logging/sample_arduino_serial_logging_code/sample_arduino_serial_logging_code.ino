#include <SoftwareSerial.h>
#include "message_definitions.h"
#include "board.h"
#include "buffer_variables.h"
bool robotRunning = FALSE;
bool loggingOn = FALSE;
bool logHeaderSent = FALSE;
char command [18];   //maximum length of command is 18 bytes including CR/LF
int command_index = 0;
int opening_delimiter_index = -1;
int separator_index = -1;
int delayPeriods = 0;   //Count to flash Lamp when robot is running
unsigned long loopCounter = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(38400);
  pinMode(USER_IO,OUTPUT);
  pinMode(MOTOR_LEFT_DIR,OUTPUT);
  pinMode(MOTOR_RIGHT_DIR,OUTPUT);
  pinMode(EMITTER_A,OUTPUT);
  pinMode(EMITTER_B,OUTPUT);
  pinMode(LAMP,OUTPUT);
  encoderSetup();
  delay(1);
  digitalWrite(MOTOR_LEFT_DIR,0); //Jiggle the motors before using the encoders
  digitalWrite(MOTOR_RIGHT_DIR,0);
  analogWrite(MOTOR_LEFT_PWM,50);
  analogWrite(MOTOR_LEFT_PWM,50);
  delay(10);
  analogWrite(MOTOR_LEFT_PWM,0);
  analogWrite(MOTOR_LEFT_PWM,0);
  delay(1);
  digitalWrite(MOTOR_LEFT_DIR,1);
  digitalWrite(MOTOR_RIGHT_DIR,1);
  analogWrite(MOTOR_LEFT_PWM,50);
  analogWrite(MOTOR_LEFT_PWM,50);
  delay(10);
  analogWrite(MOTOR_LEFT_PWM,0);
  analogWrite(MOTOR_LEFT_PWM,0);
  delay(1);
  digitalWrite(MOTOR_LEFT_DIR,0);
  digitalWrite(MOTOR_RIGHT_DIR,0);
}

void loop() {
  // put your main code here, to run repeatedly:
  int i = 0;
    loopCounter++;
    while ((Serial.available() > 0) && (command_index <18)){
      command [command_index] = Serial.read();
      if((command [command_index] == EndCharAscii)){   //we have a delimited command so execute it
        for(i = 0; i <= command_index; i++){
          if(command[i] == StartCharAscii) opening_delimiter_index = i;
          else {}
          if(command[i] == SeparatorCharAscii) separator_index = i;
          else {}
        }// for loop to scan for calibration/timer commands
        if ((opening_delimiter_index >= 0 ) && (separator_index >= 0)){ // found Open, Separator and Close Delimiters
          if ((separator_index < command_index) && (opening_delimiter_index < separator_index)){  //Check separators in the right sequence
            executeCommand();
          }//If delimiters in correct sequence
          else {}
        }//If all 3 delimiters found
        else{}
        command_index = -1; // reset to start of buffer for next command
        separator_index = -1;
        opening_delimiter_index = -1;
      }// end delimiter detected
      else {
        if (command_index >= 17) command_index = -1;  // reset to start of buffer if buffer is full and no end delimiter detected
        else {}
      }
      command_index++;
    }// Loop reading input

  if(loggingOn == TRUE)logDatavalues();
  else{}
  
  delay(10);

  delayPeriods++;
  if(delayPeriods > 100){
    delayPeriods = 0;
    if(robotRunning == TRUE){
      D13lampvalue = !D13lampvalue;
      digitalWrite(LAMP,D13lampvalue);
    }//if robot running flash the lamp
    else{}
  }// if delay period reached
  else {}//delay period not reached so do nothing
}//loop


void executeCommand (){
  int integerCommand = -1;
  int integerArgument = -1;
  integerCommand = getIntegerEquivalent(opening_delimiter_index,separator_index);
  integerArgument = getIntegerEquivalent(separator_index,command_index);
//    Serial.print(StartChar);Serial.print(DebugMessage);Serial.print(SeparatorChar);Serial.print("Command decoded as ");Serial.print(integerCommand);Serial.println(EndChar);
//    Serial.print(StartChar);Serial.print(DebugMessage);Serial.print(SeparatorChar);Serial.print("Argument decoded as ");Serial.print(integerArgument);Serial.println(EndChar);
  switch(integerCommand){
    case ReqAck:
      sendAck();
    Serial.print(StartChar);Serial.print(DebugMessage);Serial.print(SeparatorChar);Serial.print("Example Debug Message - ReqAck command received: ");Serial.print(integerCommand);Serial.println(EndChar);
      break;
    case GetAnalogIps:
      sendAnalogInputs();
      break;
    case GetDigitalIps:
      sendDigitalInputs();
      break;
    case GetAnalogOps:
      sendAnanlogOps();
      break;
    case SetLPWMvalue:
      analogWrite(MOTOR_LEFT_PWM,integerArgument);
      LeftPWMvalue = integerArgument;
      break;
    case SetRPWMvalue:
      analogWrite(MOTOR_RIGHT_PWM,integerArgument);
      RightPWMvalue = integerArgument;
      break;
    case GetDigitalOps:
      sendDigitalOutputs();
      break;
    case SetUserIObit:
      D6opvalue = integerArgument;
      digitalWrite(USER_IO,integerArgument);
      break;
    case SetLDIRbit:
      LeftDirvalue = integerArgument;
      digitalWrite(MOTOR_LEFT_DIR,integerArgument);
      break;
    case SetRDIRbit:
      RightDirvalue = integerArgument;
      digitalWrite(MOTOR_RIGHT_DIR,integerArgument);
      break;
    case SetEmAbit:
      EmitterAvalue = integerArgument;
      digitalWrite(EMITTER_A,integerArgument);
      break;
    case SetEmBbit:
      EmitterBvalue = integerArgument;
      digitalWrite(EMITTER_B,integerArgument);
      break;
    case SetLampbit:
      D13lampvalue = integerArgument;
      digitalWrite(LAMP,integerArgument);
      break;
    case SetLcounter:
      Leftcountvalue = integerArgument;
      break;
    case SetRcounter:
      Rightcountvalue = integerArgument;
      break;
    case RemoteStart:
      robotRunning = TRUE;
      break;
    case RemoteStop:
      robotRunning = FALSE;
      digitalWrite(LAMP,0);
      break;
    case StartLogging:
      loggingOn = TRUE;
      break;
    case StopLogging:
      loggingOn = FALSE;
      logHeaderSent = FALSE;
      break;
      
    default:
      sendNack();
      break;
  }//switch(integerCommand)
  
}//executeCommand()

int getIntegerEquivalent(int start_index,int end_index){
  byte ii;
  int result = 0;
  byte digit = 0;
  byte numberOfDigits = 0;
  for(ii=start_index + 1; ii<end_index; ii++){
    if((command[ii] >= Ascii0) && (command[ii] <= Ascii9)){
      digit = command[ii] - Ascii0;
      numberOfDigits++;
      if(numberOfDigits > 1)result = result *10;
      else {}
      result += digit;
    }// if ascii digit
    else{
      result = -1;
    }// not an ascii digit so return error
  }//for all ascii charcters between delimiters
  return(result);
 }//getIntegerEquivalent(int start_index,int end_index){

void sendAck(){
  Serial.print(StartChar);Serial.print(SndAck);Serial.print(SeparatorChar);Serial.print(Ack);Serial.println(EndChar);
}//void sendAck()

void sendNack(){
  Serial.print(StartChar);Serial.print(SndAck);Serial.print(SeparatorChar);Serial.print(Nack);Serial.println(EndChar);
}//void sendNack()

void decodeSelectorSwitch(){
  int analogValue = 0;
  int selectedValue = -1;
  analogValue = analogRead(FUNCTION_SELECT);
  if(analogValue > 844) S2value = 1;
  else{
    S2value = 0;
    if (analogValue > 657) selectedValue = 0;
    else
      if(analogValue > 641) selectedValue = 1;
      else
        if(analogValue > 625) selectedValue = 2;
        else
          if(analogValue > 604) selectedValue = 3;
          else
            if(analogValue > 582) selectedValue = 4;
            else
              if(analogValue > 559) selectedValue = 5;
              else
                if(analogValue > 536) selectedValue = 6;
                else
                  if(analogValue > 496) selectedValue = 7;
                  else
                    if(analogValue > 451) selectedValue = 8;
                    else
                      if(analogValue > 413) selectedValue = 9;
                      else
                        if(analogValue > 370) selectedValue = 10;
                        else
                          if(analogValue > 311) selectedValue = 11;
                          else
                            if(analogValue > 245) selectedValue = 12;
                            else
                              if(analogValue > 173) selectedValue = 13;
                              else
                                if(analogValue > 88) selectedValue = 14;
                                else
                                  selectedValue = 15;
  }//nested ifs to translate to a hex digit
  if(selectedValue >= 0){
//    Serial.print(StartChar);Serial.print(DebugMessage);Serial.print(SeparatorChar);Serial.print("DIP switch 4 decoded as ");Serial.print(selectedValue);Serial.println(EndChar);
    S4_4value = bitRead(selectedValue,0);
    S4_3value = bitRead(selectedValue,1);
    S4_2value = bitRead(selectedValue,2);
    S4_1value = bitRead(selectedValue,3);
    }//if S2 button not pressed so S4 can be decoded
    else {}
}//decodeSelectorSwitch()

void sendAnalogInputs(){
  A0value = analogRead(A0);
  A1value = analogRead(A1);
  A2value = analogRead(A2);
  A3value = analogRead(A3);
  A4value = analogRead(A4);
  A5value = analogRead(A5);
  A6value = analogRead(A6);
  A7value = analogRead(A7);
  
  Serial.print(StartChar);Serial.print(SetA0value);Serial.print(SeparatorChar);Serial.print(A0value);Serial.println(EndChar);
  Serial.print(StartChar);Serial.print(SetA1value);Serial.print(SeparatorChar);Serial.print(A1value);Serial.println(EndChar);
  Serial.print(StartChar);Serial.print(SetA2value);Serial.print(SeparatorChar);Serial.print(A2value);Serial.println(EndChar);
  Serial.print(StartChar);Serial.print(SetA3value);Serial.print(SeparatorChar);Serial.print(A3value);Serial.println(EndChar);
  Serial.print(StartChar);Serial.print(SetA4value);Serial.print(SeparatorChar);Serial.print(A4value);Serial.println(EndChar);
  Serial.print(StartChar);Serial.print(SetA5value);Serial.print(SeparatorChar);Serial.print(A5value);Serial.println(EndChar);
  Serial.print(StartChar);Serial.print(SetA6value);Serial.print(SeparatorChar);Serial.print(A6value);Serial.println(EndChar);
  Serial.print(StartChar);Serial.print(SetA7value);Serial.print(SeparatorChar);Serial.print(A7value);Serial.println(EndChar);
}//void sendAnalogueInputs()

void sendDigitalInputs(){
  decodeSelectorSwitch();
  Serial.print(StartChar);Serial.print(SetS2value);Serial.print(SeparatorChar);Serial.print(S2value);Serial.println(EndChar);
  Serial.print(StartChar);Serial.print(SetS4_1value);Serial.print(SeparatorChar);Serial.print(S4_1value);Serial.println(EndChar);
  Serial.print(StartChar);Serial.print(SetS4_2value);Serial.print(SeparatorChar);Serial.print(S4_2value);Serial.println(EndChar);
  Serial.print(StartChar);Serial.print(SetS4_3value);Serial.print(SeparatorChar);Serial.print(S4_3value);Serial.println(EndChar);
  Serial.print(StartChar);Serial.print(SetS4_4value);Serial.print(SeparatorChar);Serial.print(S4_4value);Serial.println(EndChar);
}//void sendDigitalInputs()

void sendAnanlogOps(){
  Serial.print(StartChar);Serial.print(SetLPWMvalue);Serial.print(SeparatorChar);Serial.print(LeftPWMvalue);Serial.println(EndChar);
  Serial.print(StartChar);Serial.print(SetRPWMvalue);Serial.print(SeparatorChar);Serial.print(RightPWMvalue);Serial.println(EndChar);
  Serial.print(StartChar);Serial.print(SetLcounter);Serial.print(SeparatorChar);Serial.print(Leftcountvalue);Serial.println(EndChar);
  Serial.print(StartChar);Serial.print(SetRcounter);Serial.print(SeparatorChar);Serial.print(Rightcountvalue);Serial.println(EndChar);
}//sendAnanlogOps()

void sendDigitalOutputs(){
  Serial.print(StartChar);Serial.print(SetLDIRbit);Serial.print(SeparatorChar);Serial.print(LeftDirvalue);Serial.println(EndChar);
  Serial.print(StartChar);Serial.print(SetRDIRbit);Serial.print(SeparatorChar);Serial.print(RightDirvalue);Serial.println(EndChar);
  Serial.print(StartChar);Serial.print(SetEmAbit);Serial.print(SeparatorChar);Serial.print(EmitterAvalue);Serial.println(EndChar);
  Serial.print(StartChar);Serial.print(SetEmBbit);Serial.print(SeparatorChar);Serial.print(EmitterBvalue);Serial.println(EndChar);
  Serial.print(StartChar);Serial.print(SetUserIObit);Serial.print(SeparatorChar);Serial.print(D6opvalue);Serial.println(EndChar);
  Serial.print(StartChar);Serial.print(SetLampbit);Serial.print(SeparatorChar);Serial.print(D13lampvalue);Serial.println(EndChar);
}//void sendDigitalOutputs()

void logDatavalues(){
  if(logHeaderSent == TRUE){
    A0value = analogRead(A0);
    A1value = analogRead(A1);
    A2value = analogRead(A2);
    A3value = analogRead(A3);
    A4value = analogRead(A4);
    A5value = analogRead(A5);
    A6value = analogRead(A6);
    A7value = analogRead(A7);
    decodeSelectorSwitch();
    Serial.print(StartChar);Serial.print(SetLogvalues);Serial.print(SeparatorChar);
    Serial.print(loopCounter);Serial.print(LogSeparatorChar);
    Serial.print(A0value);Serial.print(LogSeparatorChar);
    Serial.print(A1value);Serial.print(LogSeparatorChar);
    Serial.print(A2value);Serial.print(LogSeparatorChar);
    Serial.print(A3value);Serial.print(LogSeparatorChar);
    Serial.print(A4value);Serial.print(LogSeparatorChar);
    Serial.print(A5value);Serial.print(LogSeparatorChar);
    Serial.print(A6value);Serial.print(LogSeparatorChar);
    Serial.print(A7value);Serial.print(LogSeparatorChar);
    Serial.print(LeftPWMvalue);Serial.print(LogSeparatorChar);
    Serial.print(RightPWMvalue);Serial.print(LogSeparatorChar);
    Serial.print(Leftcountvalue);Serial.print(LogSeparatorChar);
    Serial.print(Rightcountvalue);Serial.print(LogSeparatorChar);
    Serial.print(S2value);Serial.print(LogSeparatorChar);
    Serial.print(S4_1value);Serial.print(LogSeparatorChar);
    Serial.print(S4_2value);Serial.print(LogSeparatorChar);
    Serial.print(S4_3value);Serial.print(LogSeparatorChar);
    Serial.print(S4_4value);Serial.print(LogSeparatorChar);
    Serial.print(D6value);Serial.print(LogSeparatorChar);
    Serial.print(D6opvalue);Serial.print(LogSeparatorChar);
    Serial.print(LeftDirvalue);Serial.print(LogSeparatorChar);
    Serial.print(RightDirvalue);Serial.print(LogSeparatorChar);
    Serial.print(EmitterAvalue);Serial.print(LogSeparatorChar);
    Serial.print(EmitterBvalue);Serial.print(LogSeparatorChar);
    Serial.print(D13lampvalue);Serial.print(LogSeparatorChar);
    Serial.println(EndChar);
  }
  else{
    logHeaderSent = TRUE;
    Serial.print(StartChar);Serial.print(SetLogvalues);Serial.print(SeparatorChar);
    Serial.print("loopCounter");Serial.print(LogSeparatorChar);
    Serial.print("A0value");Serial.print(LogSeparatorChar);
    Serial.print("A1value");Serial.print(LogSeparatorChar);
    Serial.print("A2value");Serial.print(LogSeparatorChar);
    Serial.print("A3value");Serial.print(LogSeparatorChar);
    Serial.print("A4value");Serial.print(LogSeparatorChar);
    Serial.print("A5value");Serial.print(LogSeparatorChar);
    Serial.print("A6value");Serial.print(LogSeparatorChar);
    Serial.print("A7value");Serial.print(LogSeparatorChar);
    Serial.print("LeftPWMvalue");Serial.print(LogSeparatorChar);
    Serial.print("RightPWMvalue");Serial.print(LogSeparatorChar);
    Serial.print("Leftcountvalue");Serial.print(LogSeparatorChar);
    Serial.print("Rightcountvalue");Serial.print(LogSeparatorChar);
    Serial.print("S2value");Serial.print(LogSeparatorChar);
    Serial.print("S4_1value");Serial.print(LogSeparatorChar);
    Serial.print("S4_2value");Serial.print(LogSeparatorChar);
    Serial.print("S4_3value");Serial.print(LogSeparatorChar);
    Serial.print("S4_4value");Serial.print(LogSeparatorChar);
    Serial.print("D6value");Serial.print(LogSeparatorChar);
    Serial.print("D6opvalue");Serial.print(LogSeparatorChar);
    Serial.print("LeftDirvalue");Serial.print(LogSeparatorChar);
    Serial.print("RightDirvalue");Serial.print(LogSeparatorChar);
    Serial.print("EmitterAvalue");Serial.print(LogSeparatorChar);
    Serial.print("EmitterBvalue");Serial.print(LogSeparatorChar);
    Serial.print("D13lampvalue");Serial.print(LogSeparatorChar);
    Serial.println(EndChar);
    
  }
}//logDatavalues()

void encoderReset() {
  noInterrupts();
  Leftcountvalue = 0;
  Rightcountvalue = 0;
  interrupts();
}//encoderReset()

void encoderSetup() {
  // left
  pinMode(ENCODER_LEFT_CLK, INPUT);
  pinMode(ENCODER_LEFT_B, INPUT);
  bitClear(EICRA, ISC01);
  bitSet(EICRA, ISC00);
  bitSet(EIMSK, INT0);
  // right
  pinMode(ENCODER_RIGHT_CLK, INPUT);
  pinMode(ENCODER_RIGHT_B, INPUT);
  bitClear(EICRA, ISC11);
  bitSet(EICRA, ISC10);
  bitSet(EIMSK, INT1);
  encoderReset();
}//encoderSetup()


// INT0 will respond to the XOR-ed pulse train from the leftencoder
// runs in constant time of around 3us per interrupt.
// would be faster with direct port access
ISR(INT0_vect) {
  static bool oldA = 0;
  static bool oldB = 0;
  bool newB = digitalRead(ENCODER_LEFT_B);
  bool newA = digitalRead(ENCODER_LEFT_CLK) ^ newB;
  int delta = (oldA ^ newB) - (newA ^ oldB);
  Leftcountvalue -= delta;  // run the left encoder backwards
  oldA = newA;
  oldB = newB;
}

// INT1 will respond to the XOR-ed pulse train from the right encoder
// runs in constant time of around 3us per interrupt.
// would be faster with direct port access
ISR(INT1_vect) {
  static bool oldA = 0;
  static bool oldB = 0;
  bool newB = digitalRead(ENCODER_RIGHT_B);
  bool newA = digitalRead(ENCODER_RIGHT_CLK) ^ newB;
  int delta = (oldA ^ newB) - (newA ^ oldB);
  Rightcountvalue += delta;
  oldA = newA;
  oldB = newB;
}

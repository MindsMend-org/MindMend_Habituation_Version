//(M MM D V2 05/02/2020)
//Mince @ FoldingCircles:- All The Code I Write is under this Name. 
//MindsMend.org
//By Brett Palmer 2020. All Rights Reserved.

//This version takes into account, the (Habituation Problem); With new design of visual stimulation using infinity type construction & we add Patterns.  
//Plain Coded Pre Alpha Ver 00000001. Depending on the Arduino Used Alter Pin Values. 
//Tested and Works fine on ATMEGA 2560 Chips. 30 Channels Needed, (Digital pref)



//Based on 8 Coil Setup (Timings)-
//Primer 25ms = 8 Coil Setup.       (Primer 360 seconds)-set to 36 seconds atm ten loops = 1 use
//Binding = 3.125ms = 8 Coil Setup. (Effector 840 seconds) - set to 420 atm = 7min

//The Visual Cortex Is located at Back of Head.
//     Left eye = Right Hemisphere (B)
//     Right eye = Left Hemisphere (A)

//Key:- the coils Fire in Anti Colckwise 
// Direction For this Desired Effect.

unsigned long Time = 0;
//const float Runtime = 1000*60*60; //ms/sec/min = 1 hour. 


//This Device Will Use Standard Vis spec Band. (450nmBlue or SuperBrightWhite LED) 3.5v 50mA use at least a 39R resistor.(Works Well with a 150R)R = ohm.  
//EYE LED 
//ATMega2560               01,02,03,04,05,06,07,08,09,10 //index = 0-9
int LeftEyePinArray[] = {23,25,27,29,31,33,35,37,39,41,23,25,27,29,31,33,35,37,39,41,23,25,27,29,31,33,35,37,39,41,23,25,27,29,31,33,35,37,39,41,25,31,37,23,27,33,39,29,35,41,25,31,37,23,27,33,39,29,35,41,25,31,37,23,27,33,39,29,35,41};//Critical to keep these 2 arrays the same length.
int RightEyePinArray[] ={22,24,26,28,30,32,34,36,38,40,22,24,26,28,30,32,34,36,38,40,22,24,26,28,30,32,34,36,38,40,22,24,26,28,30,32,34,36,38,40,24,30,36,22,26,32,38,28,34,40,22,24,26,28,30,32,34,36,38,40,24,30,36,22,26,32,38,28,34,40};
//Led div 2 offset 
//r= ={22,24,26,28,30,32,34,36,38,40,22,24,26,28,30,32,34,36,38,40,22,24,26,28,30,32,34,36,38,40,22,24,26,28,30,32,34,36,38,40,22,24,26,28,30,32,34,36,38,40};
//l= = {23,25,27,29,31,33,35,37,39,41,23,25,27,29,31,33,35,37,39,41,23,25,27,29,31,33,35,37,39,41,23,25,27,29,31,33,35,37,39,41,23,25,27,29,31,33,35,37,39,41};
int OFFSETLeftEyePinArray[] = {23,25,27,29,31,33,35,37,39,41,23,25,27,29,31,33,35,37,39,41,23,25,27,29,31,33,35,37,39,41,23,25,27,29,31,33,35,37,39,41,25,31,37,23,27,33,39,29,35,41,25,31,37,23,27,33,39,29,35,41,25,31,37,23,27,33,39,29,35,41};
int OFFSETRightEyePinArray[] ={22,24,26,28,30,32,34,36,38,40,22,24,26,28,30,32,34,36,38,40,22,24,26,28,30,32,34,36,38,40,22,24,26,28,30,32,34,36,38,40,24,30,36,22,26,32,38,28,34,40,22,24,26,28,30,32,34,36,38,40,24,30,36,22,26,32,38,28,34,40};

int EYEINDEX = 0;//LED_BUILTIN;//test using board led
int RLight = RightEyePinArray[EYEINDEX];
int LLight = LeftEyePinArray[EYEINDEX];

//OFFSET
int OFFSETEYEINDEX = 0;//LED_BUILTIN;//test using board led
int OFFSETRLight = RightEyePinArray[EYEINDEX];
int OFFSETLLight = LeftEyePinArray[EYEINDEX];

int ArraySIZE = sizeof(LeftEyePinArray)/sizeof(RightEyePinArray[0]);//get size of array in bits & convert to index elements. Will b value of 9 as (0-9 = 10)

//Eye Pins Clarification. so Fires R-Eye Coil L-Eye eg pin order 4,LEye,5,REye,6 !!! Anit-Clockwise around head, Fire in PinID sequence




//Coils Direct Refrence>Pin Address
int CoilA = 2; //1
int CoilB = 3; //2
int CoilC = 4; //3
int CoilD = 5; //4
int CoilE = 6; //5
int CoilF = 7; //6
int CoilG = 8; //7
int CoilH = 9; //8







void setup() {
pinMode(CoilA, OUTPUT);
pinMode(CoilB, OUTPUT);
pinMode(CoilC, OUTPUT);
pinMode(CoilD, OUTPUT);
pinMode(CoilE, OUTPUT);
pinMode(CoilF, OUTPUT);
pinMode(CoilG, OUTPUT);
pinMode(CoilH, OUTPUT);



//Pin Mode: Set to Driver Mode for Mosfet Operation.(SETUP-LOOP)
for (int i = 0;i < ArraySIZE;i++){
EYEINDEX = i; //+=1;
RLight = RightEyePinArray[EYEINDEX];
LLight = LeftEyePinArray[EYEINDEX];
pinMode(LLight, OUTPUT);
pinMode(RLight, OUTPUT);
digitalWrite(LLight, LOW);
digitalWrite(RLight, LOW);

}
//Pin Start Set All Outputs to off
//Eyes
digitalWrite(RLight, LOW);
digitalWrite(LLight, LOW);

//Brain
digitalWrite(CoilA, LOW);
digitalWrite(CoilB, LOW);
digitalWrite(CoilC, LOW);
digitalWrite(CoilD, LOW);
digitalWrite(CoilE, LOW);
digitalWrite(CoilF, LOW);
digitalWrite(CoilG, LOW);
digitalWrite(CoilH, LOW);
}








void loop() {
//Loop through pins.
//P R I M E R
//360 second Loop = 180ms once through time. 5.555555555555556hz
//Coils
EYEINDEX = -1;// to start.
OFFSETEYEINDEX = 5;

int timeforloop = (1000/180) * 36;// 360; //=1sec/oncethroughtime*360 seconds = 2000 loops

for (int i = 0; i <= timeforloop ; i++) {
EYEINDEX +=1;
OFFSETEYEINDEX +=1;

if (EYEINDEX == ArraySIZE-1){
  EYEINDEX = 0;
  }
if (OFFSETEYEINDEX == ArraySIZE-1){
  OFFSETEYEINDEX =0;
  }
RLight = RightEyePinArray[EYEINDEX];
LLight = LeftEyePinArray[EYEINDEX];
//Offset
OFFSETRLight = OFFSETRightEyePinArray[OFFSETEYEINDEX];
OFFSETLLight = OFFSETLeftEyePinArray[OFFSETEYEINDEX];

digitalWrite(CoilA, HIGH); //1 on A       
delay(2.5);
digitalWrite(CoilH, LOW);  //8 off
delay(20.0);
digitalWrite(CoilB, HIGH); //2 on B
delay(2.5);
digitalWrite(CoilA, LOW);  //1 off
delay(20.0);
digitalWrite(CoilC, HIGH); //3 on C
delay(2.5);
digitalWrite(CoilB, LOW);  //2 off
delay(20.0);
digitalWrite(CoilD, HIGH); //4 on D
digitalWrite(RLight, HIGH);//RightEyePinArray[EYEINDEX]
digitalWrite(OFFSETRLight, HIGH);
delay(2.5);
digitalWrite(LLight, HIGH);//RightEyePinArray[EYEINDEX]
digitalWrite(OFFSETLLight, HIGH);
delay(2.5);
digitalWrite(CoilC, LOW);  //3 off
delay(17.5);
digitalWrite(RLight, LOW);
digitalWrite(OFFSETRLight, LOW);
digitalWrite(CoilE, HIGH); //5 on E
delay(2.5);
digitalWrite(LLight, LOW);
digitalWrite(OFFSETLLight, LOW);
digitalWrite(CoilD, LOW);  //4 off
delay(20.0);
digitalWrite(CoilF, HIGH); //6 on F
delay(2.5);
digitalWrite(CoilE, LOW);  //5 off
delay(20.0);
digitalWrite(CoilG, HIGH); //7 on G
delay(2.5);
digitalWrite(CoilF, LOW);  //6 off
delay(20.5);
digitalWrite(CoilH, HIGH); //8 on H
delay(2.5);
digitalWrite(CoilG, LOW);  //7 off
delay(20.0);
}//end of 360 seconnd loop


//B I N D I N G
//Binding = 3.125ms = 8 Coil Setup. (Effector 840 seconds) 40hz
//840 Seconds Binding Mode
EYEINDEX = -1;//to start.
OFFSETEYEINDEX = 5;
timeforloop = 40 * 420;//840; // = 1 sec / once through = 25ms * looptime seconds
for (int Binding = 0;Binding < timeforloop;Binding ++){
EYEINDEX +=1;
OFFSETEYEINDEX +=1;

if (EYEINDEX == ArraySIZE-1){
  EYEINDEX = 0;
  }
  if (OFFSETEYEINDEX == ArraySIZE-1){
  OFFSETEYEINDEX = 0;
  }
RLight = RightEyePinArray[EYEINDEX];
LLight = LeftEyePinArray [EYEINDEX];
//Offset
OFFSETRLight = OFFSETRightEyePinArray[OFFSETEYEINDEX];
OFFSETLLight = OFFSETLeftEyePinArray[OFFSETEYEINDEX];


digitalWrite(CoilA, HIGH); //1 on A       
delay(0.125);
digitalWrite(CoilH, LOW);  //8 off
delay(3);
digitalWrite(CoilB, HIGH); //2 on B
delay(0.125);
digitalWrite(CoilA, LOW);  //1 off
delay(3);
digitalWrite(CoilC, HIGH); //3 on C
delay(0.125);
digitalWrite(CoilB, LOW);  //2 off
delay(3);
digitalWrite(CoilD, HIGH); //4 on D
digitalWrite(RLight, HIGH);         //Right Eye Drive Eye Array
digitalWrite(OFFSETRLight, HIGH); 
delay(0.125);
digitalWrite(LLight,HIGH);          //Left Eye Drive Eye Array
digitalWrite(OFFSETLLight,HIGH);
digitalWrite(CoilC, LOW);  //3 off
delay(3);
digitalWrite(RLight, LOW);          //Right Eye Turn Off Current Eye Index
digitalWrite(OFFSETRLight, LOW);
digitalWrite(CoilE, HIGH); //5 on E
delay(0.125);
digitalWrite(LLight, LOW);          //Left Eye Tuen Off Current Eye Index
digitalWrite(OFFSETLLight, LOW);
digitalWrite(CoilD, LOW);  //4 off
delay(3);
digitalWrite(CoilF, HIGH); //6 on F
delay(0.125);
digitalWrite(CoilE, LOW);  //5 off
delay(3);
digitalWrite(CoilG, HIGH); //7 on G
delay(0.125);
digitalWrite(CoilF, LOW);  //6 off
delay(3);
digitalWrite(CoilH, HIGH); //8 on H
delay(0.125);
digitalWrite(CoilG, LOW);  //7 off
delay(3);
}
//❤


}

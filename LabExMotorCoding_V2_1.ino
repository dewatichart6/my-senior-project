#include <AccelStepper.h>
#include <Servo.h> 


long receivedMMdistanceX = 0;
long receivedMMdistanceY = 0;
long receivedMMdistanceZ = 0;
long receivedMMdistanceH = 0;
long receivedMMdistanceV = 0;
long receivedMMdistanceD = 0;

char receivedCommand;

const byte interruptPinX = 36;
const byte interruptPinY = 38;
const byte interruptPinZ = 40;
const byte interruptPinH = 42;
const byte interruptPinV = 44;


const byte ENPinX = 22;
const byte STEPPinX = 2;
const byte DIRPinX = 23;

const byte ENPinY = 24;
const byte STEPPinY = 3;
const byte DIRPinY = 25;


const byte ENPinZ = 28;
const byte STEPPinZ = 5 ;
const byte DIRPinZ = 29;

const byte ENPinH = 30;
const byte STEPPinH = 6;
const byte DIRPinH = 31;

const byte ENPinV = 32;
const byte STEPPinV = 7;
const byte DIRPinV = 33;

const byte ENPinD = 34;
const byte STEPPinD = 8;
const byte DIRPinD = 35;

const byte Servopin = 9;

const byte Solenoidpin = 10;

int steppermm = 25 ;
int microstep = 1 ; 

Servo myservo;
int pos = 0; 
int i=0 ;
 
bool newData, runallowedX, runallowedY, runallowedY1, runallowedZ, runallowedH, runallowedV, runallowedD = false;

//Position in millimeters
int pos1[2] = {150,350};
int pos2[2] = {300,350};
int pos3[2] = {450,350};
int posE[2] = {765,380};
int Zdist   = 255;
int posEh   = 290;
int tube1   = 500;
int tube2   = 521;
int tube3   = 544;
int water   = 150;
int clearwater   = 60;
int Vertdist = 151;
int drain = 100;
int drop = 100;



AccelStepper stepperX(1, STEPPinX, DIRPinX); // step direct
AccelStepper stepperY(1, STEPPinY, DIRPinY);
AccelStepper stepperZ(1, STEPPinZ, DIRPinZ);
AccelStepper stepperH(1, STEPPinH, DIRPinH);
AccelStepper stepperV(1, STEPPinV, DIRPinV);
AccelStepper stepperD(1, STEPPinD, DIRPinD);


void setup()
{ 
  pinMode(interruptPinX,INPUT_PULLUP);
  pinMode(interruptPinY,INPUT_PULLUP);
  pinMode(interruptPinZ,INPUT_PULLUP);
  pinMode(interruptPinH,INPUT_PULLUP);
  pinMode(interruptPinV,INPUT_PULLUP);

  
  Serial.begin(115200);
  Serial3.begin(115200);


  stepperX.setEnablePin (ENPinX) ;
  stepperY.setEnablePin (ENPinY) ;
  stepperZ.setEnablePin (ENPinZ) ;
  stepperH.setEnablePin (ENPinH) ;
  stepperV.setEnablePin (ENPinV) ;
  stepperD.setEnablePin (ENPinD) ;

  
  stepperX.setAcceleration(10000);
  stepperY.setAcceleration(10000);
  stepperZ.setAcceleration(10000);
  stepperH.setAcceleration(10000);
  stepperV.setAcceleration(10000); 
  stepperD.setAcceleration(10000); 
  
  stepperX.enableOutputs();
  stepperY.enableOutputs();
  stepperZ.enableOutputs();
  stepperH.enableOutputs();
  stepperV.enableOutputs();
  stepperD.enableOutputs();

  myservo.attach(Servopin);

  pinMode(Solenoidpin,OUTPUT);
   
}

void loop()
{
  checkSerial();
  continuousRun();
  stopmotor();
}


void continuousRun()
{
  if (runallowedX == true)
  {
    if (stepperX.currentPosition() != receivedMMdistanceX)
    {
      stepperX.disableOutputs(); 
      stepperX.run(); 
    }
    else
    {      
      runallowedX = false;
    }
  }
    if (runallowedY == true)
  {
    if (stepperY.currentPosition() != receivedMMdistanceY)
    {
      stepperY.disableOutputs(); 
      stepperY.run(); 
    }
    else
    {      
      runallowedY = false;
    }
  }
    if (runallowedZ == true)
  {
    if (stepperZ.currentPosition() != receivedMMdistanceZ)
    {
      stepperZ.disableOutputs(); 
      stepperZ.run(); 
    }
    else
    {      
      runallowedZ = false;
    }
  }
      if (runallowedH == true)
  {
    if (stepperH.currentPosition() != receivedMMdistanceH)
    {
      stepperH.disableOutputs(); 
      stepperH.run(); 
    }
    else
    {      
      runallowedH = false;
    }
  }
      if (runallowedV == true && stepperH.currentPosition()>= 550 || stepperH.currentPosition()<= 291 )
  {
    if (stepperV.currentPosition() != receivedMMdistanceV)
    {
      stepperV.disableOutputs(); 
      stepperV.run(); 
    }
    else
    {      
      runallowedV = false;
    }
  }
  else
  {
    return;
  }
}

void checkSerial()
{
  
 if (Serial3.available()>0) //if something comes
   {
    receivedCommand = Serial3.read(); // this will read the command character
    newData = true; //this creates a flag
    Serial.print(receivedCommand);
  }

  if (newData == true) 
  {
     if (receivedCommand == 'a') // HomeALL
    {
      runallowedX = true;
      runallowedY = true;
      runallowedH = true;
      runallowedV = true;
      runallowedZ = true;

      
      receivedMMdistanceX = 200000;
      receivedMMdistanceY = 200000;
      receivedMMdistanceZ = 200000;
      receivedMMdistanceH = 200000;
      receivedMMdistanceV = 200000;
      

 
      stepperX.setMaxSpeed(1000);
      stepperY.setMaxSpeed(1000);
      stepperZ.setMaxSpeed(1000);
      stepperH.setMaxSpeed(1000);
      stepperV.setMaxSpeed(1000);
      
              for(pos = 180; pos>=0; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
      myservo.write(pos);              // tell servo to go to position in variable 'pos' 
      delay(0.01);                       // waits 15ms for the servo to reach the position
  } 
      stepperX.move(receivedMMdistanceX);
      stepperY.move(-receivedMMdistanceY);
      stepperZ.move(receivedMMdistanceZ);
      stepperH.move(-receivedMMdistanceH);
      stepperV.move(-receivedMMdistanceV);


    }

      if (receivedCommand == 'b') // HomeX
    {
      runallowedX = true;
      
      receivedMMdistanceX = (steppermm*microstep)*200000;

      stepperX.setMaxSpeed(1000);

      stepperX.move(receivedMMdistanceX);
    }

      if (receivedCommand == 'c') // HomeY
    {
      runallowedY = true;
      
      receivedMMdistanceY = (steppermm*microstep)*200000;

      stepperY.setMaxSpeed(1000);

      stepperY.move(-receivedMMdistanceY);
    }

       if (receivedCommand == 'd') // HomeZ
    {
      runallowedZ = true;
      
      receivedMMdistanceZ = (steppermm*microstep)*200000;

      stepperZ.setMaxSpeed(1000);
      
      stepperZ.move(receivedMMdistanceZ);
    }

       if (receivedCommand == 'm') // Home Horizontal Dropper
    {
      runallowedH = true;
      
      receivedMMdistanceH = (steppermm*microstep)*200000;

      stepperH.setMaxSpeed(1000);

      stepperH.move(-receivedMMdistanceH);
    }

       if (receivedCommand == 'f') // Home Vertical Dropper
    {
      runallowedV = true;
      
      receivedMMdistanceV = (steppermm*microstep)*200000;

      stepperV.setMaxSpeed(1000);

      stepperV.moveTo(-receivedMMdistanceV);
    }
    if (receivedCommand == 'g') // POS1
    {
      runallowedX = true;
      runallowedY = true;

      receivedMMdistanceX = (steppermm*microstep)*pos1[0];
      receivedMMdistanceY = (steppermm*microstep)*pos1[1];
      
      stepperZ.disableOutputs();
      receivedMMdistanceZ = 0;
      stepperZ.setMaxSpeed(1000);
      stepperZ.moveTo(receivedMMdistanceZ);
      stepperZ.runToPosition();

      stepperX.setMaxSpeed(1000);
      stepperY.setMaxSpeed(1000);
      stepperX.moveTo(-receivedMMdistanceX);
      stepperY.moveTo(receivedMMdistanceY);
    }

        if (receivedCommand == 'k') //POS2
    {
      runallowedX = true;
      runallowedY = true;

      receivedMMdistanceX = (steppermm*microstep)*pos2[0];
      receivedMMdistanceY = (steppermm*microstep)*pos2[1];
      
      stepperZ.disableOutputs();
      receivedMMdistanceZ = 0;
      stepperZ.setMaxSpeed(1000);
      stepperZ.moveTo(receivedMMdistanceZ);
      stepperZ.runToPosition();

      stepperX.setMaxSpeed(1000);
      stepperY.setMaxSpeed(1000);
      stepperX.moveTo(-receivedMMdistanceX);
      stepperY.moveTo(receivedMMdistanceY);
      
    }

    
        if (receivedCommand == 'i') // POS3
    {
      runallowedX = true;
      runallowedY = true;

      receivedMMdistanceX = (steppermm*microstep)*pos3[0];
      receivedMMdistanceY = (steppermm*microstep)*pos3[1];

      stepperZ.disableOutputs();
      receivedMMdistanceZ = 0;
      stepperZ.setMaxSpeed(1000);
      stepperZ.moveTo(receivedMMdistanceZ);
      stepperZ.runToPosition();
      

      stepperX.setMaxSpeed(1000);
      stepperY.setMaxSpeed(1000);
      stepperX.moveTo(-receivedMMdistanceX);
      stepperY.moveTo(receivedMMdistanceY);
    }

    if (receivedCommand == 'j') // POSE
    {
      runallowedX = true;
      runallowedY = true;

      receivedMMdistanceX = (steppermm*microstep)*posE[0];
      receivedMMdistanceY = (steppermm*microstep)*posE[1];

      stepperZ.disableOutputs();
      receivedMMdistanceZ = 0;
      stepperZ.setMaxSpeed(1000);
      stepperZ.moveTo(receivedMMdistanceZ);
      stepperZ.runToPosition();

      stepperX.setMaxSpeed(1000);
      stepperY.setMaxSpeed(1000);
      stepperX.moveTo(-receivedMMdistanceX);
      stepperY.moveTo(receivedMMdistanceY);
    }

    
    if (receivedCommand == 'q') // Zup
    {
      runallowedZ = true;
      
      receivedMMdistanceZ = (steppermm*microstep)*Zdist;
 
      stepperZ.setMaxSpeed(1000);

      stepperZ.moveTo(0);
    }

        if (receivedCommand == 'r') // Zdown
    {
      runallowedZ = true;
      
      receivedMMdistanceZ = (steppermm*microstep)*Zdist;
 
      stepperZ.setMaxSpeed(1000);

      stepperZ.moveTo(-receivedMMdistanceZ);
    }

        if (receivedCommand == 'u') // POSE Horizontal dropper
    {
      runallowedX = true;
      runallowedY = true;
      runallowedH = true;
      runallowedZ = true;

      
      receivedMMdistanceX = 0;
      receivedMMdistanceY = 0;
      receivedMMdistanceZ = 0;
      receivedMMdistanceH = (steppermm*microstep)*posEh;

 
      stepperX.setMaxSpeed(1000);
      stepperY.setMaxSpeed(1000);
      stepperZ.setMaxSpeed(1000);
      stepperH.setMaxSpeed(1000);
      
              for(pos = 180; pos>=0; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
      myservo.write(pos);              // tell servo to go to position in variable 'pos' 
      delay(0.01);                       // waits 15ms for the servo to reach the position
  } 
      stepperX.moveTo(receivedMMdistanceX);
      stepperY.moveTo(-receivedMMdistanceY);
      stepperZ.moveTo(receivedMMdistanceZ);
      stepperH.moveTo(receivedMMdistanceH);

    }

        if (receivedCommand == 'v') // TUBE1
    {  
      runallowedX = true;
      runallowedY = true;
      runallowedH = true;
      runallowedZ = true;

      
      receivedMMdistanceX = 0;
      receivedMMdistanceY = 0;
      receivedMMdistanceZ = 0;
      receivedMMdistanceH = (steppermm*microstep)*tube1;

      stepperV.disableOutputs();
      receivedMMdistanceV = 0;
      stepperV.setMaxSpeed(1000);
      stepperV.moveTo(receivedMMdistanceV);
      stepperV.runToPosition();

 
      stepperX.setMaxSpeed(1000);
      stepperY.setMaxSpeed(1000);
      stepperZ.setMaxSpeed(1000);
      stepperH.setMaxSpeed(1000);
      
              for(pos = 180; pos>=0; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
      myservo.write(pos);              // tell servo to go to position in variable 'pos' 
      delay(0.01);                       // waits 15ms for the servo to reach the position
  } 
      stepperX.moveTo(receivedMMdistanceX);
      stepperY.moveTo(-receivedMMdistanceY);
      stepperZ.moveTo(receivedMMdistanceZ);
      stepperH.moveTo(receivedMMdistanceH);

      
    }

        if (receivedCommand == 'w') // TUBE2
    {
             runallowedX = true;
      runallowedY = true;
      runallowedH = true;
      runallowedZ = true;

      
      receivedMMdistanceX = 0;
      receivedMMdistanceY = 0;
      receivedMMdistanceZ = 0;
      receivedMMdistanceH = (steppermm*microstep)*tube2;

       stepperV.disableOutputs();
      receivedMMdistanceV = 0;
      stepperV.setMaxSpeed(1000);
      stepperV.moveTo(receivedMMdistanceV);
      stepperV.runToPosition();

 
      stepperX.setMaxSpeed(1000);
      stepperY.setMaxSpeed(1000);
      stepperZ.setMaxSpeed(1000);
      stepperH.setMaxSpeed(1000);
      
              for(pos = 180; pos>=0; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
      myservo.write(pos);              // tell servo to go to position in variable 'pos' 
      delay(0.01);                       // waits 15ms for the servo to reach the position
  } 
      stepperX.moveTo(receivedMMdistanceX);
      stepperY.moveTo(-receivedMMdistanceY);
      stepperZ.moveTo(receivedMMdistanceZ);
      stepperH.moveTo(receivedMMdistanceH);

    }

        if (receivedCommand == 'x') // TUBE3
    {
             runallowedX = true;
      runallowedY = true;
      runallowedH = true;
      runallowedZ = true;

      
      receivedMMdistanceX = 0;
      receivedMMdistanceY = 0;
      receivedMMdistanceZ = 0;
      receivedMMdistanceH = (steppermm*microstep)*tube3;

       stepperV.disableOutputs();
      receivedMMdistanceV = 0;
      stepperV.setMaxSpeed(1000);
      stepperV.moveTo(receivedMMdistanceV);
      stepperV.runToPosition();

 
      stepperX.setMaxSpeed(1000);
      stepperY.setMaxSpeed(1000);
      stepperZ.setMaxSpeed(1000);
      stepperH.setMaxSpeed(1000);
      
              for(pos = 180; pos>=0; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
      myservo.write(pos);              // tell servo to go to position in variable 'pos' 
      delay(0.01);                       // waits 15ms for the servo to reach the position
  } 
      stepperX.moveTo(receivedMMdistanceX);
      stepperY.moveTo(-receivedMMdistanceY);
      stepperZ.moveTo(receivedMMdistanceZ);
      stepperH.moveTo(receivedMMdistanceH);

    }
        
        if (receivedCommand == '0') // Dropper down
    {
      runallowedV = true;
      stepperD.disableOutputs();
      
      receivedMMdistanceV = (steppermm*microstep)*Vertdist;
      receivedMMdistanceD = (steppermm*microstep)*30;
      stepperV.setMaxSpeed(1000);
      stepperD.setMaxSpeed(100);
      stepperD.move(receivedMMdistanceD);
      stepperD.runToPosition();
      stepperV.moveTo(receivedMMdistanceV);
      
    }

        if (receivedCommand == '1') // Dropper up
    {
      runallowedV = true;
      
      receivedMMdistanceV = (steppermm*microstep)*200000;

      stepperV.setMaxSpeed(1000);

      stepperV.moveTo(-receivedMMdistanceV);
    }
        if (receivedCommand == '2') // Drain
    {   
      stepperD.disableOutputs();
      receivedMMdistanceD = (steppermm*microstep)*30 ;
      stepperD.setMaxSpeed(200);
      stepperD.move(-receivedMMdistanceD);
      stepperD.runToPosition();
      stepperD.setCurrentPosition(0);
    }

       if (receivedCommand == '3') // Drop
    {
      stepperD.disableOutputs();
      receivedMMdistanceD = (steppermm*microstep)*2;
      stepperD.setMaxSpeed(200);
      stepperD.moveTo(receivedMMdistanceD);
      stepperD.runToPosition();
      stepperD.setCurrentPosition(0);
    }   
    if (receivedCommand == '4') //STOP
    {
      stopXmotor();
      stopYmotor();
      stopZmotor();
      stopHmotor();
      stopVmotor();
      stopDmotor();
      Serial.println("STOP "); //print actio
    }    
        if (receivedCommand == 's') // Grip
    {
       for(pos = 0; pos < 180; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(0.01);                       // waits 15ms for the servo to reach the position 
  }  
    }

       if (receivedCommand == 't') // UnGrip
    {
  for(pos = 180; pos>=0; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(0.01);                       // waits 15ms for the servo to reach the position
  } 
    }

        if (receivedCommand == '5') // WATER POS
    {
            runallowedX = true;
      runallowedY = true;
      runallowedH = true;
      runallowedZ = true;

      
      receivedMMdistanceX = 0;
      receivedMMdistanceY = 0;
      receivedMMdistanceZ = 0;
      receivedMMdistanceH = (steppermm*microstep)*water;

      stepperV.disableOutputs();
      receivedMMdistanceV = 0;
      stepperV.setMaxSpeed(1000);
      stepperV.moveTo(receivedMMdistanceV);
      stepperV.runToPosition();

 
      stepperX.setMaxSpeed(1000);
      stepperY.setMaxSpeed(1000);
      stepperZ.setMaxSpeed(1000);
      stepperH.setMaxSpeed(1000);
      
              for(pos = 180; pos>=0; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
      myservo.write(pos);              // tell servo to go to position in variable 'pos' 
      delay(0.01);                       // waits 15ms for the servo to reach the position
  } 
      stepperX.moveTo(receivedMMdistanceX);
      stepperY.moveTo(-receivedMMdistanceY);
      stepperZ.moveTo(receivedMMdistanceZ);
      stepperH.moveTo(receivedMMdistanceH);

    }
        

            if (receivedCommand == '6') // Clearwater POS
    {
            runallowedX = true;
      runallowedY = true;
      runallowedH = true;
      runallowedZ = true;

      
      receivedMMdistanceX = 0;
      receivedMMdistanceY = 0;
      receivedMMdistanceZ = 0;
      receivedMMdistanceH = (steppermm*microstep)*clearwater;

       stepperV.disableOutputs();
      receivedMMdistanceV = 0;
      stepperV.setMaxSpeed(1000);
      stepperV.moveTo(receivedMMdistanceV);
      stepperV.runToPosition();

 
      stepperX.setMaxSpeed(1000);
      stepperY.setMaxSpeed(1000);
      stepperZ.setMaxSpeed(1000);
      stepperH.setMaxSpeed(1000);
      
              for(pos = 180; pos>=0; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
      myservo.write(pos);              // tell servo to go to position in variable 'pos' 
      delay(0.01);                       // waits 15ms for the servo to reach the position
  } 
      stepperX.moveTo(receivedMMdistanceX);
      stepperY.moveTo(-receivedMMdistanceY);
      stepperZ.moveTo(receivedMMdistanceZ);
      stepperH.moveTo(receivedMMdistanceH);
    }

        if (receivedCommand == '7') // ClearTube
    {
      stepperD.disableOutputs();
      receivedMMdistanceD = (steppermm*microstep)*30;
      stepperD.setMaxSpeed(500);
      stepperD.move(receivedMMdistanceD);
      stepperD.runToPosition();
    }
    
         if (receivedCommand == '9') // TESTTUBE SHAKE
    {
      Solenoid();
    }

  }

  newData = false; 

}

void stopmotor()
{
  if (digitalRead(interruptPinX) == LOW) // Normally open
{ 
  stopXmotor();
  stepbackX();

}
  if (digitalRead(interruptPinY) == LOW) // Normally open
{ 
  stopYmotor();
  stepbackY();

}
  if (digitalRead(interruptPinZ) == LOW) // Normally open
{ 
  stopZmotor();
  stepbackZ();

}
  if (digitalRead(interruptPinH) == LOW) // Normally open
{ 
  stopHmotor();
  stepbackH();

}
  if (digitalRead(interruptPinV) == LOW) // Normally open
{ 
  stopVmotor();
  stepbackV();
}

}


void stopXmotor()
{
      runallowedX = false; //disable running 
      stepperX.setCurrentPosition(0); // reset position
      stepperX.stop(); //stop motor
}

void stopYmotor()
{
      runallowedY = false; //disable running 
      stepperY.setCurrentPosition(0); // reset position
      stepperY.stop(); //stop motor
}
void stopZmotor()
{
      runallowedZ = false; //disable running 
      stepperZ.setCurrentPosition(0); // reset position
      stepperZ.stop(); //stop motor
}
void stopHmotor()
{
      runallowedH = false; //disable running 
      stepperH.setCurrentPosition(0); // reset position
      stepperH.stop(); //stop motor
}
void stopVmotor()
{
      runallowedV = false; //disable running 
      stepperV.setCurrentPosition(0); // reset position
      stepperV.stop(); //stop motor
}
void stopDmotor()
{
      runallowedD = false; //disable running 
      stepperD.stop(); //stop motor
}
void Servo1()
{
    for(pos = 180; pos > 0; pos -= 1)  // goes from 0 degrees to 180 degrees กาง
{                                      // in steps of 1 degree 
    myservo.write(pos);                // tell servo to go to position in variable 'pos' 
    delay(0.01);                       // waits 15ms for the servo to reach the position 
}

}

void Servo2()
{
    for(pos = 0; pos< 180; pos+=1)     // goes from 180 degrees to 0 degrees หุบ
  {                                
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(0.01);                       // waits 15ms for the servo to reach the position
  } 
}
void Solenoid()
{
  for(i=0;i<21;i++)
{
  analogWrite(Solenoidpin,255);
  delay(100);
  analogWrite(Solenoidpin,0);
  delay(100);
}
}


void stepbackX()
{
   stepperX.setMaxSpeed(500);
   stepperX.move(-100);
   stepperX.runToPosition();
   stepperX.setCurrentPosition(0); // reset position      
}

void stepbackY()
{
   stepperY.setMaxSpeed(500);
   stepperY.move(100);
   stepperY.runToPosition();
   stepperY.setCurrentPosition(0); // reset position         
}

void stepbackH()
{
   stepperH.setMaxSpeed(500);
   stepperH.move(100);
   stepperH.runToPosition();
   stepperH.setCurrentPosition(0); // reset position      
}

void stepbackZ()
{
   stepperZ.setMaxSpeed(500);
   stepperZ.move(-100);
   stepperZ.runToPosition();
   stepperZ.setCurrentPosition(0); // reset position      
}

void stepbackV()
{
   stepperV.setMaxSpeed(500);
   stepperV.move(50);
   stepperV.runToPosition();
   stepperV.setCurrentPosition(0); // reset position      
}

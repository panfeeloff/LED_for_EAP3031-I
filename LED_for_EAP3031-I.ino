int ledPinr = 6;      // LED connected to digital pin 6
int ledPing = 5;
int ledPinb = 9;

int analogPinr = 1;
int analogPing = 2; 
int analogPinb = 3; // potentiometer connected to analog pin 3

int valr = 0;         // variable to store the read valrue
int valg = 0; 
int valb = 0;


int thrr = 0;  //% of full
int thrg = 30;
int thrb = 30;

int errr = 0;
int errg = 0;
int errb = 0;

int pwmr = 0;
int pwmg = 0;
int pwmb = 0;


int i = 0; //debug
//int rvalr = 0;

float resr = 0;
float resg = 0;
float resb = 0;   

//float der = 0; //derivative cont

float G = 0.1; //0.1
float tau = 0.01; //0.01

//res = res+t*err
//pwm=G*err+res

void setup()

{
  pinMode(ledPinr, OUTPUT);   // sets the pin as output
  pinMode(ledPing, OUTPUT);
  pinMode(ledPinb, OUTPUT);
  
  pinMode(analogPinr, INPUT);
  pinMode(analogPing, INPUT);
  pinMode(analogPinb, INPUT);

//int thrr = thrr*6;  //6 = 1/100*3.24v * 1023 / 5v
//int thrg = thrg*4;  //4 = 1/100*1.92v * 1023 / 5v
//int thrb = thrb*4;  //4 = 1/100*1.92v * 1023 / 5v

 Serial.begin(115200);      // open the serial port at 9600 bps:
 //thr = thr  
}
void loop()
{  
//===========RED=============
//PI controller
  valr = analogRead(analogPinr);   // read the input pin
  errr = thrr*6 - valr; //6 = 1/100*3.24v * 1023 / 5v converts % to values
  errr = errr/4;
  resr = resr+tau*errr;
  if (resr>260) resr = 260;
      //der = tau*(errr - errr0); //derivative cont
      //errr0 =  errr; //derivative cont
      // pwm = G*err+res+der; //+derivative cont 

 //if (res < -100) res = -100; //?????
 // if (res >350) res = 350; //?????
  
   pwmr = G*errr+resr; //
// pwm = res; // I cont
  if (pwmr < 0) pwmr = 0;
  if (pwmr >220) pwmr = 220;

//

//===========GREEN=============
//PI controller
  valg = analogRead(analogPing);   // read the input pin
  errg = thrg*4 - valg;    //4 = 1/100*1.92v * 1023 / 5v converts % to values
  errg = errg/4;
  resg = resg+tau*errg;
  if (resg>260) resg = 260;
  pwmg = G*errg+resg; 
  if (pwmg < 0) pwmg = 0;
  if (pwmg >220) pwmg = 220;



//===========BLUE=============+
//PI controller
  valb = analogRead(analogPinb);   // read the input pin
  errb = thrb*4 - valb;         //4 = 1/100*1.92v * 1023 / 5v converts % to values
  errb = errb/4;
  resb = resb+tau*errb;
  if (resb>260) resb = 260;
  pwmb = G*errb+resb; 
  if (pwmb < 0) pwmb = 0;
  if (pwmb >220) pwmb = 220;

/*debug
pwmr =10;
pwmg =10;
pwmb =10;
*/

    analogWrite(ledPinr,pwmr ); 
    analogWrite(ledPing,pwmg ); 
    analogWrite(ledPinb,pwmb ); 
    if (i==500) {
 // rvalr = analogRead(A0);   // read the input pin
 // Serial.print(rvalr);
  //Serial.print(" ");
  Serial.print("valg=");
  Serial.print(valg);
  Serial.print(" ");
  Serial.print("valr=");
  Serial.print(valr);
  Serial.print(" ");
  Serial.print("valb=");
  Serial.print(valb);
  Serial.print(" ");
  Serial.print("resr=");
  Serial.println(resr);
  i=0;
    }
 i = i+1;



}

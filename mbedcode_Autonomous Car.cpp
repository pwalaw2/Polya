#include "mbed.h"
#include "stdlib.h"
 
DigitalOut led1(LED3);
DigitalOut clk(PTA5 );
DigitalOut si(PTC5);
AnalogIn camData(PTC1);
PwmOut servo(PTA4);
PwmOut Motor_right(PTA12);           //PWM for the right motor
PwmOut Motor_left(PTA2);            //PWM output for  left dc motor
DigitalOut Motor_Disable1(PTD4);   //KEEP DISABLED-RIGHT     not to change becoz with the conflict with servo
DigitalOut Motor_Disable2(PTA1);    //KEEP DSIABLED-LEFT
DigitalOut EN1(PTC6);               //Enable Pin for left Motor
DigitalOut EN2(PTC10);              //Enable Pin for Right Motor
Serial pc(USBTX,USBRX);             //tx, rx
//SHIELD Connections
//DigitalOut EN(PTE21);               //Enable Pin
//DigitalOut FLT(PTE20);              //Fault Pin

float ADCdata [128];
float slopeAccum;
float slopeCount;
float approxPos;
float minVal;
 
int minLoc;

//servo motor directions 
int straight = 1700;
int hardLeft = 1300;
int slightLeft = 1550;
int slightRight = 1900;
int hardRight = 2000;


// dc motor speed variations
int dc_slow=200;
int dc_slight =8000;
int dc_fast =1600; 
int dc_stop =150;
 
int currDirection = straight;
 
int main() 
{
    
servo.period_ms(20);                // period of servo motor  = 20ms
Motor_right.period_ms(200);         // period of right dc motor  = 200ms
Motor_left.period_ms(250);          // period of left dc motor   = 200ms
EN1=1;
EN2=1;
Motor_Disable1=0;
Motor_Disable2=0;
//EN=1;
//FLT=1;
int integrationCounter = 0; 
while(1) 
{
            
if(integrationCounter % 151== 0)
{
            //__disable_irq
            si = 1;
            clk = 1;
            //wait(.00001);
            si = 0;
            clk = 0;
            integrationCounter = 0;
            
            slopeAccum = 0;
            slopeCount = 0;
            approxPos = 0;
                
}

else if (integrationCounter > 129)
{
            
       minVal = ADCdata[7];
       for (int c = 7; c < 118; c++) 
       {
           if (ADCdata[c] < minVal)
           {
                minVal = ADCdata[c];
                minLoc = c;
           }
       }
            
       for (int c = 7; c < 118; c++) 
       {
           if (ADCdata[c] >= minVal && ADCdata[c] - minVal < 0.04f && ADCdata[c] > 0.1f)
           {
                slopeAccum += c;
                slopeCount++;
           }
       }
            
       approxPos = (float)slopeAccum/(float)slopeCount;
        Motor_right.pulsewidth_us(dc_slight);    
       if(approxPos > 0 && approxPos <= 20)
       {       
            servo.pulsewidth_us(hardLeft);// changed
           // Motor_right.pulsewidth_us(dc_slight);
            //Motor_left.pulsewidth_us(dc_slight);          //Slow speed Pulse width for left  hard turns
       }  
       else if (approxPos > 20 && approxPos <= 45)
        {
            servo.pulsewidth_us(slightLeft);  //changed
           // Motor_right.pulsewidth_us(dc_slight); 
           // Motor_left.pulsewidth_us(dc_slight);         //medium speed Pulse width for left slight turns
        } 
       else if (approxPos > 45 && approxPos <= 90)
       {
            servo.pulsewidth_us(straight);
           // Motor_right.pulsewidth_us(dc_slight);
          //  Motor_left.pulsewidth_us(dc_slight);        //High speed pulse width for straight movement
       } 
       else if (approxPos > 90 && approxPos <= 105)
       {
            servo.pulsewidth_us(slightRight);
           // Motor_right.pulsewidth_us(dc_slight);
          //  Motor_left.pulsewidth_us(dc_slight);         //medium speed Pulse width for right slight turns
       } 
       else if(approxPos > 105 && approxPos <= 128)
       {
            servo.pulsewidth_us(hardRight);
          //  Motor_right.pulsewidth_us(dc_slight); 
          //  Motor_left.pulsewidth_us(dc_slight);        //Slow speed Pulse width for right hard turns
       }
       integrationCounter = 150;
}
      else
      {
            clk = 1;
            wait_us(70);
            ADCdata[integrationCounter - 1] = camData;
            clk = 0;
      }
 
        //clk = 0;
        integrationCounter++;
        //camData.
        
  } //endofwhile
} //endofmain
 

#include<StackArray.h>
#include<EEPROM.h>
StackArray<byte> unexplored;

class node
{
  public:
  unsigned long int wt=100000;
  unsigned long int conn_wts[4];

  bool t_type=0;
  bool expl=0;

  float type;//o=|,0.5=V,1=L,1.5=Y,2=T,3=+
  float explored;
  float entry_dir[4];

  char turn;//R=right,L=left,S=straight,U=uturn,r=45d right,l=45d left,a=45d y right turn,s=45d y left turn

  byte conn_count=0;
  byte prevnode=0;
  byte conn[4];

  double cordx;
  double cordy;
  node()
  {
    type = 0;
    cordx = 0;
    cordy = 0;
    explored = 0;
  }
};

node point[50];

bool s[8],d0,d1,d2,d3;
bool CP=0,t_glo_type,l_type=0,p_type=0;//T_Y for confusion between T and Y
bool act_flag=0;

byte j=0,j_count=0,checkpt=14,endpoint,actual_j=0;
byte path[40],n[100];
byte s_sum,l_sum,r_sum,m_sum,v_sum,d_sum;
byte RP=11,LP=9,RD=10,LD=6;

unsigned long int start_time,end_time,mid_time;
unsigned int dist;

int corr_fact=0,rev_corr_fact=0;

float type,dir=0;
float RMS,LMS,turnspd=40,basespd=50;//bs=80;ts=70
float PID, p_err=0, err, Kp=18, Kd=36;

#define r_factor 1

char state;

String drypath="O";//"ORURRLULRSUSRUSULRULRURE"
String actualpath="OLRRLRLR";
String realpath;

void setup() 
{
  Serial.begin(115200);
  pinMode(LED_BUILTIN,OUTPUT);
  pinMode(51,OUTPUT);
  pinMode(49,OUTPUT);
  pinMode(47,OUTPUT);
  pinMode(45,OUTPUT);
  pinMode(53,OUTPUT);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);
  pinMode(A4,INPUT);
  pinMode(A5,INPUT);
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  pinMode(A8,INPUT);
  pinMode(A9,INPUT);
  pinMode(A10,INPUT);
  pinMode(A11,INPUT);
  pinMode(12,INPUT_PULLUP);
  pinMode(8,INPUT_PULLUP);
  pinMode(5,INPUT_PULLUP);
  pinMode(4,INPUT_PULLUP);
  pinMode(RD,OUTPUT);
  pinMode(LD,OUTPUT);
  pinMode(RP,OUTPUT);
  pinMode(LP,OUTPUT);
  n[0]=0;
  start_time = millis();
//  EEPROM.put(0,actualpath);
}

void ploop()
{
  Serial.print(analogRead(A8));
  Serial.print(" ");
  Serial.print(analogRead(A9));
  Serial.print(" ");  
  Serial.print(analogRead(A10));
  Serial.print(" ");
  Serial.print(analogRead(A11));
  Serial.print(" ");
  if(analogRead(A8)>800) {d0=1;}
  else {d0=0;}
  if(analogRead(A9)>800) {d1=1;}
  else {d1=0;}
  if(analogRead(A10)>800) {d2=1;}
  else {d2=0;}
  if(analogRead(A11)>800) {d3=1;}
  else {d3=0;}
  Serial.print(d0);
  Serial.print(" ");
  Serial.print(d1);
  Serial.print(" ");
  Serial.print(d2);
  Serial.print(" ");
  Serial.print(d3);
  Serial.print("\t ");
  s[0] = digitalRead(A3);
  s[1] = digitalRead(A2);
  s[2] = digitalRead(A4);
  s[3] = digitalRead(A1);
  s[4] = digitalRead(A5);
  s[5] = digitalRead(A0);
  s[6] = digitalRead(3);
  s[7] = digitalRead(2);
  Serial.print(s[0]);
  Serial.print(s[1]);
  Serial.print(s[2]);
  Serial.print(s[3]);
  Serial.print(s[4]);
  Serial.print(s[5]);
  Serial.print(s[6]);
  Serial.println(s[7]);

}
void xloop()
{
  digitalWrite(53,1);
  delay(2000);
  digitalWrite(53,0);
  delay(2000);
}
void loop() 
{
  if(digitalRead(12) && !digitalRead(8))
  {
    dry_run_RHR();
  }
  else if(!digitalRead(12) && !digitalRead(8))
  {
    dry_run_LHR();
  }
  else if(digitalRead(12) && digitalRead(8))
  {
    if(act_flag==0)
    {
      EEPROM.get(0,realpath);
      realpath.replace("C","E");
      act_flag=1;
    }
    actual_run();
  }
}

void tloop()
{
  sensor_read();
  if(digitalRead(12))
  {
//    right();
//    halt(100000);
    analogWrite(RP, turnspd*r_factor);
    analogWrite(LP, turnspd);
    digitalWrite(RD, 0);
    digitalWrite(LD, 1);
  }
  else if(digitalRead(8))
  {
//    left();
//    halt(100000);
    analogWrite(RP, turnspd*r_factor);
    analogWrite(LP, turnspd);
    digitalWrite(RD, 1);
    digitalWrite(LD, 0);
  }
  else if(digitalRead(5))
  {
    analogWrite(RP, turnspd*r_factor);
    analogWrite(LP, turnspd);
    digitalWrite(RD, 0);
    digitalWrite(LD, 0);
  }
  else if(digitalRead(4))
  {
    analogWrite(RP, turnspd*r_factor);
    analogWrite(LP, turnspd);
    digitalWrite(RD, 1);
    digitalWrite(LD, 1);
  }  
}

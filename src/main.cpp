#include <Arduino.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#define pi 3.1415926535
int ball1,ball2,ball3,ball4,ball5,ball6,ball7,ball8,ball9,ball10,ball11,ball12,ball13,ball14,ball15,ball16,line1,line2,line3,line4,line5,line6,line7,line8,line9,line10,line11,line12,line13,line14,line15,line16;
float x1,y1,x2,y2,x3,y3,x4,y4,x5,y5,r,deg;
unsigned long time_new, time_old = 0;
int situ =0; //シチュエーション
int ba[16]={ball1,ball2,ball3,ball4,ball5,ball6,ball7,ball8,ball9,ball10,ball11,ball12,ball13,ball14,ball15,ball16};
float x[]={x1,x2,x3,x4,x5};
float y[]={y1,y2,y3,y4,y5};
void ba_val();
float ball_r();  //rの値を求める
float ball_deg(); //角度を求める
float ball_gAD(); //しきい値を求める
void pin();
void vec(float le1,float le2,float le3,float le4);
void vec5(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float x5, float y5);
void swap(int *pa, int *pb);
void bubble_sort(int n, int a[]);
void sort();
float degfunc(float tardeg);
void motor(float angle);
void setup(){
Serial.begin(9600);
for (int i =0; i<16; i++){
  ba[i]=0;
}
}


void loop() {
int A =0;
r=ball_r();
deg=ball_deg();
gAD=ball_gAD();
if (gAD[CN2] < 409){
 motor(80,80);
 wait_ms(200);
}else if (gAD[CN1] < 613 ){
  motor(50,0);
  wait_ms(300);
  motor(0,50);
  wait_ms(300);
}else if (ball2>ball16){
  digitalWrite(5,LOW);
  digitalWrite(3,HIGH);
}else if (ball15>ball1){
  digitalWrite(3,LOW);
  digitalWrite(5,HIGH);
  }  

} 
  

// put function definitions here:
void vec(float x1,float y1,float x2,float y2){
  x1=x1+x2;
  y1=y1+y2;
}
void vec5(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float x5, float y5)
{
  vec(x1,y1,x2,y2);
  vec(x3,y3,x4,y4);
  vec(x3,y3,x5,y5);
  vec(x1,y1,x3,y3);
}
void pin(){
  pinMode(8,OUTPUT);
}
void ba_val(){
  time_new= micros();
  float val1= PINJ & _BV(-1);
  float val2= PINB & _BV(6);
  float val3= PINB & _BV(4);
  float val4= PINH & _BV(5);
  float val5= PINH & _BV(3);
  float val6= PINE & _BV(2);
  float val7= PINE & _BV(4);
  float val8= PINC & _BV(3);
  float val9= PINC & _BV(5);
  float val10= PINA & _BV(6);
  float val11= PINA & _BV(4);
  float val12= PINA & _BV(2);
  float val13= PINA & _BV(0);
  float val14= PIND & _BV(1);
  float val15= PINH & _BV(-1);
  float val16= PIND & _BV(-1);
  float val[]={val1,val2,val3,val4,val5,val6,val7,val8,val9,val10,val11,val12,val13,val14,val15,val16};
  while (time_new - time_old<=833){
    for (int i=0; i<=15; i++){
       if(val[i]==1){
        ba[i]=ba[i]+1;
       } else
       {
        ba[i]=ba[i];
       }
    }
  }
  time_old = time_new;
}
void swap(int *pa, int *pb)
{
  int tmp;
 
  tmp = *pa;
  *pa = *pb;
  *pb = tmp;
}
void bubble_sort(int n, int a[])
{
  int i, j;
 
  for (i = 0; i < n; i++) {
    for (j = 1; j < n - i; j++) {
      if (a[j] < a[j - 1]) {
        swap(&a[j], &a[j - 1]);
      }
    }
  }
}
void sort(){
  bubble_sort(16,ba);
  for (int n =15; n>10; n--){
    if (ba[n]==ball1){//90
      x[15-n]=ball1;
      y[15-n]=0;
    } else if (ba[n]==ball2){//67.5
      x[15-n]=0.3826834*ball2;
      y[15-n]=0.9238795*ball2;
    }else if (ba[n]==ball3){//45
      x[15-n]=0.7071067*ball3;
      y[15-n]=0.7071067*ball3;
    }else if (ba[n]==ball4){//22.5
      x[15-n]=0.92387953*ball4;
      y[15-n]=0.38268343*ball4;
    }else if (ba[n]==ball5){//0
      x[15-n]=ball5;
      y[15-n]=0;
    }else if (ba[n]==ball6){//337.5
      x[15-n]=0.9238795*ball6;
      y[15-n]=-0.3826834*ball6;
    }else if (ba[n]==ball7){//315
      x[15-n]=0.7071067*ball7;
      y[15-n]=-0.7071067*ball7;
    }else if (ba[n]==ball8){//292.5
      x[15-n]=0.38268343*ball8;
      y[15-n]=-0.9238795*ball8;
    }else if (ba[n]==ball9){//270
      x[15-n]=0;
      y[15-n]=-1*ball9;
    }else if (ba[n]==ball10){//247.5
      x[15-n]=-0.3826834*ball10;
      y[15-n]=-0.9238795*ball10;
    }else if  (ba[n]==ball11){//225
      x[15-n]=-0.7071067*ball11;
      y[15-n]=-0.7071067*ball11;
    }else if (ba[n]==ball12){//202.5
      x[15-n]=-0.9238795*ball12;
      y[15-n]=-0.3826834*ball12;
    }else if (ba[n]==ball13){//180
      x[15-n]=-1*ball13;
      y[15-n]=0;
    }else if (ba[n]==ball14){//157.5
      x[15-n]=-0.9238795*ball14;
      y[15-n]=0.3826834*ball14;
    }else if (ba[n]==ball15){//135
      x[15-n]=-0.7071067*ball15;
      y[15-n]=0.7071067*ball15;
    }else if (ba[n]==ball16){//112.5
      x[15-n]=-0.3826834*ball16;
      y[15-n]=0.9238795*ball16;
    }
  }
 
}
float ball_r(){
  ba_val();
  sort();
  vec5(x1,y1,x2,y2,x3,y3,x4,y4,x5,y5);
  return sqrtf(x1*x1+y1*y1);
}
float ball_deg(){
    ba_val();
    sort();
    vec5(x1,y1,x2,y2,x3,y3,x4,y4,x5,y5);
    float ret = atan2f(x1,y1);
    return (180/pi)* ret;
}
float ball_deg(){
    ba_val();
    sort();
    vec5(x1,y1,x2,y2,x3,y3,x4,y4,x5,y5);
    float ret = atan2f(x1,y1);
    float deg_old= (180/pi)* ret;
  return degfunc2(deg_old);
}
float ball_gAD(){
    int
float degfunc(float tardeg){
  if (tardeg <180) {
    return 2*tardeg;
  } else  (tardeg >=180);{
    if (tardeg +90 >360){
      return (tardeg+90)-360;
    }else {
      return tardeg+90;
    }
  }
}
void motor(float angle){
 int motor_speed_1=100*sin((angle-45)*(180/pi));
 int motor_speed_2=100*sin((angle-135)*(180/pi));
 int motor_speed_3=100*sin((angle-225)*(180/pi));
 int motor_speed_4=100*sin((angle-315)*(180/pi));

 if (motor_speed_1>=0){//後で変更
  digitalWrite(1,HIGH);
   analogWrite(1,motor_speed_1);
 }else {
  digitalWrite(1,LOW);
   analogWrite(1,-motor_speed_1);
 }
 if (motor_speed_2>=0){//後で変更
  digitalWrite(1,HIGH);
  analogWrite(1,motor_speed_2);
 }else {
  digitalWrite(1,LOW);
  analogWrite(1,-motor_speed_2);
 }
 if (motor_speed_3>=0){//後で変更
  digitalWrite(1,HIGH);
  analogWrite(1,motor_speed_3);
 }else {
  digitalWrite(1,LOW);
  analogWrite(1,-motor_speed_3);
 }
 if (motor_speed_4>=0){//後で変更
  digitalWrite(1,HIGH);
  analogWrite(1,motor_speed_4);
 }else {
  digitalWrite(1,LOW);
  analogWrite(1,-motor_speed_4);
 }
}
float line (){
   line1 = 1;
   line2 = 1;
   line3 = 1;
   line4 = 1;
   line5 = 1;
   line6 = 1;
   line7 = 1;
   line8 = 1;
   line9 = 1;
   line10 = 1;
   line11 = 1;
   line12 = 1;
   line13 = 1;
   line14 = 1;
   line15 = 1;
   line16 = 1;
  int lin[] = {line1,line2,line3,line4,line5,line6,line7,line8,line9,line10,line11,line12,line13,line14,line15,line16};
  if (line1+line2+line3+line4+line5+line6+line7+line8+line9+line10+line11+line12+line13+line14+line15+line16==1){
    for (int i=0;i<16; i++ ){
      if (lin[i]==1){
        if (i<5){
        return 270-(22.5*i);
        } else {
          if (270-22.5*i>360){
            return (270-22.5*i)-360;
          } else {
            return 270-22.5*i;
          }
        }
    }
  else {
      float lin_deg;
      for (int i=0; i<16; i++){
          if(lin[i]==1){
            
       }
      }
    }
  }
}
}
float degfunc2(float b){
 if (b<90){
  return b+270;
 } else {
  return b-90;
  }
}
float sonigoal(float x1, float y1,float x2, float y2){
 return atanf((y2-y1)/(x2-x1));
}
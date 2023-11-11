#include <Arduino.h>//Arduino.hのファイルを読み込む
#include <stdio.h>//stdio.hのファイルを読み込む
#include <math.h>//math.hのファイルを読み込む
#include <time.h>//time.hのファイルを読み込む
#define pi 3.1415926535//円周率3.1215926535を定数として定義する。
int ball1,ball2,ball3,ball4,ball5,ball6,ball7,ball8,ball9,ball10,ball11,ball12,ball13,ball14,ball15,ball16,line1,line2,line3,line4,line5,line6,line7,line8,line9,line10,line11,line12,line13,line14,line15,line16;//ball,lineの関数を代入。
float x1,y1,x2,y2,x3,y3,x4,y4,x5,y5,r,deg;//x,yの値とrの値、角度を数値として表す。
unsigned long time_new, time_old = 0;//新しい時間、古い時間を変数として定義する。
int situ =0; //シチュエーション
int ba[16]={ball1,ball2,ball3,ball4,ball5,ball6,ball7,ball8,ball9,ball10,ball11,ball12,ball13,ball14,ball15,ball16};//ボールセンサーが16個。
float x[]={x1,x2,x3,x4,x5};//xの値をx1~x5として表す。
float y[]={y1,y2,y3,y4,y5};//yの値をy1~y5として表す。
void ba_val();//ボールセンサーの値valを空とする。
float ball_r();  //rの値を求める
float ball_deg(); //角度を求める
void pin();//pinを空とする。
void vec(float le1,float le2,float le3,float le4);//le1~le4までの大きさと量を示したベクトルを空とする。
void vec5(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float x5, float y5);//x1~x5,y1~y5の大きさと量を表した五個のベクトルを空とする。
void swap(int *pa, int *pb);//×pa,×pbの交換の値を空とする。
void bubble_sort(int n, int a[]);//int nとint aを比較し、条件が合えば、交換する値を空とする。
void sort();//並び替えの値を空とする。
float degfunc(float tardeg);//degfuncの値にtardegを代入する。
void motor(float angle);//モーターに角度代入する。
void setup(){//準備を始める
Serial.begin(9600);//シリアル通信のビットを9600とする。
for (int i =0; i<16; i++){//iの値を進めていき、。
  ba[i]=0;//ボールセンサーの値のiを0とする。

}
}


void loop(){//繰り返し
int A =0;//Aに0を代入する。
r=ball_r();//rにball_rを代入する。
deg=ball_deg();//degにball_degを代入する。
//ここにdefenceのプログラムを書くよ！
}
  


// put function definitions here://ここに関数定義を置く。
void vec(float x1,float y1,float x2,float y2){//ベクトルにx1,y1,x2,y2を代入。
  x1=x1+x2;//x1はx1とx2を足した値である。
  y1=y1+y2;//y1はy1とy2を足した値である。
}
void vec5(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float x5, float y5)//五個のベクトルにx1~x5とy1~y5を代入する。
{
  vec(x1,y1,x2,y2);//このベクトルはx1,y1,x2,y2が代入されている。
  vec(x3,y3,x4,y4);//このベクトルはx3,y3,x4,y4が代入されている。
  vec(x3,y3,x5,y5);//このベクトルはx3,y3,x5,y5が代入されている。
  vec(x1,y1,x3,y3);//このベクトルはx1.y1,x3,y3が代入されている。
}
void pin(){//pinの値を空とする。
  pinMode(8,OUTPUT);//Ardiunoマイコンの8ピンは出力である。
}
void ba_val(){//ボールセンサーの値のvalを空とする。
  time_new= micros();//新しい時間をArdiunoがスタートしてからの秒として数える。
  float val1= PINJ & _BV(-1);//val1のビット番号-1をPINJにビット１という値として設定する。
  float val2= PINB & _BV(6);//val2のビット番号6をPINBにビット１という値として設定する。
  float val3= PINB & _BV(4);//val3のビット番号4をPINBにビット１という値として設定する。
  float val4= PINH & _BV(5);//val4のビット番号5をPINHにビット１という値として設定する。
  float val5= PINH & _BV(3);//val5のビット番号3をPINHにビット１という値として設定する。
  float val6= PINE & _BV(2);//val6のビット番号2をPINEにビット１という値として設定する。
  float val7= PINE & _BV(4);//val7のビット番号4をPINEにビット１という値として設定する。
  float val8= PINC & _BV(3);//val8のビット番号3をPINCにビット１という値として設定する。
  float val9= PINC & _BV(5);//val9のビット番号5をPINCにビット１という値として設定する。
  float val10= PINA & _BV(6);//val10のビット番号6をPINAにビット１という値として設定する。
  float val11= PINA & _BV(4);//val11のビット番号4をPINAにビット１という値として設定する。
  float val12= PINA & _BV(2);//val12のビット番号2をPINAにビット１という値として設定する。
  float val13= PINA & _BV(0);//val13のビット番号0をPINAにビット１という値として設定する。
  float val14= PIND & _BV(1);//val14のビット番号1をPINDにビット１という値として設定する。
  float val15= PINH & _BV(-1);//val15のビット番号-1をPINHにビット１という値として設定する。
  float val16= PIND & _BV(-1);//val16のビット番号-1をPINDにビット１という値として設定する。
  float val[]={val1,val2,val3,val4,val5,val6,val7,val8,val9,val10,val11,val12,val13,val14,val15,val16};//valの中にボールセンサー16個のビット番号を代入する。
  while (time_new - time_old<=833){//新しい時間から古い時間を引いたときに833以下ならば繰り返す。
    for (int i=0; i<=15; i++){//iの値を進めていき、iが15以下ならば、iを0とした後、1足すことを繰り返す。
       if(val[i]==1){//もしvalの値が1ならば、
        ba[i]=ba[i]+1;//ボールセンサーの値を＋1する。
       } else//そうじゃなければ
       {
        ba[i]=ba[i];//ボールセンサーの値をそのままにする。
       }
    }
  }
  time_old = time_new;//古い時間に新しい時間を代入する。
}
void swap(int *pa, int *pb)//交換する値に×paと×pbの値を代入する。
{
  int tmp;//tmpをint型を宣言する。
 
  tmp = *pa;//×paを保管
  *pa = *pb;//×paに×pbを代入する。
  *pb = tmp;//×pbを保管
}
void bubble_sort(int n, int a[])//値nと値aを代入し、比べ、条件が合えば、交換する。
{
  int i, j;//iとjをint型と宣言する。
 
  for (i = 0; i < n; i++) {//iが0から進んでいき、nよりiが小さくならないまで実行する。
    for (j = 1; j < n - i; j++) {//
      if (a[j] < a[j - 1]) {//
        swap(&a[j], &a[j - 1]);//
      }
    }
  }
}
void sort(){//
  bubble_sort(16,ba);//16個のボールセンサーの値を比較し、条件が合えば、一部交換。
  for (int n =15; n>10; n--){//nを15まで進める。その値が10よりも大きくなるまで実行。
   if (ba[n]==ball1){//90//もしボールセンサーの値nがボールセンサー1と値が等しければ。
      x[15-n]=ball1;//x[15-n]にボールセンサ1の値を代入する。
      y[15-n]=0;//y[15-n]の値を0とする。
    } else if (ba[n]==ball2){//67.5　もしボールセンサーの値nがボールセンサー2の値と等しくなければ、
      x[15-n]=0.3826834*ball2;//x[15-n]にボールセンサー2に0.3826834をかけた値を代入する。
      y[15-n]=0.9238795*ball2;//
    }else if (ba[n]==ball3){//45
      x[15-n]=0.7071067*ball3;//
      y[15-n]=0.7071067*ball3;//
    }else if (ba[n]==ball4){//22.5
      x[15-n]=0.92387953*ball4;//
      y[15-n]=0.38268343*ball4;//
    }else if (ba[n]==ball5){//0
      x[15-n]=ball5;//
      y[15-n]=0;//
    }else if (ba[n]==ball6){//337.5
      x[15-n]=0.9238795*ball6;//
      y[15-n]=-0.3826834*ball6;//
    }else if (ba[n]==ball7){//315
      x[15-n]=0.7071067*ball7;//
      y[15-n]=-0.7071067*ball7;//
    }else if (ba[n]==ball8){//292.5
      x[15-n]=0.38268343*ball8;//
      y[15-n]=-0.9238795*ball8;//
    }else if (ba[n]==ball9){//270
      x[15-n]=0;//
      y[15-n]=-1*ball9;//
    }else if (ba[n]==ball10){//247.5
      x[15-n]=-0.3826834*ball10;//
      y[15-n]=-0.9238795*ball10;//
    }else if  (ba[n]==ball11){//225
      x[15-n]=-0.7071067*ball11;//
      y[15-n]=-0.7071067*ball11;//
    }else if (ba[n]==ball12){//202.5
      x[15-n]=-0.9238795*ball12;//
      y[15-n]=-0.3826834*ball12;//
    }else if (ba[n]==ball13){//180
      x[15-n]=-1*ball13;//
      y[15-n]=0;//
    }else if (ba[n]==ball14){//157.5
      x[15-n]=-0.9238795*ball14;//
      y[15-n]=0.3826834*ball14;//
    }else if (ba[n]==ball15){//135
      x[15-n]=-0.7071067*ball15;//
      y[15-n]=0.7071067*ball15;//
    }else if (ba[n]==ball16){//112.5
      x[15-n]=-0.3826834*ball16;//
      y[15-n]=0.9238795*ball16;//
    }
  }
 
}
float ball_r(){//
  ba_val();//
  sort();//
  vec5(x1,y1,x2,y2,x3,y3,x4,y4,x5,y5);//
  return sqrtf(x1*x1+y1*y1);//
}
float ball_deg(){//
    ba_val();//
    sort();//
    vec5(x1,y1,x2,y2,x3,y3,x4,y4,x5,y5);//
    float ret = atan2f(x1,y1);//
    return (180/pi)* ret;//
}
float ball_deg(){//
    ba_val();//
    sort();//
    vec5(x1,y1,x2,y2,x3,y3,x4,y4,x5,y5);//
    float ret = atan2f(x1,y1);//
    float deg_old= (180/pi)* ret;//
  return degfunc2(deg_old);//
}
float ball_gAD(){//
    int
float degfunc(float tardeg){//
  if (tardeg <180) {//
    return 2*tardeg;//
  } else  (tardeg >=180);{//
    if (tardeg +90 >360){//
      return (tardeg+90)-360;//
    }else {//
      return tardeg+90;//
    }
  }
}
void motor(float angle){//
 int motor_speed_1=100*sin((angle-45)*(180/pi));//
 int motor_speed_2=100*sin((angle-135)*(180/pi));//
 int motor_speed_3=100*sin((angle-225)*(180/pi));//
 int motor_speed_4=100*sin((angle-315)*(180/pi));//

 if (motor_speed_1>=0){//後で変更
  digitalWrite(1,HIGH);//
   analogWrite(1,motor_speed_1);//
 }else {//
  digitalWrite(1,LOW);//
   analogWrite(1,-motor_speed_1);//
 }
 if (motor_speed_2>=0){//後で変更
  digitalWrite(1,HIGH);//
  analogWrite(1,motor_speed_2);//
 }else {
  digitalWrite(1,LOW);//
  analogWrite(1,-motor_speed_2);//
 }
 if (motor_speed_3>=0){//後で変更
  digitalWrite(1,HIGH);//
  analogWrite(1,motor_speed_3);//
 }else {//
  digitalWrite(1,LOW);//
  analogWrite(1,-motor_speed_3);//
 }
 if (motor_speed_4>=0){//後で変更
  digitalWrite(1,HIGH);//
  analogWrite(1,motor_speed_4);//
 }else {//
  digitalWrite(1,LOW);//
  analogWrite(1,-motor_speed_4);//
 }
}
float line (){//
   line1 = 1;//
   line2 = 1;//
   line3 = 1;//
   line4 = 1;//
   line5 = 1;//
   line6 = 1;//
   line7 = 1;//
   line8 = 1;//
   line9 = 1;//
   line10 = 1;//
   line11 = 1;//
   line12 = 1;//
   line13 = 1;//
   line14 = 1;//
   line15 = 1;//
   line16 = 1;//
  int lin[] = {line1,line2,line3,line4,line5,line6,line7,line8,line9,line10,line11,line12,line13,line14,line15,line16};//
  if (line1+line2+line3+line4+line5+line6+line7+line8+line9+line10+line11+line12+line13+line14+line15+line16==1){//
    for (int i=0;i<16; i++ ){//
      if (lin[i]==1){//
        if (i<5){//
        return 270-(22.5*i);//
        } else {//
          if (270-22.5*i>360){//
            return (270-22.5*i)-360;//
          } else {//
            return 270-22.5*i;//
          }
        }
    }
  else {//
      float lin_deg;//
      for (int i=0; i<16; i++){//
          if(lin[i]==1){//
            
       }
      }
    }
  }
}
}
float degfunc2(float b){//
 if (b<90){//
  return b+270;//
 } else {//
  return b-90;//
  }
}
float sonigoal(float x1, float y1,float x2, float y2){//
 return atanf((y2-y1)/(x2-x1));//
}
#include <Arduino.h>//Arduino.hのファイルを読み込む
#include <stdio.h>//stdio.hのファイルを読み込む
#include <math.h>//math.hのファイルを読み込む
#include <time.h>//time.hのファイルを読み込む
#include <Wire.h>//Wire.hのファイルを読み込む
#include "arudino.h"
#include "DCmotor.h"
#define pi 3.1415926535//円周率3.1215926535を定数として定義する。
#define DSR1603_ADDRESS 0x28 // DSR1603のI2Cアドレス
#define E1 9
#define M1 8
int ball1,ball2,ball3,ball4,ball5,ball6,ball7,ball8,ball9,ball10,ball11,ball12,ball13,ball14,ball15,ball16,line1,line2,line3,line4,line5,line6,line7,line8,line9,line10,line11,line12,line13,line14,line15,line16;//ball,lineの関数を代入。
float x1,y1,x2,y2,x3,y3,x4,y4,x5,y5,r,deg;//x,yの値とrの値、角度を数値として表す。
unsigned long time_new, time_old = 0;//新しい時間、古い時間を変数として定義する。
int situ =0; //シチュエーション
int ba[16]={ball1,ball2,ball3,ball4,ball5,ball6,ball7,ball8,ball9,ball10,ball11,ball12,ball13,ball14,ball15,ball16};//ボールセンサーが16個。
float x[]={x1,x2,x3,x4,x5};//xの値をx1~x5として表す。
float y[]={y1,y2,y3,y4,y5};//yの値をy1~y5として表す。
void ba_val();//ボールセンサーの値val
float ball_r();  //rの値を求める
float ball_deg(); //角度を求める
void pin();//pin
void vec(float le1,float le2,float le3,float le4);//le1~le4までの大きさと量を示したベクトル
void vec5(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float x5, float y5);//x1~x5,y1~y5の大きさと量を表した五個のベクトルを空とする。
void swap(int *pa, int *pb);//×pa,×pbの交換の値
void bubble_sort(int n, int a[]);//int nとint aを比較し、条件が合えば、交換する値
void sort();//並び替えの値
float degfunc(float tardeg);//degfuncの値に角度のアーカイブを代入する。
void motor(float angle);//モーターに角度を代入する。
void DCmotor_init(void);
void DCmotor_set(int accel);
void setup(){//準備を始める
byte ADDRESS = 0x28;
byte EULER_REGISTER = 0x1A;
byte ON_flag=0;
Serial.begin(9600);//シリアル通信のビットを9600とする。
for (int i =0; i<16; i++){//iの値を進めていき、16がiより小さくならないまで実行する。
  ba[i]=0;//ボールセンサーの値のiを0とする。

}
}


void loop(){//繰り返し
int A =0;//Aに0を代入する。
r=ball_r();//rにball_rを代入する。
deg=ball_deg();//degにball_degを代入する。

}
  

void DCmotor_init(void){
     pinMode(M1,OUTPUT);
}
void DCmotor_set(int accel){
  int value;
  if(accel>=0){
    value=map(accel,0,100,0,255);
    digitalWrite(M1,HIGH);
    analogWrite(E1,value);
  }
  else{
    value=map(-accel,0,100,0,255);
    digitalWrite(M1,LOW);
    analogWrite(E1,value);
  }
}     
void setup()
{
  DCmotor_init();
  pinMode(14,INPUT_PULLUP);
  pinMode(15,INPUT_PULLUP);
}
void loop()
{
  if(digitalRead(14)==0)
  ON_flag=1;
  if(digitalRead(15)==0)
  ON_flag=0;

  if(ON_flag){
    DCmotor_set(-60);
  }
  else{
    DCmotor_set(0);
  }
}

void setup(){//準備を始める。
  Wire.begin();//
  Serial.begin(9600);//シリアル通信のビットを9600とする。
}

void loop(){
  Wire.beginTransmission(DSR1603_ADDRESS);
  Wire.write(0X00);//レジスタ0×00を指定
  Wire.endTransmission(false);
  Wire.requestFrom(DSR1603_ADDRESS,6,true);
  int16_t x=Wire.read() | (Wire.read() <<8);
  int16_t y=Wire.read() | (Wire.read() <<8);
  int16_t z=Wire.read() | (Wire.read() <<8);
  Serial.print("x:");
  Serial.print(x);
  Serial.print(",y:");
  Serial.print(y);
  Serial.print(",z:");
  Serial.print(z);
  delay(100);
}


int merge(byte low, byte high){
  int result = low | (high << 8);
  if(result > 32767){
    result -=65536;
  }
  return result;
}

void writeToBNO(byte reg, byte val, int dly){
  Wire.beginTransmission(ADDRESS);
  Wire.write(reg);
  Wire.write(val);
  Wire.endTransmission(false);
  delay(dly);
}

void initBNO(){
  Wire.beginTransmission(ADDRESS);
  Wire.write(0x00);
  Wire.endTransmission(false);
  Wire.requestFrom(ADDRESS,1);
  if(Wire.read()==0xa0){
    Serial.println("BNO055 found.");
    writeToBNO(0x3d,0x00,80);//operating mode = confing mode
    writeToBNO(0x3f,0x20,1000);//sys_trigger=rst_sys
    writeToBNO(0x3e,0x00,80);//pwr_mode=normal mode
    writeToBNO(0x3f,0x80,1000);//sys trigger=clk_sel ex_osc
    writeToBNO(0x3d,0x0c,80);//operating mode=nodf
  }else{
    while(1){
      Serial.println("BNO055 not found..");
      delay(1000);
    }
  }
} 


void setup(){
  //put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin(9600);
  initBNO();
}

void loop(){
  //put your main code here, to run repeatedly:
  int euler[6];

  Wire.beginTransmission(ADDRESS);
  Wire.write(EULER_REGISTER);
  Wire.endTransmission(false);

  Wire.requestFrom(ADDRESS, 6);
  byte buffer[6];
  Wire.readBytes(buffer, 6);

  euler[0] = merge(buffer[0], buffer[1]);
  euler[1] = merge(buffer[2], buffer[2]);
  euler[2] = merge(buffer[4], buffer[5]);

  float yaw =float(euler[0])/16.0;
  float roll =float(euler[1])/16.0;
  float pitch =float(euler[2])/16.0;

  Serial.print("yaw =");
  Serial.print(yaw);
  Serial.print("roll =");
  Serial.print(roll);
  Serial.print("pitch =");
  Serial.print(pitch);
  delay(50);
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
void pin(){//pinの値
  pinMode(8,OUTPUT);//Ardiunoマイコンの8ピンは出力である。
}
void ba_val(){//ボールセンサーの値のval
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
    for (int i=0; i<=15; i++){//iの値を進めていき、15がi以上にならないまで実行する。
       if(val[i]==1){//もしvalの値が1ならば、
        ba[i]=ba[i]+1;//ボールセンサーの値を＋1する。
       } else//そうじゃなければ
       {
        ba[i]=ba[i];//ボールセンサーの値をそのままにする。
       }
    }
  }
  time_old = time_new;//古い時間に新しい時間を代入する。(時間833に合わせる。)
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
    for (j = 1; j < n - i; j++) {//jが1から進んでいき、nからiを引いた値がjより小さくならないまで実行する。
      if (a[j] < a[j - 1]) {//もしaに[j-1]を代入した値が、aにjを代入した値より大きければ、
        swap(&a[j], &a[j - 1]);//aに[j]を代入した値と、aに[j-1]を代入した値を交換する。
      }
    }
  }
}
void sort(){//座標を極座標から直交座標に変換
  bubble_sort(16,ba);//16個のボールセンサーの値を比較し、条件が合えば、一部交換。
  for (int n =15; n>10; n--){//nを15まで進める。その値が10よりも大きくなるまで実行。
   if (ba[n]==ball1){//90//もしボールセンサーの値nがボールセンサー1と値が等しければ。
      x[15-n]=ball1;//x[15-n]にボールセンサ1の値を代入する。
      y[15-n]=0;//y[15-n]の値を0とする。
    } else if (ba[n]==ball2){//67.5　もしボールセンサーの値nがボールセンサー2の値と等しくなければ、
      x[15-n]=0.3826834*ball2;//x[15-n]にボールセンサー2に0.3826834をかけた値を代入する。
      y[15-n]=0.9238795*ball2;//y[15-n]にボールセンサー2に0.9238795をかけた値を代入する。
    }else if (ba[n]==ball3){//45　もしボールセンサーの値nがボールセンサー3の値と等しくなければ、
      x[15-n]=0.7071067*ball3;//x[15-n]にボールセンサー3に0.7071067をかけた値を代入する。
      y[15-n]=0.7071067*ball3;//y[15-n]にボールセンサー3に0.7071067をかけた値を代入する。
    }else if (ba[n]==ball4){//22.5　もしボールセンサーの値nがボールセンサー4の値と等しくなければ、
      x[15-n]=0.92387953*ball4;//x[15-n]にボールセンサー4に0.92387953をかけた値を代入する。
      y[15-n]=0.38268343*ball4;//y[15-n]にボールセンサー4に0.38268343をかけた値を代入する。
    }else if (ba[n]==ball5){//0　もしボールセンサーの値nがボールセンサー5の値と等しくなければ、
      x[15-n]=ball5;//x[15-n]にボールセンサー5の値を代入する。
      y[15-n]=0;//y[15-n]の数を0から進めていく。
    }else if (ba[n]==ball6){//337.5　もしボールセンサーの値nがボールセンサー6の値と等しくなければ、
      x[15-n]=0.9238795*ball6;//x[15-n]にボールセンサー6に0.9238795をかけた値を代入する。
      y[15-n]=-0.3826834*ball6;//y[15-n]にボールセンサー6に-0.3826834をかけた値を代入する。
    }else if (ba[n]==ball7){//315　もしボールセンサーの値nがボールセンサー7の値と等しくなければ、
      x[15-n]=0.7071067*ball7;//x[15-n]にボールセンサー7に0.7071067をかけた値を代入する。
      y[15-n]=-0.7071067*ball7;//y[15-n]にボールセンサー7に-0.7071067をかけた値を代入する。
    }else if (ba[n]==ball8){//292.5　もしボールセンサーの値nがボールセンサー8の値と等しくなければ、
      x[15-n]=0.38268343*ball8;//x[15-n]にボールセンサー8に0.38268343をかけた値を代入する。
      y[15-n]=-0.9238795*ball8;//y[15-n]にボールセンサー8に-0.9238795をかけた値を代入する。
    }else if (ba[n]==ball9){//270　もしボールセンサーの値nがボールセンサー9の値と等しくなければ、
      x[15-n]=0;//x[15-n]の数を0から進めていく。
      y[15-n]=-1*ball9;//y[15-n]にボールセンサー9に-1をかけた値を代入する。
    }else if (ba[n]==ball10){//247.5　もしボールセンサーの値nがボールセンサー10の値と等しくなければ、
      x[15-n]=-0.3826834*ball10;//x[15-n]にボールセンサー10に-0.3826834をかけた値を代入する。
      y[15-n]=-0.9238795*ball10;//y[15-n]にボールセンサー10に-0.9238795をかけた値を代入する。
    }else if  (ba[n]==ball11){//225　もしボールセンサーの値がボールセンサー11の値と等しくなければ、
      x[15-n]=-0.7071067*ball11;//x[15-n]にボールセンサー11に-0.7071067をかけた値を代入する。
      y[15-n]=-0.7071067*ball11;//y[15-n]にボールセンサー11に-0.7071067をかけた値を代入する・
    }else if (ba[n]==ball12){//202.5　もしボールセンサーの値nがボールセンサー12の値と等しくなければ、
      x[15-n]=-0.9238795*ball12;//x[15-n]にボールセンサー12に-0.9238795をかけた値を代入する。
      y[15-n]=-0.3826834*ball12;//y[15-n]にボールセンサー12に-0.3826834をかけた値を代入する。
    }else if (ba[n]==ball13){//180　もしボールセンサーの値nがボールセンサー13の値と等しくなければ、
      x[15-n]=-1*ball13;//x[15-n]にボールセンサー13に-1をかけた値を代入する。
      y[15-n]=0;//y[15-n]の数を0から進めていく。
    }else if (ba[n]==ball14){//157.5　もしボールセンサーの値nがボールセンサー14の値と等しくなければ、
      x[15-n]=-0.9238795*ball14;//x[15-n]にボールセンサー14に-0.9238795をかけた値を代入する。
      y[15-n]=0.3826834*ball14;//y[15-n]にボールセンサー14に0.3826834をかけた値を代入する。
    }else if (ba[n]==ball15){//135　もしボールセンサーの値nがボールセンサー15の値と等しくなければ、
      x[15-n]=-0.7071067*ball15;//x[15-n]にボールセンサー15に-0.7071067をかけた値を代入する。
      y[15-n]=0.7071067*ball15;//y[15-n]にボールセンサー15に0.7071067をかけた値を代入する。
    }else if (ba[n]==ball16){//112.5　もしボールセンサーの値nがボールセンサー16の値と等しくなければ、
      x[15-n]=-0.3826834*ball16;//x[15-n]にボールセンサー16に-0.3826834をかけた値を代入する。
      y[15-n]=0.9238795*ball16;//y[15-n]にボールセンサー16に0.9238795をかけた値を代入する。
    }
  }
 
}
float ball_r(){//ボールセンサーの値rを求める。
  ba_val();//ボールセンサーの値val
  sort();//値の並び替え
  vec5(x1,y1,x2,y2,x3,y3,x4,y4,x5,y5);//5個のベクトルにx1~x5とy1~y5に代入する。
  return sqrtf(x1*x1+y1*y1);//平方根(x1×x1+y1×y1)を返す。(元の値に戻す。)
}
float ball_deg(){//角度を求める
    ba_val();//ボールセンサーの値val
    sort();//値の並び替え
    vec5(x1,y1,x2,y2,x3,y3,x4,y4,x5,y5);//5個のベクトルにx1~x5とy1~y5に代入する。
    float ret = atan2f(x1,y1);//変数retにx1とy1から角度を求めたものを代入する。
    return (180/pi)* ret;//180から円周率を割った値に変数retをかける。
}
float ball_deg(){//角度を求める
    ba_val();//ボールセンサーの値val
    sort();//値の並び替え
    vec5(x1,y1,x2,y2,x3,y3,x4,y4,x5,y5);//5個のベクトルにx1~x5とy1~y5を代入する。
    float ret = atan2f(x1,y1);//変数retにx1とy1から角度を求めたものを代入する。
    float deg_old= (180/pi)* ret;//変数deg_oldに180から円周率を割り、変数retとかけた値を代入する。
  return degfunc2(deg_old);//degfunc2にdeg_oldの値を代入し、値を返す。
}
float degfunc(float tardeg){//degfuncに角度のアーカイブを代入する。
  if (tardeg <180) {//もし角度のアーカイブの値が180よりも小さければ、
    return 2*tardeg;//角度のアーカイブに2をかける値を返す。
  } else  (tardeg >=180);{//180よりも角度のアーカイブが大きければ、
    if (tardeg +90 >360){//もし角度のアーカイブに90を足した値が、360より大きければ、
      return (tardeg+90)-360;//角度のアーカイブに90を足した値から360を引き、値を返す。
    }else {//そうじゃなければ
      return tardeg+90;//角度のアーカイブに90を足す。
    }
  }
}
void motor(float angle){//モーターに角度を代入する。
 int motor_speed_1=100*sin((angle-45)*(180/pi));//モーターの速さ1に角度から45引いた値に180から円周率を割った値をかけ、それに100をかけた値を代入する。
 int motor_speed_2=100*sin((angle-135)*(180/pi));//モーターの速さ2に角度から135引いた値に180から円周率を割った値をかけ、それに100をかけた値を代入する。
 int motor_speed_3=100*sin((angle-225)*(180/pi));//モーターの速さ3に角度から225引いた値に180から円周率を割った値をかけ、それに100をかけた値を代入する。
 int motor_speed_4=100*sin((angle-315)*(180/pi));//モーターの速さ4に角度から315引いた値に180から円周率を割った値をかけ、それに100をかけた値を代入する。

 if (motor_speed_1>=0){//後で変更 モータースピード1が0以上ならば
  digitalWrite(1,HIGH);//8V出力する。
  analogWrite(1,motor_speed_1);//0V制御する。
 }else {//そうじゃなければ
  digitalWrite(1,LOW);//0V出力する。
  analogWrite(1,-motor_speed_1);//8V制御する。
 }
 if (motor_speed_2>=0){//後で変更　モータースピード2が0以上ならば
  digitalWrite(1,HIGH);//8V出力する。
  analogWrite(1,motor_speed_2);//0V制御する。
 }else {//そうじゃなければ
  digitalWrite(1,LOW);//0V出力する。
  analogWrite(1,-motor_speed_2);//8V制御する。
 }
 if (motor_speed_3>=0){//後で変更　モータースピード3が0以上ならば
  digitalWrite(1,HIGH);//8V出力する。
  analogWrite(1,motor_speed_3);//0V制御する。
 }else {//そうじゃなければ
  digitalWrite(1,LOW);//0V出力する。
  analogWrite(1,-motor_speed_3);//8V制御する。
 }
 if (motor_speed_4>=0){//後で変更　モータースピード4が0以上ならば
  digitalWrite(1,HIGH);//8V出力する。
  analogWrite(1,motor_speed_4);//0V制御する。
 }else {//そうじゃなければ
  digitalWrite(1,LOW);//0V出力する。
  analogWrite(1,-motor_speed_4);//8V制御する。
 }
}
float line (){//lineの値
   line1 = 1;//line1の値を1とする。
   line2 = 1;//line2の値を1とする。
   line3 = 1;//line3の値を1とする。
   line4 = 1;//line4の値を1とする。
   line5 = 1;//line5の値を1とする。
   line6 = 1;//line6の値を1とする。
   line7 = 1;//line7の値を1とする。
   line8 = 1;//line8の値を1とする。
   line9 = 1;//line9の値を1とする。
   line10 = 1;//line10の値を1とする。
   line11 = 1;//line11の値を1とする。
   line12 = 1;//line12の値を1とする。
   line13 = 1;//line13の値を1とする。
   line14 = 1;//line14の値を1とする。
   line15 = 1;//line15の値を1とする。
   line16 = 1;//line16の値を1とする。
  int lin[] = {line1,line2,line3,line4,line5,line6,line7,line8,line9,line10,line11,line12,line13,line14,line15,line16};//int型linにline1~line16までの値を代入する。
  if (line1+line2+line3+line4+line5+line6+line7+line8+line9+line10+line11+line12+line13+line14+line15+line16==1){//もしline1~line16の値を足した値が1に等しければ
    for (int i=0;i<16; i++ ){//iの値を0とし、値を進めていき、16がiより大きくならないまで実行する。
      if (lin[i]==1){//もしlinにiを代入したとき、1と等しければ、
        if (i<5){//もし5がiより大きければ
        return 270-(22.5*i);//270から22.5にiをかけた値を引き、値を返す。
        } else {//そうじゃなければ
          if (270-22.5*i>360){//もし270から22.5にiをかけた値を引いた値が、360より大きければ、
            return (270-22.5*i)-360;//270から22.5にiをかけた値を引き、そこから360を引いた値を返す。
          } else {//そうじゃなければ
            return 270-22.5*i;//270から22.5にiをかけた値を引く。
          }
        }
    }
  else {//そうじゃなければ
      float lin_deg;//linの角度
      for (int i=0; i<16; i++){//iの値を進めていき、16がiより大きくならないまで実行する。
          if(lin[i]==1){//もしlinにiを代入した値が1と等しければ
            
       }
      }
    }
  }
}
}
float degfunc2(float b){//degfunc2にbを代入する。
 if (b<90){//もし90よりbが大きければ、
  return b+270;//bに270を足し、
 } else {//そうじゃなければ
  return b-90;//bから90を引く。
  }
}
float sonicgoal(float x1, float y1,float x2, float y2){//sonicgoalにx1、y1、x2、y2を代入する。
 return atanf((y2-y1)/(x2-x1));//y2-y1からx2-x1を割った値から角度を求め、値を返す。
}
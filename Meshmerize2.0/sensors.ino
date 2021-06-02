void sensor_read()
{
  s[0] = digitalRead(A3);
  s[1] = digitalRead(A2);
  s[2] = digitalRead(A4);
  s[3] = digitalRead(A1);
  s[4] = digitalRead(A5);
  s[5] = digitalRead(A0);
  s[6] = digitalRead(3);
  s[7] = digitalRead(2);
  if(analogRead(A8)>900) {d0=1;}
  else {d0=0;}
  if(analogRead(A9)>900) {d1=1;}
  else {d1=0;}
  if(analogRead(A10)>900) {d2=1;}
  else {d2=0;}
  if(analogRead(A11)>900) {d3=1;}
  else {d3=0;}
//  Serial.print(analogRead(A8));
//  Serial.print(" ");
//  Serial.print(analogRead(A9));
//  Serial.print(" ");
//  Serial.print(analogRead(A10));
//  Serial.print(" ");
//  Serial.print(analogRead(A11));
//  Serial.print(" ");
  
  s_sum = s[0] + s[1] + s[2] + s[3] + s[4] + s[5] + s[6] + s[7];
  l_sum=s[0]+s[1];
  r_sum=s[6]+s[7];
  m_sum=s[2]+s[3]+s[4]+s[5];//m_sum=s[3]+s[4];
  v_sum=s[3]+s[4];
  d_sum=d1+d2;
}

void disp_val()
{
  Serial.print(d0);
  Serial.print(" ");
  Serial.print(d1);
  Serial.print(" ");
  Serial.print(d2);
  Serial.print(" ");
  Serial.print(d3);
  Serial.print("\t ");
  Serial.print(s[0]);
  Serial.print(s[1]);
  Serial.print(s[2]);
  Serial.print(s[3]);
  Serial.print(s[4]);
  Serial.print(s[5]);
  Serial.print(s[6]);
  Serial.println(s[7]);
//  Serial.println(err);
}

void PID_cal()
{
  err = (s[0] * (-3.5) + s[1] * (-2.5) + s[2] * (-1.5) + s[3] * (-0.5) + s[4] * (0.5) + s[5] * (1.5) + s[6] * (2.5) + s[7] * (3.5))/s_sum;
  PID = Kp*err + Kd*(err-p_err);
  p_err=err;
}

void motor_speed()
{
  RMS = basespd - PID;
  LMS = basespd + PID;
  if (RMS > 255)
  {
    RMS = 255;
  }
  if (RMS < 0)
  {
    RMS = 0;
  }
  if (LMS > 255)
  {
    LMS = 255;
  }
  if (LMS < 0)
  {
    LMS = 0;
  }
}

void linefollow()
{
  PID_cal();
  motor_speed();
  analogWrite(RP, RMS * r_factor);
  analogWrite(LP, LMS);
  digitalWrite(RD, 0);
  digitalWrite(LD, 0);
}

void fwd(int d)
{
  analogWrite(RP, basespd);
  analogWrite(LP, basespd);
  digitalWrite(RD, 0);
  digitalWrite(LD, 0);
  delay(d);
}

void halt(long int d)
{
  analogWrite(RP, 0);
  analogWrite(LP, 0);
  digitalWrite(RD, 1);
  digitalWrite(LD, 1);
  delay(d);
}

void back(long int d)
{
  analogWrite(RP, basespd);
  analogWrite(LP, basespd);
  digitalWrite(RD, 1);
  digitalWrite(LD, 1);
  delay(d);  
}

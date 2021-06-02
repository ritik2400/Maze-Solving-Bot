void turns(char S)
{
  switch(S)
  {
    case 'a':// for Right Hand Rule
    digitalWrite(45,1);
    corr_fact = 255;
    dir+=(-0.5);
    right_135();
    digitalWrite(45,0);
    break;
    
    case 's':// for Left Hand Rule
    digitalWrite(45,1);
    corr_fact = 255;
    dir+=(0.5);
    left_135();
    digitalWrite(45,0);
    break;
    
    case 'r':
    digitalWrite(45,1);
    corr_fact = 255;
    dir+=(-0.5);
    sensor_read();
    while(!s[4])
    {
//      Serial.print("linefollow = ");
//      disp_val();
      linefollow();
      sensor_read();
    }
    digitalWrite(45,0);
    break;
    
    case 'l':
    digitalWrite(45,1);
    corr_fact = 255;
    dir+=(0.5);
//    left();
    sensor_read();
    while(!s[3])
    {
//      Serial.print("linefollow = ");
//      disp_val();
      linefollow();
      sensor_read();
    }
    digitalWrite(45,0);
    break;
    
    case 'E':
    digitalWrite(53,1);
    corr_fact = 0;
    fwd(400);
    deriving(0,djiks(0,endpoint));
    realpath=actualpath;
    EEPROM.put(0,actualpath);
//    junc_format();
//    for(int k=0;k<=j;k++)
//    {
//      for(int i=0;i<point[k].conn_count;i++)
//      {
//      Serial.print(k);
//      Serial.print("-");
//      Serial.print(i);
//      Serial.print(" = ");
//      Serial.println(point[k].entry_dir[i]);
//      }
//    }
    while(!digitalRead(8))
    {
      halt(0);
    }
    break;
    
    case 'O':
    break;
    
    case 'R':
    digitalWrite(13,1);
    corr_fact = 0;
    fwd(120);
    dir+=(-1);
    right();
    digitalWrite(13,0);
    break;
    
    case 'L':
    digitalWrite(13,1);
    corr_fact = 0;
    fwd(120);
    dir+=(1);
    left();
    digitalWrite(13,0);
    break;
    
    case 'S'://fwd delay changed to 120,so that, millis coords can be set more accurately for 24cm lines or, for conditions where prev turn was Straight (S).
    digitalWrite(13,1);
    corr_fact = 0;
    fwd(110);
    digitalWrite(13,0);
    break;
    
    case 'U':
    corr_fact = 0;
    dir+=(-2);
    fwd(100);
    analogWrite(RP, turnspd*r_factor);
    analogWrite(LP, turnspd);
    digitalWrite(RD, 0);
    digitalWrite(LD, 1);
    delay(1300);
    sensor_read();
    while(!s[3])
    {
      analogWrite(RP, turnspd*r_factor);
      analogWrite(LP, turnspd);
      digitalWrite(RD, 0);
      digitalWrite(LD, 1);      
      sensor_read();
    }
//    left();
    break;

    default:
    halt(0);
  }
  halt(50);
  curr_dir(dir);
//  Serial.print("dir = ");
//  Serial.println(dir);
  p_err=0;
}

void left_135()
{
  do
  {
    analogWrite(RP, turnspd*r_factor);
    analogWrite(LP, 0);
    digitalWrite(RD, 0);
    digitalWrite(LD, 1);
    sensor_read();
  }while(!s[4]);
//  while(d_sum == 0)
//  {
//    analogWrite(RP, turnspd*r_factor);
//    analogWrite(LP, turnspd);
//    digitalWrite(RD, 0);
//    digitalWrite(LD, 1);
//    sensor_read();     
//  }  
}

void left()
{
  do
  {
    analogWrite(RP, turnspd*r_factor);
    analogWrite(LP, turnspd);
    digitalWrite(RD, LOW);
    digitalWrite(LD, HIGH);
    sensor_read();
  }while(!s[0]);
  
  do
  {
    analogWrite(RP, turnspd*r_factor);
    analogWrite(LP, turnspd);
    digitalWrite(RD, LOW);
    digitalWrite(LD, HIGH);
    sensor_read();
  }while(!s[4] || !s[3]);
//  while(s[2])//when turning of + junction, more than 3 sensors get high which gives us another junction......but if there is 12V supply then chances of happening this is very low, so we may remove this condition afterwards
//  {
//    analogWrite(RP, turnspd*r_factor);
//    analogWrite(LP, turnspd);
//    digitalWrite(RD, 1);
//    digitalWrite(LD, 0);
//    sensor_read();     
//  }
//  while(d_sum != 0)
//  {
//    analogWrite(RP, turnspd*r_factor);
//    analogWrite(LP, turnspd);
//    digitalWrite(RD, 0);
//    digitalWrite(LD, 1);
//    sensor_read();     
//  }
}

void right_135()
{
  do
  {
    analogWrite(RP, 0);
    analogWrite(LP, turnspd);
    digitalWrite(RD, 1);
    digitalWrite(LD, 0);
    sensor_read();
  }while(!s[3]);
//  while(d_sum == 0)
//  {
//    analogWrite(RP, turnspd*r_factor);
//    analogWrite(LP, turnspd);
//    digitalWrite(RD, 1);
//    digitalWrite(LD, 0);
//    sensor_read();     
//  }  
}

void right()
{
  digitalWrite(13,1);
  do
  {
    analogWrite(RP, turnspd*r_factor);
    analogWrite(LP, turnspd);
    digitalWrite(RD, 1);
    digitalWrite(LD, 0);
    sensor_read();
  }while(!s[7]);
  
  do
  {
    analogWrite(RP, turnspd*r_factor);
    analogWrite(LP, turnspd);
    digitalWrite(RD, 1);
    digitalWrite(LD, 0);
    sensor_read();
  }while(!s[4] || !s[3]);
//  while(s[5])
//  {
//    analogWrite(RP, turnspd*r_factor);
//    analogWrite(LP, turnspd);
//    digitalWrite(RD, 1);
//    digitalWrite(LD, 0);
//    sensor_read();     
//  }
//  while(d_sum != 0)
//  {
////    linefollow();//test with this
//    analogWrite(RP, turnspd*r_factor);
//    analogWrite(LP, turnspd);
//    digitalWrite(RD, 1);
//    digitalWrite(LD, 0);
//    sensor_read();     
//  }
}

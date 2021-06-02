bool junc_det_RHR()
{
  mid_time=millis();
  junc:
//  disp_val();
  type=0;
  if(((!d0 && d_sum>0 && d3) || (d0 && d_sum>0 && !d3)) && !p_type)
  {
    l_type=1;    
  }

  if(d0 && d_sum>0 && d3)
  {
    p_type=1;
    l_type=0;
  }
  if(s_sum==0)
  {
    state='U';
//    Serial.println("U");
    return 1;
  }
  else if(s_sum == 8)
  {
    type=2;
    do
    {
      plus:
      fwd(0);
      sensor_read();
//      Serial.print("s_sum = ");
//      disp_val();
      if(d0 && d1 && d2 && d3)
      {
        state = 'E';
//        Serial.println("E");
        return 1;
      }
    }while(s_sum>3);
    halt(50);
    sensor_read();
//    disp_val();
    if(m_sum>0)
    {
//      Serial.println("+R");
      type++;
    }
    else
    {
//      Serial.println("TR");
    }
    state='R';
    t_glo_type=1;
    p_type=0;
    return 1;
  }
  else if(s_sum>3 && s_sum<8 && l_type)
  {
    midtime:
    unsigned int junc_count=0;
    bool write_flag=0;
    type=1;
    sensor_read();
    do
    {
      if(r_sum>0 && junc_count<50)
      {
        state='R';
        write_flag=1;
//        Serial.println("LR");
      }
      else if(l_sum>0 && junc_count<50)
      {
        t_glo_type=1;
        state='L';
        write_flag=1;
//        Serial.println("LL");
      }

      if(d3 && write_flag && junc_count<50)
      {
        type = 1.5;
        state = 'r';
//        Serial.println("Yr");
        junc_count++;
      }
      else if(d0 && write_flag && junc_count<50)
      {
//        Serial.println("YR");
        type = 1.5;
        junc_count++;
      }

//      digitalWrite(13,1);
      fwd(0);
      sensor_read();
//      Serial.print("s_sum = ");
//      disp_val();
      if(s_sum==8)
      {
//        Serial.print("goto plus = ");
        type=2;
        goto plus;
      }
    }while(s_sum>3);
    while(d0 || d3)
    {
      fwd(0);
      sensor_read();
//      Serial.print("2nd loop");
//      disp_val();
    }
    halt(50);
    sensor_read();
//    disp_val();
    if(m_sum>0 && type!=1.5)
    {
      if(state == 'L')
      {
        state = 'S';
//        Serial.println("TS");
      }
      else
      {
//        Serial.println("TR");
      }
      type++;
    }
///    Serial.println(junc_count);
    l_type=0;
    p_type=0;
    junc_count=0;
    return 1;
  }
  else if(!p_type && (d0 && d3) && m_sum>2 && (d_sum == 0))
  {
    YA:
    type = 1.5;
    state = 'a';
//    Serial.println("Ya");
    do
    {
      fwd(0);
      sensor_read();
//      disp_val();
      if(s_sum == 8)
      {
        type=2;
//        Serial.println("node_det_RHR()");
        goto plus;
      }
      if(((!d0 && d_sum>0 && d3) || (d0 && d_sum>0 && !d3)) && !p_type)
      {
        goto junc;    
      }
  
      else if(d0 && d_sum>0 && d3)
      {
        goto junc;
      }
//      Serial.print("v_sum = ");
    }while(v_sum>0 && state == 'a');
    
    halt(50);
    l_type=0;
    p_type=0;
    return 1;

  }
  else if((v_sum>0) && (d0 || d3) && (d_sum==0) && !l_type && !p_type)
  {
    type=0.5;
    if(d0)
    {
      state = 'l';
//      Serial.println("Vl");
    }
    else if(d3)
    {
      state = 'r';
//      Serial.println("Vr");
    }
    do
    {
      fwd(0);
      sensor_read();
//      disp_val();
      if((v_sum>0) && (d0 && d3) && (d_sum==0) && type!=1.5)//type!=1.5 is not really required but it is kept just for confirmation, so, if needed can be removed.
      {
        goto YA;
      }
      else if(s_sum == 8)
      {
        type=2;
//        Serial.println("node_det_RHR()");
        goto plus;
      }
     if(((!d0 && d_sum>0 && d3) || (d0 && d_sum>0 && !d3)) && !p_type)
      {
        goto junc;    
      }
  
      else if(d0 && d_sum>0 && d3)
      {
        goto junc;
      }
   
//      Serial.println("d_all_sum = ");
    }while(((d0 + d1 + d2 + d3) != 0) && state != 'a');
    halt(50);
    l_type=0;
    p_type=0;
    return 1;
  }
  else if(s_sum>3 && s_sum<8 && ((mid_time-start_time)<500))
  {
    goto midtime;
  }
  else
  {
    return 0;
  }
}



bool junc_det_LHR()
{
  junc:
//  disp_val();
  type=0;
  if(((!d0 && d_sum>0 && d3) || (d0 && d_sum>0 && !d3)) && !p_type)
  {
    l_type=1;    
  }

  if(d0 && d_sum>0 && d3)
  {
    p_type=1;
    l_type=0;
  }
  if(s_sum==0)
  {
    state='U';
//    Serial.println("U");
    return 1;
  }
  else if(s_sum == 8)
  {
    type=2;
    do
    {
      plus:
      fwd(0);
      sensor_read();
//      Serial.print("s_sum = ");
//      disp_val();
      if(d0 && d1 && d2 && d3)
      {
        state = 'E';
//        Serial.println("E");
        return 1;
      }
    }while(s_sum>3);
    halt(50);
    sensor_read();
//    disp_val();
    if(m_sum>0)
    {
//      Serial.println("+L");
      type++;
    }
    else
    {
//      Serial.println("TL");
    }
    state='L';
    p_type=0;
    return 1;
  }
  else if(s_sum>3 && s_sum<8 && l_type)
  {
    unsigned int junc_count=0;
    bool write_flag=0;
    type=1;
    sensor_read();
    do
    {
      if(l_sum>0 && junc_count<50)
      {
        state='L';
        write_flag=1;
//        Serial.println("LL");
      }
      else if(r_sum>0 && junc_count<50)
      {
        t_glo_type=1;
        state='R';
        write_flag=1;
//        Serial.println("LR");
      }

      if(d0 && write_flag && junc_count<50)
      {
        type = 1.5;
        state = 'l';
        junc_count++;
//        Serial.println("Yl");
      }
      else if(d3 && write_flag && junc_count<50)
      {
//        Serial.println("YL");
        type = 1.5;
        junc_count++;
      }

      fwd(0);
      sensor_read();
//      Serial.print("s_sum = ");
//      disp_val();
      if(s_sum==8)
      {
//        Serial.print("goto plus = ");
        type=2;
        goto plus;
      }
    }while(s_sum>3);
    while(d0 || d3)
    {
      fwd(0);
      sensor_read();
//      Serial.print("2nd loop");
//      disp_val();
    }
    halt(50);
    sensor_read();
//    disp_val();
    if(m_sum>0 && type!=1.5)
    {
      if(state == 'R')
      {
        state = 'S';
//        Serial.println("TS");
      }
      else
      {
//        Serial.println("TL");
      }
      type++;
    }
    junc_count=0;
    l_type=0;
    p_type=0;
    return 1;
  }
  else if(!p_type && (d0 && d3) && m_sum>2 && (d_sum == 0))
  {
    YA:
    type = 1.5;
    state = 's';
//    Serial.println("Ys");
    do
    {
      fwd(0);
      sensor_read();
//      disp_val();
      if(s_sum == 8)
      {
        type=2;
//        Serial.println("node_det_RHR()");
        goto plus;
      }
      if(((!d0 && d_sum>0 && d3) || (d0 && d_sum>0 && !d3)) && !p_type)
      {
        goto junc;    
      }
  
      else if(d0 && d_sum>0 && d3)
      {
        goto junc;
      }
//      Serial.print("v_sum = ");
    }while(v_sum>0 && state == 's');
    
    halt(50);
    l_type=0;
    p_type=0;
    return 1;

  }
  else if((v_sum>0) && (d0 || d3) && (d_sum==0) && !l_type && !p_type)
  {
    type=0.5;
//    if(d0 && d_sum==0 && d3)
//    {
//      type=1.5;
//      state = 'a';// Use 'a' for Right Hand Rule......and.....'s' for Left Hand Rule
//      Serial.println("Ya");
//    }
    if(d0)
    {
      state = 'l';
//      Serial.println("Vl");
    }
    else if(d3)
    {
      state = 'r';
//      Serial.println("Vr");
    }
//    while(v_sum>0)
    do
    {
      fwd(0);
      sensor_read();
//      disp_val();
      if((v_sum>0) && (d0 && d3) && (d_sum==0) && type!=1.5)//type!=1.5 is not really required but it is kept just for confirmation, so, if needed can be removed.
      {
        goto YA;
      }
      else if(s_sum == 8)
      {
        type=2;
//        Serial.println("node_det_RHR()");
        goto plus;
      }
     if(((!d0 && d_sum>0 && d3) || (d0 && d_sum>0 && !d3)) && !p_type)
      {
        goto junc;    
      }
  
      else if(d0 && d_sum>0 && d3)
      {
        goto junc;
      }
   
//      Serial.println("d_all_sum = ");
    }while(((d0 + d1 + d2 + d3) != 0) && state != 's');
    halt(50);
    l_type=0;
    p_type=0;
    return 1;
  }  
  else
  {
    return 0;
  }
}

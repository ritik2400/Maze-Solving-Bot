void CheckPoint()
{
  byte cpj, i;
  cpj = j_count;
  while(!unexplored.isEmpty())
  {
    i = unexplored.pop();
//    Serial.println(i);
//    Serial.println(point[i].explored);
//    Serial.println(point[i].type);
    if (point[i].explored < point[i].type) //same format can be followed when returning back to normal code of dry run
    {
//      Serial.println("check_run()");
      check_run(i);
      turn_to_explore(i);
      j_count++;
//      Serial.print("j_count = ");
//      Serial.print(j_count);
      n[j_count] = i;
//          Serial.print("n[j_count] = ");
//          Serial.println(n[j_count]);
      start_time = millis();

      while (1)
      {
        digitalWrite(47,1);
        sensor_read();
        if(junc_det_RHR())
        {
          end_time = millis();
          
          rev_corr_factor(state);
          dist = (end_time - start_time) + corr_fact + rev_corr_fact;
          set_dist();
          j_count++;
          node_write(point[n[j_count-1]].cordx, point[n[j_count-1]].cordy); //type, turn, cordx, cordy, explored ...written
          j++;
           n[j_count] = j;
    Serial.print("cordx = ");
    Serial.print(point[n[j_count]].cordx);    
    Serial.print("\tcordy = ");
    Serial.println(point[n[j_count]].cordy);    
//          Serial.print("j_count = ");
//          Serial.println(j_count);
//          Serial.print("n[j_count] = ");
//          Serial.println(n[j_count]);
          norm_conn(j_count);
          if (check_repeat(j_count))
          {
            j--;
            connections(n[j_count], n[(j_count - 1)], 0);
            point[n[j_count - 1]].conn_count--;
            point[j + 1].conn_count--;
            connections(n[(j_count - 1)], n[j_count], 1);

//            Serial.print("n[j_count] = ");
//            Serial.print(n[j_count]);
//            Serial.print("\texplored = ");
//            Serial.println(point[n[j_count]].explored);
  //            Serial.print("n[j_count] = ");
//            Serial.print(n[j_count]);
//            Serial.print("\ttype = ");
//            Serial.print(point[n[j_count]].type);
            if (point[n[j_count]].explored > point[n[j_count]].type) //this will be true if bot is stuck in loop
            {
              unexplored_stack();
              digitalWrite(47,0);
              break;
              //          retrace();
            }
          }
//          Serial.print("cordx = ");
//          Serial.print(point[n[j_count]].cordx);    
//          Serial.print("\tcordy = ");
//          Serial.println(point[n[j_count]].cordy);    
          turns(state);
          start_time = millis();
        }
        else
        {
          linefollow();
        }
      }
    
    }

  }
//  Serial.println("unexplored  is empty!!");   
}

void turn_to_explore(int pt)
{
  int i, bef_turn, aft_turn;
  float assu_dir;
  for (i = 0; i < j_count; i++)
  {
    if (n[i] == pt)
    {
      break;
    }
  }
  for (bef_turn = 0; bef_turn < point[n[i]].conn_count; bef_turn++)
  {
    if (point[n[i]].conn[bef_turn] == n[i - 1])
    {
      break;
    }
  }
//  Serial.print("n[i] = ");
//  Serial.print(n[i]);
//  Serial.print(" ");
//  Serial.print(point[n[i]].type);
//  Serial.print(" ");
//  Serial.print(point[n[i]].turn);
//  Serial.print(" ");
//  Serial.print(point[n[i]].t_type);
  if (point[n[i]].type == 1.5 && point[n[i]].turn == 'R')
  {
    assu_dir = point[n[i]].entry_dir[bef_turn] + 0.5;
//    Serial.print("assu_dir = ");
//    Serial.print(assu_dir);
//    Serial.print(" - ");
//    Serial.println(dir);
    point[n[i]].explored = point[n[i]].explored + dir_update(state_cal((assu_dir - dir), 1.5, 0));
    float directtion=assu_dir-dir;
    dir_cal(directtion);
//    Serial.print("state = ");
//    Serial.println(state_cal(directtion, 1.5, 1));
    turns(state_cal(directtion, 1.5, 0));
  }
  else if (point[n[i]].type == 1.5 && point[n[i]].turn == 'r')
  {
    assu_dir = point[n[i]].entry_dir[bef_turn] + 1;
//    Serial.print("assu_dir = ");
//    Serial.print(assu_dir);
//    Serial.print(" - ");
//    Serial.println(dir);
    point[n[i]].explored = point[n[i]].explored + dir_update(state_cal((assu_dir - dir), 1.5, 1));
    float directtion=assu_dir-dir;
    dir_cal(directtion);
//    Serial.print("state = ");
//    Serial.println(state_cal(directtion, 1.5, 1));
    turns(state_cal(directtion, 1.5, 1));
  }
  else if (point[n[i]].type == 1.5 && point[n[i]].turn == 'a')
  {
    assu_dir = point[n[i]].entry_dir[bef_turn] + 0.5;
//    Serial.print("assu_dir = ");
//    Serial.print(assu_dir);
//    Serial.print(" - ");
//    Serial.println(dir);
    point[n[i]].explored = point[n[i]].explored + dir_update(state_cal((assu_dir - dir), 1.5, 0));
    float directtion=assu_dir-dir;
    dir_cal(directtion);
//    Serial.print("state = ");
//    Serial.println(state_cal(directtion, 1.5, 1));
    turns(state_cal(directtion, 1.5, 0));
  }
  else if (point[n[i]].type == 2 && point[n[i]].turn == 'R' && point[n[i]].t_type == 0)
  {
    assu_dir = point[n[i]].entry_dir[bef_turn] + 0;
//    Serial.print("assu_dir = ");
//    Serial.print(assu_dir);
//    Serial.print(" - ");
//    Serial.println(dir);
    point[n[i]].explored = point[n[i]].explored + dir_update(state_cal((assu_dir - dir), 2, 0));
    float directtion=assu_dir-dir;
    dir_cal(directtion);
//    Serial.print("state = ");
//    Serial.println(state_cal(directtion, 1.5, 1));
    turns(state_cal(directtion, 2, 0));
  }
  else if (point[n[i]].type == 2 && point[n[i]].turn == 'R' && point[n[i]].t_type == 1)
  {
    assu_dir = point[n[i]].entry_dir[bef_turn] + 1;
//    Serial.print("assu_dir = ");
//    Serial.print(assu_dir);
//    Serial.print(" - ");
//    Serial.println(dir);
    point[n[i]].explored = point[n[i]].explored + dir_update(state_cal((assu_dir - dir), 2, 0));
    float directtion=assu_dir-dir;
    dir_cal(directtion);
//    Serial.print("state = ");
//    Serial.println(state_cal(directtion, 1.5, 1));
    turns(state_cal(directtion, 2, 0));
  }
  else if (point[n[i]].type == 2 && point[n[i]].turn == 'S')
  {
    assu_dir = point[n[i]].entry_dir[bef_turn] + 1;
//    Serial.print("assu_dir = ");
//    Serial.print(assu_dir);
//    Serial.print(" - ");
//    Serial.println(dir);
    point[n[i]].explored = point[n[i]].explored + dir_update(state_cal((assu_dir - dir), 2, 0));
    float directtion=assu_dir-dir;
    dir_cal(directtion);
//    Serial.print("state = ");
//    Serial.println(state_cal(directtion, 1.5, 1));
    turns(state_cal(directtion, 2, 0));
  }
  else if (point[n[i]].type == 3 && point[n[i]].turn == 'R')
  {
    assu_dir = point[n[i]].entry_dir[bef_turn] + 0;
//    Serial.print("assu_dir = ");
//    Serial.print(assu_dir);
//    Serial.print(" - ");
//    Serial.println(dir);
    point[n[i]].explored = point[n[i]].explored + dir_update(state_cal((assu_dir - dir), 3, 0));
    point[n[i]].turn = 'S';
    float directtion=assu_dir-dir;
    dir_cal(directtion);
//    Serial.print("state = ");
//    Serial.println(state_cal(directtion, 1.5, 1));
    turns(state_cal(directtion, 3, 0));
  }
  else if (point[n[i]].type == 3 && point[n[i]].turn == 'S')
  {
    assu_dir = point[n[i]].entry_dir[bef_turn] + 1;
//    Serial.print("assu_dir = ");
//    Serial.print(assu_dir);
//    Serial.print(" - ");
//    Serial.println(dir);
    point[n[i]].explored = point[n[i]].explored + dir_update(state_cal((assu_dir - dir), 3, 0));
    float directtion=assu_dir-dir;
    dir_cal(directtion);
//    Serial.print("state = ");
//    Serial.println(state_cal(directtion, 1.5, 1));
    turns(state_cal(directtion, 3, 0));
  }
}

void check_run(byte dest)
{
  digitalWrite(49,1); 
  byte i = 0;
  deriving(dir,djiks(n[j_count],dest));//last= total no. of nodes in path given by djikstras....//dest =destination
  Serial.println(actualpath);
  turns(actualpath[i]);
  start_time=millis();
  while(1)
  {
    sensor_read();
    if (node_check()) 
    {
      i++;
      if (actualpath[i] == 'C')
      {
        actualpath = "";
//        Serial.println("OUT of check_run ");
        break;
      }
      turns(actualpath[i]);
      start_time=millis();
    }
    else
    {
      linefollow();
    }
  }
  digitalWrite(49,0);
}

bool node_check()
{
  mid_time=millis();
//  Serial.print("mid-start = ");
//  Serial.println((mid_time-start_time));
  junc:
//  disp_val();
  if(((!d0 && d_sum>0 && d3) || (d0 && d_sum>0 && !d3)) && !p_type)
  {
    l_type=1;    
  }

  if(d0 && d_sum>0 && d3)
  {
    p_type=1;
    l_type=0;
  }
  if(s_sum == 8)
  {
    do
    {
      plus:
      fwd(0);
      sensor_read();
      if(d0 && d1 && d2 && d3)
      {
        return 1;
      }
    }while(s_sum>3);
    halt(50);
    sensor_read();
    p_type=0;
    return 1;
  }
  else if(s_sum>3 && s_sum<8 && l_type)
  {
    midtime:
    sensor_read();
    do
    {
      fwd(0);
      sensor_read();
    }while(s_sum>3);
    while(d0 || d3)
    {
      fwd(0);
      sensor_read();
    }
    halt(50);
    sensor_read();
    l_type=0;
    p_type=0;
    return 1;
  }
  else if(!p_type && (d0 && d3) && m_sum>2 && (d_sum == 0))
  {
    do
    {
      fwd(0);
      sensor_read();
    }while(v_sum>0);
    
    halt(50);
    l_type=0;
    p_type=0;
    return 1;

  }
  else if((v_sum>0) && (d0 || d3) && (d_sum==0) && !l_type && !p_type)
  {
    type=0.5;
    do
    {
      fwd(0);
      sensor_read();
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

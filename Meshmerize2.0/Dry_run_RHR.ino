void dry_run_RHR()
{
  sensor_read();
  if(junc_det_RHR())
  {
    end_time = millis();
    rev_corr_factor(state);
    dist = (end_time - start_time) + corr_fact + rev_corr_fact;
    Serial.print("\t dist = ");
    Serial.println(dist);
    set_dist();
    j_count++;
    node_write(point[n[j_count-1]].cordx,point[n[j_count-1]].cordy);//type, turn, cordx, cordy, explored ...written
    j++;
    n[j_count]=j;    
    Serial.print("cordx = ");
    Serial.print(point[n[j_count]].cordx);    
    Serial.print("\tcordy = ");
    Serial.println(point[n[j_count]].cordy);    
    norm_conn(j_count);
    if(check_repeat(j_count))
    {
      digitalWrite(47,1);
        j--;      
      connections(n[j_count],n[(j_count-1)],0);
      point[n[j_count-1]].conn_count--;
      point[j+1].conn_count--;
      connections(n[(j_count-1)],n[j_count],1);

//      if(point[n[j_count]].explored > point[n[j_count]].type)//this will be true if bot is stuck in loop
//      {
//        unexplored();
//        retrace();
//      }
      digitalWrite(47,0);
    }
    if(((j==checkpt && digitalRead(4)) || (state == 'E' && digitalRead(5))) && CP==0)//check if we really need this CP flag
    {
      if(state=='E')
      {
        CP=1;
        endpoint=j;
      }
      digitalWrite(51,1);
      float temp_dir;
      if( state == 'R' || state == 'r' || state == 'a' || state == 'S')
      {
        temp_dir = dir - dir_update(state);
      }
      else if( state == 'L' || state == 'l' || state == 's')
      {
        temp_dir = dir + dir_update(state);
      } 
      else if( state == 'U')
      {
        temp_dir = dir + 2;
      }
//      Serial.print("temp_dr without curr_dir = ");
//      Serial.println(temp_dir);      
      curr_dir(temp_dir);
//      Serial.print("temp_dr = ");
//      Serial.println(temp_dir);      
////      fwd(120);
      turns('U');
//      Serial.print("dir = ");
//      Serial.println(dir);
//      halt(3000);
      unexplored_stack();
      CheckPoint();
      if(CP==0)
      {
        check_run(checkpt);
        j_count++;
        n[j_count]=checkpt;
//      Serial.print("j_count = ");
//      Serial.println(j_count);
//      Serial.print("n[j_count] = ");
//      Serial.println(n[j_count]);
//      Serial.print("dir = ");
//      Serial.println(dir);
        float directtion=temp_dir-dir;
        dir_cal(directtion);
        state=state_cal(directtion,point[checkpt].type,1);//check if it works well with flag always 1(if it takes proper turns)
//      Serial.print("state = "); 
//      Serial.println(state); 
      }
      else
      {
        check_run(endpoint);
        state='E';
      }
      digitalWrite(51,0);
    }
////    checkpoint:
    drypath.concat(state);
    turns(state);

//    Serial.print("n[j_count] = ");
//    Serial.print(n[j_count]);    
//    Serial.print("\ttype = ");
//    Serial.print(point[n[j_count]].type);
//    Serial.print("\texplored = ");
//    Serial.print(point[n[j_count]].explored);
//    Serial.print("\tturn = ");
//    Serial.println(point[n[j_count]].turn);

    start_time = millis();
  }
  else
  {
    linefollow();
  }
}

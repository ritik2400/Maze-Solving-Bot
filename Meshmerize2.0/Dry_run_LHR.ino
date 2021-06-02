void dry_run_LHR()
{
  sensor_read();
  if(junc_det_LHR())
  {
    end_time = millis();
    digitalWrite(13,1);
    rev_corr_factor(state);
    dist = (end_time - start_time) + corr_fact + rev_corr_fact;
    set_dist();
//    halt(2000);
    j_count++;
    node_write(point[n[j_count-1]].cordx,point[n[j_count-1]].cordy);//type, turn, cordx, cordy, explored ...written
    j++;
    n[j_count]=j;  
    norm_conn(j_count);
    if(check_repeat(j_count))
    {
      j--;
      connections(n[j_count],n[(j_count-1)],0);
      point[n[j_count-1]].conn_count--;
      point[j+1].conn_count--;
      connections(n[(j_count-1)],n[j_count],1);

//      if(point[n[j_count]].explored > point[n[j_count]].type)//this will be true if bot is tuck in loop
//      {
//        unexplored();
//        retrace();
//      }
    }
//    if(j==checkpt && CP==0)//check if we really need this CP flag
//    {
//      float temp_dir;
//      if( state == 'R' || state == 'r' || state == 'a' || state == 'S')
//      {
//        temp_dir = dir - dir_update(state);
//      }
//      else if( state == 'L' || state == 'l' || state == 's')
//      {
//        temp_dir = dir + dir_update(state);
//      }
//      else if( state == 'U')
//      {
//        temp_dir = dir + 2*dir_update(state);
//      }
//      
//      rev_for_checkpt();
//      unexplored_stack();
//      CheckPoint();
//      check_run(checkpt);
//      
//      j_count++;
//      n[j_count]=checkpt;
//      state=state_cal((temp_dir - dir),point[checkpt].type,1);//check if it works well with flag always 1(if it takes proper turns)
//    }
//    checkpoint:
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
    digitalWrite(13,LOW);
//    halt(2000);
    start_time = millis();
  }
  else
  {
    linefollow();
  }
}

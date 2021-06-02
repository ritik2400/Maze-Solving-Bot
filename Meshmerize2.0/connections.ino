void connections(byte l,byte k,bool f)//k is connected to l, flag f denotes the dir to be saved,i.e. 0=non-inverted direction and 1=inverted direction
{
  float d;
  int i;
  d=dir;
//  Serial.print("l= ");
//  Serial.println(l);  
//  Serial.print("k= ");
//  Serial.println(k);
  if(point[l].explored <= point[l].type || point[l].conn_count < 4)//...."|| point[l].conn_count < 4" this condition is put for failsafe,if anything wrong (if at any case of + node).
  {
    for(i=0;i<point[l].conn_count;i++)
    {
//        Serial.println("before");
//        Serial.print(l);
//        Serial.print("-");
//        Serial.print(i);
//        Serial.print(" = ");
//        Serial.println(point[l].conn[i]);
//        Serial.print(" == ");
//        Serial.println(k);

      if(point[l].conn[i] == k)
      {
        break;
      }
    }
    if(i == point[n[l]].conn_count)
    {
//      Serial.print("i = ");
//      Serial.println(i);
      point[l].conn[i]=k;
      point[l].conn_wts[i]=dist;
      if(f)
      {
          d=d-2;
          curr_dir(d);
      }
      point[l].entry_dir[i]=d;
      point[l].conn_count++;
    }
  }
}

void norm_conn(byte j_c)
{
  float d;
  point[n[j_c]].conn[point[n[j_c]].conn_count] = n[j_c-1];
  point[n[j_c]].conn_wts[point[n[j_c]].conn_count] = dist;
  point[n[j_c]].entry_dir[point[n[j_c]].conn_count] = dir;
//  Serial.print(n[j_c]);
//  Serial.print("-");
//  Serial.print(point[n[j_c]].conn_count);
//  Serial.print(" = ");
//  Serial.println(n[j_c-1]);
  point[n[j_c]].conn_count++;
//  Serial.print("\t  ");
//  Serial.println(point[n[j_c]].conn_count);

  point[n[j_c-1]].conn[point[n[j_c-1]].conn_count] = n[j_c];
  point[n[j_c-1]].conn_wts[point[n[j_c-1]].conn_count] = dist;
  d=dir-2;
  curr_dir(d);
  point[n[j_c-1]].entry_dir[point[n[j_c-1]].conn_count] = d;
//  Serial.print(n[j_c-1]);
//  Serial.print("-");
//  Serial.print(point[n[j_c-1]].conn_count);
//  Serial.print(" = ");
//  Serial.println(n[j_c]);
  point[n[j_c-1]].conn_count++;
//  Serial.print("\t  ");
//  Serial.println(point[n[j_c-1]].conn_count);

}

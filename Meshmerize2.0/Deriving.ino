void deriving(float d,byte last)//last= total no. of nodes in path,d= current directions//d=this is the initial direction
{
  byte l,k,m;
  float diff;
  for(l=1;l<last;l++)//last will be the position of the last node,i.e. endpoint
  {
    for(k=0;k<point[path[l]].conn_count;k++)
    {
      if(point[path[l]].conn[k] == path[l-1])
      {
        break;
      }
    }
    diff = point[path[l]].entry_dir[k]-d;
    dir_cal(diff);
    for(m=0;m<point[path[l-1]].conn_count;m++)
    {
      if(point[path[l-1]].entry_dir[m] == d)
      {
        break;
      }
    }
    if(point[path[l-1]].type == 1.5)
    {
      float dif;
      switch(m)
      {
        case 0:
        dif = abs(point[path[l-1]].entry_dir[1] - point[path[l-1]].entry_dir[2]);
        dir_cal(dif);
        if(abs(dif) == 1)
        {
          actualpath.concat(state_cal(diff,point[path[l-1]].type,1));
        }
        else
        {
          actualpath.concat(state_cal(diff,point[path[l-1]].type,0));
        }
        break;
        
        case 1:
        dif = abs(point[path[l-1]].entry_dir[0] - point[path[l-1]].entry_dir[2]);
        dir_cal(dif);
        if(abs(dif) == 1)
        {
          actualpath.concat(state_cal(diff,point[path[l-1]].type,1));
        }
        else
        {
          actualpath.concat(state_cal(diff,point[path[l-1]].type,0));
        }
        break;
        
        case 2:
        dif = abs(point[path[l-1]].entry_dir[1] - point[path[l-1]].entry_dir[2]);
        dir_cal(dif);
        if(abs(dif) == 1)
        {
          actualpath.concat(state_cal(diff,point[path[l-1]].type,1));
        }
        else
        {
          actualpath.concat(state_cal(diff,point[path[l-1]].type,0));
        }
        break;
      }
    }
    else
    {
      actualpath.concat(state_cal(diff,point[path[l-1]].type,0));
    }
    d = point[path[l]].entry_dir[k];
  }
  if(l == last)
  {
    actualpath.concat(state_cal(6,0,0));
  }
}

void dir_cal(float &dif)
{
  if(dif<-2)
  {
    dif=dif+4;
  }
  else if(dif>2)
  {
    dif=dif-4;
  }
}

char state_cal(float dif,float typ,bool f)//flag is for showing y traced from 135d = 1, y from 90d = 0
{
  if(dif == 6)
  {
    return 'C';
  }
  else if(dif == 2 || dif == -2)
  {
    return 'U';
  }
  else if(dif == 1)
  {
    return 'L';
  }
  
  else if(dif == -1)
  {
    return 'R';
  }
  
  else if(dif == 0)
  {
    return 'S';
  }
  
  else if(dif == 0.5 && typ == 0.5)
  {
    return 'l';
  }
  
  else if(dif == -0.5 && typ == 0.5 )
  {
    return 'r';
  }
  
  else if(dif == 0.5 && typ == 1.5 && f)
  {
    return 's';
  }
  
  else if(dif == 0.5 && typ == 1.5 && !f)
  {
    return 'l';
  }

  else if(dif == -0.5 && typ == 1.5 && f)
  {
    return 'a';
  }
  
  else if(dif == -0.5 && typ == 1.5 && !f)
  {
    return 'r';
  }
}

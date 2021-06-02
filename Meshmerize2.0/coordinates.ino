float dir_update(char S)//this function to be used for exploration updates
{
  float d;
  switch(S)
  {
    case 'a':// for Right Hand Rule
    d = (0.5);
    break;
    
    case 's':// for Left Hand Rule
    d = (0.5);
    break;
    
    case 'r':
    d = (0.5);
    break;
    
    case 'l':
    d = (0.5);
    break;
    
    case 'R':
    d = (1);
    break;
    
    case 'S':
    d = 1;
    break;
    
    case 'L':
    d = (1);
    break;
        
    case 'U':
    d = (0);
    break;
  }
  return d;
}

void curr_dir(float &d)
{
  if(d<0)
  {
    d=4+d;
  }
  else if(d>=4)
  {
    d=d-4;
  }
}

void set_dist()
{
  if(dist>=750 && dist<=1160)//buffer 200
  {
    dist=24;
  }
  else if(dist>=1205 && dist<=1605)
  {
    dist=34;
  }
  else if(dist>=1825 && dist<=2225)
  {
    dist=48;
  }
  else if(dist>=2700 && dist<=3200)
  {
    dist=68;
  }
  else if(dist>=240 && dist<=640)
  {
    dist=13;
  }
  else
  {
    dist=34;
  }
}

void node_write(double x,double y)
{
  float d;
  d=dir+1;
  curr_dir(d);
  point[j+1].t_type = t_glo_type;
  point[j+1].cordx = round(x + dist * cos((d/0.5)*0.785398));
  point[j+1].cordy = round(y + dist * sin((d/0.5)*0.785398));
  point[j+1].turn = state;
  point[j+1].type = type;
  point[j+1].explored = dir_update(state);
  t_glo_type=0;
}

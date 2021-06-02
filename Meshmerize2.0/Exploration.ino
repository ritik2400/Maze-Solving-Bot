bool check_repeat(byte j_c)
{
  int i;
  for(i=(j-1); i>=0; i--)
  {
    if(point_check(i,j))
    {
      point[i].explored = point[i].explored + dir_update(state);
      n[j_c] = i;
      return 1;
    }
  }
  return 0;
}

bool unexplored_stack()//this pushes the unexplored points in the stack
{
  int i;
  for(i=0;i<j;i++)
  {
    if(point[i].explored < point[i].type)
    {
      unexplored.push(i);
    }
  }
}


bool point_check(int i,byte k)
{
  bool xco=0,yco=0;
  if(round(point[k].cordx) == round(point[i].cordx))
  {
    xco=1;
  }
  if(round(point[k].cordy) == round(point[i].cordy))
  {
    yco=1;
  }
  return (xco && yco);
}

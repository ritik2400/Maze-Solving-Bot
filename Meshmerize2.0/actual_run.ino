void actual_run()
{
  sensor_read();
  if(node_check())
  {
    actual_j++;
    turns(realpath[actual_j]);
  }
  else
  {
    linefollow();
  }
}

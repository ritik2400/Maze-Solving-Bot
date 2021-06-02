byte djiks(byte firstno,byte lastno)
{ 
//    Serial.print("point[4].expl=");
//    Serial.println(point[4].expl);
//    Serial.print("point[4].wt=");
//    Serial.println(point[4].wt);
//  Serial.print("firstno = ");
//  Serial.print(firstno);
//  Serial.print("\tlastno = ");
//  Serial.println(lastno);  
 // Serial.println(j);
  point[firstno].wt=0;
  int i=0;
  int counter = 0;
  int minno=0;
  unsigned long int minwt=100001;
  while (minno != lastno)
  {
    minwt = 100001;
    for (counter = 0; counter <= j; counter++)//finding the index of the node with minimum weight
    {
      if (point[counter].expl == 0)
      {
        if (point[counter].wt < minwt)
        {
          minwt = point[counter].wt;
          minno = counter;
        }
      }
    }
//    Serial.println(minwt);
//     Serial.println(minno);
     counter = 0;
//     Serial.print("No of connections of ");
//     Serial.print(minno);
//     Serial.print(" is ");
//     Serial.println(point[minno].conn_count);

    if (minno != lastno)//if minimum weight is of lastno node, don't explore it
    {
//      Serial.println("z");
//      Serial.println(point[minno].conn_count);
      for (counter = 0; counter < point[minno].conn_count; counter++) {
        if (point[point[minno].conn[counter]].wt > point[minno].wt + point[minno].conn_wts[counter])//if current weight of a connection is more than the weight of min wt node + wt of path then overwrite the weight
        {
          point[point[minno].conn[counter]].wt = point[minno].wt + point[minno].conn_wts[counter];
          point[point[minno].conn[counter]].prevnode = minno;
//          Serial.print("Updated wt of ");
//          Serial.print(point[minno].conn[counter]);
//          Serial.print(" is ");
//          Serial.println(point[point[minno].conn[counter]].wt);
//          Serial.print("Prevnode index for ");
//          Serial.print(point[minno].conn[counter]);
//          Serial.print("=");
//          Serial.println(minno);
        }
      }
      point[minno].expl = 1;
    }
  }
    i = lastno;
    path[0] = lastno;
    counter = 1;
    while (i != firstno) //storing shortest path in reverse
    {
//          Serial.print("i=");
//          Serial.println(i);
      path[counter] = point[i].prevnode;
  //    //Serial.println(path[counter]);
      i = point[i].prevnode;
      counter++;
    }
//  Serial.print("counter is ");
//  Serial.println(counter);
//
//  Serial.print(path[0]);
//  Serial.print(path[1]);
//  Serial.print(path[2]);
//  Serial.println("");



  byte temp;
  for (int k = 0; k < counter / 2; k++) //reversing the shortest path array
  {
//    Serial.println(counter);
//    Serial.print("Before swap: path[");
//    Serial.print(k);
//    Serial.print("]=");
//    Serial.println(path[k]);
    temp = path[k];
    path[k] = path[counter - 1 - k];
    path[counter - 1 - k] = temp;
//    Serial.print("After swap: path[");
//    Serial.print(k);
//    Serial.print("]=");
//    Serial.println(path[k]);
//    Serial.println("-------");
//    Serial.print(path[0]);
//    Serial.print(path[1]);
//    Serial.println(path[2]);
//    Serial.println("-------");
  }

for(int ghf=0;ghf<=j;ghf++)
{
  point[ghf].wt=100000;
  point[ghf].expl=0;
//  Serial.print(ghf);
//  Serial.print(" = ");
//    Serial.print(point[ghf].expl);
//    Serial.print("\t");
//    Serial.println(point[ghf].wt);
}
return counter;


//  Serial.println("");
}

void junc_format()
{
  while((drypath.indexOf("U")+1))
  {
    drypath.replace("RUR","S");//for normal nodes
    drypath.replace("LUL","S");
    drypath.replace("RUS","L");
    drypath.replace("SUR","L");
    drypath.replace("LUS","R");
    drypath.replace("SUL","R");
    drypath.replace("RUL","U");
    drypath.replace("LUR","U");
    drypath.replace("SUS","U");

    drypath.replace("aUR","S");//for Y node by RHR
    drypath.replace("sUr","U");
    drypath.replace("RUr","l");
    drypath.replace("lUa","U");
    drypath.replace("rUa","L");

    drypath.replace("lUr","U");//for V node
    drypath.replace("rUl","U");

    drypath.replace("lUs","U");//for Y node by LHR
    drypath.replace("LUl","U");
    drypath.replace("rUs","U");
    drypath.replace("sUL","U");
    drypath.replace("aUl","U");
  }
}

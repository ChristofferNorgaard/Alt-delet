void Accel(int steps, int a, int maxspeed, int minspeed = 100){
  int v = minspeed;
  float time_from = 0;
  for(int i = 0; i<steps; i++){
    if(v < maxspeed){
      time_from += 60/v;
      if(time_from*a > 1){
        v += round(a*60/v);
        time_from = 0;
        }
       /*
        * if(endsenzor) - tukaj je prostor tudi za end senzorje
        */
    }
    myStepper.setSpeed(v);
    myStepper.step(1);
  }
}
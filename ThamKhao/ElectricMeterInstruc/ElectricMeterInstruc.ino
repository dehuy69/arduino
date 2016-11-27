float sample2, val, actualval, amps, totamps, avgamps, amphr, watt, energy, voltage;
long milisec, Time;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  sample2, val, actualval, amps, totamps, avgamps, amphr, watt, energy, voltage = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < 150; i++)
  {
    sample2 += analogRead(A1); //read the current from sensor
    delay(2);
  }
  sample2 = sample2 / 150;
  val = (5.0 * sample2) / 1024.0;
  actualval = val - 2.5; // offset voltage is 2.5v
  voltage = actualval;
  amps = actualval * 1000 /66;
  milisec = millis(); // calculate time in milliseconds
  Time = milisec / 1000; // convert milliseconds to seconds
  totamps = totamps + amps; // calculate total amps
  avgamps = totamps / Time; // average amps
  amphr = (avgamps * Time) / 3600; // amp-hour
  watt = voltage * amps; // power=voltage*current
  //energy = (watt * Time) / 3600; //Watt - sec is again convert to Watt - Hr by dividing 1hr(3600sec)
  energy = (watt * Time) / (1000 * 3600); //for reading in kWh
  Serial.print("VOLTAGE : ");
  Serial.print(voltage);
  Serial.println("Volt");
  Serial.print("CURRENT :");
  Serial.print(amps);
  Serial.println("Amps");
  Serial.print("POWER :");
  Serial.print(watt);
  Serial.println("Watt");
  Serial.print("ENERGY CONSUMED :");
  Serial.print(energy);
  Serial.println("Watt-Hour");
  Serial.println(""); // print the next sets of parameter after a blank line
  delay(2000);
}

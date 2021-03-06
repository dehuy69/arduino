/*
  Liquid flow rate sensor -DIYhacking.com Arvind Sanjeev

  Measure the liquid/water flow rate using this code.
  Connect Vcc and Gnd of sensor to arduino, and the
  signal line to arduino digital pin 2.

*/
int pulseCount;
void pulseCounter()
{
  pulseCount++;
}
class FlowMeter
{
  public:
    int sensorInterrupt = 0; // 0 = digital pin 2
    int sensorPin = 2;
    float calibrationFactor = 4.5;
    float flowRate;
    unsigned int flowMilliLitres;
    unsigned long totalMilliLitres;
    int totalLitres;

    void Setup()
    {

      // The hall-effect flow sensor outputs approximately 4.5 pulses per second per
      // litre/minute of flow.

      pinMode(sensorPin, INPUT);
      digitalWrite(sensorPin, HIGH);
      pulseCount = 0;
      flowRate = 0;
      flowMilliLitres = 0;
      totalMilliLitres = 0;
      totalLitres = 0;

      // The Hall-effect sensor is connected to pin 2 which uses interrupt 0.
      // Configured to trigger on a FALLING state change (transition from HIGH
      // state to LOW state)
      attachInterrupt(sensorInterrupt, pulseCounter, FALLING);
    }

    /**
      Main program loop
    */
    void Loop() // chạy ở chu kì 1 giây
    {
      // Disable the interrupt while calculating flow rate and sending the value to
      // the host
      detachInterrupt(sensorInterrupt);

      // Because this loop may not complete in exactly 1 second intervals we calculate
      // the number of milliseconds that have passed since the last execution and use
      // that to scale the output. We also apply the calibrationFactor to scale the output
      // based on the number of pulses per second per units of measure (litres/minute in
      // this case) coming from the sensor.
      flowRate = pulseCount / calibrationFactor;

      // Divide the flow rate in litres/minute by 60 to determine how many litres have
      // passed through the sensor in this 1 second interval, then multiply by 1000 to
      // convert to millilitres.
      flowMilliLitres = (flowRate / 60) * 1000;

      // Add the millilitres passed in this second to the cumulative total
      totalMilliLitres += flowMilliLitres;

      if ((totalMilliLitres / 1000 - totalLitres) > 1)
      {
        totalLitres = totalMilliLitres / 1000;
      }

      /*
        unsigned int frac;

        // Print the flow rate for this second in litres / minute
        Serial.print("Flow rate: ");
        Serial.print(int(flowRate)); // Print the integer part of the variable
        Serial.print(".");           // Print the decimal point
        // Determine the fractional part. The 10 multiplier gives us 1 decimal place.
        frac = (flowRate - int(flowRate)) * 10;
        Serial.print(frac, DEC); // Print the fractional part of the variable
        Serial.print("L/min");
        // Print the number of litres flowed in this second
        Serial.print("  Current Liquid Flowing: "); // Output separator
        Serial.print(flowMilliLitres);
        Serial.print("mL/Sec");

        // Print the cumulative total of litres flowed since starting
        Serial.print("  Output Liquid Quantity: "); // Output separator
        Serial.print(totalMilliLitres);
        Serial.println("mL");
      */
      // Reset the pulse counter so we can start incrementing again
      pulseCount = 0;

      // Enable the interrupt again now that we've finished sending output
      attachInterrupt(sensorInterrupt, pulseCounter, FALLING);
    }
};

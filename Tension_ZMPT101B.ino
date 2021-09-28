#include <Filters.h>  //external library that can be downloaded at this adress: https://www.arduinolibraries.info/libraries/filters


//*******variables to be used in the code
float testFrequency = 50;                     // Frequency used in our context(Africa)
float windowLength = 40.0/testFrequency;     // how long to average the signal, for statistist

int Sensor = 0; 

float intercept = -0.04; // to be adjusted based on calibration testing
float slope = 0.055; // this code can be modified to obtain the value that we have
//0.0405
float current_Volts; // Voltage
RunningStatistics inputStats;                //Use the Filters library to do calculations of the RMS requires a load of coding
float volt=0;

void setup() {
    Serial.begin( 9600 );    // start the serial port
    inputStats.setWindowSecs( windowLength );  //library calculations
}

void loop() {
  // put your main code here, to run repeatedly:
  volt = voltage();
  delay(3000);  //wait 3 seconds
}


float voltage(){  
    Sensor = analogRead(A5);  // read the analog value from the analog port
    inputStats.input(Sensor);  // log to Stats function
    current_Volts = intercept + slope * inputStats.sigma(); //Calibrations for offset and amplitude
    current_Volts= current_Volts*(40.3231);                //Further calibrations for the amplitude
    Serial.print( "Voltage: " );
    Serial.print( current_Volts ); //print the value
    delay(10);
    return current_Volts;
}

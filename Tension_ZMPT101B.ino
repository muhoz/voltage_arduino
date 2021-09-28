#include <Filters.h> //Easy library to do the calculations

float testFrequency = 50;                     // test signal frequency (Hz)
float windowLength = 40.0/testFrequency;     // how long to average the signal, for statistist

int Sensor = 0; //Sensor analog input, here it's A0
int Sensor1 = 0; //Sensor analog input, here it's A0

float intercept = -0.04; // to be adjusted based on calibration testing
float slope = 0.055; // to be adjusted based on calibration testing
//0.0405
float current_Volts; // Voltage
float current_Volts1; // Voltage
      RunningStatistics inputStats;                //Easy life lines, actual calculation of the RMS requires a load of coding
      RunningStatistics inputStats1;                //Easy life lines, actual calculation of the RMS requires a load of coding


void setup() {
    Serial.begin( 9600 );    // start the serial port
    inputStats.setWindowSecs( windowLength );
}

void loop() {
  // put your main code here, to run repeatedly:
  Sensor = analogRead(A5);  // read the analog in value:
  Sensor1 = analogRead(A9);  // read the analog in value:

        inputStats.input(Sensor);  // log to Stats function
        inputStats1.input(Sensor1);  // log to Stats function

            current_Volts = intercept + slope * inputStats.sigma(); //Calibartions for offset and amplitude
            current_Volts1 = intercept + slope * inputStats1.sigma(); //Calibartions for offset and amplitude

            current_Volts= current_Volts*(40.3231);                //Further calibrations for the amplitude
            current_Volts1= current_Volts1*(40.3231);                //Further calibrations for the amplitude

            Serial.print( "\tVoltage1: " );
            Serial.print( current_Volts ); //Calculation and Value display is done the rest is if you're using an OLED displ
            delay(10);
            Serial.print( "\tVoltage2: " );
            Serial.print( current_Volts1 ); //Calculation and Value display is done the rest is if you're using an OLED displ
            delay(10);

            
}

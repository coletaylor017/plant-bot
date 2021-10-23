/**
 * Written by Cole Taylor, October 2021 for a Lassonde Make Space lab at the University of Utah
 */

// ========== CONSTANTS: adjust these for your particular house plant and tubing setup ==========

// The soil moisture percentage at which the pump will activate. Range 0-100. 0 means no water
const int soilMoistureThreshold = 40;

// The amount of time (in milliseconds) the water pump pulses for
// Adjust this slightly based on the length of your water tube
const int waterPulseDuration = 1000;

// The amount of time (in milliseconds) the program will wait between reading soil moisture
const int waterInterval = 10000;

// SOIL MOISTURE SENSOR CALIBRATION
// Note: the max should be the value when the sensor is dry
//       the min is the value when it is submerged in water
//       You need to calibrate this since every sensor is different
const int soilWet = 276; // CHANGE THIS based on the console output Nick: 230 Justin: 280
const int soilDry = 555; // CHANGE THIS Nick: 480 Justin: 520

// v Don't change these unless you re-wire your arduino
// The digital (HI/LO) pin that the water pump runs on
const int pumpPin = 2;
// The analog (range of values) pin that the soil moisture sensor input comes in on
const int soilPin = 14;

/**
 * Setup code runs once at the beginning
 */
void setup()
{
  Serial.begin(9600);
  pinMode(pumpPin, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

/**
 * Runs repeateatedly, forever
 */
void loop()
{
  // read the pin that the soil moisture sensor is connected to
  int soilMoistureRaw = analogRead(soilPin);
  
  // convert the raw range to a percentage
  int soilMoisture = map(soilMoistureRaw, soilDry, soilWet, 0, 100);
  
  // print the soil moisture values to the console
  Serial.print("Soil moisture (raw): ");
  Serial.print(soilMoistureRaw);
  Serial.print("\t");
  Serial.print("Soil moisture (mapped 0-1): ");
  Serial.print(soilMoisture);
  Serial.print("\n");

  // if the soil moisture ever goes below 40%
  if (soilMoisture < soilMoistureThreshold)
  {
    // pulse the water pump
    digitalWrite(2, HIGH);
//      digitalWrite(LED_BUILTIN, HIGH);
    delay(waterPulseDuration);
    digitalWrite(2, LOW);
//      digitalWrite(LED_BUILTIN, LOW);

    // Wait 10 seconds before reading the soil moisture value again
    delay(waterInterval);
  }
  
  delay(200);

}

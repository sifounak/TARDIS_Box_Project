// UC = user-controlled input

// ========== //
// Pin layout //
// ========== //
const int LED = 3;
const int SPK = 4;
const int MIC = A1;

// ======================= //
// Light-related constants //
// ======================= //

// Pulse range constants
const int initVal  = 255;  // UC - initial LED value
const int maxVal   = 255;  // UC - brightest LED value
const int minVal   = 16;   // UC - lowest LED value
const int oscAmp   = floor(0.5*float(maxVal-minVal));
const int midVal   = maxVal - oscAmp;

// Pulse number and durations
const int nPulses                 = 5;    // UC - number of pulses
const int nSamples                = 100;  // UC - number of samples per pulse
const float p1                    = 2.0;  // UC - period of 1st pulse in seconds
const float p2                    = 1.75; // UC - period of 2nd-5th pulses in seconds
const float holdMaxVal[nPulses+2] = {250,300,200,300,300,700}; // UC - delay between pulses
const float pulseDelay[nPulses+1] = {1850/float(nSamples),
                                     1400/float(nSamples),
                                     1500/float(nSamples),
                                     1400/float(nSamples),
                                     1500/float(nSamples)};   // UC - delay between samples in milliseconds
const float twoDivSamples         = 2.0/float(nSamples);      // pre-computed 2.0/nSamples to lower operation count

// ============= //
// Mic constants //
// ============= //
const int micThresh = 1000;  // UC - microphone threshold

// ============== //
// Math constants //
// ============== //
const float pi = 3.14159;

// ========================= //
// Global volatile variables //
// ========================= //
int buttonState = 0;

// =============== //
// Debugging flags //
// =============== //
bool debugOn = false;  // UC - only really useful on non-Trinket hardware


// ====== //
// SETUP //
// ====== //
void setup() {

  // Set pin modes
  pinMode(LED,OUTPUT);
  pinMode(SPK,OUTPUT);

  // Set initial trigger value to off;
  digitalWrite(SPK,0);

  // Initialize LED value
  setLedValue(initVal); // Start with the LED on

  // Debugging options
  if( debugOn ) {
    Serial.begin(9600); // Other baud rates can be used...
  }

}

// ========= //
// MAIN LOOP //
// ========= //
void loop() {

  // Trigger audio and lights if the mic detects a large value
  if( analogRead(MIC) > micThresh ) {
    playAudio();
    pulseLights();
    delay(500);  // delay 0.5 seconds before allowing another trigger
  }

}

// ========== //
// PLAY AUDIO //
// ========== //
void playAudio() {
  digitalWrite(SPK,1);
  delay(100);
  digitalWrite(SPK,0);
}

// ============= //
// SET LED VALUE //
// ============= //
void setLedValue(int ledVal) {

  // Set values for LED
  analogWrite(LED,ledVal);

  // Print to serial if debug is on
  if( debugOn ) {
    Serial.print("LED value: ");
    Serial.println(ledVal);
  }
}

// ========== //
// PULSE LEDS //
// ========== //
void pulseLights() {

  // Initialized data
  int outVal;

  // Loop through all pulses
  delay(holdMaxVal[1]);  // Initial delay before pulses begin
  for( int j = 0; j < nPulses; j = j+1 ){
    for( int i = 0; i < nSamples; i = i+1 ){
      outVal = midVal + int(oscAmp*sin((float(i)*twoDivSamples + 0.5)*pi));
      setLedValue(outVal);
      delay(pulseDelay[j]);
    }
    delay(holdMaxVal[j+1]);
  }

}



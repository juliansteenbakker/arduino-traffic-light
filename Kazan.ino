
#define GROEN  5                        
#define ORANJE  6                        
#define ROOD  7
#define VOL  4
#define BUTTON  2
#define LED1    8
#define LED2    9                       
#define LED3    10
#define LED4    11

int buttonState = LOW;        // the current reading from the buttuon
int lastButtonState = HIGH;   // the previous reading from the button
int reading;                  // updated reading from the button

long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers
int state = 0;

unsigned long randomTime = 500;          // begin time of program
unsigned long previousMillis = 0;        // will store last time LED was updated

// variables for automated traffic light
int a = 1;
int b = 0;
int c = 0;
int d = 0;

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON, INPUT);
  pinMode(GROEN, OUTPUT);       
  pinMode(ORANJE, OUTPUT);
  pinMode(ROOD, OUTPUT);
  pinMode(VOL, OUTPUT);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  trafficLightOff();

}

void loop() {
  reading = digitalRead(BUTTON);        // read the state of the pushbutton value
  
   if (reading != lastButtonState) {
      lastDebounceTime = millis();
      lastButtonState = reading;
   } 

   if ((millis() - lastDebounceTime) > debounceDelay) {
       if (buttonState != lastButtonState) {
           buttonState = lastButtonState;
           if (buttonState == HIGH) {
            if (state == 0) {
              state = 1;
            } else if (state == 1) {
              state = 2;
              } else if (state == 2) {
              state = 3;
              } else if (state == 3) {
              state = 4;
              } else if (state == 4) {
              state = 5;
              } else if (state == 5) {
              state = 0;
            }
            Serial.println("KLIK");
           }
       }
   }
      
  if (state == 0) {
    trafficLightNoDelay();
  } else if (state == 1) {
    trafficLightRed();
  } else if (state == 2) {
    trafficLightOrange();
  } else if (state == 3) {
    trafficLightGreen();
  } else if (state == 4) {
    trafficLightFull();
  } else if (state == 5) {
    trafficLightOff();
  }  
}

void trafficLightNoDelay() {
  digitalWrite(LED4, HIGH);
  if (millis() - previousMillis >= randomTime && a == 1 || d == 1) {
    d = 0;
    randomTime = random(20000, 60000);
    Serial.println(randomTime);
    a = 0;
    b = 1;
    previousMillis = millis();
    digitalWrite(ROOD,HIGH);   
    digitalWrite(GROEN, LOW);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED2, LOW);
    digitalWrite(LED1, LOW);
    digitalWrite(VOL, LOW);
  }
  
  if (millis() - previousMillis >= randomTime && b == 1) {
    b = 0;
    c = 1;
    previousMillis = millis();
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, LOW);
    digitalWrite(GROEN,HIGH);          // Turns Relay Off
    digitalWrite(ORANJE,LOW);           // Turns ON Relays 2

  }
      
  if (millis() - previousMillis >= 4000 && c == 1) {
    randomTime = random(20000, 40000);
    Serial.println(randomTime);
    c = 0;
    a = 1;
    previousMillis = millis();
    digitalWrite(LED3, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED1, HIGH);
    digitalWrite(ORANJE,HIGH);
    digitalWrite(VOL, HIGH);
    digitalWrite(ROOD,LOW);
  }
   
}

void trafficLightRed() {
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  digitalWrite(ROOD, LOW);
  digitalWrite(ORANJE, HIGH);
  digitalWrite(GROEN, HIGH);
  digitalWrite(VOL, HIGH);
}

void trafficLightOrange() {
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, LOW);
  digitalWrite(GROEN, HIGH);
  digitalWrite(ORANJE, LOW);
  digitalWrite(ROOD, HIGH);
  digitalWrite(VOL, HIGH);
}

void trafficLightGreen() {
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, HIGH);
  digitalWrite(ROOD, HIGH);
  digitalWrite(ORANJE, HIGH);
  digitalWrite(GROEN, LOW);
  digitalWrite(VOL, HIGH);
}

void trafficLightFull() {
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);
  digitalWrite(GROEN, HIGH);
  digitalWrite(ORANJE, HIGH);
  digitalWrite(ROOD, HIGH);
  digitalWrite(VOL, LOW);
}

void trafficLightOff() {
  d = 1;
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  digitalWrite(GROEN, HIGH);
  digitalWrite(ORANJE, HIGH);
  digitalWrite(ROOD, HIGH);
  digitalWrite(VOL, HIGH);
}

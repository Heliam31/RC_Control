/* LEDC Fade Arduino Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)
   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

// use 12 bit precision for LEDC timer
#define LEDC_TIMER_12_BIT 12

// use 5000 Hz as a LEDC base frequency
#define LEDC_BASE_FREQ 5000

// fade LED PIN (replace with LED_BUILTIN constant for built-in LED)
#define LED_BLUE 1
#define LED_YELLOW 3
#define LED_RED 21

// define starting duty, target duty and maximum fade time
#define LEDC_START_DUTY  (0)
#define LEDC_TARGET_DUTY (4095)
#define LEDC_FADE_TIME   (1000)

bool fade_ended = false;  // status of LED fade
bool fade_in = true;
int current_led = 0;

void ARDUINO_ISR_ATTR LED_FADE_ISR() {
  fade_ended = true;
}

void setup() {
  // Initialize serial communication at 115200 bits per second:
  Serial.begin(115200);

  // Setup timer with given frequency, resolution and attach it to a led pin with auto-selected channel
  ledcAttach(LED_BLUE, LEDC_BASE_FREQ, LEDC_TIMER_12_BIT);
  ledcAttach(LED_YELLOW, LEDC_BASE_FREQ, LEDC_TIMER_12_BIT);
  ledcAttach(LED_RED, LEDC_BASE_FREQ, LEDC_TIMER_12_BIT);
  
  // Setup and start fade on led (duty from 0 to 4095)
  ledcFade(LED_BLUE, LEDC_START_DUTY, LEDC_TARGET_DUTY, LEDC_FADE_TIME);
  Serial.println("LED Fade on started.");

  // Wait for fade to end
  delay(LEDC_FADE_TIME);

  // Setup and start fade off led and use ISR (duty from 4095 to 0)
  ledcFadeWithInterrupt(LED_BLUE, LEDC_TARGET_DUTY, LEDC_START_DUTY, LEDC_FADE_TIME, LED_FADE_ISR);
  Serial.println("LED Fade off started.");
}

void loop() {
  // Check if fade_ended flag was set to true in ISR
  if (fade_ended) {
    Serial.println("LED fade ended");
    fade_ended = false;


      switch (current_led) {
        case 0:
          // Check what fade should be started next
          if (fade_in) {
            ledcFadeWithInterrupt(LED_BLUE, LEDC_START_DUTY, LEDC_TARGET_DUTY, LEDC_FADE_TIME, LED_FADE_ISR);
            Serial.println("blue LED Fade in started.");
            fade_in = false;
          } else {
            ledcFadeWithInterrupt(LED_BLUE, LEDC_TARGET_DUTY, LEDC_START_DUTY, LEDC_FADE_TIME, LED_FADE_ISR);
            Serial.println("blue LED Fade out started.");
            fade_in = true;
            current_led ++;
          }
          break;

        case 1:
          // Check what fade should be started next
          if (fade_in) {
            ledcFadeWithInterrupt(LED_YELLOW, LEDC_START_DUTY, LEDC_TARGET_DUTY, LEDC_FADE_TIME, LED_FADE_ISR);
            Serial.println("yellow LED Fade in started.");
            fade_in = false;
          } else {
            ledcFadeWithInterrupt(LED_YELLOW, LEDC_TARGET_DUTY, LEDC_START_DUTY, LEDC_FADE_TIME, LED_FADE_ISR);
            Serial.println("yellow LED Fade out started.");
            fade_in = true;
            current_led ++;
          }
          break;

        case 2:
          // Check what fade should be started next
          if (fade_in) {
            ledcFadeWithInterrupt(LED_RED, LEDC_START_DUTY, LEDC_TARGET_DUTY, LEDC_FADE_TIME, LED_FADE_ISR);
            Serial.println("Red LED Fade in started.");
            fade_in = false;
          } else {
            ledcFadeWithInterrupt(LED_RED, LEDC_TARGET_DUTY, LEDC_START_DUTY, LEDC_FADE_TIME, LED_FADE_ISR);
            Serial.println("Red LED Fade out started.");
            fade_in = true;
            current_led = 0;
          }
          break;


        default:
          printf("frero wtf");
          return;
      }





  }
}

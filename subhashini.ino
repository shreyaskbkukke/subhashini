#include <LCDWIKI_GUI.h> // Core graphics library
#include <LCDWIKI_KBV.h> // Hardware-specific library
#include "DHT.h"

LCDWIKI_KBV mylcd(ILI9486, A3, A2, A1, A0, A4); // Model, CS, CD, WR, RD, Reset
#define BLACK 0x0000
#define WHITE 0xFFFF
#define GREEN 0x0FF0

const char* slokas[] = {
  "Sathyameveshware loke\nsathyam padmashritha sadaa\nSathyamulaani  sarvani\nsathyannasthi param padam",
  "Kimapyasthi swabhaavena\nsundaram vaapyasundaram\nYadeva rochathe yasmai\nthadbavethasya sundaram",
  "Krodhaha prithim pranashayathi\nmaano vinayanaashanaha\nMaaya mithrani naashayathi\nmobhaha sarvavinaashanaha",
  "Gopaayitharam daathaaram\ndamanithyamathandritham\nAkaamadweshasamyuktha\nmanurajyanthi maanavaha",
  "Sarva paravasham dukham\nsarva athmavasham sukham\nYethadwidyaathsamasena\nlakshanam sukhadukhayoho",
  "Loke kulam kulam\nthaavadyavathpurvasamanvayaha\nGunaprabhave vichinne\nsamaaptham sakalam kulam"
};

const char* subhashithas[] = {
  "Pruthvivyam thrini rathnani\njalam annam subhashitham\nmudeihi paashanakhandeshu\nrathnasajnaa pradiyathe",
  "Himalayaam samaarabya\nyaavath indu sarovaram\ntham devanirmitham desham\nhindustanam prachakshathe",
  "Ayam nijaha paro vethi\ngananaa laguchethasaam\nudaaracharithanam thu\ndusudeiva kutumbakam",
  "Astadashapuranaanam  saaram\nvyasena karthikam\nparopakaraha punyayaha\npaapaaya paripidanam",
  "Ashwasya bhushanam  vegoo\nmatham syad gajabhudshanam\nchathuryam bhushanam naaya\nudyoge narabhushanam",
  "Na abhisheko na samsaraha\nsimhasya kriyathe vane\nvikramarjithasathvasya\nswayameva  mrugedratha",
};

const int SlokaButtonPin = 53; // Digital pin to connect the button for slokas
const int SubhashithaButtonPin = 52; // Digital pin to connect the button for subhashithas

int currentSlokaIndex = 0; // Tracks the currently displayed sloka
int currentSubhashithaIndex = 0; // Tracks the currently displayed subhashitha
const int SensorButtonPin = 51;


DHT dht(50, DHT22);

void setup() {
  Serial.begin(9600);
  mylcd.Init_LCD();
  mylcd.Set_Rotation(3); // Rotate display to landscape mode
  Serial.println(mylcd.Read_ID(), HEX);

  for (int progress = 0; progress <= 100; progress += 10) {
    drawLoadingScreen(progress);
    delay(200);
  }

  pinMode(SlokaButtonPin, INPUT_PULLUP); // Set the button pin for slokas as an input with a pull-up resistor
  pinMode(SubhashithaButtonPin, INPUT_PULLUP); // Set the button pin for subhashithas as an input with a pull-up resistor

  drawHomeScreen();

  pinMode(SensorButtonPin, INPUT_PULLUP); // Set the button pin for sensor readings as an input with a pull-up resistor
  dht.begin(); // Initialize the DHT sensor
}

void drawLoadingScreen(int progress) {
  mylcd.Set_Text_Mode(0);
  mylcd.Set_Text_Size(3);
  mylcd.Set_Text_colour(BLACK);
  mylcd.Set_Text_Back_colour(WHITE);
  mylcd.Fill_Screen(WHITE);
  mylcd.Print_String("Loading...", 50, 100);

  // Draw a black progress bar
  int barX = 50;
  int barY = 150;
  int barWidth = 220;
  int barHeight = 20;
  mylcd.Set_Draw_color(BLACK);
  mylcd.Fill_Rectangle(barX, barY, barX + barWidth, barY + barHeight);

  // Fill the progress bar based on the given progress
  int fillWidth = map(progress, 0, 100, 0, barWidth);
  mylcd.Set_Draw_color(GREEN);
  mylcd.Fill_Rectangle(barX, barY, barX + fillWidth, barY + barHeight);
}

void drawHomeScreen() {
  mylcd.Set_Text_Mode(0);
mylcd.Set_Text_Size(2);
mylcd.Set_Text_colour(BLACK);
mylcd.Set_Text_Back_colour(WHITE);
mylcd.Fill_Screen(WHITE);

mylcd.Set_Text_Size(3);
mylcd.Print_String("I am Subhashini", 80, 100);
mylcd.Set_Text_Size(2); // Set a larger text size
mylcd.Print_String("Made by Sanskrit Department", 80, 200);
mylcd.Set_Text_Size(2); // Set a larger text size
mylcd.Print_String("KSS College Subrahmanya.", 80, 250);
}

void displaySloka(const char* sloka) {
  mylcd.Print_String(sloka, 50, 100);
}

void displaySensorData(float temperature, float humidity) {
  mylcd.Set_Text_Mode(0);
  mylcd.Set_Text_Size(2);
  mylcd.Set_Text_colour(BLACK);
  mylcd.Set_Text_Back_colour(WHITE);
  mylcd.Print_String("Temperature: " + String(temperature, 1) + " C", 50, 100);
  mylcd.Print_String("Humidity: " + String(humidity, 1) + " %", 50, 150);
}

void displaySubhashitha(const char* subhashitha) {
  mylcd.Print_String(subhashitha, 50, 100);
}

void loop() {

  // Check the button state for slokas
  if (digitalRead(SlokaButtonPin) == LOW) {
    mylcd.Set_Text_Size(3);
    mylcd.Fill_Screen(WHITE); // Replace WHITE with the desired background color
    currentSlokaIndex = (currentSlokaIndex + 1) % (sizeof(slokas) / sizeof(slokas[0]));
    delay(200); // Debounce the button
    displaySloka(slokas[currentSlokaIndex]);
    delay(3000);
  }

  // Check the button state for subhashithas
  if (digitalRead(SubhashithaButtonPin) == LOW) {
    mylcd.Set_Text_Size(3);
    currentSubhashithaIndex = (currentSubhashithaIndex + 1) % (sizeof(subhashithas) / sizeof(subhashithas[0]));
    delay(200); // Debounce the button
    displaySubhashitha(subhashithas[currentSubhashithaIndex]);
    delay(3000);
  }

  if (digitalRead(SensorButtonPin) == LOW) {
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    drawHomeScreen(); // Clear the screen
    displaySensorData(temperature, humidity); // Display temperature and humidity data
    delay(5000); // Display the data for 5 seconds
    drawHomeScreen(); // Clear the screen again
  }

  // Delay to avoid rapid changes when the buttons are held down
  delay(500);
}

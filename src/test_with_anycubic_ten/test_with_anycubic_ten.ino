// https://aliexpress.ru/item/1005001621936295.html?sku_id=12000016846765674&spm=a2g2w.productlist.list.13.64dadcdfQq504e

#include <Thermistor.h>
#include <NTC_Thermistor.h>
#include <SmoothThermistor.h>

#define TEMP_PIN               A0
#define REFERENCE_RESISTANCE   100000
#define NOMINAL_RESISTANCE     100000
#define NOMINAL_TEMPERATURE    25
#define B_VALUE                3950

#define SMOOTHING_FACTOR 5
Thermistor* thermistor = NULL;

#define TEN_PIN 9
#define MAX_HOT_LEVEL 250
#define DOBAVKA_T 20


#define ANSWER_T 210 // <=================================================

#define temp_history_size 10
int temp_history[temp_history_size] = {0};

void setup() {
  Serial.begin(9600);
  pinMode(TEN_PIN,OUTPUT);
  digitalWrite(TEN_PIN,0);

  pinMode(13,OUTPUT);

  Thermistor* originThermistor = new NTC_Thermistor(
    TEMP_PIN,
    REFERENCE_RESISTANCE,
    NOMINAL_RESISTANCE,
    NOMINAL_TEMPERATURE,
    B_VALUE
  );
  thermistor = new SmoothThermistor(originThermistor, SMOOTHING_FACTOR);
}

void loop() {
  long int t = average_temp();
  Serial.println(t);
  long int e = ANSWER_T - t;

  if (e>10) digitalWrite(13,0);
  else digitalWrite(13,1);
  
  //if (e<0) e = 0;
  e *= 30;
  e += DOBAVKA_T;
  ten(e);
}

int average_temp() {
  unsigned int average = 0;
  for (int i = 0; i<temp_history_size-1; i++) {
    temp_history[i] = temp_history[i+1];
    average += temp_history[i];
  }
  temp_history[temp_history_size-1] = temp();
  average += temp_history[temp_history_size-1];
  return average/temp_history_size;
}

int temp() {
  //return map(temp_basic(),510,0,27,300);
  //return temp_basic();
  return thermistor->readCelsius();
}

int temp_basic() {
  return analogRead(TEMP_PIN);
}

void ten(long int hot_level) {
  analogWrite(TEN_PIN,map(constrain(hot_level,0,100),0,100,0,MAX_HOT_LEVEL));
  //Serial.println(hot_level);
}

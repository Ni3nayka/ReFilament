// https://aliexpress.ru/item/1005001621936295.html?sku_id=12000016846765674&spm=a2g2w.productlist.list.13.64dadcdfQq504e

#define DIR_1 10
#define DIR_2 11
#define TEMP_PIN A0

#define temp_history_size 10
int temp_history[temp_history_size] = {0};

void setup() {
  Serial.begin(9600);
  pinMode(DIR_1,OUTPUT);
  pinMode(DIR_2,OUTPUT);
  digitalWrite(DIR_1,0);
  digitalWrite(DIR_2,0);
}

void loop() {
  Serial.println(average_temp());
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
  return temp_basic();
}

int temp_basic() {
  return analogRead(TEMP_PIN);
}

void ten(int hot_level) {
  analogWrite(DIR_1,map(constrain(hot_level,0,100),0,100,0,255));
}

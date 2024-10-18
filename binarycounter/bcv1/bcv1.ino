#define SER 2
#define RCLK 3
#define SERCLK 4
#define ADD 6
#define SUB 5
#define DOUBLE 8
#define HALF 7
void setup() {
  Serial.begin(9600);
  pinMode(SER, OUTPUT);
  pinMode(RCLK, OUTPUT);
  pinMode(SERCLK, OUTPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);

 digitalWrite(RCLK, LOW);
shiftOut(SER, SERCLK, MSBFIRST, 0);
digitalWrite(RCLK, HIGH);

}
  uint8_t num = 0;
  int8_t states = 0;
  //int8_t n_states = 0;
  
void loop() {

  //assigns the first four bits of states to each state of the buttons
  states = (states | 0x01) & ((digitalRead(ADD) << 0) | ~(0x01)); 
  states = (states | 0x02) & ((digitalRead(SUB) << 1) | ~(0x02));
  states = (states | 0x04) & ((digitalRead(DOUBLE) << 2) | ~(0x04));
  states = (states | 0x08) & ((digitalRead(HALF) << 3) | ~(0x08));
   Serial.println(num);
//if it is first cycle of a button press
  num += !(states & 0x10) && (states & 0x01); //increment num by 1 
  num -= !(states & 0x20) && (states & 0x02); //decrement num by 1
  num = num << (!(states & 0x40) && (states & 0x04)); //double num
  num = num >> (!(states & 0x80) && (states & 0x08)); //half num

//writes num to the shift register, then LEDS
digitalWrite(RCLK, LOW);
shiftOut(SER, SERCLK, MSBFIRST, num);
digitalWrite(RCLK, HIGH);


  //after initial button press set corresponding bit to show that press has already been processed
  states = (states | 0x10) & (states << 4) | (states & 0x0f); 
  states = (states | 0x20) & (states << 4) | (states & 0x0f);
  states = (states | 0x40) & (states << 4) | (states & 0x0f);
  states = (states | 0x80) & (states << 4) | (states & 0x0f);
  
  
  //if the user presses a different button after pressing the one they committed the action of it will not clear the system
  //This has been fixed, user can press hold buttons and then press others as it is now non blocking
   

  

}

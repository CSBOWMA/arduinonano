void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(13, INPUT);
  digitalWrite(10, HIGH);  
}
  long num = 0;
  int state = 0;
  int state2 = 0;
void loop() {

  //maps out num to its binary representation
  for (int i = 2; i <= 9; i++) { 
    digitalWrite(i, num & (0x1 << (i-2))); 
  }
  state2 = state;
  state = digitalRead(13);
  
  num += state2 < state; //Change in state, when state increases i.e. on button press
  num = num%256;
}

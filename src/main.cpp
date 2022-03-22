/* 
  master
 
  main para pegar dados do slave e manda via serial
 */

#include <SPI.h>

#define PIN_ACTIVE_SLAVE 2

void print_data_get_master();
void get_data_slave();
int8_t check_data_is_correct();

uint8_t count = 0;
int8_t check = 1;

int data[4] = {0, 0, 0, 0};



void setup()
{
  Serial.begin(9600);

  pinMode(PIN_ACTIVE_SLAVE, OUTPUT);
  pinMode(SS, INPUT_PULLUP);
  pinMode(MOSI, OUTPUT);
  pinMode(SCK, INPUT);
  SPCR |= _BV(SPE);
  SPI.attachInterrupt();  //allows SPI interrupt

  digitalWrite(PIN_ACTIVE_SLAVE, HIGH);

}

void loop(void)
{
  
  if(count == 4 && check == 0) {
    Serial.println("if linha 46");
    print_data_get_master();
  count = 0;
    } 

  }


ISR (SPI_STC_vect)   //Inerrrput routine function
{
  data[count] = SPDR;
  count ++;
}

// factor alterar tempo de pulso para 50ms
void get_data_slave() {
  
  digitalWrite(PIN_ACTIVE_SLAVE, LOW);
  delay(500);
  digitalWrite(PIN_ACTIVE_SLAVE, HIGH);
}

void print_data_get_master() {

  for(uint8_t i = 0; i < 4; i++) {
    Serial.println(data[i]);
  }
    
}

int8_t check_data_is_correct() {
    int soma = 0;
    int8_t result = 1;
  for(int8_t i = 0; i < 3; i++) {
    soma += data[i];
  }
  if(soma == data[3]) {
   soma = 0;
    result = 0;
  } else {

   soma = 0;
   result = 1;
  }
  return result;
}
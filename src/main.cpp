/* 
  master
 
  main para pegar dados do slave e manda via serial
 */

#include <SPI.h>
#include <YF_s201c.h>

#define PIN_ACTIVE_SLAVE 2

void print_data_get_master();
void get_data_slave();

uint8_t count = 0;
int8_t check = 1;
unsigned int sumTest = 0;

 Data_all_sensor_t data = {0, 0, 0, 0};


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

  sumTest = check_sum(data);

    if(!data[3] == 0) {
    print_data_get_master();
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
  delay(10);
  digitalWrite(PIN_ACTIVE_SLAVE, HIGH);
}

void print_data_get_master() {

  for(uint8_t i = 0; i < 3; i++) {
    Serial.println(data[i]);
  }
      Serial.print("checksum");
    Serial.println(sumTest);
    Serial.print("do spi ");
    Serial.println(data[3]);
    
}

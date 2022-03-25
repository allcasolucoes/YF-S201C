/* 
  master
 
  main para pegar dados do slave e manda via serial
 */

#include <SPI.h>
#include <YF_s201c.h>

#define PIN_ACTIVE_SLAVE 7

void print_data_get_master();
void get_data_slave();

void post_old_data();

uint8_t count = 0;
int check = 0;

 Data_all_sensor_t data = {0, 0, 0, 0};
 Data_all_sensor_t dataOld = {0, 0, 0, 0};



void setup()
{

  Serial.begin(9600);


  pinMode(PIN_ACTIVE_SLAVE, OUTPUT);
  digitalWrite(PIN_ACTIVE_SLAVE, HIGH);

  
  pinMode(SS, INPUT_PULLUP);
  pinMode(MOSI, OUTPUT);
  pinMode(SCK, INPUT);
  SPCR |= _BV(SPE);
  SPI.attachInterrupt();  //allows SPI interrupt


}

void loop(void)
{

  get_data_slave();

  check = check_sum(data);

    if(data[3] == check && data[0] != 0) {

    post_old_data();
   // print_data_get_master();

    } else {
      Serial.println("Solicitando do slave");
    }

  }

ISR (SPI_STC_vect)   //Inerrrput routine function
{
  data[count] = SPDR;
  count ++;
}

void post_old_data() {

      for(uint8_t i = 0; i < 3; i++) {

      if(data[i] < dataOld[i]) {
          Serial.print(data[i]);
          Serial.print(" -1 ");
          Serial.print(dataOld[i]);
          Serial.println(" ");
      }
      if(data[i] == dataOld[i]) {
          Serial.print(data[i]);
          Serial.print(" +0 ");
          Serial.print(dataOld[i]);
          Serial.println(" ");

      }
      if(data[i] > dataOld[i]) {
          Serial.print(data[i]);
          Serial.print(" +1 ");
          Serial.print(dataOld[i]);
          Serial.println(" ");

      }
      Serial.println("------------");
        }

        for(uint8_t d = 0; d < 3; d++) {
        dataOld[d] = data[d];
        }
}

// factor alterar tempo de pulso para 50ms
void get_data_slave() {
  
  digitalWrite(PIN_ACTIVE_SLAVE, LOW);
  delay(10);
  digitalWrite(PIN_ACTIVE_SLAVE, HIGH);
  delay(2000);
}


void print_data_get_master() {
  for(uint8_t i = 0; i < 3; i++) {
    Serial.println(data[i]);
  } 
}

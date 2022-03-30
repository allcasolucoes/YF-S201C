/* 
  master
 
  main para pegar dados do slave e manda via serial
 */

#include <SPI.h>
#include <YF_s201c.h>

#define PIN_ACTIVE_SLAVE 7

void get_data_slave();
float fluxo(int pulso);
void send_data_fluxo(int *pulse,volatile int *dataOld);

void view_data_old(volatile int *data);

void post_old_data();

uint8_t count = 0;
int check = 0;
uint8_t updade = 0;

 Data_all_sensor_t data = {0, 0, 0, 0};
 //Data_all_sensor_t dataOld = {24, 26, 25, 75};
  volatile int data_antiga[4] = {5, 5, 5, 75};


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

      delay(200);
    //post_old_data();
    send_data_fluxo(data, data_antiga);

    } else {
      Serial.println("Aguardando dados do modulo");

    }   

    Serial.println("----- data");
    view_data_old(data);

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
  delay(2000);
}


float fluxo(int pulso) {
return pulso / 10.7;

}

void send_data_fluxo(int *pulse,volatile int *dataOld) {
  Serial.println("---------------------");
    int i;
    for(i = 0; i < 3; i++) {
        
    float tmp = 0;
    if(pulse[i] > dataOld[i]) {
       dataOld[i] += 1;
        tmp = dataOld[i]  / 10.7;
       
         Serial.println(tmp);
    } 
    if(pulse[i] < dataOld[i]) {
         dataOld[i] -= 1;
        tmp = dataOld[i]  / 10.7;
         Serial.println(tmp);
    } 
     if(pulse[i] == dataOld[i]) {
        tmp = dataOld[i] / 10.7;
         Serial.println(tmp);
    }
        
    }
  Serial.println("###############");

}

void view_data_old(volatile int *data) {
       for(int i = 0; i < 3; i++) {
      Serial.println(data[i]);
    }
}
/* 
  main file comunication slave spi

 */

#include <Arduino.h>
#include <SPI.h>
#define PIN3_INT_1 3
#define SLAVE_SENSOR_1 10
#define PIN_GET_DATA 2


void increment_pulse_sensor_1();
void send_to_master_vasao(float vasao);
void send_to_master_vetor_test();
void set_value_sensor();

int check_sum(int *data);
float vazao_sensor_1;
unsigned int total_pulse_1_second;
uint8_t pin_2_state = 0;

int data[4] = {0, 0, 0, 0};



void setup() {

  SPI.begin();

  pinMode(PIN_GET_DATA, INPUT);
  Serial.begin(9600);
  pinMode(PIN3_INT_1, INPUT);                          // configura pino 3 para receber sinal e chamar interrupção 1
  attachInterrupt(1, increment_pulse_sensor_1, RISING);      // habilita chamada à primeira interrupção (rotâmetro 1)

}

void loop() {
  
  total_pulse_1_second = 0;

  // mudar para posteriomente interrupcao via software
  sei();
  delay(1000);
  cli();      

/* 
  Equação para conversão da contagem de pulsos em fluxo (L/min) para rot. 1
  espera-se que os fluxos não passem de 500 L/min
 */
  vazao_sensor_1 = total_pulse_1_second / 10.7;                    
                                                  
  Serial.println(vazao_sensor_1); // linha para ser removida

  //send_to_master_vasao(vazao_sensor_1);

  pin_2_state = digitalRead(PIN_GET_DATA);

// refatorar para interrupçãos
  if(pin_2_state) {
  send_to_master_vetor_test();
  delay(100);
  Serial.println("bottão precionado");

}

}
// rotina chamada pela interrupção provocada pelo rotâmetro 1
void increment_pulse_sensor_1() {
  total_pulse_1_second++;

}

void send_to_master_vasao(float vasao) {

  digitalWrite(SLAVE_SENSOR_1, LOW);
  SPI.transfer(15);
  delay(100);
}

void set_value_sensor() {
  for(int i = 0; i < 3; i++) {
    data[i] = 15 + i;
    }
    data[3] = check_sum(data);
}

void send_to_master_vetor_test() {
  set_value_sensor();
  for(int i = 0; i < 4; i++) {
    digitalWrite(SLAVE_SENSOR_1, LOW);
    SPI.transfer(data[i]);
    delay(100);
    }
  digitalWrite(SLAVE_SENSOR_1, HIGH);
}


// factor para checagem de tramanho vetor
int check_sum(int *data) {
  int checksum = 0;
    for(int i = 0; i < 3; i++) {
      checksum += data[i];
    }
    return checksum;
}
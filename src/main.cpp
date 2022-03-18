/* 
  main file comunication slave spi

 */

#include <Arduino.h>
#include <SPI.h>
#define PIN3_INT_1 3
#define SLAVE_SENSOR_1 10

void increment_pulse_sensor_1();
void send_to_master_vasao(float vasao);
char buf = 15;
float vazao_sensor_1;
unsigned int total_pulse_1_second;



void setup() {

  digitalWrite(SLAVE_SENSOR_1, HIGH);
  SPI.begin();


  Serial.begin(9600);
  pinMode(PIN3_INT_1, INPUT);                          // configura pino 3 para receber sinal e chamar interrupção 1
  attachInterrupt(1, increment_pulse_sensor_1, RISING);      // habilita chamada à primeira interrupção (rotâmetro 1)

}

void loop() {
  
  total_pulse_1_second = 0;
  sei();          // habilita interrupção
  delay(1000);                                    // aguarda 1 segundo entre leituras
  cli();          // desabilita interrupção

/* 
  Equação para conversão da contagem de pulsos em fluxo (L/min) para rot. 1
  espera-se que os fluxos não passem de 500 L/min
 */
  Serial.println(total_pulse_1_second); // linha para ser removida

  vazao_sensor_1 = total_pulse_1_second / 10.7;                    
                                                  
  Serial.println(vazao_sensor_1); // linha para ser removida

  send_to_master_vasao(vazao_sensor_1);

}
// rotina chamada pela interrupção provocada pelo rotâmetro 1
void increment_pulse_sensor_1() {
  total_pulse_1_second++;
}

void send_to_master_vasao(float vasao) {

  digitalWrite(SLAVE_SENSOR_1, LOW);
  SPI.transfer(4.3);
  delay(5); // em teste
  digitalWrite(SLAVE_SENSOR_1, HIGH);
  delay(100);
}
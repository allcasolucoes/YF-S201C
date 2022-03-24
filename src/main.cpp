/* 
  main file comunication slave spi

 */

#include <Arduino.h>
#include <SPI.h>
#include <YF_s201c.h>

 Data_all_sensor_t  data_all_sensor = {0, 0, 0, 0};

float vazao_sensor_1;
uint8_t pin_2_state = 0;
volatile unsigned int total_pulse_1_second = 0;

struct Config_slave config_slave;

void increment_pulse_sensor_1();
void send_all_data_to_master();


void setup() {

  config_slave.pin_interrupt_count = 3;
  config_slave.pin_ss = 10;

  SlaveSend::config_interrupt_to_active();

 SPI.begin();

 Serial.begin(9600);// testes devem ser removidos 

  pinMode(config_slave.pin_interrupt_count, INPUT);

  attachInterrupt(digitalPinToInterrupt(config_slave.pin_interrupt_count), 
  increment_pulse_sensor_1, RISING);
}

void loop() {

  total_pulse_1_second = 0;

  sei();
  delay(1000);
  cli();

  // testes devem ser removidos 
  data_all_sensor[0] = total_pulse_1_second;
  Serial.print("Leiruta numero pulos: ");
  Serial.println(total_pulse_1_second);
 
}


// encapsular em uma funlçao que receve função como parametro
ISR (PCINT2_vect) {
  send_all_data_to_master();
  }

void increment_pulse_sensor_1() {
  total_pulse_1_second ++;
}

 void send_all_data_to_master() {
    
   send_to_master_vetor_data(config_slave.pin_ss, data_all_sensor);
   Serial.print("Interrupcao 4");
} 
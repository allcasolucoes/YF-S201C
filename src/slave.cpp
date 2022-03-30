/* 
  main file comunication slave spi

 */

#include <Arduino.h>
#include <SPI.h>
#include <YF_s201c.h>

Data_all_sensor_t  data_all_sensor = {0, 0, 0, 0};


volatile unsigned int total_pulse_1_second = 0;
volatile unsigned int total_pulse_1_second2 = 0;


struct Config_slave config_slave;

void increment_pulse_sensor_1();
void increment_pulse_sensor_2();

void setup() {

  config_slave.pin_interrupt_count = 3;
  config_slave.pin_ss = 10;

// inicia configução para interrupcap de chamada do master
SlaveSend::config_interrupt_to_active();

 SPI.begin();

 Serial.begin(9600);// testes devem ser removidos 

  pinMode(config_slave.pin_interrupt_count, INPUT);

  attachInterrupt(digitalPinToInterrupt(config_slave.pin_interrupt_count), 
  increment_pulse_sensor_1, RISING);
    attachInterrupt(digitalPinToInterrupt(2), 
  increment_pulse_sensor_2, RISING);


}

void loop() {

  total_pulse_1_second = 0;
  total_pulse_1_second2 = 0;

  sei();
  delay(1000);
  cli();

  // testes devem ser removidos 
  data_all_sensor[0] = total_pulse_1_second;
  data_all_sensor[1] = total_pulse_1_second2;

}


// encapsular em uma funlçao que receve função como parametro
  ISR (PCINT2_vect) {
  PCICR |= B00000000; // disabled interrupts on PD port
  send_to_master_vetor_data(config_slave.pin_ss, data_all_sensor);
  delayMicroseconds(100);
  PCICR |= B00000100; // Enable interrupts on PD port
  }  

void increment_pulse_sensor_1() {
  total_pulse_1_second ++;
}
void increment_pulse_sensor_2() {
  total_pulse_1_second2 ++;
}

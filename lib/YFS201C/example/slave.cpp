/* 
 github.com/kleysoncastro
 
 ** exemplo deve ser gravado no MCU que sera responsavel por ler dados dos sensores
  e enviar via spi

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

// corrigir pinos de interrupção
  config_slave.pin_interrupt_count = 3;
  config_slave.pin_ss = 10;
  config_slave.pin_get_data = 2;

  SPI.begin();
  Serial.begin(9600);

  pinMode(config_slave.pin_get_data, INPUT_PULLUP);
  pinMode(config_slave.pin_interrupt_count, INPUT);// configura pino 3 para receber sinal e chamar interrupção 1

  attachInterrupt(digitalPinToInterrupt(config_slave.pin_interrupt_count), increment_pulse_sensor_1, RISING);// habilita chamada à primeira interrupção (rotâmetro 1)
  attachInterrupt(digitalPinToInterrupt(config_slave.pin_get_data), send_all_data_to_master, LOW);
}

void loop() {
  
  // mudar para posteriomente interrupcao via software
  total_pulse_1_second = 0;

  sei();
  delay(1000);
  cli();
  data_all_sensor[0] = total_pulse_1_second;

/* 
  Equação para conversão da contagem de pulsos em fluxo (L/min) para rot. 1
  espera-se que os fluxos não passem de 500 L/min
 */
  // vazao_sensor_1 = total_pulse_1_second / 10.7;                    


}

void increment_pulse_sensor_1() {
  total_pulse_1_second ++;
}

void send_all_data_to_master() {
    send_to_master_vetor_data(config_slave.pin_ss, data_all_sensor);
    delayMicroseconds(100);

}
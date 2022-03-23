#include <Arduino.h>
#include <SPI.h>
#include "YF_s201c.h"

// factor para checagem de tramanho vetor
int check_sum(int *data_all_sensor) {
  int checksum = 0;
    for(int i = 0; i < 3; i++) {
      checksum += data_all_sensor[i];
    }
    return checksum;
}


void send_to_master_vetor_data(uint8_t pin_ss, int *data_all_sensor) {
  //set_value_sensor(data_all_sensor);
  for(int i = 0; i < 4; i++) {
    digitalWrite(pin_ss, LOW);
    if(i == 3) data_all_sensor[3] = check_sum(data_all_sensor);
    SPI.transfer(data_all_sensor[i]);
    Serial.print("checke sum ");
    Serial.println(data_all_sensor[3]);
    Serial.print("posicao 0: ");
    Serial.println(data_all_sensor[0]);
    }
    Serial.println(data_all_sensor[3]);
  digitalWrite(pin_ss, HIGH);
}


void send_to_master_vasao(float vasao, uint8_t pin_ss) {

  digitalWrite(pin_ss, LOW);
  SPI.transfer(15);
  delay(100);
}

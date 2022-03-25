#include "YF_s201c.h"

// Retorna o soma das 3 primeiras posições do vetor
unsigned int check_sum(int *data_all_sensor) {
  unsigned int checksum = 0;
    for(int i = 0; i < 3; i++) {
      checksum += data_all_sensor[i];
    }

    return checksum;
}


void send_to_master_vetor_data(uint8_t pin_ss, int *data_all_sensor) {
  for(int i = 0; i < 4; i++) {
    digitalWrite(pin_ss, LOW);
    if(i == 3) data_all_sensor[3] = check_sum(data_all_sensor);
    SPI.transfer(data_all_sensor[i]);
    }
    SPI.endTransaction();
  digitalWrite(pin_ss, HIGH);
}


void send_to_master_vasao(float vasao, uint8_t pin_ss) {

  digitalWrite(pin_ss, LOW);
  SPI.transfer(15);
  delay(100);
  }

// Configuração para port D
// Interrupção D4
 void SlaveSend::config_interrupt_to_active() {

  pinMode(4, INPUT_PULLUP);
  PCICR |= B00000100; // Enable interrupts on PD port
  PCMSK2 |= B00010000; // Trigger interrupts on pins D4 
  
}


 
#include <Arduino.h>
#include <SPI.h>

#ifndef YFS201C_H
#define YFS201C_H

        typedef int Data_all_sensor_t[4];
        struct Config_slave {
        int8_t pin_interrupt_count;
        int8_t pin_ss;
        };
        void send_to_master_vetor_data(uint8_t pin_ss, int *data_all_sensor);
        unsigned int check_sum(int *data_all_sensor);


    class SlaveSend {
        
        public:
        static void config_interrupt_to_active();
        private:
        void send_to_master_vasao(float vasao);

    };

#endif
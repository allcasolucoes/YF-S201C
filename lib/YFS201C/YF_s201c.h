#ifndef YFS201C_H
#define YFS201C_H
        typedef int Data_all_sensor_t[4];
        struct Config_slave {
        int8_t pin_interrupt_count;
        int8_t pin_ss;
        int8_t pin_get_data;
        };
        void send_to_master_vetor_data(uint8_t pin_ss, int *data_all_sensor);

namespace Saleve { 
    class SlaveSend {

        private:
        void send_to_master_vasao(float vasao);
        int check_sum(int *data_all_sensor);

    };
};

#endif
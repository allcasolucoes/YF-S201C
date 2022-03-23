#### @uth `github.com/kleysoncastro` email `kleysoncastro99@gmail.com`

## Lib para leiruta de fluxometros
##  Modelos: 

* YF-S201C

## MCu's testados
* Atmega328p

### Para usar esse lib duas estruturas de dados de dados são necessárias.

```c
// 1º estrutura é um typedef int[4],
// 3 primeiras posições fica o número de pulsos dos sensores
// 4º posição fica o checksum
struct Config_slave config_slave;

// exemplo de uso
Data_all_sensor_t  data_all_sensor = {0, 0, 0, 0};

// setando checksum ex:
data_all_sensor[3] = checksum(data);

```

### Segunda estrutura de dados, configurações
```c
 struct Config_slave {
        int8_t pin_interrupt_count;
        int8_t pin_ss;
        int8_t pin_get_data;
        };
/* 
* pin_interrupt é o pino onde esta o sensor rotometro
* pin_ss é o pino de seleção slave select
* pin_get_data pino ativo em low [por interrupt] para enviar os dados, 
 */

// exemplo de uso
  config_slave.pin_interrupt_count = 3;
  config_slave.pin_ss = 10;
  config_slave.pin_get_data = 2;
```


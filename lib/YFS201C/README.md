#### @uth `github.com/kleysoncastro` email `kleysoncastro99@gmail.com`

## Lib para leituta de fluxometros
##  Modelos: 

* YF-S201C

## MCu's testados
* Atmega328p

### Para usar esse lib duas estruturas de dados são necessárias;
### Essa lib depende de `<SPI.h>`


###  1º estrutura é um `typedef int[4]` 
3 primeiras posições do vetor fica o número de pulsos dos sensores 
4º posição fica o checksum

```c

// YF_s201c.h
typedef int Data_all_sensor_t[4];

// exemplo de uso
 Data_all_sensor_t  data_all_sensor = {0, 0, 0, 0};
```
### As 3 primeiras posições do vetor serão setadas por interrupção

#### exemplo:
```c
void loop() {

  total_pulse_1_second = 0;

  sei();
  delay(1000);
  cli();
  data_all_sensor[0] = total_pulse_1_second;
 
}

void increment_pulse_sensor_1() {
  total_pulse_1_second ++;
}

```

## Sobre a função checksum();
Ela recebe um `Data_all_sensor_t` e retorna `int`

`A função checksum() é usanda internamente, não precisa ser chamada, isso é feito internamente`

### Segunda estrutura de dados, `struct Config_slav`
```c
 struct Config_slave {
        int8_t pin_interrupt_count;
        int8_t pin_ss;
        int8_t pin_get_data;
        };
```
#### pin_interrupt é o pino onde esta o sensor rotometro.
#### pin_ss é o pino de seleção slave select.
#### pin_get_data pino ativo em low [por interrupt] para enviar os dados.

#### exemplo:
```c
struct Config_slave config_slave;

void setup() {
config_slave.pin_interrupt_count = 3; 
config_slave.pin_ss = 10; 
config_slave.pin_get_data = 2; 
...
}
```


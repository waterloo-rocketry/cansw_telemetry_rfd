#include <xc.h>

#include "adc.h"
#include "device_config.h"
#include "platform.h"
#include "radio.h"
#include "uart.h"

#define MAX_LOOP_TIME_DIFF_ms 500
#define MAX_SENSOR_TIME_DIFF_ms 5

static void can_msg_handler(const can_msg_t *msg);

// MAIN JUST TO TEST UART DRIVER WITH LEDS

int main(void) {
  // initialize oscillator, millis() function, and pins
  oscillator_init();
  timer0_init();
  gpio_init();

  // init uart
  uart_init(115200, 48000000UL, true);

  // enable global interrupts
  INTCON0bits.GIE = 1;

  // loop timer
  uint32_t last_millis = millis();
  uint32_t last_sensor_millis = millis();

  bool heartbeat = false;

  while (1) {
    CLRWDT(); // reset watchdog timer

    if (OSCCON2 != 0x70) { // if fail-safe clock monitor has triggered
      oscillator_init();
    }

    // heartbeat led + uart
    if (millis() - last_millis > MAX_LOOP_TIME_DIFF_ms) {
      // update loop counter
      last_millis = millis();

      // visual heartbeat indicator
      BLUE_LED_SET(heartbeat);
      RED_LED_SET(heartbeat);
      heartbeat = !heartbeat;

      // UART test
      const char *test = "Hello World V2.1 ";
      for (uint8_t i = 0; test[i] != '\0'; i++) {
        uart_transmit_byte(test[i]);
      }
    }

    // keep the board stable when USB-Serial is connected
    if (millis() - last_sensor_millis > MAX_SENSOR_TIME_DIFF_ms) {
      update_sensor_low_pass();
    }
  }
}

static void __interrupt() interrupt_handler(void) {
  // timer0 interrupt for millis
  if (PIE3bits.TMR0IE == 1 && PIR3bits.TMR0IF == 1) {
    timer0_handle_interrupt();
    PIR3bits.TMR0IF = 0;
  } else if (PIR3 & 0x78) {
    uart_interrupt_handler(); // UART rx/tx
  }
}

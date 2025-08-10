#include "pico/stdlib.h"

#define LED1_PIN      16   // GPIO16
#define LED2_PIN      20   // GPIO20
#define ONBOARD_LED   25   // GPIO25 (onboard LED)

static void blink_pin(uint pin, int times, uint32_t period_ms) {
    for (int i = 0; i < times; ++i) {
        gpio_put(pin, 1);
        sleep_ms(period_ms);
        gpio_put(pin, 0);
        sleep_ms(period_ms);
    }
}

int main() {
    stdio_init_all();

    // Init LEDs
    gpio_init(LED1_PIN);
    gpio_set_dir(LED1_PIN, GPIO_OUT);
    gpio_put(LED1_PIN, 0);

    gpio_init(LED2_PIN);
    gpio_set_dir(LED2_PIN, GPIO_OUT);
    gpio_put(LED2_PIN, 0);

    gpio_init(ONBOARD_LED);
    gpio_set_dir(ONBOARD_LED, GPIO_OUT);
    gpio_put(ONBOARD_LED, 0);

    const uint32_t period_ms = 250;
    const int times = 10;

    while (true) {
        blink_pin(LED1_PIN, times, period_ms);     // GPIO16 (LED 1) x10
        blink_pin(ONBOARD_LED, times, period_ms);  // GPIO25 (Default which is the onboard LED) x10
        blink_pin(LED2_PIN, times, period_ms);     // GPIO20 (LED 2) x10
    }
}

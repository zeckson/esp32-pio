#include <HardwareSerial.h>
#include "WiFi.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

#define BLINK_GPIO GPIO_NUM_2

TickType_t DELAY = 1000 / portTICK_PERIOD_MS;

void blink(int nTimes) {

    nTimes = nTimes < 0 ? 0 : nTimes;

    for (int i = 0; i < nTimes; i++) {
        /* Blink off (output low) */
        printf("Turning off the LED\n");
        gpio_set_level(BLINK_GPIO, 0);

        vTaskDelay(DELAY);
        /* Blink on (output high) */
        printf("Turning on the LED\n");
        gpio_set_level(BLINK_GPIO, 1);
        vTaskDelay(DELAY);
    }
}

const char *ssid = "xxx";
const char *password = "xxx";

void setup() {
    gpio_pad_select_gpio(BLINK_GPIO);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);

    Serial.begin(115200);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("Connecting to WiFi..");
    }

    blink(3);
    Serial.println("Connected to the WiFi network");

}

void loop() {}
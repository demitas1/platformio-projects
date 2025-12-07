#include <Arduino.h>
#include <FreeRTOS.h>
#include <task.h>

#define LED_PIN 25

void vBlinkTask(void *pvParameters) {
    pinMode(LED_PIN, OUTPUT);

    while (1) {
        digitalWrite(LED_PIN, HIGH);
        Serial.println("LED ON");
        vTaskDelay(pdMS_TO_TICKS(500));

        digitalWrite(LED_PIN, LOW);
        Serial.println("LED OFF");
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void setup() {
    Serial.begin(115200);
    delay(2000);  // Wait for serial connection

    Serial.println("Starting LED Blink with FreeRTOS");

    xTaskCreate(
        vBlinkTask,
        "Blink",
        256,
        NULL,
        1,
        NULL
    );
}

void loop() {
    // FreeRTOS handles tasks
    vTaskDelay(pdMS_TO_TICKS(1000));
}

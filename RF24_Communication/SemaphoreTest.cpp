// SemaphoreTest.cpp

#include <Arduino.h>

#include <mutex>

#include "ProgramDefinitions.h"

#include "SemaphoreTest.h"

#if defined (_SEMAPHORE_TEST_)

SemaphoreHandle_t mutex = xSemaphoreCreateMutex();

void SetupSemaphoreTest() {

    assert(mutex);
    Serial.begin(112500);
    xTaskCreate(vTask1, "Task 1", 10000, NULL, 1, NULL);
    xTaskCreate(vTask2, "Task 2", 10000, NULL, 1, NULL);
}

void LoopSemaphoreTest() {}

void vTask1(void* pvParameters) {
    for (;;) {
        xSemaphoreTake(mutex, portMAX_DELAY); // enter critical section
        Serial.println("Task 1 is running");
        xSemaphoreGive(mutex); // exit critical section
    }
}

void vTask2(void* pvParameters) {
    for (;;) {
        xSemaphoreTake(mutex, portMAX_DELAY); // enter critical section
        Serial.println("Task 2 is running");
        xSemaphoreGive(mutex); // exit critical section
    }
}

#endif

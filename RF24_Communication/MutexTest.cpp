// MutexTest.cpp

#include <Arduino.h>

#include <mutex>

#include "ProgramDefinitions.h"

#include "MutexTest.h"

#if defined (_MUTEX_TEST_)

std::mutex serial_mtx;

void setup() {
    Serial.begin(112500);
    xTaskCreate(vTask1, "Task 1", 10000, NULL, 1, NULL);
    xTaskCreate(vTask2, "Task 2", 10000, NULL, 1, NULL);
}

void loop() {}

void vTask1(void* pvParameters) {
    for (;;) {
        std::lock_guard<std::mutex> lck(serial_mtx);
        Serial.println("Task 1 is running");
    }
}

void vTask2(void* pvParameters) {
    for (;;) {
        std::lock_guard<std::mutex> lck(serial_mtx);
        Serial.println("Task 2 is running");
    }
}


#endif

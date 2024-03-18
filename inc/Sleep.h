#pragma once
#ifndef SLEEP_H
#define SLEEP_H
#include <chrono>

void customSleep(int milliseconds) {
    auto start = std::chrono::high_resolution_clock::now();
    auto end = start + std::chrono::milliseconds(milliseconds);
    while (std::chrono::high_resolution_clock::now() < end) {
        // Busy-wait loop.
    }
}
#endif
#pragma once
#include <chrono>
#include <iomanip>
using namespace std;

struct TimingResult {
    double avg_ms = 0.0;
    long long avg_ns = 0;
    int repetitions = 1;
};

template <typename Explorer>
TimingResult measure_time(const graphProblem& problem) {
    int repetitions = 1;
    volatile size_t sink = 0;

    while (repetitions <= (1 << 20)) {
        auto start = chrono::steady_clock::now();
        for (int i = 0; i < repetitions; ++i) {
            Explorer probe_explorer;
            sink += probe_explorer.search_solution(problem).size();
        }
        auto end = chrono::steady_clock::now();

        const long long total_ns = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        if (total_ns > 0) {
            TimingResult result;
            result.repetitions = repetitions;
            result.avg_ns = total_ns / repetitions;
            result.avg_ms = static_cast<double>(result.avg_ns) / 1e6;
            return result;
        }
        repetitions *= 2;
    }

    (void)sink;
    return {};
}
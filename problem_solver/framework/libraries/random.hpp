#pragma once

#include <random>
using namespace std;
class Random {
    public:
        static int random_int(int min, int max) {
            std::uniform_int_distribution<int> dis(min, max);
            return dis(generator());
        }

        static double random_double(double min, double max) {
            std::uniform_real_distribution<double> dis(min, max);
            return dis(generator());
        }

        static double random() {
            std::uniform_real_distribution<double> dis(0.0, 1.0);
            return dis(generator());
        }

    private:
        static std::mt19937& generator() {
            static thread_local std::mt19937 gen(std::random_device{}());
            return gen;
        }
};

inline int random_int(int min, int max) {
    return Random::random_int(min, max);
}

inline double random_double(double min, double max) {
    return Random::random_double(min, max);
}

inline double random() {
    return Random::random();
}
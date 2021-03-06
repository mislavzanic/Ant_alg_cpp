//
// Created by mislav on 12/16/20.
//

#ifndef MHRAD_RANDOM_H
#define MHRAD_RANDOM_H

#include <ctime>
#include <random>

template <typename Engine = std::mt19937>
class Random {
    template <typename T>
    using UniformDistr    = std::uniform_real_distribution<T>;
    using UniformIntDistr = std::uniform_int_distribution<int>;

public:
    Random(int seed = std::time(nullptr)) : m_prng(seed) {}
    Random(const Random& r) : m_prng(r.m_prng) {}
    Random(Random&& r) : m_prng(std::move(r.m_prng)) {}
    int getIntInRange(int low, int high) { return getNumberInRange<UniformIntDistr>(low, high); }
    float getFloatInRange(float low, float high) { return getNumberInRange<UniformDistr<float>>(low, high); }
    double getDoubleInRange(double low, double high) { return getNumberInRange<UniformDistr<double>>(low, high); }

    template <typename T>
    T getNumberInRange(T low, T high) { return getNumberInRange<UniformDistr<T>>(low, high); }

    template <typename Dist, typename T>
    T getNumberInRange(T low, T high) {
        Dist dist(low, high);
        return dist(m_prng);
    }

    Engine& getEngine() { return m_prng; }

private:
    Engine m_prng;
};


#endif //MHRAD_RANDOM_H

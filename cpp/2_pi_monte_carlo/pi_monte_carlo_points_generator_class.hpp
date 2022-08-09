#ifndef __PI_MONTE_CARLO_POINTS_GENERATOR_CLASS_HPP__
#define __PI_MONTE_CARLO_POINTS_GENERATOR_CLASS_HPP__

#include "stdafx.hpp"

class PIMonteCarloPointsGenerator
{
private:
    unsigned long long gp = 0, ap = 0;          // хорошие точки и всего точек
    unsigned int n_;                            // количество генерируемых точек
    
    double pi_;

public:
    PIMonteCarloPointsGenerator(): n_(1000) { }
    PIMonteCarloPointsGenerator(unsigned int n): n_(n) { }

    void set_n(unsigned int n) { n_ = n; }
    unsigned int get_n() { return n_; }

    void next();                                // сгенерировать следующие n_ точек
    double get_pi();                            // считаем Пи на сгенерированном кол-ве точек
};

#endif

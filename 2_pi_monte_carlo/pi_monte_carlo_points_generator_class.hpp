#pragma once

class PIMonteCarloPointsGenerator
{
    private:
        unsigned long long gp_ = 0, ap_ = 0;        // хорошие точки и всего точек
        unsigned int n_;                            // количество генерируемых точек

        double pi_;

    public:
        PIMonteCarloPointsGenerator(): n_( 1000 ) { }
        PIMonteCarloPointsGenerator( unsigned int n ): n_( n ) { }

        unsigned long long get_good_points()
        {
            return gp_;
        }
        unsigned long long get_all_points()
        {
            return ap_;
        }

        void set_n( unsigned int n )
        {
            n_ = n;
        }
        unsigned int get_n()
        {
            return n_;
        }

        void next();                                // сгенерировать следующие n_ точек
        double get_pi();                            // считаем Пи на сгенерированном кол-ве точек
};

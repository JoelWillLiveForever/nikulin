#pragma once

class SampleAbstract
{
    protected:
        unsigned long long _sample_size = 1000;
        bool _use_classic = false;

    public:
        SampleAbstract()
        {}
        SampleAbstract( unsigned long long sample_size, bool use_classic ):
            _sample_size( sample_size ),
            _use_classic( use_classic )
        {}

        virtual std::vector<double> get_random_vector() = 0;
        virtual void print_sample_to_csv() = 0;

        const virtual std::string &whoami() const = 0;

        // get & set
        void set_sample_size( unsigned long long sample_size )
        {
            _sample_size = sample_size;
        }
        unsigned long long get_sample_size()
        {
            return _sample_size;
        }

        void set_use_classic( bool use_classic )
        {
            _use_classic = use_classic;
        }
        bool get_use_classic()
        {
            return _use_classic;
        }
};

class SampleMT19937 : public SampleAbstract
{
    private:
        std::mt19937 _gen;
        std::uniform_real_distribution<double> _dist;

    public:
        SampleMT19937()
        {
            std::random_device rd;

            _gen = std::mt19937( rd() );
            _dist = std::uniform_real_distribution<double>( 0, 1 );
        }
        SampleMT19937( unsigned long long sample_size, bool use_classic ) : SampleAbstract( sample_size, use_classic )
        {
            std::random_device rd;

            _gen = std::mt19937( rd() );
            _dist = std::uniform_real_distribution<double>( 0, 1 );
        }

        std::vector<double> get_random_vector();
        void print_sample_to_csv();

        const std::string &whoami() const
        {
            static const std::string result{"mt19937"};
            return result;
        }
};

class SampleXS64 : public SampleAbstract
{
    private:
        RandomContext64 _rctx;

    public:
        SampleXS64()
        {
            InitRandomContext64( &_rctx );
        }
        SampleXS64( unsigned long long sample_size, bool use_classic ) : SampleAbstract( sample_size, use_classic )
        {
            InitRandomContext64( &_rctx );
        }

        std::vector<double> get_random_vector();
        void print_sample_to_csv();

        const std::string &whoami() const
        {
            static const std::string result{"xs64"};
            return result;
        }
};

class SampleXS1024 : public SampleAbstract
{
    private:
        RandomContext1024 _rctx;

    public:
        SampleXS1024()
        {
            InitRandomContext1024( &_rctx );
        }
        SampleXS1024( unsigned long long sample_size, bool use_classic ) : SampleAbstract( sample_size, use_classic )
        {
            InitRandomContext1024( &_rctx );
        }

        std::vector<double> get_random_vector();
        void print_sample_to_csv();

        const std::string &whoami() const
        {
            static const std::string result{"xs1024"};
            return result;
        }
};

class SampleRand16 : public SampleAbstract
{
    private:
        RandomContext16 _rctx;

    public:
        SampleRand16()
        {
            InitRandomContext16( &_rctx );
        }
        SampleRand16( unsigned long long sample_size, bool use_classic ) : SampleAbstract( sample_size, use_classic )
        {
            InitRandomContext16( &_rctx );
        }

        std::vector<double> get_random_vector();
        void print_sample_to_csv();

        const std::string &whoami() const
        {
            static const std::string result{"rand16"};
            return result;
        }
};

class SampleRand32 : public SampleAbstract
{
    private:
        RandomContext32 _rctx;

    public:
        SampleRand32()
        {
            InitRandomContext32( &_rctx );
        }
        SampleRand32( unsigned long long sample_size, bool use_classic ) : SampleAbstract( sample_size, use_classic )
        {
            InitRandomContext32( &_rctx );
        }

        std::vector<double> get_random_vector();
        void print_sample_to_csv();

        const std::string &whoami() const
        {
            static const std::string result{ "rand32" };
            return result;
        }
};
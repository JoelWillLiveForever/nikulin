#include "stdafx.hpp"

#include "random_generator__sample_abstract_class.hpp"

#include "xor_shift_64__sample_class.hpp"
#include "xor_shift_1024__sample_class.hpp"
#include "mt19937__sample_class.hpp"

int main(int argc, char *argv[])
{
    if ( argc == 2 )
    {
        if ( std::string(argv[1]) == "-h" || std::string(argv[1]) == "--help" )
        {
            std::cout 
                << "Usage:\n"
                << argv[0] <<" [options]\n"
                << "\nOptions:\n"
                "-h, --help" << "\tShow program help info\n"
                "-v, --version" << "\tDisplay program version\n"
                "--xs64 [total_points, range_start, range_end]" << "\tUse XORShift64 random generator\n"
                "--xs1024 [total_points, range_start, range_end]" << "\tUse XORShift64 random generator\n"
                "--mt19937 [total_points, range_start, range_end]" << "\tUse CPP STD MT19937 random generator\n"
                << std::endl;
        }
        else if ( std::string(argv[1]) == "-v" || std::string(argv[1]) == "--version" )
            std::cout << "1.0.0.0" << std::endl;
        else
        {
            std::cerr << "Bad arguments!\n";
            return EXIT_FAILURE;
        }
    }
    else if ( argc == 5 )
    {
        RandomGenerator_SampleAbstract *obj;
        std::string arg = argv[1];

        if ( arg == "--xs64" )
            obj = new XORShift64_Sample();
        else if ( arg == "--xs1024" )
            obj = new XORShift1024_Sample();
        else if ( arg == "--mt19937" )
            obj = new MT19937_Sample();
        else
        {
            std::cerr << "Bad arguments!\n";
            return EXIT_FAILURE;
        }

        char *pCh;
        unsigned long total_nums = strtoul(argv[2], &pCh, 10);

        if ( (pCh == argv[2]) || (*pCh != '\0') )
        {
            std::cerr << "Invalid number: " << argv[2] << '\n';
            return EXIT_FAILURE;
        }      

        double range_start = atof(argv[3]),
               range_end = atof(argv[4]);

        (*obj).print_sample_to_csv(total_nums, range_start, range_end);
    }
    else
    {
        std::cerr << "Bad arguments!" << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

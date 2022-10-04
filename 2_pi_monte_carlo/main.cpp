#include "pch.hpp"

#include "samples.hpp"

extern "C" 
{
    #include "generators.h"
    #include "version.h"
}

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
                "-h, --help" << "\t\t\tShow program help info\n"
                "-v, --version" << "\t\t\tDisplay program version\n\n"
                "--xs64    [total_points]" << "\tUse XORShift64 random generator\n"
                "--xs1024  [total_points]" << "\tUse XORShift64 random generator\n"
                "--mt19937 [total_points]" << "\tUse CPP STD MT19937 random generator\n"
                "--rand    [total_points]" << "\tUse C stdlib.h random generator\n"
                << std::endl;
        }
        else if ( std::string(argv[1]) == "-v" || std::string(argv[1]) == "--version" )
            std::cout << VERSION_MAJOR << "." 
                      << VERSION_MINOR << "." 
                      << VERSION_PATCH << "." 
                      << VERSION_TWEAK 
                      << std::endl;
        else
        {
            std::cerr << "Bad arguments!\n";
            return EXIT_FAILURE;
        }
    }
    else if ( argc == 3 )
    {
        RandomGenerator_SampleAbstract *obj;
        std::string arg = argv[1];

        if ( arg == "--xs64" )
            obj = new XORShift64_Sample();
        else if ( arg == "--xs1024" )
            obj = new XORShift1024_Sample();
        else if ( arg == "--mt19937" )
            obj = new MT19937_Sample();
        else if ( arg == "--rand" )
            obj = new CSTDLibRand_Sample();
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
        
        // засекаем время генерации выборки
        auto start = std::chrono::high_resolution_clock::now();
        (*obj).print_sample_to_csv(total_nums);
        auto stop = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        std::cout << "Elapsed time for generator: \"" << (*obj).whoami() << "\"; Total values: " << total_nums << "\t --- " << duration.count() << " microseconds" << std::endl;
    }
    else
    {
        std::cerr << "Bad arguments!" << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

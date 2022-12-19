#include "version.h"
#include "samples.hpp"

namespace po = boost::program_options;

typedef enum
{
    XOR_SHIFT_64,
    XOR_SHIFT_1024,
    MT19937,
    RAND16,
    RAND32
} GeneratorType;

inline std::istream &operator >> ( std::istream &in, GeneratorType &generator )
{
    std::string arg;
    in >> arg;

    if ( arg == "xor-shift-64" )
        generator = XOR_SHIFT_64;
    else if ( arg == "xor-shift-1024" )
        generator = XOR_SHIFT_1024;
    else if ( arg == "mt19937" )
        generator = MT19937;
    else if ( arg == "rand16" )
        generator = RAND16;
    else if (arg == "rand32")
        generator = RAND32;
    else
    {
        //throw po::validation_error(po::validation_error::invalid_option_value);
        std::ostringstream ss;
        ss << "Value must be xor-shift-64, xor-shift-1024, mt19937, rand16 or rand32 you supplied " << std::quoted( arg );
        throw std::invalid_argument( ss.str() );
    }

    return in;
}

int main( int argc, char **argv )
{
    try
    {
        po::options_description generic( "Generic options" );
        generic.add_options()
        ( "help,h", "Get help message" )
        ( "version,v", "Get program version" )
        ;

        po::options_description config( "Configuration" );
        config.add_options()
        ( "classic,c", "Use the classic method of generating a sample in the range (0..1)" )
        ( "generator,g", po::value<GeneratorType>()->default_value( XOR_SHIFT_64, "xor-shift-64" ), "Set generator type" )
        ( "sample-size,s", po::value<unsigned long>()->default_value( 1000 ), "Set sample size" )
        ;

        po::options_description desc;
        desc.add( generic ).add( config );

        po::variables_map vm;
        po::store( po::command_line_parser( argc, argv ).options( desc ).allow_unregistered().run(), vm );
        po::notify( vm );

        //    if ( vm.count( "help" ) || argc == 1 )
        if ( vm.count( "help" ) )
        {
            std::cout << desc << '\n';
            return EXIT_SUCCESS;
        }

        if ( vm.count( "version" ) )
        {
            std::string version = "?";
#if defined(__VERSION_H__)
            version = std::to_string(VERSION_MAJOR) + "."
                + std::to_string(VERSION_MINOR) + "."
                + std::to_string(VERSION_PATCH) + "."
                + std::to_string(VERSION_TWEAK) + "-"
                + BUILD_DATE;

#if defined(__GIT_VERSION_H__)
            version += " (" + std::string(GIT_COMMIT_HASH) + ")";
#endif

#endif
            std::cout << version << std::endl;
            return EXIT_SUCCESS;
        }

        bool isClassic = false;
        if ( vm.count( "classic" ) )
            isClassic = true;

        unsigned long sample_size = vm["sample-size"].as<unsigned long>();
        GeneratorType generator = vm["generator"].as<GeneratorType>();

        SampleAbstract *obj;
        switch ( generator )
        {
            case XOR_SHIFT_64:
                obj = new SampleXS64(sample_size, isClassic);
                break;

            case XOR_SHIFT_1024:
                obj = new SampleXS1024(sample_size, isClassic);
                break;

            case MT19937:
                obj = new SampleMT19937(sample_size, isClassic);
                break;

            case RAND16:
                obj = new SampleRand16(sample_size, isClassic);
                break;

            case RAND32:
                obj = new SampleRand32(sample_size, isClassic);
                break;

            default:
                throw std::exception( "Cannot find generator" );
        }

        // засекаем время генерации выборки
        auto start = std::chrono::high_resolution_clock::now();
        ( *obj ).print_sample_to_csv();
        auto stop = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::microseconds>( stop - start );
        std::cout << "Elapsed time for generator: \"" << ( *obj ).whoami() << "\"; Total values: " << sample_size << "\t --- "
                  << duration.count() << " microseconds" << std::endl;

        return EXIT_SUCCESS;
    }
    catch ( const std::exception &e )
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}

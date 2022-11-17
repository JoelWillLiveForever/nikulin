/**
 * @file main.cpp
 * @author Vladimir Nikulin (mail.jorey@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-11-15
 *
 * Условие задачи 1:
 * Имеется 10 гирь весом 100, 200, 300, 500, 1000, 1200, 1400, 1500, 2000 и 3000 г.
 * Сколькими способами гирями этого набора можно составить вес в V грамм?
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "version.h"

#include "weight_combinator.hpp"
#include "weight_combinator_io.hpp"

// коды ошибок
/// @brief Ошибка при инициализации логгера
#define EXIT_FAILURE_LOGGER_INIT 2

/// @brief Ошибка при чтении аргументов с помощью boost::program_options
#define EXIT_FAILURE_PROGRAM_OPTIONS 3

/// Была встречена какая-то ошибка из std namespace
#define EXIT_FAILURE_STD 4

namespace po = boost::program_options;

static std::string program_name = "?";

/**
 * @brief Поддерживаемые временные единицы, для измерения скорости выполнения программы
 * @details https://evileg.com/en/post/430/
 */
enum TimeUnit
{
    OFF,
    SECONDS,
    MILLISECONDS,
    MICROSECONDS,
    NANOSECONDS
};

/**
 * @brief Ввод TimeUnit из stdin
 *
 * @param in Ссылка на объект потока
 * @param unit Ссылка на объект TimeUnit
 * @return std::istream& Возвращаем ссылку на объект потока
 */
inline std::istream &operator>>( std::istream &in, TimeUnit &unit )
{
    std::string token;
    in >> token;

    transform( token.begin(), token.end(), token.begin(), ::tolower );

    if ( token == "off" || token == "0" )
        unit = TimeUnit::OFF;
    else if ( token == "seconds" || token == "ss" || token == "1" )
        unit = TimeUnit::SECONDS;
    else if ( token == "milliseconds" || token == "ms" || token == "2" )
        unit = TimeUnit::MILLISECONDS;
    else if ( token == "microseconds" || token == "us" || token == "3" )
        unit = TimeUnit::MICROSECONDS;
    else if ( token == "nanoseconds" || token == "ns" || token == "4" )
        unit = TimeUnit::NANOSECONDS;
    else
        in.setstate( std::ios_base::failbit );

    return in;
}

/**
 * @brief Вывод TimeUnit в stdout
 *
 * @param out Ссылка на объект потока
 * @param unit Ссылка на объект TimeUnit
 * @return std::ostream& Возвращаем ссылку на объект потока
 */
inline std::ostream &operator<<( std::ostream &out, const TimeUnit &unit )
{
    std::string value;

    switch ( unit )
    {
        case TimeUnit::SECONDS:
            value = "seconds";
            break;

        case TimeUnit::MILLISECONDS:
            value = "milliseconds";
            break;

        case TimeUnit::MICROSECONDS:
            value = "microseconds";
            break;

        case TimeUnit::NANOSECONDS:
            value = "nanoseconds";
            break;

        default:
            value = "off";
            break;
    }

    out << value;
    return out;
}

/// @brief Псевдоним (alias) для std::vector<unsigned int>
using Nomenclature = std::vector<unsigned int>;

/**
 * @brief Вывод номенклатуры в stdout
 *
 * @param out Ссылка на объект потока
 * @param v Ссылка на объект Nomenclature (std::vector<unsigned int>)
 * @return std::ostream& Возвращаем ссылку на объект потока
 */
inline std::ostream &operator<<( std::ostream &out, const Nomenclature &v )
{
    if ( !v.empty() )
    {
        out << "[";

        for ( Nomenclature::const_iterator it = v.begin(); it != v.end(); ++it )
        {
            ( v.end() - it ) != 1
            ? out << *it << ", "
                  : out << *it;
        }

        out << "]";
    }

    return out;
}

/**
 * @brief Точка входа в программу
 *
 * @param argc Количество аргументов
 * @param argv Сами аргументы
 * @return int Статус код ошибки
 */
int main( int argc, char **argv )
{
    // вытягиваем имя проги из argv[0]
    boost::filesystem::path p = argv[0];
    program_name = p.stem().string();

    // Общие опции
    po::options_description generic( "Generic options" );
    generic.add_options()
    ( "help,h", "Get help message" )
    ( "version,v", "Get program version" )
    ( "time-unit,u", po::value<TimeUnit>()->default_value( TimeUnit::OFF, "off" ),
      "Set units for measuring execution time \nTime units: \noff | (0) \nseconds | ss | (1) \nmilliseconds | ms | (2) \nmicroseconds | us | (3) \nnanoseconds | ns | (4)" )
    ( "log-filename", po::value<std::string>()->default_value( program_name + ".txt" ), "Set filename for logfile" )
    ( "log-max-file-size", po::value<unsigned int>()->default_value( 1024 ), "Set max size for logfile" )
    ( "log-max-files", po::value<unsigned int>()->default_value( 3 ), "Set max files for logs" )
    ( "log-enable", po::value<bool>()->default_value( true ), "Enable or disable logging to file" )
    ( "log-enable-in-console", po::value<bool>()->default_value( false ), "Enable or disable logging to console" )
    ;

    // Опции для управления значениями аргументов, которые подаются программе на вход
    po::options_description config( "Argument management options" );
    config.add_options()
    ( "target,t", po::value<unsigned int>()->default_value( 11200 ), "Set target weight" )
    ( "nomenclature,n", po::value<Nomenclature>()
      ->multitoken()
      ->default_value(
          Nomenclature{ 100, 200, 300, 500, 1000, 1200, 1400, 1500, 2000, 3000 },
          "100, 200, 300, 500, 1000, 1200, 1400, 1500, 2000, 3000"
      ),
      "Set weights nomenclature" )
    ;

    po::options_description desc;
    desc.add( generic ).add( config );

    try
    {
        po::variables_map vm;
        po::store( po::command_line_parser( argc, argv ).options( desc ).allow_unregistered().run(), vm );
        po::notify( vm );

        bool log_enable = vm["log-enable"].as<bool>();
        bool log_enable_in_console = vm["log-enable-in-console"].as<bool>();

        // Инициализация логгера
        std::string log_filename = vm["log-filename"].as<std::string>();

        unsigned int log_max_file_size = vm["log-max-file-size"].as<unsigned int>();
        unsigned int log_max_files = vm["log-max-files"].as<unsigned int>();

        auto logger = spdlog::rotating_logger_mt( "MAIN", "logs/" + log_filename, log_max_file_size,
                                                  log_max_files );   // логгер на вывод в файл
        spdlog::flush_on( spdlog::level::err );

        log_enable
        ? spdlog::set_level( spdlog::level::trace )
        : spdlog::set_level( spdlog::level::off );

        auto console_logger = spdlog::stdout_color_mt( "MAIN-CONSOLE",
                                                       spdlog::color_mode::automatic );  // логгер на вывод в терминал
        console_logger->flush_on( spdlog::level::err );

        log_enable_in_console
        ? console_logger->set_level( spdlog::level::trace )
        : console_logger->set_level( spdlog::level::off );

        spdlog::set_default_logger( logger );

        // Вывод help
        if ( vm.count( "help" ) )
        {
            std::cout << desc << '\n';

            spdlog::info( "Exit {}", EXIT_SUCCESS );
            console_logger->info( "Exit {}", EXIT_SUCCESS );

            return EXIT_SUCCESS;
        }

        // Вывод версии
        if ( vm.count( "version" ) )
        {
            std::string version = "?";
            #if defined(__VERSION_H__)
            version = VERSION_MAJOR + "."
                      + VERSION_MINOR + "."
                      + VERSION_PATCH + "."
                      + VERSION_TWEAK + "-"
                      + BUILD_DATE;
            #elif defined(__GIT_VERSION_H__)
            version = GIT_COMMIT_HASH;
            #endif
            std::cout << version << std::endl;

            spdlog::info( "Exit {}", EXIT_SUCCESS );
            console_logger->info( "Exit {}", EXIT_SUCCESS );

            return EXIT_SUCCESS;
        }

        // Запись полученных аргументов в соответствующие переменные
        TimeUnit time_unit = vm["time-unit"].as<TimeUnit>();

        unsigned int target = vm["target"].as<unsigned int>();

        Nomenclature nomenclature = vm["nomenclature"].as<Nomenclature>();

        //TODO: make it better if you can
        std::ostringstream time_unit_out;
        time_unit_out << time_unit;

        spdlog::debug( "Command line arguments: \nlog-filename: {} \nlog-max-file-size: {} \nlog-max-files {} \ntime-unit: {} \ntarget: {} \nnomenclature: {}",
                       log_filename, log_max_file_size, log_max_files, time_unit_out.str(), target, nomenclature );
        console_logger->debug( "Command line arguments: \nlog-filename: {} \nlog-max-file-size: {} \nlog-max-files {} \ntime-unit: {} \ntarget: {} \nnomenclature: {}",
                               log_filename, log_max_file_size, log_max_files, time_unit_out.str(), target, nomenclature );

        WeightCombinator::Combinations combinations;
        WeightCombinator combinator;

        std::ostringstream result;

        if ( time_unit != TimeUnit::OFF )
        {
            auto start = std::chrono::high_resolution_clock::now();
            combinator.combine( target, combinations, nomenclature );
            auto stop = std::chrono::high_resolution_clock::now();

            std::ostringstream out;

            switch ( time_unit )
            {
                case OFF:
                    break;

                case SECONDS:
                {
                    auto duration = std::chrono::duration_cast<std::chrono::seconds>( stop - start );
                    out << "Elapsed time: " << duration.count() << " sec" << std::endl;
                    break;
                }

                case MILLISECONDS:
                {
                    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>( stop - start );
                    out << "Elapsed time: " << duration.count() << " ms" << std::endl;
                    break;
                }

                case MICROSECONDS:
                {
                    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( stop - start );
                    out << "Elapsed time: " << duration.count() << " us" << std::endl;
                    break;
                }

                case NANOSECONDS:
                {
                    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>( stop - start );
                    out << "Elapsed time: " << duration.count() << " ns" << std::endl;
                    break;
                }
            }

            result << combinations;
            result << out.str();
        }
        else
        {
            combinator.combine( target, combinations, nomenclature );
            result << combinations;
        }

        spdlog::info( result.str() );
        spdlog::info( "Exit {}", EXIT_SUCCESS );

        console_logger->info( result.str() );
        console_logger->info( "Exit {}", EXIT_SUCCESS );

        std::cout << result.str() << std::endl;

        return EXIT_SUCCESS;
    }
    catch ( const po::error &ex )
    {
        //spdlog::error(ex.what());
        //spdlog::info("Exit {}", EXIT_FAILURE_PROGRAM_OPTIONS);

        std::cerr << ex.what() << std::endl;

        return EXIT_FAILURE_PROGRAM_OPTIONS;
    }
    catch ( const spdlog::spdlog_ex &ex )
    {
        //spdlog::error(ex.what());
        //spdlog::info("Exit {}", EXIT_FAILURE_LOGGER_INIT);

        std::cerr << "Log initialization failed: " << ex.what() << std::endl;

        return EXIT_FAILURE_LOGGER_INIT;
    }
    catch ( const std::exception &ex )
    {
        //spdlog::error(ex.what());
        //spdlog::info("Exit {}", EXIT_FAILURE_STD);

        std::cerr << ex.what() << std::endl;

        return EXIT_FAILURE_STD;
    }
}

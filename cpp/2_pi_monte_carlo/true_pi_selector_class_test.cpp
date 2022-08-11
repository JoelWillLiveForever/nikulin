#include "true_pi_selector_class_test.hpp"

bool TruePISelectorTest::select_pi_test()
{
    double expected = 3.141;
    double eps = 0.001;

    int total_threads = 5;

    TruePISelector obj(total_threads, eps);
    double result = obj.select_pi();
    
    return std::fabs(expected - result) <= eps;
}

void TruePISelectorTest::test()
{
    std::cout     
        << "\n\tTesting \"TruePISelector\" class:" 
        << std::endl;

    //auto old_buffer = std::cout.rdbuf(nullptr);
    std::cout.setstate(std::ios_base::failbit);     // запрещаем вывод в консоль всех сообщений из функции select_pi()

    bool select_pi_test_result = select_pi_test();

    //std::cout.rdbuf(old_buffer);
    std::cout.clear();                              // разрешаем вывод в консоль 

    std::cout
        << std::setw(0) 
        << "\t\t"
        << (select_pi_test_result ? "OK" : "FAIL")
        << " --- \"select_pi()\""
        << std::endl;
}

/**
 * @file weight_combinator.hpp
 * @author Vladimir Nikulin (mail.jorey@gmail.com)
 * @brief Модуль с классом WeightCombinator
 * @version 0.1
 * @date 2022-11-15
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

/**
 * @brief Этот класс используется для расчёта всех возможных вариантов перестановок гирь, из которых необходимо получить заданный вес
 *
 */
class WeightCombinator
{
    public:
        /// @brief Тип данных для хранения номенклатуры гирь
        typedef std::vector<unsigned int> Weights;

        /// @brief Тип данных для хранения комбинаций
        typedef std::vector<std::vector<unsigned int>> Combinations;

    private:
        /// @brief // Максимальный размер номенклатуры гирь
        static const char allowed_bits_ = sizeof( unsigned int ) * 8;

    public:
        /**
         * @brief Read-only метод для получения значения @var allowed_bits_
         *
         * @return char
         */
        static char get_allowed_bits()
        {
            return allowed_bits_;
        };

        /// @brief Функция поиска комбинаций для заданного веса
        /// @param target Заданный вес, комбинации для которого ищем
        /// @param combinations Переданный по ссылке массив, в который добавляем комбинации гирь (работает как return value)
        /// @param weights Номенклатура гирь
        void combine( unsigned int target,
                      WeightCombinator::Combinations &combinations,
                      WeightCombinator::Weights &weights );

        //TODO: try fix it
        //friend inline std::ostream& operator<<(std::ostream& out, const WeightCombinator::Combinations& data);
        //friend inline std::ostream& operator<<(std::ostream& out, const WeightCombinator& obj);
};

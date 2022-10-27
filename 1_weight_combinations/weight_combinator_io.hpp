#pragma once

#include "weight_combinator.hpp"

class WeightCombinator;

std::ostream& operator<< (std::ostream& out, WeightCombinator::Combinations const& data);
//std::ostream& operator>> (std::ostream& out, WeightCombinator::Combinations const& data);
#pragma once

template <typename T_State>
class GeneticOperator {
public:
    virtual ~GeneticOperator() = default;
    virtual T_State crossover(const T_State& parent1, const T_State& parent2, int xover_point) const = 0;
    virtual T_State mutate(const T_State& individual) const = 0;
    virtual bool is_solution(const T_State& individual) const = 0;
    virtual int genome_size(const T_State& individual) const = 0;
};
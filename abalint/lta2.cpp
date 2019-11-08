#include <benchmark/benchmark.h>

#include <vector>
#include <list>
#include <numeric>

template< typename T >
int sum(const T& container)
{
    return std::accumulate(container.begin(), container.end(), 0);
}


template< typename T >
static void benchmarkSum(benchmark::State& state)
{
    T container;
    auto size = state.range(0);
    state.SetItemsProcessed(size);

    for (auto i = size; i; --i)
    {
        container.push_back(i);
    }

    for(auto _ : state)
    {
        // what we are benchmarking
        auto x = sum(container);
        benchmark::DoNotOptimize(container.front());
        benchmark::DoNotOptimize(x);
    }
}

BENCHMARK_TEMPLATE(benchmarkSum, std::vector<int>)->Range(1024, 1024*1024);
BENCHMARK_TEMPLATE(benchmarkSum, std::list<int>)->Range(1024, 1024*1024);
BENCHMARK_MAIN();

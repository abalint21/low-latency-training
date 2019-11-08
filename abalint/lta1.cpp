#include <benchmark/benchmark.h>

#include <numeric>
#include <vector>
#include <list>
#include <cstdlib>

auto generateData(int n)
{
    std::vector<int> v;
    for (auto i = n; i; --i)
    {
        v.push_back(std::rand());
    }

    return v;
}

static void generateDataBenchmark(benchmark::State& state)
{
    // prologue - not part of the measurement
    for(auto _ : state)
    {
        // what we are benchmarking
        generateData(10);
    }
    // epilogue - not part of the measurement
}

static void generateDataBenchmarkAccumulate(benchmark::State& state)
{
    // prologue - not part of the measurement
    for(auto _ : state)
    {
        // what we are benchmarking
        auto data = generateData(10);
        std::accumulate(data.cbegin(), data.cend(), 0);
        benchmark::DoNotOptimize(data.data()); // say to the compiler not to optimize out out the vector's internal data
    }
    // epilogue - not part of the measurement
}

static void generateDataBenchmarkAccumulateRanged(benchmark::State& state)
{
    auto size = state.range(0);

    // prologue - not part of the measurement
    for(auto _ : state)
    {
        // what we are benchmarking
        auto data = generateData(size);
        std::accumulate(data.cbegin(), data.cend(), 0);
        benchmark::DoNotOptimize(data.data()); // say to the compiler not to optimize out out the vector's internal data
    }
    // epilogue - not part of the measurement
}

template< typename Container >
static void generateDataBenchmark(benchmark::State& state)
{
    auto size = state.range(0);
    state.SetItemsProcessed(size); // see how many items have been processed in a state iteration
    state.SetBytesProcessed(size * sizeof(int));
    // prologue - not part of the measurement
    for(auto _ : state)
    {
        Container v;
        for (int i = 0; i < size; ++i)
        {
            v.push_back(i);
        }
    }
    // epilogue - not part of the measurement
}

//BENCHMARK(generateDataBenchmark);
BENCHMARK(generateDataBenchmarkAccumulate);
//BENCHMARK(generateDataBenchmarkAccumulateRanged)->Arg(1000)->Arg(10000); // will test for 1000 / 10000
//BENCHMARK(generateDataBenchmarkAccumulateRanged)->Range(1024, 128*1024); // will test for different values from 1024 -> 128*1024
//BENCHMARK_TEMPLATE(generateDataBenchmark, std::vector<int>)->Arg(1000)->Arg(10000); // will test for 1000 / 10000
//BENCHMARK_TEMPLATE(generateDataBenchmark, std::list<int>)->Arg(1000)->Arg(10000); // will test for 1000 / 10000

BENCHMARK_MAIN();

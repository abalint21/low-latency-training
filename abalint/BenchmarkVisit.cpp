#include <benchmark/benchmark.h>

#include <vector>
#include <numeric>
#include <cstdlib>

auto generateIdxLinear(int n)
{
    std::vector<int> idx;

    idx.reserve(n);
    for (auto i = 0; i < n; ++i)
    {
        idx[i] = i;
    }

    return idx;
}

auto generateIdxRand(int n)
{
    std::vector<int> idx;

    idx.reserve(n);
    for (auto i = 0; i < n; ++i)
    {
        idx[i] = std::rand() % n;
    }

    return idx;
}

static void benchmarkCacheLinear(benchmark::State& state)
{
    auto size = state.range(0);
    state.SetBytesProcessed(size * 2* sizeof(int));

    auto idx = generateIdxLinear(size);
    std::vector<int> data;
    data.reserve(size);
    for (auto i = 0; i < size; ++i)
    {
        data[i] = std::rand();
    }

    for(auto _ : state)
    {
        // what we are benchmarking
        auto sum = 0;
        for (auto i = 0; i < size; ++i)
        {
            sum += data[idx[i]];
        }
        benchmark::DoNotOptimize(sum);
        benchmark::DoNotOptimize(data.front());
        benchmark::DoNotOptimize(idx.front());
    }
}

static void benchmarkCacheRand(benchmark::State& state)
{
    auto size = state.range(0);
    state.SetBytesProcessed(size * 2* sizeof(int));

    auto idx = generateIdxRand(size);
    std::vector<int> data;
    data.reserve(size);
    for (auto i = 0; i < size; ++i)
    {
        data[i] = std::rand();
    }

    for(auto _ : state)
    {
        // what we are benchmarking
        auto sum = 0;
        for (auto i = 0; i < size; ++i)
        {
            sum += data[idx[i]];
        }
        benchmark::DoNotOptimize(sum);
        benchmark::DoNotOptimize(data.front());
        benchmark::DoNotOptimize(idx.front());
    }
}

//BENCHMARK(benchmarkCache)->Range(1024, 1024*1024);
BENCHMARK(benchmarkCacheLinear)->Arg(1024)->Arg(1024*1024);
BENCHMARK(benchmarkCacheRand)->Arg(1024)->Arg(1024*1024);
BENCHMARK_MAIN();

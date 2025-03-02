# Timing & benchmarking

In C++, timing and measuring the passage of time is an important aspect of performance measurement and real-time applications.
The C++ standard library provides a toolset for working with time and measuring durations using the `<chrono>` header.

### Timing in C++

Timing in C++ typically involves measuring how long a piece of code takes to execute. This is often done for performance profiling or to
implement features that require precise timing.

### `<chrono>` Library

The `<chrono>` library in C++ provides a variety of utilities to work with time and durations. It includes facilities for:

1. **Time Points**: Represent specific points in time.
2. **Durations**: Represent the difference between two time points, or a span of time.
3. **Clocks**: Provide the current time and measure elapsed time.

#### Key Components of `<chrono>`

1. **Clocks**:

   - `std::chrono::system_clock`: Represents real-time clock, which is the system-wide wall clock. It's typically used to get the current
     time and date.
   - `std::chrono::steady_clock`: Represents a monotonic clock that cannot be adjusted. It's used for measuring elapsed time and is suitable for performance measurements.
   - `std::chrono::high_resolution_clock`: Provides the smallest tick period available on the system. It’s often used for fine-grained
     performance measurements.

2. **Time Points**:

   - `std::chrono::time_point`: Represents a point in time relative to a clock. For example, `std::chrono::system_clock::now()` returns
     a `std::chrono::time_point` representing the current time according to `system_clock`.

3. **Durations**:
   - `std::chrono::duration`: Represents a time span. For example, `std::chrono::seconds`, `std::chrono::milliseconds`, and
     `std::chrono::nanoseconds` are common durations.

#### Basic Usage

Here is a simple example demonstrating how to use `<chrono>` to measure the execution time of a piece of code:

```cpp
#include <iostream>
#include <chrono>
#include <thread>

int main() {
    // Get the starting time point
    auto start = std::chrono::high_resolution_clock::now();

    // Code to measure
    std::this_thread::sleep_for(std::chrono::seconds(2)); // Simulate some work

    // Get the ending time point
    auto end = std::chrono::high_resolution_clock::now();

    // Calculate the duration
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Elapsed time: " << elapsed.count() << " seconds\n";

    return 0;
}
```

### Explanation

- `std::chrono::high_resolution_clock::now()` returns the current time point.
- `std::this_thread::sleep_for()` is used to simulate work by making the thread sleep.
- `end - start` calculates the elapsed time as a `std::chrono::duration`.
- `elapsed.count()` gives the elapsed time in seconds as a `double`.

This example demonstrates how you can measure the time it takes to execute a block of code. The `<chrono>` library provides a high level
of precision and flexibility for time measurement and management in C++.

you may have seen the above code which is right but you may be asking that what if i want to know the performence of an function it will then
require me to write the whole code in that function but a smart way is to create an class or an struct for this

```c
#include<iostream>
#include<thread>
#include<chrono>

struct timer
{
std::chrono::time_point<std::chrono::high_resolution_clock> start , end;
std::chrono::duration<float> time_taken;

     timer()
     {
       start = std::chrono::high_resolution_clock::now();
     }

     ~timer()
     {
       end = std::chrono::high_resolution_clock::now();
       time_taken = end - start;
       float ms = time_taken.count() * 1000.0f;
       std::cout << "Elapsed time: " << ms << " milliseconds" << std::endl;
     }

};

void fun()
{
timer t1;
for(int i = 0 ; i < 100 ; i++)
{
std::cout << "Hello" << std::endl;
}
}

int main()
{
fun();
return 0;
}
```

by doing this you will easly find the time taken for an code to execute

note that there are many other platforms which are better then chrono but std::chrono is like an default for measuring timing

# bench marking

Benchmarking in C++ (or any programming language) refers to the process of measuring the performance of code to assess how efficiently
it executes. The primary goal of benchmarking is to identify the time or resources required by different parts of the code,
which helps developers make informed decisions about optimization and performance improvements. Here’s a detailed look at benchmarking in C++:

### Key Concepts of Benchmarking

1. **Performance Metrics**:

   - **Execution Time**: Measures how long a piece of code takes to run. This can be broken down into total execution time, time per
     iteration, or time per function call.
   - **Memory Usage**: Measures how much memory is used by the code, which can be important for understanding the impact of data structures and algorithms.
   - **CPU Utilization**: Measures how much CPU resources are consumed by the code, which can be relevant in multi-threaded applications.

2. **Benchmarking Tools**:
   - **Standard Library Functions**: C++ standard library functions like `std::chrono` for measuring time.
   - **Benchmarking Libraries**: Specialized libraries designed for performance measurement and benchmarking, such as Google Benchmark.

### Methods of Benchmarking

1. **Manual Timing**:

   - You can use standard library functions to manually measure execution time.
   - **Example** using `std::chrono`:

     ```cpp
     #include <iostream>
     #include <chrono>

     void performTask() {
         // Simulate some work
         for (int i = 0; i < 1000000; ++i);
     }

     int main() {
         auto start = std::chrono::high_resolution_clock::now();

         performTask();

         auto end = std::chrono::high_resolution_clock::now();
         std::chrono::duration<double> elapsed = end - start;

         std::cout << "Time taken: " << elapsed.count() << " seconds\n";
         return 0;
     }
     ```

2. **Profiling Tools**:

   - Profilers provide more detailed information about performance, including function call frequency and memory usage.
   - **Examples**: `gprof`, `Valgrind (Callgrind)`, `Visual Studio Profiler`, and `Intel VTune`.

3. **Benchmarking Libraries**:

   - Libraries like **Google Benchmark** offer a structured way to perform benchmarks with features like automated runs, statistical
     analysis, and reporting.
   - **Example** using Google Benchmark:

     ```cpp
     #include <benchmark/benchmark.h>

     static void BM_FunctionToBenchmark(benchmark::State& state) {
         for (auto _ : state) {
             // Code to benchmark
         }
     }
     BENCHMARK(BM_FunctionToBenchmark);

     BENCHMARK_MAIN();
     ```

4. **Micro-Benchmarks**:

   - These are benchmarks focused on small pieces of code or individual functions to understand their performance characteristics. They are useful for fine-tuning and optimization.

5. **Macro-Benchmarks**:
   - These benchmarks assess the performance of larger applications or systems as a whole, providing insight into overall efficiency and
     behavior under real-world conditions.

### Best Practices for Benchmarking

1. **Isolate the Code**:

   - Ensure that the code being benchmarked is isolated from other processes or operations that might affect its performance. Avoid
     including unrelated tasks or operations in the benchmark.

2. **Warm-Up Runs**:

   - Include a warm-up phase before measuring the performance to ensure that the code is executed in a stable state. This helps to
     mitigate the effects of cold-start conditions or JIT compilation.

3. **Multiple Iterations**:

   - Run the benchmark multiple times and take an average to account for variations in execution time. This provides more accurate
     and reliable performance metrics.

4. **Consistent Environment**:

   - Run benchmarks in a consistent and controlled environment to avoid fluctuations in results due to external factors like system
     load or hardware differences.

5. **Analyze and Interpret**:
   - Use the results to identify performance bottlenecks and areas for optimization. Consider both time and memory metrics to get a
     comprehensive view of the code's performance.

---

### right way

note that there are many ways to do benchmarking but you should do it the right way as the procss of finding the benchmarking can make
you code slow and give you abnormal benchmarks also you should know that debug mode is different from release mode so both will take different time to excuete an code

lets have an example

```c
#include<iostream>
#include<chrono>

struct timer
{
std::chrono::time_point<std::chrono::high_resolution_clock> M_startTimepoint , Endpoint;
timer()
{
M_startTimepoint = std::chrono::high_resolution_clock::now();
}
~timer()
{
stop();
}

    void stop()
    {
    	Endpoint = std::chrono::high_resolution_clock::now();
    	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(Endpoint - M_startTimepoint).count();

      //to convert the duration into microsec

    	double milli_s = duration * 0.001;

    	std::cout << "microsec = " << duration << "  &    millisec = " << milli_s << std::endl;

    }

};

int main()
{
int value = 0;
{
timer t1;
for (int i = 0; i < 100000; i++)
value += 2;
}
std::cout << value << std::endl;

    __debugbreak();     //this is an vs only function or feature used to put break points on an emty lines

}
```

- `debug mode result`

  ```bash
  microsec = 223 & millisec = 0.223
  200000
  ```

- `release mode result`

  ```bash
    microsec = 0 & millisec = 0
    200000
  ```

here you can see that the release mode takes 0 sec what!! how is that possible so what does the compiler does it optimize the code in release mode where for debug mode that is not the case While it might depend on the context, the general consensus is to use release mode for benchmarking performance. This approach ensures you get accurate and relevant results that reflect how your code will behave in a real-world environment. but for some cases you should use debug mode but when you are benchmarking the whole code you should use release mode but when you are finding benchmarking of an specific code which contains can be known at compile time it is more obvious to use debug mode also note that the debug mode has some overhead so that could also make the benchmarking wrong

- ## Assemblly code in debug mode

  006871CC mov eax,dword ptr [value] ;This instruction moves the value stored in the variable value into the EAX register.
  006871CF add eax,2 ;This instruction adds 2 to the value currently in the EAX register.
  After this instruction, EAX ;holds the new value of value + 2.
  006871D2 mov dword ptr [value],eax ;This instruction moves the value in the EAX register back into the variable value.
  006871D5 jmp main+4Ah (06871BAh) ;after this instruction the compiler jumps to an different part of code

- ## Assemblly code in release mode

  00E6113F mov dword ptr [ebp-4],0FFFFFFFFh
  std::cout << value << std::endl;
  00E61146 mov ecx,dword ptr [_imp_?cout@std@@3V?$basic_ostream@DU?$char_traits@D@std@@@1@A (0E63068h)]
  00E6114C push 30D40h
  00E61151 call dword ptr [__imp_std::basic_ostream<char,std::char_traits<char> >::operator<< (0E63038h)]
  00E61157 mov ecx,eax
  00E61159 call dword ptr [__imp_std::basic_ostream<char,std::char_traits<char> >::operator<< (0E63034h)]

you can see that there is no add instruction here like in the debug mode in the release mode
the only thing compiler does here is that it push some no on the stack
00E6114C push 30D40h this hex no in decimal is 200000
this shows that at release mode the compiler optimizes the code and does no work becase the value is known at compie time and
simply prints that no on the terminal
so this mean that the loop is not executed

so for such type of code that is evaluated at compile time we can not find its benchmarks at release mode you should use deug mode

so if you are menchmarking any code so always ensure that the work is being done or else you will be bench marking absolutly nothing
like here beacase the compiler can actually aggresivlly change your code

## lets find the performence difference between shared and unique pointers

```cpp
#include<iostream>
#include<chrono>
#include<memory>
#include<array>

struct timer
{
std::chrono::time_point<std::chrono::high_resolution_clock> M_startTimepoint , Endpoint;
timer()
{
M_startTimepoint = std::chrono::high_resolution_clock::now();
}
~timer()
{
stop();
}

    void stop()
    {
    	Endpoint = std::chrono::high_resolution_clock::now();
    	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(Endpoint - M_startTimepoint).count();

    	double milli_s = duration * 0.001;

    	std::cout << "microsec = " << duration << "  &    millisec = " << milli_s << std::endl;

    }

};

int main()
{
struct vector
{
float x, y;
};
std::cout << "shared pointer using make_shared\n";
{
std::array<std::shared_ptr<vector>, 1000> sharedptr;
timer t;
for(int i = 0; i < sharedptr.size(); i++)
{
sharedptr[i] = std::make_shared<vector>();
}
}

    std::cout << "shared pointer with out using make_shared	\n";

    {
    	std::array<std::shared_ptr<vector>, 1000> sharedptr;
    	timer t;
    	for (int i = 0; i < sharedptr.size(); i++)
    	{
    		sharedptr[i] = std::shared_ptr<vector>(new vector());
    	}
    }

    std::cout << "unique pointer with make_unique\n";

    {
    	std::array<std::unique_ptr<vector>, 1000> sharedptr;
    	timer t;
    	for (int i = 0; i < sharedptr.size(); i++)
    	{
    		sharedptr[i] = std::make_unique<vector>();
    	}
    }

    std::cout << "unique pointer without make_unique\n";

    {
    	std::array<std::unique_ptr<vector>, 1000> sharedptr;
    	timer t;
    	for (int i = 0; i < sharedptr.size(); i++)
    	{
    		sharedptr[i] = std::unique_ptr<vector>(new vector());
    	}
    }

}
```

- ## debug mode

```bash
shared pointer using make_shared
microsec = 10219 & millisec = 10.219

shared pointer with out using make_shared
microsec = 2752 & millisec = 2.752

unique pointer with make_unique
microsec = 1465 & millisec = 1.465

unique pointer without make_unique
microsec = 2184 & millisec = 2.184
```

- ## release mode

```bash
shared pointer using make_shared
microsec = 185 & millisec = 0.185

shared pointer with out using make_shared
microsec = 307 & millisec = 0.307

unique pointer with make_unique
microsec = 106 & millisec = 0.106

unique pointer without make_unique
microsec = 126 & millisec = 0.126
```

by looking at these benchmarks you can see that the shared pointers are slower then unique pointers
and you can also see that make_unique and make_shared make the code faster instead of making the code slow
so you should be using them




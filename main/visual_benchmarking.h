#pragma once

#include <string>
#include <chrono>
#include <algorithm>
#include <fstream>
#include <thread>
#include <iostream> // Add this include for debug output

struct ProfileResult
{
    std::string Name;
    long long Start, End;
    uint32_t ThreadID;
};

struct InstrumentationSession
{
    std::string Name;
};

class Instrumentor
{
private:
    InstrumentationSession *m_CurrentSession;
    std::ofstream m_OutputStream;
    int m_ProfileCount;

    Instrumentor()
        : m_CurrentSession(nullptr), m_ProfileCount(0)
    {
    }

public:
    Instrumentor(const Instrumentor &) = delete;
    Instrumentor &operator=(const Instrumentor &) = delete;

    void BeginSession(const std::string &name, const std::string &filepath = "results.json")
    {
        m_OutputStream.open(filepath, std::ios::out | std::ios::trunc); // Ensure the file is opened in truncate mode
        WriteHeader();
        m_CurrentSession = new InstrumentationSession{name};
        std::cout << "Session started: " << name << std::endl; // Debug output
    }

    void EndSession()
    {
        WriteFooter();
        m_OutputStream.close();
        delete m_CurrentSession;
        m_CurrentSession = nullptr;
        m_ProfileCount = 0;
        std::cout << "Session ended" << std::endl; // Debug output
    }

    void WriteProfile(const ProfileResult &result)
    {
        if (m_ProfileCount++ > 0)
            m_OutputStream << ",";

        std::string name = result.Name;
        std::replace(name.begin(), name.end(), '"', '\'');

        m_OutputStream << "{";
        m_OutputStream << "\"cat\":\"function\",";
        m_OutputStream << "\"dur\":" << (result.End - result.Start) << ',';
        m_OutputStream << "\"name\":\"" << name << "\",";
        m_OutputStream << "\"ph\":\"X\",";
        m_OutputStream << "\"pid\":0,";
        m_OutputStream << "\"tid\":" << result.ThreadID << ",";
        m_OutputStream << "\"ts\":" << result.Start;
        m_OutputStream << "}";

        m_OutputStream.flush();
        std::cout << "Profile written for: " << name << std::endl; // Debug output
    }

    void WriteHeader()
    {
        m_OutputStream << "{\"otherData\": {},\"traceEvents\":[";
        m_OutputStream.flush();
    }

    void WriteFooter()
    {
        m_OutputStream << "]}";
        m_OutputStream.flush();
    }

    static Instrumentor &Get()
    {
        static Instrumentor instance;
        return instance;
    }
};

class InstrumentationTimer
{
public:
    InstrumentationTimer(const char *name)
        : m_Name(name), m_Stopped(false)
    {
        m_StartTimepoint = std::chrono::high_resolution_clock::now();
        std::cout << "Timer started for: " << m_Name << std::endl; // Debug output
    }

    ~InstrumentationTimer()
    {
        if (!m_Stopped)
            Stop();
    }

    void Stop()
    {
        auto endTimepoint = std::chrono::high_resolution_clock::now();

        long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
        long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

        uint32_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
        Instrumentor::Get().WriteProfile({m_Name, start, end, threadID});

        m_Stopped = true;
        std::cout << "Timer stopped for: " << m_Name << std::endl; // Debug output
    }

private:
    const char *m_Name;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
    bool m_Stopped;
};

#define profiling 1

#if profiling
// Check for Visual Studio compiler

#ifdef _MSC_VER
#define profile_scope(name) InstrumentationTimer timer##__LINE__(name)
#define profile_Function() profile_scope(__FUNCSIG__)

// Check for GCC or Clang compiler
#elif defined(__GNUC__) || defined(__clang__)
#define profile_scope(name) InstrumentationTimer timer##__LINE__(name)
#define profile_Function() profile_scope(__PRETTY_FUNCTION__)

// Add additional compiler checks if needed
#else
#error "Unsupported compiler"
#endif

// Conditional profiling session management (for all compilers)
#define begin_session(session_name) Instrumentor::Get().BeginSession(session_name)
#define end_session() Instrumentor::Get().EndSession()

#else
#define profile_scope(name)
#define profile_Function()

// If profiling is off, just begin and end session
#define begin_session(session_name)
#define end_session()
#endif
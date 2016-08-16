#ifndef MULTITHREADINGOUTPUT_HPP_INCLUDED
#define MULTITHREADINGOUTPUT_HPP_INCLUDED

#include <mutex>

// Mutex to write to the console.
namespace Multithreading
{
    static std::mutex outputMutex;
}

#endif // MULTITHREADINGOUTPUT_HPP_INCLUDED

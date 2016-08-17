#ifndef MULTITHREADING_HPP_INCLUDED
#define MULTITHREADING_HPP_INCLUDED

#include <mutex>

// Mutex to write to the console.
namespace Multithreading
{
    static std::mutex outputMutex;
    static std::mutex databaseMutex;
}

#endif // MULTITHREADING_HPP_INCLUDED

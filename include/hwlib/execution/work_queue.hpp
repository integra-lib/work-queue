#pragma once

#include <functional>

namespace hwlib::execution
{

/// Deferred-execution abstraction: the handler runs later, on whatever context
/// the implementation owns. Implementations are platform specific.
class IWorkQueue
{
public:
    IWorkQueue()          = default;
    virtual ~IWorkQueue() = default;

    IWorkQueue(const IWorkQueue&)            = delete;
    IWorkQueue& operator=(const IWorkQueue&) = delete;
    IWorkQueue(IWorkQueue&&)                 = delete;
    IWorkQueue& operator=(IWorkQueue&&)      = delete;

    virtual void Submit()                                  = 0;
    virtual void SetHandler(std::function<void()> handler) = 0;
};

} // namespace hwlib::execution

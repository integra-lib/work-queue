#include <gtest/gtest.h>

#include <functional>
#include <integra/work_queue.hpp>
#include <utility>

namespace
{

// Minimal implementation, standing in for a platform one: Submit() runs the
// handler immediately.
class ImmediateWorkQueue : public integra::IWorkQueue
{
public:
    void Submit() override
    {
        if (m_handler)
        {
            m_handler();
        }
    }

    void SetHandler(std::function<void()> handler) override
    {
        m_handler = std::move(handler);
    }

private:
    std::function<void()> m_handler;
};

TEST(WorkQueueTest, SubmitWithoutAHandlerIsANoOp)
{
    ImmediateWorkQueue queue;
    queue.Submit();
    SUCCEED();
}

TEST(WorkQueueTest, SubmitRunsTheRegisteredHandler)
{
    ImmediateWorkQueue queue;
    int calls = 0;
    queue.SetHandler([&calls]() { ++calls; });

    queue.Submit();
    queue.Submit();
    EXPECT_EQ(calls, 2);
}

TEST(WorkQueueTest, SetHandlerReplacesThePreviousOne)
{
    ImmediateWorkQueue queue;
    int first  = 0;
    int second = 0;
    queue.SetHandler([&first]() { ++first; });
    queue.SetHandler([&second]() { ++second; });

    queue.Submit();
    EXPECT_EQ(first, 0);
    EXPECT_EQ(second, 1);
}

TEST(WorkQueueTest, IsUsableThroughTheInterface)
{
    ImmediateWorkQueue queue;
    integra::IWorkQueue& iface = queue;
    int calls                  = 0;
    iface.SetHandler([&calls]() { ++calls; });
    iface.Submit();
    EXPECT_EQ(calls, 1);
}

} // namespace

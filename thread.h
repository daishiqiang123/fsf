#pragma once

#include <functional>
#include <memory>
#include <atomic>
#include <thread>

#include "noncopable.h"

class Thread
{
public:
    using threadFunc = std::function<void()>;

    explicit Thread(threadFunc, const std::string &name = std::string());
    ~Thread();

    void start();
    void join();

    bool started() const { return started_; }
    pid_t tid() const { return tid_; }
    const std::string& name() const { return name_; }

    static int numCreated() { return numCreated_; }
private:
    void setDefaultName();

    bool started_;
    bool joined_;
    std::shared_ptr<std::thread> thread_;
    pid_t tid_;
    threadFunc func_;
    std::string name_;
    static std::atomic_int numCreated_;
};
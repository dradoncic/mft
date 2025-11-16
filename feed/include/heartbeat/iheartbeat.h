#pragma once
#include <string>
#include <functional>

class IWSConnector;

enum class HeartbeatStatus
{
    HEALTHY,
    STALE,
    MISSED_BEAT
};

class IHeartbeatPolicy
{
    public:
    virtual ~IHeartbeatPolicy() = default;

    virtual void on_message(IWSConnector& conn, const std::string_view msg) = 0;

    virtual void on_connected(IWSConnector& conn) = 0;

    virtual HeartbeatStatus get_status() const = 0;

    std::function<void(HeartbeatStatus)> on_status_change;
};
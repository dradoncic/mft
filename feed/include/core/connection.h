#pragma once
#include <string>

enum class ConnectionState
{
    DISCONNECTED,
    CONNECTING,
    CONNECTED,
    RECONNECTING,
    ERROR
};

inline std::string connection_state_to_string(ConnectionState state)
{
    switch (state)
    {
        case ConnectionState::DISCONNECTED:
            return "DISCONNECTED";
        case ConnectionState::CONNECTING:
            return "CONNECTING";
        case ConnectionState::CONNECTED:
            return "CONNECTED";
        case ConnectionState::RECONNECTING:
            return "RECONNECTING";
        case ConnectionState::ERROR:
            return "ERROR";
        default:
            return "UNKNOWN";
    }
}
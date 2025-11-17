#include "websocket/iws.h"
#include "heartbeat/iheartbeat.h"

void IWSConnector::handle_message(const std::string_view msg)
{
    if (heartbeat_policy_)
        heartbeat_policy_->on_message(*this, msg);
    if (message_adapter_)
        message_adapter_->on_message(msg);
}

void IWSConnector::handle_disconnect()
{
    set_state(ConnectionState::DISCONNECTED);
    if (on_disconnected)
        on_disconnected();
}
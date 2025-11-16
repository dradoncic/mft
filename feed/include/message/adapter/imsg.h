#pragma once
#include <simdjson.h>

#include <functional>
#include <memory>
#include <string>

#include "../domain/feed_message.h"
class IMessageAdapter
{
   public:
    virtual ~IMessageAdapter() = default;

    virtual void on_message(const std::string_view msg) = 0;

    void on_parsed_message(
        std::function<void(const std::shared_ptr<FeedMessage>&)> callback)
    {
        parsed_message_callback_ = std::move(callback);
    }

   protected:
    simdjson::ondemand::parser parser_;
    std::function<void(const std::shared_ptr<FeedMessage>&)>
        parsed_message_callback_;

    void emit(std::shared_ptr<FeedMessage> msg)
    {
        if (parsed_message_callback_)
            parsed_message_callback_(msg);
    }
};
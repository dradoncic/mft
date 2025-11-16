#pragma once
#include <string>
#include <vector>

#include "../../auth/iauth.h"

struct SubscriptionRequest
{
    std::string channel;
    std::vector<std::string> products;
    std::optional<std::shared_ptr<IAuthProvider>> auth_provider;
};

class ISubscribeBuilder
{
   public:
    virtual ~ISubscribeBuilder() = default;

    virtual std::string build(const SubscriptionRequest& req) = 0;
};

class SubscriptionManager
{
   public:
    void add_subscription(const SubscriptionRequest& req)
    {
        subscriptions_.push_back(req);
    }

    const std::vector<SubscriptionRequest>& get_subscriptions() const
    {
        return subscriptions_;
    }

    void clear_subscriptions()
    {
        subscriptions_.clear();
    }

    bool has_subscriptions() const
    {
        return !subscriptions_.empty();
    }

    size_t subscription_count() const
    {
        return subscriptions_.size();
    }

   private:
    std::vector<SubscriptionRequest> subscriptions_;
};
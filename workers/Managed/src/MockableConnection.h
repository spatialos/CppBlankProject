#ifndef CPP_CONNECTION_MOCK_MOCKABLE_CONNECTION_H
#define CPP_CONNECTION_MOCK_MOCKABLE_CONNECTION_H

#include <improbable/collections.h>
#include <improbable/defaults.h>
#include <improbable/detail/worker_detail.h>
#include <improbable/worker.h>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

namespace worker {

struct CombinedOpList {
    OpList op_list;
};

class MockableConnection {
public:
    MockableConnection(Connection &connection);

    // Noncopyable, but movable.
    MockableConnection(const MockableConnection &) = delete;

    MockableConnection(MockableConnection
    &&) = default;

    MockableConnection &operator=(const MockableConnection &) = delete;

    MockableConnection &operator=(MockableConnection &&) = default;

    bool IsConnected() const;

    std::string GetWorkerId() const;

    worker::List<std::string> GetWorkerAttributes() const;

    Option<std::string> GetWorkerFlag(const std::string &flag_name) const;

    CombinedOpList GetOpList(std::uint32_t timeout_millis);

    void SendLogMessage(LogLevel level, const std::string &logger_name, const std::string &message,
                        const Option<EntityId> &entity_id = {});

    void SendMetrics(Metrics &metrics);

    RequestId<ReserveEntityIdRequest>
    SendReserveEntityIdRequest(const Option<std::uint32_t> &timeout_millis);

    RequestId<ReserveEntityIdsRequest>
    SendReserveEntityIdsRequest(std::uint32_t number_of_entity_ids,
                                const Option<std::uint32_t> &timeout_millis);

    RequestId<CreateEntityRequest>
    SendCreateEntityRequest(const Entity &entity, const Option<EntityId> &entity_id,
                            const Option<std::uint32_t> &timeout_millis);

    RequestId<DeleteEntityRequest>
    SendDeleteEntityRequest(EntityId entity_id, const Option<std::uint32_t> &timeout_millis);

    RequestId<EntityQueryRequest> SendEntityQueryRequest(const query::EntityQuery &entity_query,
                                                         const Option<std::uint32_t> &timeout_millis);

    void SendComponentInterest(EntityId entity_id,
                               const Map<ComponentId, InterestOverride> &interest_overrides);

    void SendAuthorityLossImminentAcknowledgement(EntityId entity_id, ComponentId component_id);

    template<typename T>
    void SendAuthorityLossImminentAcknowledgement(EntityId entity_id);

    template<typename T>
    void SendComponentUpdate(EntityId entity_id, const typename T::Update &update);

    template<typename T>
    void SendComponentUpdate(EntityId entity_id, typename T::Update &&update);

    template<typename T>
    RequestId<OutgoingCommandRequest<T>>
    SendCommandRequest(EntityId entity_id, const typename T::Request &request,
                       const Option<std::uint32_t> &timeout_millis,
                       const CommandParameters &parameters = {false});

    template<typename T>
    RequestId<OutgoingCommandRequest<T>>
    SendCommandRequest(EntityId entity_id, typename T::Request &&request,
                       const Option<std::uint32_t> &timeout_millis,
                       const CommandParameters &parameters = {false});

    template<typename T>
    void SendCommandResponse(RequestId<IncomingCommandRequest<T>> request_id,
                             const typename T::Response &response);

    template<typename T>
    void SendCommandResponse(RequestId<IncomingCommandRequest<T>> request_id,
                             typename T::Response &&response);

    template<typename T>
    void SendCommandFailure(RequestId<IncomingCommandRequest<T>> request_id,
                            const std::string &message);

    void SetProtocolLoggingEnabled(bool enabled);

private:
    Connection connection;
};
}

#endif //CPP_CONNECTION_MOCK_MOCKABLE_CONNECTION_H

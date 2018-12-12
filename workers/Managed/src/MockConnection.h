#ifndef CPP_CONNECTION_MOCK_CONNECTION_H
#define CPP_CONNECTION_MOCK_CONNECTION_H

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
#include "FakeOp.h"

namespace worker {

class MockConnection {
public:
    MockConnection() : fakeOpList{List<FakeOp>{}} {}

    bool IsConnected() const {
        return true;
    }

    std::string GetWorkerId() const {
        return "WorkerId";
    }

    List<std::string> GetWorkerAttributes() const {
        return List<std::string>{"attribute"};
    }

    Option<std::string> GetWorkerFlag(const std::string &flag_name) const {
        return Option<std::string>("flag_value");
    }

    List<FakeOp> GetOpList(std::uint32_t timeout_millis) {
        auto returnFakeOpList = fakeOpList;
        fakeOpList.clear();
        return returnFakeOpList;
    }

    void SendLogMessage(LogLevel level, const std::string& logger_name, const std::string& message,
                        const Option<EntityId>& entity_id = {}) {

    }

    void SendMetrics(Metrics &metrics) {
    }

    RequestId<ReserveEntityIdRequest>
    SendReserveEntityIdRequest(const Option<uint32_t> &timeout_millis) {
        return RequestId<ReserveEntityIdRequest>(1);
    }

    RequestId<ReserveEntityIdsRequest>
    SendReserveEntityIdsRequest(std::uint32_t number_of_entity_ids,
                                                        const Option<uint32_t> &timeout_millis) {
        return RequestId<ReserveEntityIdsRequest>(1);
    }

    RequestId<CreateEntityRequest>
    SendCreateEntityRequest(const Entity &entity,
                                                    const Option<EntityId> &entity_id,
                                                    const Option<uint32_t> &timeout_millis) {
        return RequestId<CreateEntityRequest>(1);
    }

    RequestId<DeleteEntityRequest>
    SendDeleteEntityRequest(EntityId entity_id,
                                                    const Option<uint32_t> &timeout_millis) {
        return RequestId<DeleteEntityRequest>(1);
    }

    RequestId<EntityQueryRequest>
    SendEntityQueryRequest(const query::EntityQuery &entity_query,
                                                   const Option<uint32_t> &timeout_millis) {
        return RequestId<EntityQueryRequest>(1);
    }

    void SendComponentInterest(EntityId entity_id,
                                                       const Map<ComponentId, InterestOverride> &interest_overrides) {

    }

    void SendAuthorityLossImminentAcknowledgement(EntityId entity_id,
                                                                          ComponentId component_id) {

    }

    template<typename T>
    void SendAuthorityLossImminentAcknowledgement(EntityId entity_id) {

    }

    template<typename T>
    void SendComponentUpdate(EntityId entity_id, const typename T::Update &update) {
        auto op = std::shared_ptr<void>(new ComponentUpdateOp<T>{entity_id, update});
        FakeOpCompleteType type{
            FAKE_OP_TYPE_COMPONENT_UPDATE,
            T::ComponentId
        };

        FakeOp fakeOp{
            type,
            std::move(op)
        };

        fakeOpList.emplace_back(fakeOp);
    }

    template<typename T>
    void SendComponentUpdate(EntityId entity_id, typename T::Update &&update) {
    }

    template<typename T>
    RequestId<OutgoingCommandRequest<T>>
    SendCommandRequest(EntityId entity_id, const typename T::Request &request,
                                               const Option<uint32_t> &timeout_millis,
                                               const CommandParameters &parameters) {
    }

    template<typename T>
    RequestId<OutgoingCommandRequest<T>>
    SendCommandRequest(EntityId entity_id, typename T::Request &&request,
                                               const Option<uint32_t> &timeout_millis,
                                               const CommandParameters &parameters) {
    }

    template<typename T>
    void SendCommandResponse(RequestId<IncomingCommandRequest<T>> request_id,
                                                     const typename T::Response &response) {
    }

    template<typename T>
    void SendCommandResponse(RequestId<IncomingCommandRequest<T>> request_id,
                                                     typename T::Response &&response) {
    }

    template<typename T>
    void SendCommandFailure(RequestId<IncomingCommandRequest<T>> request_id,
                                                    const std::string &message) {
    }

    void SetProtocolLoggingEnabled(bool enabled) {
    }

private:
    List<FakeOp> fakeOpList;
};

}

#endif //CPP_CONNECTION_MOCK_CONNECTION_H

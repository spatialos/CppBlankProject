#include "MockConnection.h"

worker::MockConnection::MockConnection() : fake_op_list{worker::List<worker::FakeOp>{}} {}

bool worker::MockConnection::IsConnected() const {
    return true;
}

std::string worker::MockConnection::GetWorkerId() const {
    return "WorkerId";
}

worker::List<std::string> worker::MockConnection::GetWorkerAttributes() const {
    return worker::List<std::string>{"attribute"};
}

worker::Option<std::string> worker::MockConnection::GetWorkerFlag(const std::string &flag_name) const {
    return worker::Option<std::string>("flag_value");
}

worker::List<worker::FakeOp> worker::MockConnection::GetOpList(std::uint32_t timeout_millis) {
    /* TODO(nik): Check that this actually copies the list. */
    auto fake_op_list_copy =  fake_op_list;
    fake_op_list.clear();
    return fake_op_list_copy;
}

void worker::MockConnection::SendLogMessage(worker::LogLevel level, const std::string &logger_name,
                                                const std::string &message,
                                                const worker::Option<worker::EntityId> &entity_id) {
}

void worker::MockConnection::SendMetrics(worker::Metrics &metrics) {
}

worker::RequestId<worker::ReserveEntityIdRequest>
worker::MockConnection::SendReserveEntityIdRequest(const worker::Option<uint32_t> &timeout_millis) {
    return worker::RequestId<worker::ReserveEntityIdRequest>(1);
}

worker::RequestId<worker::ReserveEntityIdsRequest>
worker::MockConnection::SendReserveEntityIdsRequest(std::uint32_t number_of_entity_ids,
                                                        const worker::Option<uint32_t> &timeout_millis) {
    return worker::RequestId<worker::ReserveEntityIdsRequest>(1);
}

worker::RequestId<worker::CreateEntityRequest>
worker::MockConnection::SendCreateEntityRequest(const worker::Entity &entity,
                                                    const worker::Option<worker::EntityId> &entity_id,
                                                    const worker::Option<uint32_t> &timeout_millis) {
    return worker::RequestId<worker::CreateEntityRequest>(1);
}

worker::RequestId<worker::DeleteEntityRequest>
worker::MockConnection::SendDeleteEntityRequest(worker::EntityId entity_id,
                                                    const worker::Option<uint32_t> &timeout_millis) {
    return worker::RequestId<worker::DeleteEntityRequest>(1);
}

worker::RequestId<worker::EntityQueryRequest>
worker::MockConnection::SendEntityQueryRequest(const worker::query::EntityQuery &entity_query,
                                                   const worker::Option<uint32_t> &timeout_millis) {
    return worker::RequestId<worker::EntityQueryRequest>(1);
}

void worker::MockConnection::SendComponentInterest(worker::EntityId entity_id,
                                                       const worker::Map<worker::ComponentId, worker::InterestOverride> &interest_overrides) {

}

void worker::MockConnection::SendAuthorityLossImminentAcknowledgement(worker::EntityId entity_id,
                                                                      worker::ComponentId component_id) {

}

template<typename T>
void worker::MockConnection::SendAuthorityLossImminentAcknowledgement(worker::EntityId entity_id) {

}

template<typename T>
void worker::MockConnection::SendComponentUpdate(worker::EntityId entity_id, const typename T::Update &update) {
    auto op = new ComponentUpdateOp<T>{entity_id, update};
    FakeOpCompleteType type {
        FAKE_OP_TYPE_COMPONENT_UPDATE,
        T::ComponentId
    };

    FakeOp fakeOp {
        type,
        op
    };

    fake_op_list.emplace_back(fakeOp);
}

template<typename T>
void worker::MockConnection::SendComponentUpdate(worker::EntityId entity_id, typename T::Update &&update) {
}

template<typename T>
worker::RequestId<worker::OutgoingCommandRequest<T>>
worker::MockConnection::SendCommandRequest(worker::EntityId entity_id, const typename T::Request &request,
                                               const worker::Option<uint32_t> &timeout_millis,
                                               const worker::CommandParameters &parameters) {
}

template<typename T>
worker::RequestId<worker::OutgoingCommandRequest<T>>
worker::MockConnection::SendCommandRequest(worker::EntityId entity_id, typename T::Request &&request,
                                               const worker::Option<uint32_t> &timeout_millis,
                                               const worker::CommandParameters &parameters) {
}

template<typename T>
void worker::MockConnection::SendCommandResponse(worker::RequestId<worker::IncomingCommandRequest<T>> request_id,
                                                     const typename T::Response &response) {
}

template<typename T>
void worker::MockConnection::SendCommandResponse(worker::RequestId<worker::IncomingCommandRequest<T>> request_id,
                                                     typename T::Response &&response) {
}

template<typename T>
void worker::MockConnection::SendCommandFailure(worker::RequestId<worker::IncomingCommandRequest<T>> request_id,
                                                    const std::string &message) {
}

void worker::MockConnection::SetProtocolLoggingEnabled(bool enabled) {
}

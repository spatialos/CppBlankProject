#include "MockableConnection.h"

worker::MockableConnection::MockableConnection(worker::Connection &connection) : connection{std::move(connection)} {}

std::string worker::MockableConnection::GetWorkerId() const {
    return connection.GetWorkerId();
}

bool worker::MockableConnection::IsConnected() const {
    return connection.IsConnected();
}

worker::List<std::string> worker::MockableConnection::GetWorkerAttributes() const {
    return connection.GetWorkerAttributes();
}

worker::Option<std::string> worker::MockableConnection::GetWorkerFlag(const std::string &flag_name) const {
    return connection.GetWorkerFlag(flag_name);
}

worker::CombinedOpList worker::MockableConnection::GetOpList(std::uint32_t timeout_millis) {
    worker::CombinedOpList combinedOpList = {
            connection.GetOpList(timeout_millis)
    };
    return combinedOpList;
}

void worker::MockableConnection::SendLogMessage(worker::LogLevel level, const std::string &logger_name,
                                                const std::string &message,
                                                const worker::Option<worker::EntityId> &entity_id) {
    connection.SendLogMessage(level, logger_name, message, entity_id);
}

void worker::MockableConnection::SendMetrics(worker::Metrics &metrics) {
    connection.SendMetrics(metrics);
}

worker::RequestId<worker::ReserveEntityIdRequest>
worker::MockableConnection::SendReserveEntityIdRequest(const worker::Option<uint32_t> &timeout_millis) {
    return connection.SendReserveEntityIdRequest(timeout_millis);
}

worker::RequestId<worker::ReserveEntityIdsRequest>
worker::MockableConnection::SendReserveEntityIdsRequest(std::uint32_t number_of_entity_ids,
                                                        const worker::Option<uint32_t> &timeout_millis) {
    return connection.SendReserveEntityIdsRequest(number_of_entity_ids, timeout_millis);
}

worker::RequestId<worker::CreateEntityRequest>
worker::MockableConnection::SendCreateEntityRequest(const worker::Entity &entity,
                                                    const worker::Option<worker::EntityId> &entity_id,
                                                    const worker::Option<uint32_t> &timeout_millis) {
    return connection.SendCreateEntityRequest(entity, entity_id, timeout_millis);
}

worker::RequestId<worker::DeleteEntityRequest>
worker::MockableConnection::SendDeleteEntityRequest(worker::EntityId entity_id,
                                                    const worker::Option<uint32_t> &timeout_millis) {
    return connection.SendDeleteEntityRequest(entity_id, timeout_millis);
}

worker::RequestId<worker::EntityQueryRequest>
worker::MockableConnection::SendEntityQueryRequest(const worker::query::EntityQuery &entity_query,
                                                   const worker::Option<uint32_t> &timeout_millis) {
    return connection.SendEntityQueryRequest(entity_query, timeout_millis);
}

void worker::MockableConnection::SendComponentInterest(worker::EntityId entity_id,
                                                       const worker::Map<worker::ComponentId, worker::InterestOverride> &interest_overrides) {
    return connection.SendComponentInterest(entity_id, interest_overrides);

}

void worker::MockableConnection::SendAuthorityLossImminentAcknowledgement(worker::EntityId entity_id,
                                                                          worker::ComponentId component_id) {
    return connection.SendAuthorityLossImminentAcknowledgement(entity_id, component_id);
}

template<typename T>
void worker::MockableConnection::SendAuthorityLossImminentAcknowledgement(worker::EntityId entity_id) {
    return connection.SendAuthorityLossImminentAcknowledgement(entity_id);
}

template<typename T>
void worker::MockableConnection::SendComponentUpdate(worker::EntityId entity_id, const typename T::Update &update) {
    return connection.SendComponentUpdate(entity_id, update);
}

template<typename T>
void worker::MockableConnection::SendComponentUpdate(worker::EntityId entity_id, typename T::Update &&update) {
    return connection.SendComponentUpdate(entity_id, update);
}

template<typename T>
worker::RequestId<worker::OutgoingCommandRequest<T>>
worker::MockableConnection::SendCommandRequest(worker::EntityId entity_id, const typename T::Request &request,
                                               const worker::Option<uint32_t> &timeout_millis,
                                               const worker::CommandParameters &parameters) {
    return connection.SendCommandRequest(entity_id, request, timeout_millis, parameters);
}

template<typename T>
worker::RequestId<worker::OutgoingCommandRequest<T>>
worker::MockableConnection::SendCommandRequest(worker::EntityId entity_id, typename T::Request &&request,
                                               const worker::Option<uint32_t> &timeout_millis,
                                               const worker::CommandParameters &parameters) {
    return connection.SendCommandRequest(entity_id, request, timeout_millis, parameters);
}

template<typename T>
void worker::MockableConnection::SendCommandResponse(worker::RequestId<worker::IncomingCommandRequest<T>> request_id,
                                                     const typename T::Response &response) {
    return connection.SendCommandResponse(request_id, response);
}

template<typename T>
void worker::MockableConnection::SendCommandResponse(worker::RequestId<worker::IncomingCommandRequest<T>> request_id,
                                                     typename T::Response &&response) {
    return connection.SendCommandResponse(request_id, response);
}

template<typename T>
void worker::MockableConnection::SendCommandFailure(worker::RequestId<worker::IncomingCommandRequest<T>> request_id,
                                                    const std::string &message) {
    connection.SendCommandFailure(request_id, message);
}

void worker::MockableConnection::SetProtocolLoggingEnabled(bool enabled) {
    connection.SetProtocolLoggingEnabled(enabled);
}

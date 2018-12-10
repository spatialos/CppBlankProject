#include "MockableDispatcher.h"


worker::MockableDispatcher::MockableDispatcher(worker::Dispatcher &dispatcher) : dispatcher{dispatcher} {}

worker::MockableDispatcher::CallbackKey
worker::MockableDispatcher::OnDisconnect(const worker::MockableDispatcher::Callback<worker::DisconnectOp> &callback) {
    return dispatcher.OnDisconnect(callback);
}

worker::MockableDispatcher::CallbackKey
worker::MockableDispatcher::OnFlagUpdate(const worker::MockableDispatcher::Callback<worker::FlagUpdateOp> &callback) {
    return dispatcher.OnFlagUpdate(callback);
}

worker::MockableDispatcher::CallbackKey
worker::MockableDispatcher::OnLogMessage(const worker::MockableDispatcher::Callback<worker::LogMessageOp> &callback) {
    return dispatcher.OnLogMessage(callback);
}

worker::MockableDispatcher::CallbackKey
worker::MockableDispatcher::OnMetrics(const worker::MockableDispatcher::Callback<worker::MetricsOp> &callback) {
    return dispatcher.OnMetrics(callback);
}

worker::MockableDispatcher::CallbackKey worker::MockableDispatcher::OnCriticalSection(
        const worker::MockableDispatcher::Callback<worker::CriticalSectionOp> &callback) {
    return dispatcher.OnCriticalSection(callback);
}

worker::MockableDispatcher::CallbackKey
worker::MockableDispatcher::OnAddEntity(const worker::MockableDispatcher::Callback<worker::AddEntityOp> &callback) {
    return dispatcher.OnAddEntity(callback);
}

worker::MockableDispatcher::CallbackKey worker::MockableDispatcher::OnRemoveEntity(
        const worker::MockableDispatcher::Callback<worker::RemoveEntityOp> &callback) {
    return dispatcher.OnRemoveEntity(callback);
}

worker::MockableDispatcher::CallbackKey worker::MockableDispatcher::OnReserveEntityIdResponse(
        const worker::MockableDispatcher::Callback<worker::ReserveEntityIdResponseOp> &callback) {
    return dispatcher.OnReserveEntityIdResponse(callback);
}

worker::MockableDispatcher::CallbackKey worker::MockableDispatcher::OnReserveEntityIdsResponse(
        const worker::MockableDispatcher::Callback<worker::ReserveEntityIdsResponseOp> &callback) {
    return dispatcher.OnReserveEntityIdsResponse(callback);
}

worker::MockableDispatcher::CallbackKey worker::MockableDispatcher::OnCreateEntityResponse(
        const worker::MockableDispatcher::Callback<worker::CreateEntityResponseOp> &callback) {
    return dispatcher.OnCreateEntityResponse(callback);
}

worker::MockableDispatcher::CallbackKey worker::MockableDispatcher::OnDeleteEntityResponse(
        const worker::MockableDispatcher::Callback<worker::DeleteEntityResponseOp> &callback) {
    return dispatcher.OnDeleteEntityResponse(callback);
}

worker::MockableDispatcher::CallbackKey worker::MockableDispatcher::OnEntityQueryResponse(
        const worker::MockableDispatcher::Callback<worker::EntityQueryResponseOp> &callback) {
    return dispatcher.OnEntityQueryResponse(callback);
}

template<typename T>
worker::MockableDispatcher::CallbackKey worker::MockableDispatcher::OnAddComponent(
        const worker::MockableDispatcher::Callback<worker::AddComponentOp<T>> &callback) {
    return dispatcher.OnAddComponent(callback);
}

template<typename T>
worker::MockableDispatcher::CallbackKey worker::MockableDispatcher::OnRemoveComponent(
        const worker::MockableDispatcher::Callback<worker::RemoveComponentOp> &callback) {
    return dispatcher.OnRemoveComponent(callback);
}

template<typename T>
worker::MockableDispatcher::CallbackKey worker::MockableDispatcher::OnAuthorityChange(
        const worker::MockableDispatcher::Callback<worker::AuthorityChangeOp> &callback) {
    return dispatcher.OnAuthorityChange(callback);
}

template<typename T>
worker::MockableDispatcher::CallbackKey worker::MockableDispatcher::OnComponentUpdate(
        const worker::MockableDispatcher::Callback<worker::ComponentUpdateOp<T>> &callback) {
    return dispatcher.OnComponentUpdate(callback);
}

template<typename T>
worker::MockableDispatcher::CallbackKey worker::MockableDispatcher::OnCommandRequest(
        const worker::MockableDispatcher::Callback<worker::CommandRequestOp<T>> &callback) {
    return dispatcher.OnCommandRequest(callback);
}

template<typename T>
worker::MockableDispatcher::CallbackKey worker::MockableDispatcher::OnCommandResponse(
        const worker::MockableDispatcher::Callback<worker::CommandResponseOp<T>> &callback) {
    return dispatcher.OnCommandResponse(callback);
}

void worker::MockableDispatcher::Remove(worker::MockableDispatcher::CallbackKey key) {
    dispatcher.Remove(key);
}

void worker::MockableDispatcher::Process(const worker::CombinedOpList &combined_op_list) const {
    dispatcher.Process(combined_op_list.op_list);
}

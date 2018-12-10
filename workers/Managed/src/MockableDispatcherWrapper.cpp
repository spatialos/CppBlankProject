#include "MockableDispatcherWrapper.h"


worker::MockableDispatcherWrapper::MockableDispatcherWrapper(worker::Dispatcher &dispatcher) : dispatcher{dispatcher} {}

worker::MockableDispatcherWrapper::CallbackKey
worker::MockableDispatcherWrapper::OnDisconnect(const worker::MockableDispatcherWrapper::Callback<worker::DisconnectOp> &callback) {
    return dispatcher.OnDisconnect(callback);
}

worker::MockableDispatcherWrapper::CallbackKey
worker::MockableDispatcherWrapper::OnFlagUpdate(const worker::MockableDispatcherWrapper::Callback<worker::FlagUpdateOp> &callback) {
    return dispatcher.OnFlagUpdate(callback);
}

worker::MockableDispatcherWrapper::CallbackKey
worker::MockableDispatcherWrapper::OnLogMessage(const worker::MockableDispatcherWrapper::Callback<worker::LogMessageOp> &callback) {
    return dispatcher.OnLogMessage(callback);
}

worker::MockableDispatcherWrapper::CallbackKey
worker::MockableDispatcherWrapper::OnMetrics(const worker::MockableDispatcherWrapper::Callback<worker::MetricsOp> &callback) {
    return dispatcher.OnMetrics(callback);
}

worker::MockableDispatcherWrapper::CallbackKey worker::MockableDispatcherWrapper::OnCriticalSection(
        const worker::MockableDispatcherWrapper::Callback<worker::CriticalSectionOp> &callback) {
    return dispatcher.OnCriticalSection(callback);
}

worker::MockableDispatcherWrapper::CallbackKey
worker::MockableDispatcherWrapper::OnAddEntity(const worker::MockableDispatcherWrapper::Callback<worker::AddEntityOp> &callback) {
    return dispatcher.OnAddEntity(callback);
}

worker::MockableDispatcherWrapper::CallbackKey worker::MockableDispatcherWrapper::OnRemoveEntity(
        const worker::MockableDispatcherWrapper::Callback<worker::RemoveEntityOp> &callback) {
    return dispatcher.OnRemoveEntity(callback);
}

worker::MockableDispatcherWrapper::CallbackKey worker::MockableDispatcherWrapper::OnReserveEntityIdResponse(
        const worker::MockableDispatcherWrapper::Callback<worker::ReserveEntityIdResponseOp> &callback) {
    return dispatcher.OnReserveEntityIdResponse(callback);
}

worker::MockableDispatcherWrapper::CallbackKey worker::MockableDispatcherWrapper::OnReserveEntityIdsResponse(
        const worker::MockableDispatcherWrapper::Callback<worker::ReserveEntityIdsResponseOp> &callback) {
    return dispatcher.OnReserveEntityIdsResponse(callback);
}

worker::MockableDispatcherWrapper::CallbackKey worker::MockableDispatcherWrapper::OnCreateEntityResponse(
        const worker::MockableDispatcherWrapper::Callback<worker::CreateEntityResponseOp> &callback) {
    return dispatcher.OnCreateEntityResponse(callback);
}

worker::MockableDispatcherWrapper::CallbackKey worker::MockableDispatcherWrapper::OnDeleteEntityResponse(
        const worker::MockableDispatcherWrapper::Callback<worker::DeleteEntityResponseOp> &callback) {
    return dispatcher.OnDeleteEntityResponse(callback);
}

worker::MockableDispatcherWrapper::CallbackKey worker::MockableDispatcherWrapper::OnEntityQueryResponse(
        const worker::MockableDispatcherWrapper::Callback<worker::EntityQueryResponseOp> &callback) {
    return dispatcher.OnEntityQueryResponse(callback);
}

template<typename T>
worker::MockableDispatcherWrapper::CallbackKey worker::MockableDispatcherWrapper::OnAddComponent(
        const worker::MockableDispatcherWrapper::Callback<worker::AddComponentOp<T>> &callback) {
    return dispatcher.OnAddComponent(callback);
}

template<typename T>
worker::MockableDispatcherWrapper::CallbackKey worker::MockableDispatcherWrapper::OnRemoveComponent(
        const worker::MockableDispatcherWrapper::Callback<worker::RemoveComponentOp> &callback) {
    return dispatcher.OnRemoveComponent(callback);
}

template<typename T>
worker::MockableDispatcherWrapper::CallbackKey worker::MockableDispatcherWrapper::OnAuthorityChange(
        const worker::MockableDispatcherWrapper::Callback<worker::AuthorityChangeOp> &callback) {
    return dispatcher.OnAuthorityChange(callback);
}

template<typename T>
worker::MockableDispatcherWrapper::CallbackKey worker::MockableDispatcherWrapper::OnComponentUpdate(
        const worker::MockableDispatcherWrapper::Callback<worker::ComponentUpdateOp<T>> &callback) {
    return dispatcher.OnComponentUpdate(callback);
}

template<typename T>
worker::MockableDispatcherWrapper::CallbackKey worker::MockableDispatcherWrapper::OnCommandRequest(
        const worker::MockableDispatcherWrapper::Callback<worker::CommandRequestOp<T>> &callback) {
    return dispatcher.OnCommandRequest(callback);
}

template<typename T>
worker::MockableDispatcherWrapper::CallbackKey worker::MockableDispatcherWrapper::OnCommandResponse(
        const worker::MockableDispatcherWrapper::Callback<worker::CommandResponseOp<T>> &callback) {
    return dispatcher.OnCommandResponse(callback);
}

void worker::MockableDispatcherWrapper::Remove(worker::MockableDispatcherWrapper::CallbackKey key) {
    dispatcher.Remove(key);
}

void worker::MockableDispatcherWrapper::Process(const worker::CombinedOpList &combined_op_list) const {
    dispatcher.Process(combined_op_list.op_list);
}

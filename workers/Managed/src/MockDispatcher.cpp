#include "MockDispatcher.h"

worker::MockDispatcher::MockDispatcher(const worker::ComponentRegistry &registry) : registry{registry} {}

worker::MockDispatcher::CallbackKey
worker::MockDispatcher::OnDisconnect(const worker::MockDispatcher::Callback<worker::DisconnectOp> &callback) {
    return worker::MockDispatcher::CallbackKey{1};
}

worker::MockDispatcher::CallbackKey
worker::MockDispatcher::OnFlagUpdate(const worker::MockDispatcher::Callback<worker::FlagUpdateOp> &callback) {
    return worker::MockDispatcher::CallbackKey{1};
}

worker::MockDispatcher::CallbackKey
worker::MockDispatcher::OnLogMessage(const worker::MockDispatcher::Callback<worker::LogMessageOp> &callback) {
    return worker::MockDispatcher::CallbackKey{1};
}

worker::MockDispatcher::CallbackKey
worker::MockDispatcher::OnMetrics(const worker::MockDispatcher::Callback<worker::MetricsOp> &callback) {
    return worker::MockDispatcher::CallbackKey{1};
}

worker::MockDispatcher::CallbackKey worker::MockDispatcher::OnCriticalSection(
        const worker::MockDispatcher::Callback<worker::CriticalSectionOp> &callback) {
    return worker::MockDispatcher::CallbackKey{1};
}

worker::MockDispatcher::CallbackKey
worker::MockDispatcher::OnAddEntity(const worker::MockDispatcher::Callback<worker::AddEntityOp> &callback) {
    return worker::MockDispatcher::CallbackKey{1};
}

worker::MockDispatcher::CallbackKey worker::MockDispatcher::OnRemoveEntity(
        const worker::MockDispatcher::Callback<worker::RemoveEntityOp> &callback) {
    return worker::MockDispatcher::CallbackKey{1};
}

worker::MockDispatcher::CallbackKey worker::MockDispatcher::OnReserveEntityIdResponse(
        const worker::MockDispatcher::Callback<worker::ReserveEntityIdResponseOp> &callback) {
    return worker::MockDispatcher::CallbackKey{1};
}

worker::MockDispatcher::CallbackKey worker::MockDispatcher::OnReserveEntityIdsResponse(
        const worker::MockDispatcher::Callback<worker::ReserveEntityIdsResponseOp> &callback) {
    return worker::MockDispatcher::CallbackKey{1};
}

worker::MockDispatcher::CallbackKey worker::MockDispatcher::OnCreateEntityResponse(
        const worker::MockDispatcher::Callback<worker::CreateEntityResponseOp> &callback) {
    return worker::MockDispatcher::CallbackKey{1};
}

worker::MockDispatcher::CallbackKey worker::MockDispatcher::OnDeleteEntityResponse(
        const worker::MockDispatcher::Callback<worker::DeleteEntityResponseOp> &callback) {
    return worker::MockDispatcher::CallbackKey{1};
}

worker::MockDispatcher::CallbackKey worker::MockDispatcher::OnEntityQueryResponse(
        const worker::MockDispatcher::Callback<worker::EntityQueryResponseOp> &callback) {
    return worker::MockDispatcher::CallbackKey{1};
}

template<typename T>
worker::MockDispatcher::CallbackKey worker::MockDispatcher::OnAddComponent(
        const worker::MockDispatcher::Callback<worker::AddComponentOp<T>> &callback) {
    return worker::MockDispatcher::CallbackKey{1};
}

template<typename T>
worker::MockDispatcher::CallbackKey worker::MockDispatcher::OnRemoveComponent(
        const worker::MockDispatcher::Callback<worker::RemoveComponentOp> &callback) {
    return worker::MockDispatcher::CallbackKey{1};
}

template<typename T>
worker::MockDispatcher::CallbackKey worker::MockDispatcher::OnAuthorityChange(
        const worker::MockDispatcher::Callback<worker::AuthorityChangeOp> &callback) {
    return worker::MockDispatcher::CallbackKey{1};
}

template<typename T>
worker::MockDispatcher::CallbackKey worker::MockDispatcher::OnComponentUpdate(
        const worker::MockDispatcher::Callback<worker::ComponentUpdateOp<T>> &callback) {
    return worker::MockDispatcher::CallbackKey{1};
}

template<typename T>
worker::MockDispatcher::CallbackKey worker::MockDispatcher::OnCommandRequest(
        const worker::MockDispatcher::Callback<worker::CommandRequestOp<T>> &callback) {
    return worker::MockDispatcher::CallbackKey{1};
}

template<typename T>
worker::MockDispatcher::CallbackKey worker::MockDispatcher::OnCommandResponse(
        const worker::MockDispatcher::Callback<worker::CommandResponseOp<T>> &callback) {
    return worker::MockDispatcher::CallbackKey{1};
}

void worker::MockDispatcher::Remove(worker::MockDispatcher::CallbackKey key) {
}

void worker::MockDispatcher::Process(const worker::List<worker::FakeOp> &fake_op_list) const {
    for (auto iterator = fake_op_list.begin(); iterator != fake_op_list.end(); ++iterator) {
        auto fake_op = *iterator;
        switch (fake_op.type) {
            case FAKE_OP_TYPE_COMPONENT_UPDATE:
                return;
        }
    }
}

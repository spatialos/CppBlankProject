#ifndef CPP_CONNECTION_MOCK_MOCKABLEDISPATCHER_H
#define CPP_CONNECTION_MOCK_MOCKABLEDISPATCHER_H
#include <improbable/collections.h>
#include <improbable/defaults.h>
#include <improbable/detail/worker_detail.h>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include "MockableConnectionWrapper.h"

namespace worker {

class MockableDispatcherWrapper {
public:
    template<typename T>
    using Callback = std::function<void(const T &)>;
    using CallbackKey = std::uint64_t;

    MockableDispatcherWrapper(Dispatcher &dispatcher);

    // Not copyable or movable.
    MockableDispatcherWrapper(const MockableDispatcherWrapper &) = delete;

    MockableDispatcherWrapper(MockableDispatcherWrapper &&) = delete;

    MockableDispatcherWrapper &operator=(const MockableDispatcherWrapper &) = delete;

    MockableDispatcherWrapper &operator=(MockableDispatcherWrapper &&) = delete;

    CallbackKey OnDisconnect(const Callback<DisconnectOp> &callback);

    CallbackKey OnFlagUpdate(const Callback<FlagUpdateOp> &callback);

    CallbackKey OnLogMessage(const Callback<LogMessageOp> &callback);

    CallbackKey OnMetrics(const Callback<MetricsOp> &callback);

    CallbackKey OnCriticalSection(const Callback<CriticalSectionOp> &callback);

    CallbackKey OnAddEntity(const Callback<AddEntityOp> &callback);

    CallbackKey OnRemoveEntity(const Callback<RemoveEntityOp> &callback);

    CallbackKey OnReserveEntityIdResponse(const Callback<ReserveEntityIdResponseOp> &callback);

    CallbackKey OnReserveEntityIdsResponse(const Callback<ReserveEntityIdsResponseOp> &callback);

    CallbackKey OnCreateEntityResponse(const Callback<CreateEntityResponseOp> &callback);

    CallbackKey OnDeleteEntityResponse(const Callback<DeleteEntityResponseOp> &callback);

    CallbackKey OnEntityQueryResponse(const Callback<EntityQueryResponseOp> &callback);

    template<typename T>
    CallbackKey OnAddComponent(const Callback<AddComponentOp < T>> & callback);

    template<typename T>
    CallbackKey OnRemoveComponent(const Callback<RemoveComponentOp> &callback);

    template<typename T>
    CallbackKey OnAuthorityChange(const Callback<AuthorityChangeOp> &callback);

    template<typename T>
    CallbackKey OnComponentUpdate(const Callback<ComponentUpdateOp < T>>

    & callback);

    template<typename T>
    CallbackKey OnCommandRequest(const Callback<CommandRequestOp < T>>

    & callback);

    template<typename T>
    CallbackKey OnCommandResponse(const Callback<CommandResponseOp < T>>

    & callback);

    void Remove(CallbackKey key);

    void Process(const CombinedOpList &combined_op_list) const;

private:
    Dispatcher &dispatcher;
};

}

#endif //CPP_CONNECTION_MOCK_MOCKABLEDISPATCHER_H

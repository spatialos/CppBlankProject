#ifndef CPP_CONNECTION_MOCK_MOCKABLEDISPATCHER_H
#define CPP_CONNECTION_MOCK_MOCKABLEDISPATCHER_H
#include <improbable/collections.h>
#include <improbable/defaults.h>
#include <improbable/detail/worker_detail.h>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include "MockConnection.h"

/* NOTE: We define the implementation in the header file to avoid the 'unresolved external symbol' errors
 * we try to link the header and have a source file contain the implementation. */

namespace worker {

class MockDispatcher {
public:
    template<typename T>
    using Callback = std::function<void(const T &)>;
    using CallbackKey = std::uint64_t;

    MockDispatcher(const ComponentRegistry &registry) : registry{registry},
    callbackMap{std::map<FakeOpCompleteType, List<std::function<void(void*)>>>{}}
    {
    }

    CallbackKey
    OnDisconnect(const Callback<DisconnectOp> &callback) {
        return CallbackKey{1};
    }

    CallbackKey
    OnFlagUpdate(const Callback<FlagUpdateOp> &callback) {
        return CallbackKey{1};
    }

    CallbackKey
    OnLogMessage(const Callback<LogMessageOp> &callback) {
        return CallbackKey{1};
    }

    CallbackKey
    OnMetrics(const Callback<MetricsOp> &callback) {
        return CallbackKey{1};
    }

    CallbackKey OnCriticalSection(
            const Callback<CriticalSectionOp> &callback) {
        return CallbackKey{1};
    }

    CallbackKey
    OnAddEntity(const Callback<AddEntityOp> &callback) {
        return CallbackKey{1};
    }

    CallbackKey OnRemoveEntity(
            const Callback<RemoveEntityOp> &callback) {
        return CallbackKey{1};
    }

    CallbackKey OnReserveEntityIdResponse(
            const Callback<ReserveEntityIdResponseOp> &callback) {
        return CallbackKey{1};
    }

    CallbackKey OnReserveEntityIdsResponse(
            const Callback<ReserveEntityIdsResponseOp> &callback) {
        return CallbackKey{1};
    }

    CallbackKey OnCreateEntityResponse(
            const Callback<CreateEntityResponseOp> &callback) {
        return CallbackKey{1};
    }

    CallbackKey OnDeleteEntityResponse(
            const Callback<DeleteEntityResponseOp> &callback) {
        return CallbackKey{1};
    }

    CallbackKey OnEntityQueryResponse(
            const Callback<EntityQueryResponseOp> &callback) {
        return CallbackKey{1};
    }

    template<typename T>
    CallbackKey OnAddComponent(const Callback<AddComponentOp<T>> &callback) {
        return CallbackKey{1};
    }

    template<typename T>
    CallbackKey OnRemoveComponent(
            const Callback<RemoveComponentOp> &callback) {
        return CallbackKey{1};
    }

    template<typename T>
    CallbackKey OnAuthorityChange(
            const Callback<AuthorityChangeOp> &callback) {
        return CallbackKey{1};
    }

    template<typename T>
    CallbackKey OnComponentUpdate(const Callback<ComponentUpdateOp<T>> &callback) {
        auto fakeOpCompleteType = FakeOpCompleteType{
                FAKE_OP_TYPE_COMPONENT_UPDATE,
                T::ComponentId
        };
        auto wrappedCallback = [callback](void* data) {
            callback(*static_cast<ComponentUpdateOp<T>*>(data));
        };

        callbackMap[fakeOpCompleteType].emplace_back(wrappedCallback);
        return CallbackKey{1};
    }

    template<typename T>
    CallbackKey OnCommandRequest(
            const Callback<CommandRequestOp<T>> &callback) {
        return CallbackKey{1};
    }

    template<typename T>
    CallbackKey OnCommandResponse(
            const Callback<CommandResponseOp<T>> &callback) {
        return CallbackKey{1};
    }

    void Remove(CallbackKey key) {
    }

    void Process(const List<FakeOp> &fakeOpList) const {
        for (auto iterator = fakeOpList.begin(); iterator != fakeOpList.end(); ++iterator) {
            const FakeOp &fakeOp = *iterator;
            FakeOpCompleteType fakeOpCompleteType = fakeOp.completeType;
            auto mapIter = callbackMap.find(fakeOpCompleteType);
            if (mapIter != callbackMap.end())
            {
                auto callbackList = mapIter->second;
                for (auto callbackIter = callbackList.begin(); callbackIter != callbackList.end(); ++callbackIter)
                {
                    auto callback = *callbackIter;
                    (callback) (fakeOp.data.get());
                }
            }
        }
    }


private:
    const ComponentRegistry &registry;
    std::map<FakeOpCompleteType, List<std::function<void(void*)>>> callbackMap;
};

}

#endif //CPP_CONNECTION_MOCK_MOCKABLEDISPATCHER_H

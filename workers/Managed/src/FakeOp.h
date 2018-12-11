#ifndef CPP_CONNECTION_MOCK_FAKEOPLIST_H
#define CPP_CONNECTION_MOCK_FAKEOPLIST_H

namespace worker {

typedef enum FakeOpType {
    FAKE_OP_TYPE_DISCONNECT = 1,
    FAKE_OP_TYPE_FLAG_UPDATE = 2,
    FAKE_OP_TYPE_LOG_MESSAGE = 3,
    FAKE_OP_TYPE_METRICS = 4,
    FAKE_OP_TYPE_CRITICAL_SECTION = 5,
    FAKE_OP_TYPE_ADD_ENTITY = 6,
    FAKE_OP_TYPE_REMOVE_ENTITY = 7,
    FAKE_OP_TYPE_RESERVE_ENTITY_IDS_RESPONSE = 8,
    FAKE_OP_TYPE_CREATE_ENTITY_RESPONSE = 9,
    FAKE_OP_TYPE_DELETE_ENTITY_RESPONSE = 10,
    FAKE_OP_TYPE_ENTITY_QUERY_RESPONSE = 11,
    FAKE_OP_TYPE_ADD_COMPONENT = 12,
    FAKE_OP_TYPE_REMOVE_COMPONENT = 13,
    FAKE_OP_TYPE_AUTHORITY_CHANGE = 14,
    FAKE_OP_TYPE_COMPONENT_UPDATE = 15,
    FAKE_OP_TYPE_COMMAND_REQUEST = 16,
    FAKE_OP_TYPE_COMMAND_RESPONSE = 17,
} FakeOpType;

struct FakeOpCompleteType {
    FakeOpType type;
    ComponentId componentId;

    bool operator==(const FakeOpCompleteType &o) const {
        return o.type == type && componentId == o.componentId;
    }

    bool operator<(const FakeOpCompleteType &o) const {
        return type < o.type || (type == o.type && componentId < o.componentId);
    }
};

struct FakeOp {
    FakeOpCompleteType completeType;
    void* data;
};

}

#endif //CPP_CONNECTION_MOCK_FAKEOPLIST_H

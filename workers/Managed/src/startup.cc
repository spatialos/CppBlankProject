#include <improbable/worker.h>
#include <improbable/standard_library.h>
#include <iostream>

// Use this to make a worker::ComponentRegistry. This worker doesn't use any components yet
// For example use worker::Components<improbable::Position, improbable::Metadata> to track these common components
using EmptyRegistry = worker::Components<>;

// Constants and parameters
const int ErrorExitStatus = 1;
const std::string kLoggerName = "startup.cc";
const std::uint32_t kGetOpListTimeoutInMilliseconds = 100;

worker::Connection ConnectWithReceptionist(const std::string hostname, 
                                           const std::uint16_t port,
                                           const std::string& worker_id, 
                                           const worker::ConnectionParameters& connection_parameters) {
    auto future = worker::Connection::ConnectAsync(EmptyRegistry{}, hostname, port, worker_id, connection_parameters);
    return future.Get();
}

// Entry point
int main(int argc, char** argv) {
    auto print_usage = [&]() {
        std::cout << "Usage: Managed receptionist <hostname> <port> <worker_id>" << std::endl;
        std::cout << std::endl;
        std::cout << "Connects to SpatialOS" << std::endl;
        std::cout << "    <hostname>      - hostname of the receptionist or locator to connect to.";
        std::cout << std::endl;
        std::cout << "    <port>          - port to use if connecting through the receptionist.";
        std::cout << std::endl;
        std::cout << "    <worker_id>     - name of the worker assigned by SpatialOS." << std::endl;
        std::cout << std::endl;
    };

    if (argc != 5) {
        print_usage();
        return ErrorExitStatus;
    }

    worker::ConnectionParameters parameters;
    parameters.WorkerType = "Managed";
    parameters.Network.ConnectionType = worker::NetworkConnectionType::kTcp;
    parameters.Network.UseExternalIp = false;

    // Connect with receptionist
    worker::Connection connection = ConnectWithReceptionist(argv[2], atoi(argv[3]), argv[4], parameters);

    connection.SendLogMessage(worker::LogLevel::kInfo, kLoggerName, "Connected successfully");

    // Register callbacks and run the worker main loop.
    worker::Dispatcher dispatcher{EmptyRegistry{}};
    bool is_connected = connection.IsConnected();

    dispatcher.OnDisconnect([&](const worker::DisconnectOp& op) {
        std::cerr << "[disconnect] " << op.Reason << std::endl;
        is_connected = false;
    });

    // Print messages received from SpatialOS
    dispatcher.OnLogMessage([&](const worker::LogMessageOp& op) {
        if (op.Level == worker::LogLevel::kFatal) {
            std::cerr << "Fatal error: " << op.Message << std::endl;
            std::terminate();
        }
        std::cout << "Connection: " << op.Message << std::endl;
    });

    while (is_connected) {
        dispatcher.Process(connection.GetOpList(kGetOpListTimeoutInMilliseconds));
    }

    return ErrorExitStatus;
}

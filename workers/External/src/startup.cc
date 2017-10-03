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

// Connection helpers
worker::Connection ConnectWithLocator(const std::string hostname, 
                                      const std::string project_name,
                                      const std::string deployment_id, 
                                      const std::string login_token,
                                      const worker::ConnectionParameters& connection_parameters) {
    worker::LocatorParameters locator_parameters;
    locator_parameters.ProjectName = project_name;
    locator_parameters.CredentialsType = worker::LocatorCredentialsType::kLoginToken;
    locator_parameters.LoginToken.Token = login_token;

    worker::Locator locator{ hostname, locator_parameters };

    auto queue_status_callback = [&](const worker::QueueStatus& queue_status) {
        if (!queue_status.Error.empty()) {
            std::cerr << "Error while queueing: " << *queue_status.Error << std::endl;
            return false;
        }
        std::cout << "Worker of type '" << connection_parameters.WorkerType
            << "' connecting through locator: queueing." << std::endl;
        return true;
    };

    auto future = locator.ConnectAsync(EmptyRegistry{}, deployment_id, connection_parameters, queue_status_callback);
    return future.Get();
}


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
        std::cout << "Usage: External receptionist <hostname> <port> <worker_id>" << std::endl;
        std::cout << "       External locator <hostname> <project_name> <deployment_id> <login_token>";
        std::cout << std::endl;
        std::cout << "Connects to SpatialOS" << std::endl;
        std::cout << "    <hostname>      - hostname of the receptionist or locator to connect to.";
        std::cout << std::endl;
        std::cout << "    <port>          - port to use if connecting through the receptionist.";
        std::cout << std::endl;
        std::cout << "    <worker_id>     - name of the worker assigned by SpatialOS." << std::endl;
        std::cout << "    <project_name>  - name of the project to run." << std::endl;
        std::cout << "    <deployment_id> - name of the cloud deployment to run." << std::endl;
        std::cout << "    <login_token>   - token to use when connecting through the locator.";
        std::cout << std::endl;
    };

    if (argc < 2) {
        print_usage();
        return ErrorExitStatus;
    }

    const std::string connection_type = argv[1];
    if (connection_type != "receptionist" && connection_type != "locator") {
        print_usage();
        return ErrorExitStatus;
    }

    bool use_locator = connection_type == "locator";

    if ((use_locator && argc != 6) || (!use_locator && argc != 5)) {
        print_usage();
        return ErrorExitStatus;
    }

    worker::ConnectionParameters parameters;
    parameters.WorkerType = "External";
    parameters.Network.ConnectionType = worker::NetworkConnectionType::kTcp;
    parameters.Network.UseExternalIp = true;

    // Connect with locator or receptionist
    worker::Connection connection = use_locator
        ? ConnectWithLocator(argv[2], argv[3], argv[4], argv[5], parameters)
        : ConnectWithReceptionist(argv[2], atoi(argv[3]), argv[4], parameters);

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

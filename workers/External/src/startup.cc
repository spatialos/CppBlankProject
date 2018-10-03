#include <algorithm>
#include <chrono>
#include <cstdlib>
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

std::string get_random_characters(size_t count) {
    const auto randchar = []() -> char {
        const char charset[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
        const auto max_index = sizeof(charset) - 1;
        return charset[std::rand() % max_index];
    };
    std::string str(count, 0);
    std::generate_n(str.begin(), count, randchar);
    return str;
}

// Entry point
int main(int argc, char** argv) {
    auto now = std::chrono::high_resolution_clock::now();
    std::srand(std::chrono::time_point_cast<std::chrono::nanoseconds>(now).time_since_epoch().count());

    auto print_usage = [&]() {
        std::cout << "Usage: External receptionist <hostname> <port> <worker_id>" << std::endl;
        std::cout << "       External locator <hostname> <project_name> <deployment_id> <login_token>";
        std::cout << std::endl;
        std::cout << "Connects to SpatialOS" << std::endl;
        std::cout << "    <hostname>       - hostname of the receptionist or locator to connect to.";
        std::cout << std::endl;
        std::cout << "    <port>           - port to use if connecting through the receptionist.";
        std::cout << std::endl;
        std::cout << "    <worker_id>      - name of the worker assigned by SpatialOS." << std::endl;
        std::cout << "    <project_name>   - name of the project to run." << std::endl;
        std::cout << "    <deployment_id>  - name of the cloud deployment to run." << std::endl;
        std::cout << "    <login_token>   - token to use when connecting through the locator.";
        std::cout << std::endl;
    };

    worker::ConnectionParameters parameters;
    parameters.WorkerType = "External";
    parameters.Network.ConnectionType = worker::NetworkConnectionType::kTcp;
    parameters.Network.UseExternalIp = true;

    std::vector<std::string> arguments;

    // if no arguments are supplied, use the defaults for a local deployment
    if (argc == 1) {
        arguments = { "receptionist", "localhost", "7777", parameters.WorkerType + "_" + get_random_characters(4) };
    } else {
        arguments = std::vector<std::string>(argv + 1, argv + argc);
    }

    const std::string connection_type = arguments[0];
    if (connection_type != "receptionist" && connection_type != "locator") {
        print_usage();
        return ErrorExitStatus;
    }

    const bool use_locator = connection_type == "locator";

    if ((use_locator && arguments.size() != 5) || (!use_locator && arguments.size() != 4)) {
        print_usage();
        return ErrorExitStatus;
    }

    // Connect with locator or receptionist
    worker::Connection connection = use_locator
        ? ConnectWithLocator(arguments[1], arguments[2], arguments[3], arguments[4], parameters)
        : ConnectWithReceptionist(arguments[1], atoi(arguments[2].c_str()), arguments[3], parameters);

    connection.SendLogMessage(worker::LogLevel::kInfo, kLoggerName, "Connected successfully");

    // Register callbacks and run the worker main loop.
    worker::Dispatcher dispatcher{ EmptyRegistry{} };
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

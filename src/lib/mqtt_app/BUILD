load("@rules_cc//cc:defs.bzl", "cc_library", "cc_binary")

# System-installed Paho MQTT C library
cc_library(
    name = "paho_mqtt_c",
    includes = ["/usr/include/mqtt"],  # Use the system include path
    linkopts = [
        "-L/usr/lib/x86_64-linux-gnu",
        "-lpaho-mqtt3a", "-lpaho-mqtt3c", "-lpaho-mqtt3cs", "-lpaho-mqtt3as"
    ],  # Link against system-installed MQTT C libraries
    visibility = ["//visibility:public"],
)

# System-installed Paho MQTT C++ library
cc_library(
    name = "paho_mqtt_cpp",
    includes = ["/usr/include/mqtt"],  # Use the system include path
    linkopts = [
        "-L/usr/lib/x86_64-linux-gnu",
        "-lpaho-mqttpp3"  # Link against system-installed MQTT C++ library
    ],
    deps = [":paho_mqtt_c"],  # C++ depends on C
    visibility = ["//visibility:public"],
)

cc_library(
    name = "MqttClientLib",
    srcs = [
        "MqttClient.cc",
    ],
    hdrs = [
        "MqttClient.h",
        "IMqttBroker.h",
        "RealMqttBroker.h",
    ],
    deps = [
        ":paho_mqtt_cpp",
        ":paho_mqtt_c",
    ],
    visibility = ["//visibility:public"],  # Make this library accessible to tests
)

# MQTT Main Binary (Entry Point)
cc_binary(
    name = "main",
    srcs = ["main.cc"],  # Contains only main()
    deps = [
        ":MqttClientLib",
    ],
)

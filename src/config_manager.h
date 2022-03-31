//
// Created by Sinow on 2022/3/30.
//

#ifndef SIHTTP_CONFIG_MANAGER_H
#define SIHTTP_CONFIG_MANAGER_H

#include <nlohmann/json.hpp>
#include <unistd.h>
#include "cstring"
#include <cerrno>
#include <stdexcept>
#include <fcntl.h>

#include <fstream>
#include <sstream>
#include <regex>


class ConfigManager {
private:
    using json = nlohmann::json;
    std::string _listen_address{"0.0.0.0"};
    std::regex _ipv4_address_pattern{"^(25[0-5]|2[0-4]\\d|[0-1]?\\d?\\d)(\\.(25[0-5]|2[0-4]\\d|[0-1]?\\d?\\d)){3}$"};
    uint16_t _listen_port{80};

    void LoadBasic(nlohmann::basic_json<> const &config_basic) throw(std::runtime_error) {
        if (config_basic.contains("listen_address")) {
            auto listen_address = config_basic["listen_address"].get<std::string>();
            if (!std::regex_match(listen_address, _ipv4_address_pattern))
                throw std::runtime_error("listen_address invalid");
            _listen_address = std::move(listen_address);
        } else
            throw std::runtime_error("listen_address not found in config.json");

        if (config_basic.contains("port")) {
            _listen_port = config_basic["port"].get<uint16_t>();
        } else
            throw std::runtime_error("listen port not found in config.json");

    }

    std::string ReadConfig(std::string const &pathname) {
        std::ifstream inConfig;
        inConfig.open(pathname, std::ios::in);
        if (!inConfig.is_open())
            throw std::runtime_error("Open config.json Failed");
        std::stringstream strStream{};
        strStream << inConfig.rdbuf();

        return strStream.str();
    }

    ConfigManager() = default;

public:
    ConfigManager(ConfigManager const &) = delete;

    ConfigManager(ConfigManager &&) = delete;

    static ConfigManager &instance() {
        static ConfigManager _instance;
        return _instance;
    }

    void LoadConfig() throw(std::runtime_error) {
        auto config_parsed = json::parse(ReadConfig("config.json"));
        if (config_parsed.contains("basic")) {
            LoadBasic(config_parsed["basic"]);
        } else
            throw std::runtime_error("basic not found in config.json");
    }

public:
    std::string getListenAddress() const noexcept {
        return _listen_address;
    }

    uint16_t getListenPort() const noexcept {
        return _listen_port;
    }
};


ConfigManager &Config() {
    return ConfigManager::instance();
}


#endif //SIHTTP_CONFIG_MANAGER_H

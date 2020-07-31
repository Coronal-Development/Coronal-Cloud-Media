#include "config.h"
#include "json/json.h"
#include <direct.h>
namespace meri
{
    Config::Config()
    {
    }

    Config::~Config()
    {
    }

    MeriStatus Config::ReadConfig(std::string config_file_name)
    {
        json_file_.open(config_file_name, std::ios::binary);
        if (json_file_.fail()) return MeriStatus::kError;
        Json::Value root;
        json_file_ >> root;
        configuration_.insert(std::make_pair("logfile", root.get("logfile", "meri.log").asString()));
        configuration_.insert(std::make_pair("control-listen-ip", root.get("control-listen-ip", "127.0").asString()));
        configuration_.insert(std::make_pair("control-port", root.get("control-port", 9566).asInt()));

        return MeriStatus::kNomal;
    }
}// !namespace meri

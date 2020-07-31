#ifndef MERI_COMMON_JSONDATA_H_
#define MERI_COMMON_JSONDATA_H_
#include "nlohmann/json.hpp"
#include <fstream>
namespace meri
{
    class JsonData
    {
    public:
        JsonData() = default;
        JsonData(std::istream & i);
        JsonData(const std::string &_str);
        ~JsonData() = default;
    public:
        template<typename Target_Type>
        Target_Type GetValueByKey(const std::string key, const Target_Type& default_value = Target_Type{})
        {
            auto j = json_data_.value(key, nlohmann::json{});
            if (j.is_null()) return std::move(default_value);
            return  j;
        }
        std::string GetStringByKey(const std::string& key,const int& space_num = 0);
        JsonData GetJsonDataByKey(const std::string& key);
        friend std::istream & operator>>(std::istream & i, JsonData & jsonData);
        void operator=(const std::string& str_json);
        void operator=(const JsonData& json_data);
        void AddtionJsonData(const JsonData& json_data);
        std::string ToString(const int& space_num = 0);
        void StrToJsonData(const std::string& result);
        bool empty();
        std::size_t size() const noexcept;
    protected:
        void operator=(const nlohmann::json& j);
        JsonData(const nlohmann::json& json_data);
        nlohmann::json json_data_;
    };
    using PtrJsonData = std::shared_ptr<JsonData>;
}/* meri */
#endif // !MERI_COMMON_JSONDATA_H_


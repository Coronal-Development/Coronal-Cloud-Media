#include "jsondata.h"
namespace meri
{
    void JsonData::operator=(const nlohmann::json & j)
    {
        json_data_ = j;
    }
    
    JsonData::JsonData(const nlohmann::json& jsonData)
        :json_data_(jsonData)
    {}
    
    JsonData::JsonData(std::istream & i)
    {
        try
        {
            i >> json_data_;
        }
        catch (...)
        {
            json_data_ = nlohmann::json{};
        }
    	
    }
    
    JsonData::JsonData(const std::string & _str)
    {
        StrToJsonData(_str);
    }
    
    std::string JsonData::GetStringByKey(const std::string& key,const int& space_num)
    {
        return space_num == 0 ? GetValueByKey(key, nlohmann::json{}).dump()
            : GetValueByKey(key, nlohmann::json{}).dump(space_num);
    }
    
    JsonData JsonData::GetJsonDataByKey(const std::string& key)
    {
        auto j = json_data_.value(key, nlohmann::json{});
        if (j.is_null()) return nlohmann::json{};
        return j;
    }
    
    void JsonData::operator=(const std::string& str_json)
    {
        json_data_ = nlohmann::json::parse(str_json);
    }
    
    void JsonData::operator=(const JsonData& json_data)
    {
        json_data_ = json_data.json_data_;
    }
    
    void JsonData::AddtionJsonData(const JsonData & json_data)
    {
        json_data_.push_back(json_data.json_data_);
    }
    
    std::string JsonData::ToString(const int& space_num)
    {
        return space_num == 0 ? json_data_.dump() : json_data_.dump(space_num);
    }
    
    void JsonData::StrToJsonData(const std::string & result)
    {
        try
        {
            json_data_ = nlohmann::json::parse(result);
        }
        catch (...)
        {
            json_data_ = nlohmann::json{};
        }
        
    }
    
    bool JsonData::empty()
    {
        return json_data_.empty();
    }
    
    std::size_t JsonData::size() const noexcept
    {
        return json_data_.size();
    }
    
    std::istream & operator>>(std::istream & i, JsonData & jsonData)
    {
        i >> jsonData.json_data_;
        return i;
    }
}


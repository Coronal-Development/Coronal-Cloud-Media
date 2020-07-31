#ifndef MERI_CONFIG_H_
#define MERI_CONFIG_H_
#include "../common/common.h"

namespace meri
{
	using ConfigVariant = std::variant<int, bool, std::string, float, double>;
	class Config
	{
	public:
		SINGLETON_DEFINE(Config);

		MeriStatus ReadConfig(std::string config_file_name = "config.json");

		template<typename T = int>
		T GetValue(std::string name)
		{
			auto it = configuration_.find(name);
			if (it != configuration_.end())
			{
				assert(std::holds_alternative<T>(it->second));
				return std::get<T>(it->second);
			}
			return T{};
		}

	private:
		Config();
		~Config();

		std::ifstream json_file_;
		std::unordered_map<std::string, ConfigVariant> configuration_;
	}; // !class Config
} // !namespace meri

#endif // !MERI_CONFIG_H_

#ifndef MERI_DATA_MESSAGE_H_
#define MERI_DATA_MESSAGE_H_

namespace meri
{


	class DataMessage
	{
	public:
		enum class DataMessageType
		{
			kNull = 0,
			kMouseKey = 1
		};
		DataMessage(DataMessageType type = DataMessageType::kNull, size_t size = 0)
			: type_(type), size_(size) {};
		virtual ~DataMessage() {};

		DataMessageType type_;
		size_t size_;
	};
} // !namespace meri

#endif // !MERI_DATA_MESSAGE_H_

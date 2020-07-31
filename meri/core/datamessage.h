#ifndef MERI_DATA_MESSAGE_H_
#define MERI_DATA_MESSAGE_H_

namespace meri
{


	class DataMessage
	{
	public:
		enum DataMessageType
		{
			kNull = 0,
			kMouseMove = 1,
			kLeftButtonDown = 2,
			kLeftButtonUp = 3,
			kRightButtonDown = 4,
			kRightButtonUp = 5,
			kMiddleButtonDown = 6,
			kMiddleButtonUp = 7,
			kMiddleButtonDownWheel = 8,
			kMiddleButtonUpWheel= 9,
			kKeyboardDown = 10,
			kKeyboardUp = 11,

		};
		DataMessage(DataMessageType type = DataMessageType::kNull, size_t size = 0)
			: type_(type), size_(size) {};
		virtual ~DataMessage() {};

		DataMessageType type_;
		size_t size_;
	};
} // !namespace meri

#endif // !MERI_DATA_MESSAGE_H_

#pragma once
#include <string>
#include <vector>
#include <map>
#include <typeinfo>

namespace Json
{
	class Node;

	typedef std::map<std::string, Node> object;
	typedef std::vector<Node> array;

	enum class Type
	{
		NONE,
		NULLPTR,
		BOOL,
		NUMBER,
		STRING,
		OBJECT,
		ARRAY,
	};

	class Node
	{
		Type type;
		std::string dataName;

	private:
		union Data
		{
			bool boolData;
			double numberData;
			std::string* stringData;
			object* objectData;
			array* arrayData;

			Data()
				: boolData(nullptr)
			{
			}

			Data(Type dataType)
				: boolData(nullptr)
			{
				switch (dataType)
				{
				case Json::Type::NONE:
					break;
				case Json::Type::NULLPTR:
					break;
				case Json::Type::BOOL:
					boolData = false;
					break;
				case Json::Type::NUMBER:
					numberData = 0;
					break;
				case Json::Type::STRING:
					stringData = new std::string();
					break;
				case Json::Type::OBJECT:
					objectData = new object();
					break;
				case Json::Type::ARRAY:
					arrayData = new array();
					break;
				}
			}

			~Data()
			{
			}

		} data;
	public:
		Node()
			: type(Type::NONE)
			, dataName()
			, data()
		{
		}

		Node(Type type)
			: type(type)
			, dataName()
			, data(this->type)
		{
		}

		// ノードを配列や文字列などで作成するとデータ挿入時にコピーコンストラクタが走って仮インスタンスのポインタで
		// 上書きされる上に仮インスタンスがその後デストラクタが走るから自前でコピーコンストラクタを実装する
		Node(const Node& n)
			: type(n.type)
			, dataName(n.dataName)
		{
			switch (type)
			{
			case Json::Type::BOOL:
				data.boolData = n.data.boolData;
				break;
			case Json::Type::NUMBER:
				data.numberData = n.data.numberData;
				break;
			case Json::Type::STRING:
				data.stringData = new std::string();
				*data.stringData = *n.data.stringData;
				break;
			case Json::Type::OBJECT:
				data.objectData = new object();
				*data.objectData = *n.data.objectData;
				break;
			case Json::Type::ARRAY:
				data.arrayData = new array();
				*data.arrayData = *n.data.arrayData;
				break;
			}
		}

		~Node()
		{
			switch (type)
			{
			case Json::Type::STRING:
				delete data.stringData;
				data.stringData = nullptr;
				break;
			case Json::Type::OBJECT:
				delete data.objectData;
				data.objectData = nullptr;
				break;
			case Json::Type::ARRAY:
				delete data.arrayData;
				data.arrayData = nullptr;
				break;
			}
		}

		template <typename T>
		T& Get()
		{
			if (typeid(T) == typeid(bool))return *(T*)(void*)&data.boolData;
			if (typeid(T) == typeid(std::string))return *(T*)(void*)data.stringData;
			if (typeid(T) == typeid(object))return *(T*)(void*)data.objectData;
			if (typeid(T) == typeid(array))return *(T*)(void*)data.arrayData;

			return *(T*)(void*)&data.numberData;
		}
	};
}
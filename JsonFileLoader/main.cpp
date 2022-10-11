#include "Json.h"

#include <crtdbg.h>
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// �󂯎�葤����m�[�h�ɑ΂��Ēǉ��������ꍇ�͎Q�ƌ^�ɂ��Ȃ��ƃC���X�^���X�V�������ꂿ�Ⴄ���璍��
	Json::Node node(Json::Type::OBJECT);
	auto& data = node.Get<Json::object>();
	data.insert(std::make_pair("aaaa",Json::Node(Json::Type::BOOL)));
	data.insert(std::make_pair("aaaaa",Json::Node(Json::Type::NUMBER)));
	data.insert(std::make_pair("aaaaaa",Json::Node(Json::Type::BOOL)));
	data.insert(std::make_pair("aaaaaaa",Json::Node(Json::Type::ARRAY)));

	auto& data2 = data["aaaaaaa"].Get<Json::array>();
	data2.push_back(Json::Node(Json::Type::BOOL));
	data2.push_back(Json::Node(Json::Type::BOOL));

	// ������data2��object�ł͂Ȃ�array���Ƃ̎Q�Ƃ͊O��邩�璍��
	node.Get<Json::object>().insert(std::make_pair("aaaaaaaa", Json::Node(Json::Type::NUMBER)));

	int intData = node.Get<Json::object>()["aaaaa"].Get<int>();

	node.Get<Json::object>().insert(std::make_pair("aaaaaaaaa",Json::Node(Json::Type::OBJECT)));
	data["aaaaaaaaa"].Get<Json::object>().insert(std::make_pair("aaa", Json::Node(Json::Type::BOOL)));
	data["aaaaaaaaa"].Get<Json::object>().insert(std::make_pair("aaaa", Json::Node(Json::Type::NUMBER)));

	// �����܂łō���Ă�����̂�Json�ŏo�͂���Ƃ����炭����
	// �f�[�^�̖��O�͂��ĂȂ����牼��
	/*

	node : {
		"aaaa" : false
		"aaaaa" : 0
		"aaaaaa" : false
		"aaaaaaa" : [false,false]
		"aaaaaaaaa" : 0
		"aaaaaaaaaa" : {
			"aaa" : false
			"aaaa" : false
		}
	}
	*/

	return 0;
}
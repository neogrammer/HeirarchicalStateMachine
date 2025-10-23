#include "Input.h"
#include "Controlled.h"
#include "Scripted.h"

Input::Input()
	: inputSource{ nullptr }
{

}

Input::Input(input::SourceType type_)
	: inputSource{nullptr}
{
	switch (type_)
	{
	case input::SourceType::Controlled:
		inputSource = std::make_unique<Controlled>();
	case input::SourceType::Scripted:
		inputSource = std::make_unique<Scripted>();
	default:
		break;
	};
}

Input::~Input()
{
}

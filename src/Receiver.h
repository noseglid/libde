#ifndef __DE__RECEIVER_H__
#define __DE__RECEIVER_H__

#include <pjson.hpp>

namespace de {

	class Receiver
	{
	public:
		virtual void absorb(std::string event, const Json::Value& data) = 0;
	};
};

#endif

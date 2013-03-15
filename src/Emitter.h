#ifndef __DE__EMITTER_H__
#define __DE__EMITTER_H__

#include "Receiver.h"

#include <map>

namespace de {
	class Emitter
	{
		std::multimap<std::string, Receiver *> stakeholders;

	protected:
		Emitter();

	public:
		void on(std::string event, Receiver *rec);
		void off(std::string, Receiver *rec);
		void emit(std::string event, Json::Value data);
	};
};


#endif

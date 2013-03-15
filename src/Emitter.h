#ifndef __DE__EMITTER_H__
#define __DE__EMITTER_H__

#include <map>
#include <functional>
#include <pjson.hpp>

namespace de {
	class Emitter
	{
		typedef std::function< void(const Json::Value& data) > event_cb;

		std::multimap<std::string, event_cb> stakeholders;

	protected:
		Emitter();

	public:
		void on(std::string event, event_cb cb);
		void off(std::string, event_cb cb);
		void emit(std::string event, const Json::Value& data);
	};
};


#endif

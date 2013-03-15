#include "Emitter.h"

namespace de {

	Emitter::Emitter()
	{
	}

	void
	Emitter::on(std::string event, event_cb cb)
	{
		stakeholders.insert(std::make_pair(event, cb));
	}

	void
	Emitter::off(std::string event, event_cb cb)
	{
		auto range = stakeholders.equal_range(event);
		for (auto it = range.first; it != range.second; ++it) {
			//if (it->second == cb) {
				stakeholders.erase(it);
				break;
			//}
		}
	}

	void
	Emitter::emit(std::string event, const Json::Value& data)
	{
		auto range = stakeholders.equal_range(event);
		for (auto it = range.first; it != range.second; ++it) {
			(it->second)(data);
		}
	}
}

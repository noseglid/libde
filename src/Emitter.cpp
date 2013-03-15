#include "Emitter.h"

namespace de {

	Emitter::Emitter()
	{
	}

	void
	Emitter::on(std::string event, Receiver *recv)
	{
		stakeholders.insert(std::make_pair(event, recv));
	}

	void
	Emitter::off(std::string event, Receiver *recv)
	{
		auto range = stakeholders.equal_range(event);
		for (auto it = range.first; it != range.second; ++it) {
			if (it->second == recv) {
				stakeholders.erase(it);
				break;
			}
		}
	}

	void
	Emitter::emit(std::string event, Json::Value data)
	{
		auto range = stakeholders.equal_range(event);
		for (auto it = range.first; it != range.second; ++it) {
			it->second->absorb(event, data);
		}
	}

}

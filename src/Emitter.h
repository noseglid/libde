#ifndef __DE__EMITTER_H__
#define __DE__EMITTER_H__

#include <map>
#include <functional>
#include <string>

namespace de {
	class Emitter
	{
		typedef std::function< void() > event_cb;
		typedef std::multimap<std::string, event_cb> mm_t;

		mm_t consumers;

	protected:
		Emitter()
		{
		}

	public:
		typedef mm_t::iterator id_t;

		id_t on(std::string event, event_cb cb)
		{
			return consumers.insert(std::make_pair(event, cb));
		}

		void off(id_t id)
		{
			consumers.erase(id);
		}

		void disable(std::string event)
		{
			consumers.erase(event);
		}

		void emit(std::string event)
		{
			mm_t tmp = consumers;
			auto range = tmp.equal_range(event);
			for (auto it = range.first; it != range.second; ++it) {
				(it->second)();
			}
		}

	};
};


#endif

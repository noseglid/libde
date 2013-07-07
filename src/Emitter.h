#ifndef __DE__EMITTER_H__
#define __DE__EMITTER_H__

#include <map>
#include <functional>
#include <string>

namespace de {
	struct __nodata {};

	template <class T = struct __nodata>
	class Emitter
	{
		typedef std::function< void(T) > event_cb;
		typedef std::multimap<std::string, event_cb> mm_t;

		mm_t consumers;

	protected:
		Emitter()
		{
		}

	public:
		typedef typename mm_t::iterator id_t;

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

		void emit(std::string event, T data)
		{
			mm_t tmp = consumers;
			auto range = tmp.equal_range(event);
			auto it = range.first;
			while (it != range.second) {
				auto current = it++;
				(current->second)(data);
			}
		}
	};

	template <>
	class Emitter <struct __nodata>
	{
		typedef std::function< void() > event_cb;
		typedef std::multimap<std::string, event_cb> mm_t;

		mm_t consumers;

	protected:
		Emitter()
		{
		}

	public:
		typedef typename mm_t::iterator id_t;

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
			auto it = range.first;
			while (it != range.second) {
				auto current = it++;
				(current->second)();
			}
		}
	};
};


#endif

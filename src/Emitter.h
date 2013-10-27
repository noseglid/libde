#ifndef __DE__EMITTER_H__
#define __DE__EMITTER_H__

#include <map>
#include <vector>
#include <functional>
#include <string>

namespace de {
  struct __nodata {};

  struct key {
    int id;
    std::string event;

    key(int id, std::string event) : id(id), event(event) {}
    bool operator<(const key& rhs) const { return event < rhs.event; }
  };

  template <class T = struct __nodata>
  class Emitter
  {
    typedef std::function< void(T) > event_cb;
    typedef std::multimap<key, event_cb> mm_t;
    static std::map<Emitter<T>*, std::vector<int>> erased;

    mm_t consumers;

    int cur_id;

  protected:
    Emitter() : cur_id(0)
    {
    }

    ~Emitter()
    {
      erased.erase(this);
    }

  public:
    typedef typename mm_t::iterator id_t;

    id_t on(std::string event, event_cb cb)
    {
      return consumers.insert(std::make_pair(key(cur_id++, event), cb));
    }

    void off(id_t id)
    {
      erased[this].push_back(id->first.id);
      consumers.erase(id);
    }

    void disable(std::string event)
    {
      consumers.erase(key(-1, event));
    }

    void emit(std::string event, T data)
    {
      mm_t tmp = consumers;
      auto range = tmp.equal_range(key(-1, event));
      auto it = range.first;
      while (it != range.second) {
        auto current = it++;

        auto found = std::find(erased[this].begin(), erased[this].end(), current->first.id);
        if (erased[this].end() != found) continue;

        (current->second)(data);
      }
      erased[this].clear();
    }
  };

  template <>
  class Emitter <struct __nodata>
  {
    typedef std::function< void() > event_cb;
    typedef std::multimap<key, event_cb> mm_t;
    static std::map<Emitter<__nodata>*, std::vector<int>> erased;

    mm_t consumers;

    int cur_id;

  protected:
    Emitter() : cur_id(0)
    {
    }

    ~Emitter()
    {
      erased.erase(this);
    }

  public:
    typedef typename mm_t::iterator id_t;

    id_t on(std::string event, event_cb cb)
    {
      return consumers.insert(std::make_pair(key(cur_id++, event), cb));
    }

    void off(id_t id)
    {
      erased[this].push_back(id->first.id);
      consumers.erase(id);
    }

    void disable(std::string event)
    {
      consumers.erase(key(-1, event));
    }

    void emit(std::string event)
    {
      mm_t tmp = consumers;
      auto range = tmp.equal_range(key(-1, event));
      auto it = range.first;
      while (it != range.second) {
        auto current = it++;

        auto found = std::find(erased[this].begin(), erased[this].end(), current->first.id);
        if (erased[this].end() != found) continue;

        (current->second)();
      }
      erased[this].clear();
    }
  };

  template <typename T>
  std::map<Emitter<T>*, std::vector<int>> de::Emitter<T>::erased;

  std::map<Emitter<__nodata>*, std::vector<int>> de::Emitter<__nodata>::erased;
};

#endif

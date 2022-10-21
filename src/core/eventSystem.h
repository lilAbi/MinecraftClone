
#ifndef GAMEENGINEV2_EVENTSYSTEM_H
#define GAMEENGINEV2_EVENTSYSTEM_H
#include <vector>
#include "event.h"

namespace core::Events {

    class EventSystem;

    inline static EventSystem* gEventSystem = nullptr;

    class EventSystem {
    public:
        EventSystem() = default;
        ~EventSystem() = default;

        void AddEvent(Event event);

    public:
        std::vector<Event> eventQueue{};
    };
}


#endif //GAMEENGINEV2_EVENTSYSTEM_H


#ifndef GAMEENGINEV2_EVENT_H
#define GAMEENGINEV2_EVENT_H

namespace core::Events{
    enum class EventType{
        WindowResize = 0,
        MousePress,
        MouseMove,
        KeyPress,
        Default
    };


    struct Event {
        EventType eventType;
    };

}


#endif //GAMEENGINEV2_EVENT_H

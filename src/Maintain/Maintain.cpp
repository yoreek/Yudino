#if defined(ARDUINO) && ARDUINO >= 100
#  include "Arduino.h"
#else
#  include "WProgram.h"
#endif
#include "Maintain.h"

void MaintainedCollection::add(MaintainedObject *obj) {
    obj->next = _objects;
    _objects  = obj;
}

void MaintainedCollection::forceMaintain() {
    maintain(true);
}

void MaintainedCollection::maintain() {
    maintain(false);
}

void MaintainedCollection::maintain(bool force) {
    uint32_t          now;
    MaintainedObject *obj;

    now = millis();
    if (!force
        && _timeLastMaintain != 0
        && now >= _timeLastMaintain
        && (now - _timeLastMaintain) < _maintainInterval * 1000) {
        return;
    }

    _timeLastMaintain = now;

    obj = _objects;
    while (obj != NULL) {
        obj->maintain();
        obj = obj->next;
    }
}

MaintainedObject *MaintainedCollection::get(int n) {
    MaintainedObject *obj;
    int               i;

    obj = _objects;
    i   = 0;
    while (obj != NULL && i != n) {
        obj = obj->next;
        i++;
    }

    return obj;
}

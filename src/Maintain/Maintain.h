#pragma once
#ifndef _MAINTAIN_H_
#define _MAINTAIN_H_

#if defined(ARDUINO) && ARDUINO >= 100
#  include "Arduino.h"
#else
#  include "WProgram.h"
#endif

class MaintainedObject {
    public:
        MaintainedObject(void) :
            next(NULL)
        {};
        virtual void maintain() {};
        MaintainedObject *next;
};

class MaintainedCollection {
    public:
        MaintainedCollection(uint32_t maintainInterval) :
            _objects(NULL),
            _maintainInterval(maintainInterval),
            _timeLastMaintain(0)
        {};
        void add(MaintainedObject *obj);
        void maintain();
        void forceMaintain();
        void maintain(bool force);
        MaintainedObject *first(void) {
            return _objects;
        };
        MaintainedObject *get(int n);

    private:
        MaintainedObject *_objects;
        uint32_t          _maintainInterval;
        uint32_t          _timeLastMaintain;
};

#endif

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

class MaintainedCollectionSimple {
    public:
        MaintainedCollectionSimple(void) :
            _objects(NULL)
        {};
        void add(MaintainedObject *obj);
        virtual void maintain() {};
        MaintainedObject *first(void) {
            return _objects;
        };
        MaintainedObject *get(int n);

    protected:
        MaintainedObject *_objects;
};

class MaintainedCollection: public MaintainedCollectionSimple {
    public:
        MaintainedCollection(uint32_t maintainInterval) :
            MaintainedCollectionSimple(),
            _maintainInterval(maintainInterval),
            _timeLastMaintain(0)
        {};
        virtual void maintain();
        virtual void forceMaintain();
        virtual void maintain(bool force);

    protected:
        uint32_t _maintainInterval;
        uint32_t _timeLastMaintain;
};

#endif

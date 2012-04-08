// Copyright (C) 2008 by Vinnie Falco, this file is part of VFLib.
// See the file README.md for licensing information.

#ifndef VF_STATICOBJECT_VFHEADER
#define VF_STATICOBJECT_VFHEADER

#include "../threads/vf_SpinDelay.h"

//
// A full suite of thread-safe objects designed for static storage duration.
//
// Wraps an object with a thread-safe initialization preamble so that it can
// properly exist with static storage duration.
//
// Implementation notes:
//
//   This is accomplished by omitting the constructor and relying on the C++
//   specification that plain data types with static storage duration are filled
//   with zeroes before any other initialization code executes.
//
// Spec: N2914=09-0104
//
// [3.6.2] Initialization of non-local objects
//
//         Objects with static storage duration (3.7.1) or thread storage
//         duration (3.7.2) shall be zero-initialized (8.5) before any
//         other initialization takes place.
//
// Requirements:
//
//  Object must be constructible without parameters.
//  The StaticObject must be declared with static storage duration or
//    the behavior is undefined.
//
// Usage example:
//
// Object* getInstance ()
// {
//   static StaticObject <Object> instance;
//   return instance->getObject ();
// }
//

namespace Static {

//------------------------------------------------------------------------------

// Holds an object with static storage duration.
// The owner determines if and when the object is constructed and destroyed.
// Caller is responsible for synchronization.
//
template <class ObjectType, class Tag>
class Storage
{
public:
  static inline void construct ()
  {
    new (getObjectPtr ()) ObjectType;
  }

  static inline void destroy ()
  {
    getObjectPtr()->~ObjectType ();
  }

  static inline ObjectType* getObjectPtr ()
  {
    return reinterpret_cast <ObjectType*> (s_storage);
  }

  static inline ObjectType& getObject ()
  {
    return *getObjectPtr ();
  }

  inline ObjectType* operator-> () const
  {
    return getObjectPtr ();
  }

  inline ObjectType& operator* () const
  {
    return getObject ();
  }

  inline operator ObjectType* () const
  {
    return getObjectPtr ();
  }

private:
  static char s_storage [sizeof (ObjectType)];
};

template <class ObjectType, class Tag>
char Storage <ObjectType, Tag>::s_storage [sizeof (ObjectType)];

//------------------------------------------------------------------------------

// Provides a thread safe flag for indicating if and when
// initialization is required for an object with static storage duration.
// 
class Initializer
{
public:
  /*
  bool inited () const
  {
    return m_state.get () == stateInitialized;
  }
  */

  // If the condition is not initialized, the first caller will
  // receive true, while concurrent callers get blocked until
  // initialization completes.
  //
  bool begin ()
  {
    bool shouldInitialize;

    if (m_state.get () == stateUninitialized)
    {
      if (m_state.compareAndSetBool (stateInitializing, stateUninitialized))
      {
        shouldInitialize = true;
      }
      else
      {
        SpinDelay delay;

        do
        {
          delay.pause ();
        }
        while (m_state.get () != stateInitialized);

        shouldInitialize = false;
      }
    }
    else
    {
      shouldInitialize = false;
    }

    return shouldInitialize;
  }

  // Called to signal that the initialization is complete
  //
  void end ()
  {
    m_state.set (stateInitialized);
  }

private:
  enum
  {
    stateUninitialized = 0, // must be zero
    stateInitializing,
    stateInitialized
  };

  VF_JUCE::Atomic <int> m_state;
};

}

#endif

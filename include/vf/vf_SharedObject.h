// Copyright (C) 2008-2011 by One Guy Group, Inc., All rights reserved worldwide.
// This file is released under the MIT License:
// http://www.opensource.org/licenses/mit-license.php

#ifndef __VF_SHAREDOBJECT_VFHEADER__
#define __VF_SHAREDOBJECT_VFHEADER__

//
// A copy of juce::ReferenceCountedObject,
// with the following features:
//
// - Shorter name
//
// - Return value of decReferenceCount() indicates the
//   object was deleted (This can be handy for assertions)
//
// - Derived class may override the behavior of destruction.
//   For example, to offload the delete cost to another thread.
//
// TODO: REMOVE DEPEDENDENCE ON JUCE ATOMIC!!!
class SharedObject
{
public:
  inline void incReferenceCount() throw()
  {
    ++refCount;
  }

  inline bool decReferenceCount() throw()
  {
    vfassert (getReferenceCount() > 0);

    bool final;

    if (--refCount == 0)
    {
      destroySharedObject ();
      final = true;
    }
    else
    {
      final = false;
    }
    
    return final;
  }

  inline int getReferenceCount() const throw()
  {
    return refCount.get();
  }

protected:
  SharedObject()
  {
  }

  virtual ~SharedObject()
  {
    vfassert (getReferenceCount() == 0);
  }

  virtual void destroySharedObject ()
  {
    // default implementation
    delete this;
  }

private:
  VF_JUCE::Atomic <int> refCount;
};

template <class SharedObjectClass>
class SharedObjectPtr
{
public:
  inline SharedObjectPtr() throw()
    : referencedObject (0)
  {
  }

  inline SharedObjectPtr (SharedObjectClass* const refCountedObject) throw()
    : referencedObject (refCountedObject)
  {
    if (refCountedObject != 0)
      refCountedObject->incReferenceCount();
  }

  inline SharedObjectPtr (const SharedObjectPtr<SharedObjectClass>& other) throw()
    : referencedObject (other.referencedObject)
  {
    if (referencedObject != 0)
      referencedObject->incReferenceCount();
  }

  SharedObjectPtr<SharedObjectClass>& operator= (const SharedObjectPtr<SharedObjectClass>& other)
  {
    SharedObjectClass* const newObject = other.referencedObject;

    if (newObject != referencedObject)
    {
      if (newObject != 0)
        newObject->incReferenceCount();

      SharedObjectClass* const oldObject = referencedObject;
      referencedObject = newObject;

      if (oldObject != 0)
        oldObject->decReferenceCount();
    }

    return *this;
  }

  SharedObjectPtr<SharedObjectClass>& operator= (SharedObjectClass* const newObject)
  {
    if (referencedObject != newObject)
    {
      if (newObject != 0)
        newObject->incReferenceCount();

      SharedObjectClass* const oldObject = referencedObject;
      referencedObject = newObject;

      if (oldObject != 0)
        oldObject->decReferenceCount();
    }

    return *this;
  }

  inline ~SharedObjectPtr()
  {
    if (referencedObject != 0)
      referencedObject->decReferenceCount();
  }

  inline operator SharedObjectClass*() const throw()
  {
    return referencedObject;
  }

  inline SharedObjectClass* operator->() const throw()
  {
    return referencedObject;
  }

  inline SharedObjectClass* getObject() const throw()
  {
    return referencedObject;
  }

private:
  SharedObjectClass* referencedObject;
};

template <class SharedObjectClass>
bool operator== (const SharedObjectPtr<SharedObjectClass>& object1, SharedObjectClass* const object2) throw()
{
  return object1.getObject() == object2;
}

template <class SharedObjectClass>
bool operator== (const SharedObjectPtr<SharedObjectClass>& object1, const SharedObjectPtr<SharedObjectClass>& object2) throw()
{
  return object1.getObject() == object2.getObject();
}

template <class SharedObjectClass>
bool operator== (SharedObjectClass* object1, SharedObjectPtr<SharedObjectClass>& object2) throw()
{
  return object1 == object2.getObject();
}

template <class SharedObjectClass>
bool operator!= (const SharedObjectPtr<SharedObjectClass>& object1, const SharedObjectClass* object2) throw()
{
  return object1.getObject() != object2;
}

template <class SharedObjectClass>
bool operator!= (const SharedObjectPtr<SharedObjectClass>& object1, SharedObjectPtr<SharedObjectClass>& object2) throw()
{
  return object1.getObject() != object2.getObject();
}
template <class SharedObjectClass>
bool operator!= (SharedObjectClass* object1, SharedObjectPtr<SharedObjectClass>& object2) throw()
{
  return object1 != object2.getObject();
}

#endif

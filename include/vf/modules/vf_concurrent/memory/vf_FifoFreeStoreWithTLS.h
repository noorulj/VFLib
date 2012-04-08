// Copyright (C) 2008 by Vinnie Falco, this file is part of VFLib.
// See the file README.md for licensing information.

#ifndef VF_FIFOFREESTOREWITHTLS_VFHEADER
#define VF_FIFOFREESTOREWITHTLS_VFHEADER

#ifndef DOXYGEN

#if VF_USE_BOOST

#include "vf_GlobalPagedFreeStore.h"

/****
  Lock-free and mostly wait-free memory allocator optimized for FIFO
  style usage patterns.

  It is expected that over time, deallocations will occur in roughly
  the same order as allocations.

  Invariants:

  #1 allocate() and deallocate() are fully concurrent

  #2 The ABA problem is handled automatically

  This implementation uses Thread Local Storage to further improve
  performance. However, it requires boost style thread_specific_ptr.
*/
class FifoFreeStoreWithTLS
{
public:
  FifoFreeStoreWithTLS ();
  ~FifoFreeStoreWithTLS ();

  void* allocate (const size_t bytes);
  static void deallocate (void* const p);

private:
  typedef GlobalPagedFreeStore PagedFreeStoreType;
  struct Header;

  class Page;

  inline Page* newPage ();
  static inline void deletePage (Page* page);

private:
  class PerThreadData;
  boost::thread_specific_ptr <PerThreadData> m_tsp;

  PagedFreeStoreType::Ptr m_pages;
};

#endif

#endif

#endif

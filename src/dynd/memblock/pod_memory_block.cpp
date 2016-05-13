//
// Copyright (C) 2011-16 DyND Developers
// BSD 2-Clause License, see LICENSE.txt
//

#include <algorithm>
#include <cstdlib>
#include <stdexcept>
#include <vector>

#include <dynd/memblock/pod_memory_block.hpp>

using namespace std;
using namespace dynd;

intrusive_ptr<memory_block_data> dynd::make_pod_memory_block(const ndt::type &tp, intptr_t initial_capacity_bytes) {
  pod_memory_block *pmb =
      new pod_memory_block(tp.get_default_data_size(), tp.get_data_alignment(), initial_capacity_bytes);
  return intrusive_ptr<memory_block_data>(reinterpret_cast<memory_block_data *>(pmb), false);
}

char *pod_memory_block::alloc(size_t count) {
  pod_memory_block *self = this;

  intptr_t size_bytes = count * reinterpret_cast<pod_memory_block *>(self)->data_size;

  //    cout << "allocating " << size_bytes << " of memory with alignment " << alignment << endl;
  // Allocate new POD memory of the requested size and alignment
  pod_memory_block *emb = reinterpret_cast<pod_memory_block *>(self);
  char *begin = reinterpret_cast<char *>((reinterpret_cast<uintptr_t>(emb->m_memory_current) +
                                          reinterpret_cast<pod_memory_block *>(self)->data_alignment - 1) &
                                         ~(reinterpret_cast<pod_memory_block *>(self)->data_alignment - 1));
  char *end = begin + size_bytes;
  if (end > emb->m_memory_end) {
    emb->m_total_allocated_capacity -= emb->m_memory_end - emb->m_memory_current;
    // Allocate memory to double the amount used so far, or the requested size, whichever is larger
    // NOTE: We're assuming malloc produces memory which has good enough alignment for anything
    emb->append_memory(max(emb->m_total_allocated_capacity, size_bytes));
    begin = emb->m_memory_begin;
    end = begin + size_bytes;
  }

  // Indicate where to allocate the next memory
  emb->m_memory_current = end;

  // Return the allocated memory
  return begin;
  //    cout << "allocated at address " << (void *)begin << endl;
}

char *pod_memory_block::resize(char *inout_begin, size_t count) {
  intptr_t size_bytes = count * data_size;

  // Resizes previously allocated POD memory to the requested size
  pod_memory_block *emb = this;
  //    cout << "resizing memory " << (void *)*inout_begin << " / " << (void *)*inout_end << " from size " <<
  // (*inout_end - *inout_begin) << " to " << size_bytes << endl;
  //    cout << "memory state before " << (void *)emb->m_memory_begin << " / " << (void *)emb->m_memory_current << " /
  // " << (void *)emb->m_memory_end << endl;
  char **inout_end = &emb->m_memory_current;
  char *end = inout_begin + size_bytes;
  if (end <= emb->m_memory_end) {
    // If it fits, just adjust the current allocation point
    emb->m_memory_current = end;
    *inout_end = end;
  } else {
    // If it doesn't fit, need to copy to newly malloc'd memory
    char *old_current = inout_begin, *old_end = *inout_end;
    // Allocate memory to double the amount used so far, or the requested size, whichever is larger
    // NOTE: We're assuming malloc produces memory which has good enough alignment for anything
    emb->append_memory(max(emb->m_total_allocated_capacity, size_bytes));
    memcpy(emb->m_memory_begin, inout_begin, *inout_end - inout_begin);
    end = emb->m_memory_begin + size_bytes;
    emb->m_memory_current = end;
    inout_begin = emb->m_memory_begin;
    *inout_end = end;
    emb->m_total_allocated_capacity -= old_end - old_current;
  }
  //    cout << "memory state after " << (void *)emb->m_memory_begin << " / " << (void *)emb->m_memory_current << " /
  // " << (void *)emb->m_memory_end << endl;

  return inout_begin;
}

void pod_memory_block::finalize() {
  // Finalizes POD memory so there are no more allocations
  pod_memory_block *emb = this;

  if (emb->m_memory_current < emb->m_memory_end) {
    emb->m_total_allocated_capacity -= emb->m_memory_end - emb->m_memory_current;
  }
  emb->m_memory_begin = NULL;
  emb->m_memory_current = NULL;
  emb->m_memory_end = NULL;
}

void pod_memory_block::reset() {
  // Resets the POD memory so it can reuse it from the start
  pod_memory_block *emb = this;

  if (emb->m_memory_handles.size() > 1) {
    // If there are more than one allocated memory chunks,
    // throw them all away except the last
    for (size_t i = 0, i_end = emb->m_memory_handles.size() - 1; i != i_end; ++i) {
      free(emb->m_memory_handles[i]);
    }
    emb->m_memory_handles.front() = emb->m_memory_handles.back();
    emb->m_memory_handles.resize(1);
  }

  // Reset to use the whole chunk
  emb->m_memory_current = emb->m_memory_begin;
  emb->m_total_allocated_capacity = emb->m_memory_end - emb->m_memory_begin;
}

void pod_memory_block::debug_print(std::ostream &o, const std::string &indent) {
  o << indent << "------ memory_block at " << static_cast<const void *>(this) << "\n";
  o << indent << " reference count: " << m_use_count << "\n";
  if (m_memory_begin != NULL) {
    o << indent << " allocated: " << m_total_allocated_capacity << "\n";
  } else {
    o << indent << " finalized: " << m_total_allocated_capacity << "\n";
  }
  o << indent << "------" << endl;
}

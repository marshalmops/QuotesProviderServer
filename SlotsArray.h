#ifndef SLOTSARRAY_H
#define SLOTSARRAY_H

#include <vector>
#include <algorithm>
#include <memory>

#include "SlotArrayItem.h"

template <class T>
class SlotsArray
{
    constexpr static const size_t C_START_SIZE  = 8;
    constexpr static const size_t C_EXPAND_STEP = 8;
    
protected:
    bool expandSlots()
    {
        auto **prevSlots = m_slots;
        auto prevSize    = m_size;
        
        m_size  = m_size + C_EXPAND_STEP;
        m_slots = new T*[m_size];
        
        if (!m_slots) return false;
        
        auto newSlotsIndex = 0;
        
        for (auto prevSlotsIter = prevSlots; prevSlotsIter < prevSlotsIter + prevSize; ++prevSlotsIter, ++newSlotsIndex) {
            m_slots[newSlotsIndex] = *prevSlotsIter;
        }
        
        delete []prevSlots;
        
        return true;
    }
    
public:
    SlotsArray()
        : m_slots{},
          m_size {C_START_SIZE}
    {
        
    }
    
    ~SlotsArray()
    {
        for (auto i = m_slots; i < m_slots + m_size; ++i)
            if (*i != nullptr) delete (*i);
        
        if (m_slots) delete[] m_slots;
    }
    
    SlotArrayItem<T>* putItem(T &&item)
    {
        auto curIndex = 0;
        
        for (auto slotsIter = m_slots; slotsIter < m_slots + m_size; ++slotsIter, ++curIndex) {
            if (!(*slotsIter)) return (*slotsIter = new SlotArrayItem<T>{curIndex, std::move(item)});
        }
        
        if (!expandSlots()) return nullptr;
        
        return (m_slots[curIndex + 1] = new T{std::move(item)});
    }
    
    SlotArrayItem<T>* getItem(const size_t index)
    {
        if (index >= m_size) return nullptr;
        if (!m_slots[index]) return nullptr;
        
        return m_slots[index];
    }
    
    bool eraseItem(const size_t index)
    {
        if (index >= m_size) return false;
        if (!m_slots[index]) return false;
        
        delete m_slots[index];
        
        return true;
    }
    
private:
    SlotArrayItem<T>** m_slots;
    size_t            m_size;
};

#endif // SLOTSARRAY_H

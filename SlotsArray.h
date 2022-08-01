#ifndef SLOTSARRAY_H
#define SLOTSARRAY_H

#include <vector>
#include <algorithm>
#include <memory> 
#include <QDebug>

#include "SlotArrayItem.h"

template <class T>
class SlotsArray
{
    constexpr static const size_t C_START_SIZE  = 8;
    constexpr static const size_t C_EXPAND_STEP = 8;
    
protected:
    bool expandSlots()
    {
        SlotArrayItem<T> **prevSlots{m_slots};
        
        auto prevSize = m_size;
        
        m_size  = m_size + C_EXPAND_STEP;
        m_slots = new SlotArrayItem<T>*[m_size];
        
        if (!m_slots) return false;
        
        for (auto prevSlotsIndex = 0; prevSlotsIndex < prevSize; ++prevSlotsIndex) {
            m_slots[prevSlotsIndex] = *(prevSlots + prevSlotsIndex);
        }
        
        for (auto i = prevSize; i < m_size; ++i)
            m_slots[i] = nullptr;
        
        delete []prevSlots;
        
        return true;
    }
    
public:
    SlotsArray()
        : m_slots(new SlotArrayItem<T>*[C_START_SIZE]),
          m_size {C_START_SIZE}
    {
        for (auto i = 0; i < m_size; ++i)
            m_slots[i] = nullptr;
    }
    
    ~SlotsArray()
    {
        if (m_slots == nullptr)
            return;
        
        for (auto i = 0; i < m_size; ++i) {
            if (m_slots[i]  == nullptr) continue;
            
            delete (m_slots[i]);
        }
        
        if (m_slots) delete[] m_slots;
    }
    
    SlotArrayItem<T>* putItem(T &&item)
    {
        auto curIndex = 0;
        
        for (auto i = 0; i < m_size; ++i, ++curIndex) {
            if (!(m_slots[i])) 
                return (m_slots[i] = new SlotArrayItem<T>{i, std::move(item)});
        }
        
        if (!expandSlots()) return nullptr;
        
        return (m_slots[curIndex + 1] = new SlotArrayItem<T>{curIndex + 1, std::move(item)});
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
        
        m_slots[index] = nullptr;
        
        return true;
    }
    
    size_t size() const {
        return m_size;
    }
    
private:
    SlotArrayItem<T>** m_slots;
    size_t             m_size;
};

#endif // SLOTSARRAY_H

#ifndef SLOTARRAYITEM_H
#define SLOTARRAYITEM_H

#include <stdint.h>
#include <memory>

template <class T>
class SlotArrayItem
{
public:
    SlotArrayItem()
        : m_slotIndex{0},
          m_value{}
    {
        
    }
    
    SlotArrayItem(const size_t slotIndex,
                  T &&value)
        : m_slotIndex{slotIndex},
          m_value{std::move(value)}
    {
        
    }
    
    size_t getIndex() const
    {
        return m_slotIndex;
    }
    
    T& getValue()
    {
        return m_value;
    }
    
private:
    size_t m_slotIndex;
    T      m_value;
};

#endif // SLOTARRAYITEM_H

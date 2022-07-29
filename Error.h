#ifndef ERROR_H
#define ERROR_H

#include <string>

class Error
{
public:
    using String = std::string;
    
    Error(const String &text = String{},
          const bool isCritical = false);
    
    const String& getText   () const;
    bool          isCritical() const;
    
    bool isValid() const;
    
private:
    String m_text;
    bool   m_isCritical;
};

#endif // ERROR_H

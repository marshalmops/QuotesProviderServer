#ifndef ERROR_H
#define ERROR_H

#include <string>

class Error
{
public:
    using String = std::string;
    
    Error() = delete;
    Error(const String &text,
          const bool isCritical = false);
    
    const String& getText   () const;
    bool          isCritical() const;
    
private:
    String m_text;
    bool   m_isCritical;
};

#endif // ERROR_H

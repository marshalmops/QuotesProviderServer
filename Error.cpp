#include "Error.h"

Error::Error(const Error::String &text,
             const bool isCritical)
    : m_text      {text},
      m_isCritical{isCritical}
{
    
}

const Error::String& Error::getText() const
{
    return m_text;
}

bool Error::isCritical() const
{
    return m_isCritical;
}

bool Error::isValid() const
{
    return !m_text.empty();
}

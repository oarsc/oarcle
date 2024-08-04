#ifndef MESSAGE_H
#define MESSAGE_H

#include <iostream>

#include "consts.h"

class Message {
public:
    Message(const uint8_t data[] = nullptr, const uint32_t &length = 0);

    const uint8_t* getData() const { return m_data; }
    const long long getSize() const { return m_pointer; }

    uint8_t readU8();
    uint16_t readU16();
    uint32_t readU32();
    std::string readString();
    std::string readRestAsString();

    bool hasU8() const;
    bool hasU16() const;
    bool hasU32() const;
    bool hasString() const;

    void writeU8(const uint8_t &byte);
    void writeU16(const uint16_t &value);
    void writeU32(const uint32_t &value);
    void writeString(const std::string &message);

private:
    bool containsBytes(const uint32_t &numberOfBytes) const;

    bool m_writeMode;
    long long m_pointer = 0;
    long long m_size = 0;
    enum { max_length = MAX_MESSAGE_SIZE };
    uint8_t m_data[max_length];
};

#endif // MESSAGE_H
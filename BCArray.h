#ifndef BCARRAY_H
#define BCARRAY_H

#define ZERO_MASK(ind, len) (~((uint8_t)(0xFF << (ind)) >> (8 - (len)) << (8 - (ind) - (len))))

class BCArray {
public:
    BCArray(const uint8_t cap, const uint16_t length);
    ~BCArray();

    void put(const uint16_t idx, const uint8_t val);
    uint8_t get(const uint16_t idx) const;

    uint16_t length();
    uint8_t capacity();
    uint8_t* byteArray();
    uint16_t bytesLength();
private:
    uint8_t _cap;
    uint16_t _length;
    uint8_t* _data;
};


BCArray::BCArray(const uint8_t cap, const uint16_t length) {
    _cap = cap;
    _length = length;
    _data = new uint8_t[_cap * _length / 8];
}
BCArray::~BCArray() {
    delete[] _data;
}

void BCArray::put(const uint16_t idx, const uint8_t val) {
    // TODO: assert(idx < _length)
    uint16_t byind = idx * _cap / 8;  // byte index
    uint16_t biind = (idx * _cap) % 8;  // bit index
    uint8_t v = val & (0xFF >> (8 - _cap));  // cut off all bits that are outside of _cap range
    // if value is on two adjacent bytes
    if (biind + _cap > 8) {
        // # of bits on the next byte
        uint8_t capRight = (biind + _cap) - 8;
        // shifted values for current & next bytes
        uint8_t shiftedVLeft = v >> capRight;
        uint8_t shiftedVRight = (v & (0xFF >> (8 - capRight))) << (8 - capRight);
        // zero masks for current & next bytes
        uint8_t zeroMaskLeft = ZERO_MASK(biind, _cap - capRight);
        uint8_t zeroMaskRight = ZERO_MASK(0, capRight); // TODO: optimization required here
        // mask data and paste shifted values
        _data[byind] = (_data[byind] & zeroMaskLeft) | shiftedVLeft;
        _data[byind + 1] = (_data[byind + 1] & zeroMaskRight) | shiftedVRight;
    }
    // if value is on one current byte
    else {
        // shift value to its final position
        uint8_t shiftedV = v << 8 - biind - _cap;  // TODO: the same as v >> capRight
        // get mask with zeros at the value's final position
        uint8_t zeroMask = ZERO_MASK(biind, _cap);
        _data[byind] = (_data[byind] & zeroMask) | shiftedV;  // mask the data and paste value
    }
}
uint8_t BCArray::get(const uint16_t idx) const {
    // TODO: assert(idx < _length)
    uint16_t byind = idx * _cap / 8;  // byte index
    uint16_t biind = (idx * _cap) % 8;  // bit index
    // if value is on two adjacent bytes
    if (biind + _cap > 8) {
        uint8_t capRight = (biind + _cap) - 8;
        uint8_t leftV = _data[byind] & (uint8_t)(0xFF >> 8 - (_cap - capRight));
        uint8_t v = _data[byind + 1] >> 8 - capRight;
        return v | leftV << capRight;
    }
    // if value is on one current byte
    else {
        return (uint8_t)(_data[byind] << biind) >> (8 - _cap);
    }
}

uint8_t* BCArray::byteArray() {
    return _data;
}
uint16_t BCArray::bytesLength() {
    return _cap * _length / 8;
}
uint16_t BCArray::length() {
    return _length;
}
uint8_t BCArray::capacity() {
    return _cap;
}

#endif // BCARRAY_H
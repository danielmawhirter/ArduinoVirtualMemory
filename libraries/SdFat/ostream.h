/* Arduino SdFat Library
 * Copyright (C) 2012 by William Greiman
 *
 * This file is part of the Arduino SdFat Library
 *
 * This Library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This Library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with the Arduino SdFat Library.  If not, see
 * <http://www.gnu.org/licenses/>.
 */
#ifndef ostream_h
#define ostream_h
/**
 * \file
 * \brief \ref ostream class
 */
#include <ios.h>
//------------------------------------------------------------------------------
/** macro for flash inserter */
#define pstr(str) pgm(PSTR(str))
/** \struct pgm
 * \brief type for string in flash
 */
struct pgm {
  /** Pointer to flash string */
  char *ptr;
  /** constructor
   * \param[in] str initializer for pointer.
   */
  explicit pgm(char* str) : ptr(str) {}
  /** constructor
   * \param[in] str initializer for pointer.
   */
  explicit pgm(const char *str) : ptr(const_cast<char*>(str)) {}
};
//==============================================================================
/**
 * \class ostream
 * \brief Output Stream
 */
class ostream : public virtual ios {
 public:
  ostream() {}

  /** call manipulator
   * \param[in] pf function to call
   * \return the stream
   */
  ostream& operator<< (ostream& (*pf)(ostream& str)) {
    return pf(*this);
  }
  /** call manipulator
   * \param[in] pf function to call
   * \return the stream
   */
  ostream& operator<< (ios_base& (*pf)(ios_base& str)) {
    pf(*this);
    return *this;
  }
  /** Output bool
   * \param[in] arg value to output
   * \return the stream
   */
  ostream &operator<< (bool arg) {
    putBool(arg);
    return *this;
  }
  /** Output string
   * \param[in] arg string to output
   * \return the stream
   */
  ostream &operator<< (const char *arg) {
    putStr(arg);
    return *this;
  }
  /** Output string
   * \param[in] arg string to output
   * \return the stream
   */
  ostream &operator<< (const signed char *arg) {
    putStr((const char*)arg);
    return *this;
  }
  /** Output string
   * \param[in] arg string to output
   * \return the stream
   */
  ostream &operator<< (const unsigned char *arg) {
    putStr((const char*)arg);
    return *this;
  }
  /** Output character
   * \param[in] arg character to output
   * \return the stream
   */
  ostream &operator<< (char arg) {
    putChar(arg);
    return *this;
  }
  /** Output character
   * \param[in] arg character to output
   * \return the stream
   */
  ostream &operator<< (signed char arg) {
    putChar(static_cast<char>(arg));
    return *this;
  }
  /** Output character
   * \param[in] arg character to output
   * \return the stream
   */
  ostream &operator<< (unsigned char arg) {
    putChar(static_cast<char>(arg));
    return *this;
  }
  /** Output double
   * \param[in] arg value to output
   * \return the stream
   */
  ostream &operator<< (double arg) {
    putDouble(arg);
    return *this;
  }
  /** Output float
   * \param[in] arg value to output
   * \return the stream
   */
  ostream &operator<< (float arg) {
    putDouble(arg);
    return *this;
  }
  /** Output signed short
   * \param[in] arg value to output
   * \return the stream
   */
  ostream &operator<< (short arg) {  // NOLINT
    putNum((int32_t)arg);
    return *this;
  }
  /** Output unsigned short
   * \param[in] arg value to output
   * \return the stream
   */
  ostream &operator<< (unsigned short arg) {  // NOLINT
    putNum((uint32_t)arg);
    return *this;
  }
  /** Output signed int
   * \param[in] arg value to output
   * \return the stream
   */
  ostream &operator<< (int arg) {
    putNum((int32_t)arg);
    return *this;
  }
  /** Output unsigned int
   * \param[in] arg value to output
   * \return the stream
   */
  ostream &operator<< (unsigned int arg) {
    putNum((uint32_t)arg);
    return *this;
  }
  /** Output signed long
   * \param[in] arg value to output
   * \return the stream
   */
  ostream &operator<< (long arg) {  // NOLINT
    putNum((int32_t)arg);
    return *this;
  }
  /** Output unsigned long
   * \param[in] arg value to output
   * \return the stream
   */
  ostream &operator<< (unsigned long arg) {  // NOLINT
    putNum((uint32_t)arg);
    return *this;
  }
  /** Output pointer
   * \param[in] arg value to output
   * \return the stream
   */
  ostream& operator<< (const void* arg) {
    putNum(reinterpret_cast<uint32_t>(arg));
    return *this;
  }
  /** Output a string from flash using the pstr() macro
   * \param[in] arg pgm struct pointing to string
   * \return the stream
   */
  ostream &operator<< (pgm arg) {
    putPgm(arg.ptr);
    return *this;
  }
  /** Output a string from flash using the Arduino F() macro.
   * \param[in] arg pointing to flash string
   * \return the stream
   */
  ostream &operator<< (const __FlashStringHelper *arg) {
    putPgm(reinterpret_cast<const char*>(arg));
    return *this;
  }
  /**
   * Puts a character in a stream.
   *
   * The unformatted output function inserts the element \a ch.
   * It returns *this.
   *
   * \param[in] ch The character
   * \return A reference to the ostream object.
   */
  ostream& put(char ch) {
    putch(ch);
    return *this;
  }
//  ostream& write(char *str, streamsize count);
  /**
   * Flushes the buffer associated with this stream. The flush function
   * calls the sync function of the associated file.
   * \return A reference to the ostream object.
   */
  ostream& flush() {
    if (!sync()) setstate(badbit);
    return *this;
  }
  /**
   * \return the stream position
   */
  pos_type tellp() {return tellpos();}
  /**
   * Set the stream position
   * \param[in] pos The absolute position in which to move the write pointer.
   * \return Is always *this.  Failure is indicated by the state of *this.
   */
  ostream& seekp(pos_type pos) {
    if (!seekpos(pos)) setstate(failbit);
    return *this;
  }
  /**
   * Set the stream position.
   *
   * \param[in] off An offset to move the write pointer relative to way.
   * \a off is a signed 32-bit int so the offset is limited to +- 2GB.
   * \param[in] way One of ios::beg, ios::cur, or ios::end.
   * \return Is always *this.  Failure is indicated by the state of *this.
   */
  ostream& seekp(off_type off, seekdir way) {
    if (!seekoff(off, way)) setstate(failbit);
    return *this;
  }

 protected:
  /// @cond SHOW_PROTECTED
  /** Put character with binary/text conversion
   * \param[in] ch character to write
   */
  virtual void putch(char ch) = 0;
  virtual void putstr(const char *str) = 0;
  virtual bool seekoff(off_type pos, seekdir way) = 0;
  virtual bool seekpos(pos_type pos) = 0;
  virtual bool sync() = 0;

  virtual pos_type tellpos() = 0;
  /// @endcond
 private:
  void do_fill(unsigned len);
  void fill_not_left(unsigned len);
  char* fmtNum(uint32_t n, char *ptr, uint8_t base);
  void putBool(bool b);
  void putChar(char c);
  void putDouble(double n);
  void putNum(uint32_t n, bool neg = false);
  void putNum(int32_t n);
  void putPgm(const char* str);
  void putStr(const char* str);
};
#endif  // ostream_h

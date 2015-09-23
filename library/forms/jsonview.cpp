/*
 * Copyright (c) 2015, Oracle and/or its affiliates. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; version 2 of the
 * License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301  USA
 */

#include <set>
#include <sstream>
#include <cctype>
#include <algorithm>

#include <boost/assign.hpp>
#include <boost/make_shared.hpp>

#include "mforms/jsonview.h"
#include "mforms/panel.h"
#include "mforms/code_editor.h"
#include "mforms/tabview.h"
#include "base/string_utilities.h"

#undef min

using namespace mforms;
using namespace JsonParser;


// JSON Data structures implementation

/**
 * @brief  Default constructor creates empty element.
 */
JsonObject::JsonObject()
{
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Copy constructor.
 * @param other a JsonObject of identical element and allocator types.
 */
JsonObject::JsonObject(const JsonObject &other) : _data(other._data)
{
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Assignment operator.
 * @param other a JsonObject of identical element and allocator types.
 *
 * @return returns the reference to assigned value.
 */
JsonObject &JsonObject::operator=(const JsonObject &other)
{
  //if (*this != other)
  _data = other._data;
  return *this;
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Returns a read/write iterator.
 *
 * Returns a read/write iterator that points to the first
 * element in the JsonObject container. Iteration is done in accessing order according to the key.
 *
 * @return iterator for begining of sequence.
 */
JsonObject::Iterator JsonObject::begin()
{
  return _data.begin();
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Returns a readonly iterator.
 *
 * Returns a readonly iterator that points to the first
 * element in the JsonObject container. Iteration is done in accessing order according to the key.
 *
 * @return iterator for begining of sequence.
 */
JsonObject::ConstIterator JsonObject::begin() const
{
  return _data.begin();
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Returns a readonly iterator.
 *
 * Returns a readonly iterator that points to the first
 * element in the JsonObject container. Iteration is done in accessing order according to the key.
 *
 * @return iterator for begining of sequence.
 */
JsonObject::ConstIterator JsonObject::cbegin() const
{
  return _data.begin();
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Returns iterator for end of sequence.
 *
 * Returns a read/write iterator that points to one past the last pair in the JsonObject container.
 *
 * @return iterator for end of sequence.
 */
JsonObject::Iterator JsonObject::end()
{
  return _data.end();
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Returns a readonly iterator.
 *
 * Returns a readonly (const) iterator that points to one past the last pair in the JsonObject container.
 *
 * @return iterator for end of sequence.
 */
JsonObject::ConstIterator JsonObject::end() const
{
  return _data.end();
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Returns a readonly iterator.
 *
 * Returns a readonly (const) iterator that points to one past the last pair in the JsonObject container.
 *
 * @return iterator for end of sequence.
 */
JsonObject::ConstIterator JsonObject::cend() const
{
  return _data.end();
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Returns the size of the JsonObject container.
 *
 * @return the size of the JsonObject container.
 */
JsonObject::SizeType JsonObject::size()
{
  return _data.size();
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Tries to find an element in a JsonObject container.
 *
 * @param key Kay to be located in the JsonObject container.
 * @return Iterator pointing to element, or end() if not found.
 */
JsonObject::Iterator JsonObject::find(const KeyType &key)
{
  return _data.find(key);
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Tries to find an element in a JsonObject container.
 *
 * @param key Kay to be located in the JsonObject container.
 * @return Read only iterator pointing to element, or end() if not found.
 */
JsonObject::ConstIterator JsonObject::find(const KeyType &key) const
{
  return _data.find(key);
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Test if container is empty.
 *
 * @return returns true if the JsonObject container is empty.
 */
bool JsonObject::empty() const
{
  return _data.empty();
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Erases all elements in a JsonObject container.
 *
 */
void JsonObject::clear()
{
  _data.clear();
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Erases an element from a JsonObject container.
 *
 * @param it An iterator pointing to the element to be erased.
 */
void JsonObject::erase(Iterator it)
{
  _data.erase(it);
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Erases an element from a JsonObject container.
 *
 * @param first An iterator pointing to the start of the range to be erased.
 * @param last An iterator pointing to the end of the range to be erased.
 */
void JsonObject::erase(Iterator first, Iterator last)
{
  _data.erase(first, last);
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Attempts to insert a Json value into the container.
 *
 * @param  key  The key for which json data should be stored.
 * @param  value  JsonValue to be inserted.
 */
void JsonObject::insert(const KeyType &key, const JsonValue &value)
{
  _data[key] = value;
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Access to the data..
 *
 * @param name The key for which json data should be accesed.
 * @return A reference to the data whose key is equivalent to 'key', if
 *         such a data is present in the Json container. If no such data is present
 *         new key is created
 */
JsonValue &JsonObject::operator [](const std::string &name)
{
  return _data[name];
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Access to JsonObject container data.
 *
 * @param key The key for which data should be retrieved.
 * @return A reference to the data whose key is equivalent to 'key', if
 *         such a data is present in the Json container. If no such data is present
 *         std::out_of_range is thrown.
 */
JsonValue &JsonObject::get(const KeyType &key)
{
  if (_data.count(key) == 0)
    throw std::out_of_range(base::strfmt("no element '%s' found in caontainer", key.c_str()));
  return _data[key];
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Access to JsonObject container data.
 *
 * @param key The key for which data should be retrieved.
 * @return  A const reference to the data whose key is equivalent to 'key', if
 *          such a data is present in the Json container. If no such data is present
 *          std::out_of_range is thrown.
 */
const JsonValue &JsonObject::get(const KeyType &key) const
{
  if (_data.count(key) == 0)
    throw std::out_of_range(base::strfmt("no element '%s' found in caontainer", key.c_str()));
  return _data.at(key);
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Default constructor.
 *
 */
JsonArray::JsonArray()
{
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Copy constructor.
 * @param other a JsonObject of identical element and allocator types.
 */
JsonArray::JsonArray(const JsonArray &other) : _data(other._data)
{
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Assignment operator.
 * @param other a JsonArray of identical element and allocator types.
 *
 * @return returns the reference to assigned value.
 */
JsonArray &JsonArray::operator=(const JsonArray &other)
{
  _data = other._data;
  return *this;
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief  Access to the data.
 * @param pos The index of the element for which data should be
 *            accessed.
 * @return Read/write reference to data stored in continer.
 *         If no such data is present std::out_of_range is thrown.
 */
JsonValue &JsonArray::at(SizeType pos)
{
  if (pos > _data.size())
    throw std::out_of_range(base::strfmt("Index '%lu' is out of range.", pos));
  return _data.at(pos);
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Access to the data.
 * @param pos The index of the element for which data should be
 *        accessed.
 * @return Read only reference to data stored in continer.
 *         If no such data is present std::out_of_range is thrown.
 */
const JsonValue &JsonArray::at(SizeType pos) const
{
  if (pos > _data.size())
    throw std::out_of_range(base::strfmt("Index '%lu' is out of range.", pos));
  return _data.at(pos);
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief  Access to the data.
 * @param pos The index of the element for which data should be accessed.
 * @return Read/Write reference to data stored in continer.
 *
 *  This operator allows for easy, array-style, data access.
 */
JsonValue &JsonArray::operator[](SizeType pos)
{
  assert(pos < _data.size());
  return _data[pos];
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief  Access to the data.
 * @param pos The index of the element for which data should be accessed.
 * @return Read only reference to data stored in continer.
 *
 *  This operator allows for easy, array-style, data access.
 */
const JsonValue &JsonArray::operator[](SizeType pos) const
{
  assert(pos < _data.size());
  return _data[pos];
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Returns a read/write iterator.
 *
 * Returns a read/write iterator that points to the first
 * element in the JsonArray container.
 *
 * @return iterator for begining of sequence.
 */
JsonArray::Iterator JsonArray::begin()
{
  return _data.begin();
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Returns a rad only iterator.
 *
 * Returns a read only iterator that points to the first
 * element in the JsonArray container.
 *
 * @return iterator for begining of sequence.
 */
JsonArray::ConstIterator JsonArray::begin() const
{
  return _data.begin();
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Returns a rad only iterator.
 *
 * Returns a read only iterator that points to the first
 * element in the JsonArray container.
 *
 * @return iterator for begining of sequence.
 */
JsonArray::ConstIterator JsonArray::cbegin() const
{
  return _data.begin();
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Returns iterator for end of sequence.
 *
 * Returns a read/write iterator that points to one past the last pair in the JsonArray container.
 *
 * @return iterator for end of sequence.
 */
JsonArray::Iterator JsonArray::end()
{
  return _data.end();
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Returns iterator for end of sequence.
 *
 * Returns a read only iterator that points to one past the last pair in the JsonArray container.
 *
 * @return iterator for end of sequence.
 */
JsonArray::ConstIterator JsonArray::end() const
{
  return _data.end();
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Returns iterator for end of sequence.
 *
 * Returns a read only iterator that points to one past the last pair in the JsonArray container.
 *
 * @return iterator for end of sequence.
 */
JsonArray::ConstIterator JsonArray::cend() const
{
  return _data.end();
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Get size of JsonArray.
 *
 * @return return length of sequence.
 */
JsonArray::SizeType JsonArray::size()
{
  return _data.size();
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Test if container is empty.
 *
 * @return returns true if the JsonArray container is empty.
 */
bool JsonArray::empty() const
{
  return _data.empty();
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Erases all elements in a JsonArray container.
 *
 */
void JsonArray::clear()
{
  _data.clear();
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Erases an element from a JsonArray container.
 *
 * @param it An iterator pointing to the element to be erased.
 * @return An iterator pointing to the element immediately following
 *         a position prior to the element being erased. If no such
 *         element exists, end() is returned.
 */
JsonArray::Iterator JsonArray::erase(Iterator pos)
{
  return _data.erase(pos);

}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Erases an element from a JsonArray container.
 *
 * @param first An iterator pointing to the start of the range to be erased.
 * @param last An iterator pointing to the end of the range to be erased.
 * @return An iterator pointing to the element immediately following
 *         a position prior to the element being erased.If no such
 *         element exists, end() is returned.
 */
JsonArray::Iterator JsonArray::erase(Iterator first, Iterator last)
{
  return _data.erase(first, last);
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Attempts to insert value at pos.
 * @param pos A iterator to the JsonArray where insert value.
 * @param value JsonValue to be inserted.
 *
 * @return An iterator that points to the inserted data.
 */
JsonArray::Iterator JsonArray::insert(Iterator pos, const JsonValue &value)
{
  return _data.insert(pos, value);
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Add data to the end of the container.
 * @param value JsonValue to be inserted.
 *
 */
void JsonArray::pushBack(const ValueType &value)
{
  _data.push_back(value);
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief default destructor.
 *
 */
JsonValue::JsonValue()
  : _double(0), _integer64(0), _uint64(0), _bool(false), _type(VEmpty)
{
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief  Copy constructor.
 * @param other A JsonValue of identical element and allocator types.
 */
JsonValue::JsonValue(const JsonValue &rhs)
   : _double(rhs._double), _integer64(rhs._integer64), _uint64(rhs._uint64), _bool(rhs._bool),
   _string(rhs._string), _object(rhs._object), _array(rhs._array), _type(rhs._type)
{
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Assignment operator.
 * @param other A JsonValue of identical element and allocator types.
 *
 * @return returns the reference to assigned value.
 */
JsonValue &JsonValue::operator=(const JsonValue &rhs)
{
  _double = rhs._double;
  _integer64 = rhs._integer64;
  _uint64 = rhs._uint64;
  _bool = rhs._bool;
  _string = rhs._string;
  _object = rhs._object;
  _array = rhs._array;
  _type = rhs._type;
  return *this;
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief  Construct JsonValue from string.
 * @param val A string value.
 */
JsonValue::JsonValue(const std::string &val)
   : _double(0), _bool(false), _string(val), _type(VString)
{
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief  Construct JsonValue from string.
 * @param val A string const value.
 */
JsonValue::JsonValue(const char* val)
  : _double(0), _integer64(0), _uint64(0), _bool(false), _type(VString)
{
  _string = std::string(val != NULL ? val : "");
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Construct JsonValue from bool.
 * @param val A bool value.
 */
JsonValue::JsonValue(bool val)
  : _double(0), _integer64(0), _uint64(0), _bool(val), _type(VBoolean)
{
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Construct JsonValue from int.
 * @param val A int value.
 */
JsonValue::JsonValue(int val)
  : _double(0), _integer64(0), _uint64(0), _bool(false), _type(VInt)
{
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Construct JsonValue from int64_t.
 * @param val A int value.
 */
JsonValue::JsonValue(int64_t val)
  : _double(0), _integer64(val), _uint64(0), _bool(false), _type(VInt64)
{
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Construct JsonValue from uint64_t.
 * @param val A int value.
 */
JsonValue::JsonValue(uint64_t val)
  : _double(0), _integer64(0), _uint64(val), _bool(false), _type(VUint64)
{
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief implicit cast to jsonObject element type. throw if its not possible.
 *
 */
JsonValue::operator const JsonObject & () const
{
  if (getType() != VObject)
    throw std::bad_cast();
  return getObject();
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief implicit cast to JsonArray element type. throw if its not possible.
 *
 */
JsonValue::operator const JsonArray & () const
{
  if (getType() != VArray)
    throw std::bad_cast();
  return getArray();
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief implicit cast to int element type. throw if its not possible.
 *
 */
JsonValue::operator int() const
{
  if (getType() != VInt)
    throw std::bad_cast();
  return getInt();

}

//--------------------------------------------------------------------------------------------------

/**
 * @brief implicit cast to double element type. throw if its not possible.
 *
 */
JsonValue::operator double() const
{
  if (getType() != VDouble)
    throw std::bad_cast();
  return getDouble();

}

//--------------------------------------------------------------------------------------------------

/**
 * @brief implicit cast to int64_t element type. throw if its not possible.
 *
 */
JsonValue::operator int64_t() const
{
  if (getType() != VInt64)
    throw std::bad_cast();
  return getInt64();

}
//--------------------------------------------------------------------------------------------------

/**
 * @brief implicit cast to uint64_t element type. throw if its not possible.
 *
 */
JsonValue::operator uint64_t() const
{
  if (getType() != VUint64)
    throw std::bad_cast();
  return getUint64();

}

//--------------------------------------------------------------------------------------------------

/**
 * @brief implicit cast to bool element type. throw if its not possible.
 *
 */
JsonValue::operator bool() const
{
  if (getType() != VBoolean)
    throw std::bad_cast();
   return getBool();
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief implicit cast to std::string element type. throw if its not possible.
 *
 */
JsonValue::operator const std::string & () const
{
  if (getType() != VString)
    throw std::bad_cast();
  return getString();
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Construct JsonValue from double.
 *
 * @param val A double value.
 */
JsonValue::JsonValue(double val)
  : _double(val), _integer64(0), _uint64(0), _bool(false), _type(VDouble)
{
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Construct JsonValue from JsonObject value.
 *
 * @param val A JsonObject value.
 */
JsonValue::JsonValue(const JsonObject &val)
  : _double(0), _integer64(0), _uint64(0), _bool(false), _object(val), _type(VObject)
{
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Construct JsonValue from JsonArray value.
 *
 * @param val A JsonArray value.
 */
JsonValue::JsonValue(const JsonArray &val)
  : _double(0), _integer64(0), _uint64(0), _bool(false), _array(val), _type(VArray)
{
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Access to type of value.
 *
 * @return return type of value.
 */
DataType JsonValue::getType() const
{
  return _type;
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Access to the double value.
 *
 * @return return double value.
 */
double JsonValue::getDouble() const
{
  return _double;
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Set number value.
 *
 * @param val A double value to set.
 */
void JsonValue::setNumber(double val)
{
  _double = val;
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Access to the int value.
 *
 * @return return int value.
 */
int JsonValue::getInt() const
{
  return static_cast<int>(_double);
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Access to the int64_t value.
 *
 * @return return int64_t value.
 */
int64_t JsonValue::getInt64() const
{
  return _integer64;
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Set int64_t value.
 *
 * @param val A int64_t value to set.
 */
void JsonValue::setInt64(int64_t val)
{
  _integer64 = val;
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Access to the uint64_t value.
 *
 * @return return uint64 value.
 */
uint64_t JsonValue::getUint64() const
{
  return _uint64;
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Set uint64_t value.
 *
 * @param val A uint64_t value to set.
 */
void JsonValue::setUint64(uint64_t val)
{
  _uint64 = val;
}


//--------------------------------------------------------------------------------------------------

/**
 * @brief Access to the bool value.
 *
 * @return return bool value.
 */
bool JsonValue::getBool() const
{
  return _bool;
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Set bool value.
 *
 * @param val A bool value to set.
 */
void JsonValue::setBool(bool val)
{
  _bool = val;
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Access to the string value.
 *
 * @return return const reference to string value.
 */
const std::string &JsonValue::getString() const
{
  return _string;
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Set string value.
 *
 * @param val A string reference to set.
 */
void JsonValue::setString(const std::string &val)
{
  _string = val;
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Access to the JsonObject value.
 *
 * @return return reference to the JsonObject value.
 */
JsonObject &JsonValue::getObject()
{
  return _object;
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Access to the JsonObject value.
 *
 * @return return const reference to the JsonObject value.
 */
const JsonObject &JsonValue::getObject() const
{
  return _object;
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Set JsonObject value.
 *
 * @param val A reference to JsonObject to set.
 */
void JsonValue::setObject(const JsonObject &val)
{
  _object = val;
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Access to the JsonArray value.
 *
 * @return return reference to the JsonObject value.
 */
JsonArray &JsonValue::getArray()
{
  return _array;
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Set setArray value.
 *
 * @param val A reference to setArray to set.
 */
void JsonValue::setArray(const JsonArray &val)
{
  _array = val;
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Access to the double value.
 *
 * @return return double value.
 */
const JsonArray &JsonValue::getArray() const
{
  return _array;
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Set JsonValue type.
 *
 * @param type A type to set.
 */
void JsonValue::setType(DataType type)
{
   _type = type;
}

//--------------------------------------------------------------------------------------------------

// JSON reader implementation

/**
 * @brief Construtor
 *        Construct JsonReader from string
 *
 * @param value string reference contaning Json data
 */
JsonReader::JsonReader(const std::string &value)
  : _jsonText(value), _actualPos(0)
{
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Returns the next available character but does not consume it.
 *
 * @return An char representing the next character to be read, or 0 if there are no characters to be read.
 */
char JsonReader::peek()
{
  return (_actualPos < _jsonText.length()) ? _jsonText[_actualPos] : static_cast<char>(0);
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Check if the end of a string has been reached
 *
 * @param
 * @return Returns a bool value true when the end of a string has been reached
 */
bool JsonReader::eos()
{
  return _actualPos == _jsonText.length();
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Indicates whether the specified  character is categorized as white space.
 *
 * @param c The character to evaluate.
 * @return true if c is white space; otherwise, false.
 */
bool JsonReader::isWhiteSpace(char c)
{
  return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief skip white spaces.
 *
 */
void JsonReader::eatWhitespace()
{
  while(isWhiteSpace(peek()))
    moveAhead();
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Consume actual character and move the next available.
 *
 */
void JsonReader::moveAhead()
{
  _actualPos = std::min(_actualPos + 1, _jsonText.length());
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Try to parse Json data.
 *
 * @param text String to parse.
 * @param value Parsed Json value.
 */
void JsonReader::read(const std::string &text, JsonValue &value)
{
  JsonReader reader(text);
  reader.scan();
  reader.parse(value);
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Scan every character in Json data.
 *
 */
void JsonReader::scan()
{
  while (!eos())
  {
    eatWhitespace();
    std::string value;
    JsonToken::JsonTokenType type = JsonToken::JsonTokenEmpty;
    char chr = peek();
    switch (chr)
    {
    case '{':
      value += chr;
      type = JsonToken::JsonTokenObjectStart;
      moveAhead();
      break;

    case '}':
      value += chr;
      type = JsonToken::JsonTokenObjectEnd;
      moveAhead();
      break;

    case '[':
      value += chr;
      type = JsonToken::JsonTokenArrayStart;
      moveAhead();
      break;

    case ']':
      value += chr;
      type = JsonToken::JsonTokenArrayEnd;
      moveAhead();
      break;

    case ',':
      value += chr;
      type = JsonToken::JsonTokenNext;
      moveAhead();
      break;

    case ':':
      value += chr;
      type = JsonToken::JsonTokenAssign;
      moveAhead();
      break;

    case '"':
      value = getJsonString();
      type = JsonToken::JsonTokenString;
      break;

    case '-':
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      value = getJsonNumber();
      type = JsonToken::JsonTokenNumber;
      break;
    case 't':
    case 'f':
      value = getJsonBoolean();
      type = JsonToken::JsonTokenBoolean;
      break;
    case 'n':
      checkJsonEmpty();
      type = JsonToken::JsonTokenEmpty;
      break;
    case 'u':
      checkJsonEmpty("undefined"); //only valid in java script, it is not valid json value according to
      type = JsonToken::JsonTokenEmpty;
      break;

    case 0:
      break;
    default:
      throw ParserException(std::string("Unexpected start sequence: ") + chr); // @@FIXMEE
    }
    _tokens.push_back(JsonToken(type, value));
  }
  _tokenIterator = _tokens.begin();
  _tokenEnd = _tokens.end();
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Check if Json data contains given text starting with actual reader position.
 *
 * @param text String to check.
 * @return true if text match to readed text from Json data member; otherwise, false.
 */
bool JsonReader::match(const std::string &text)
{
  bool match = !text.empty();
  std::string::const_iterator end = text.end();
  for(std::string::const_iterator it = text.begin(); it != end; ++it)
  {
    if (eos() || *it != peek())
    {
      match = false;
      break;
    }
    moveAhead();
  }
  return match;
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Parse json string.
 *
 * @return Parsed value.
 */
std::string JsonReader::getJsonString()
{
  moveAhead();
  std::string string;
  while (eos() == false && peek() != '"')
  {
    char currentChar = peek();
    moveAhead();
    if (currentChar == '\\' && !eos())
    {
      currentChar = peek();
      moveAhead();
      switch (currentChar)
      {
      case '/':
      case '"':
      case '\\':
        string += currentChar;
        break;
      case 'b':
        string += '\b';
        break;
      case 'f':
        string += '\f';
        break;
      case 'n':
        string += '\n';
        break;
      case 'r':
        string += '\r';
        break;
      case 't':
        string += '\t';
        break;
      /*case 'u':
        string += '\x';*/
      default:
          throw ParserException(std::string("Unrecognized escape sequence: \\") + currentChar);
      }
    }
    else
    {
      string.push_back(currentChar);
    }
  }
  if (!match("\""))
    throw ParserException(std::string("Expected: \" "));
  return string;
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Parse json null literal.
 *
 * @param text String to check.
 */
void JsonReader::checkJsonEmpty(const std::string &text/* = "null" */)
{
  std::string emptyString;
  for (size_t i = 0; i < text.size() && !eos(); ++i)
  {
    char ch = peek();
    if(isspace(ch))
      break;
    emptyString += ch;
    moveAhead();
  }
  if (emptyString.compare(text) != 0)
    throw ParserException(std::string("Unexpected token: ") + emptyString);
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Get a string literal from Json data buffer.
 *
 * @return returns the parsed bool as string.
 */
std::string JsonReader::getJsonBoolean()
{
  const int size = peek() == 'f' ? 5 : 4;
  std::string boolString;
  for (int i = 0; i < size && !eos(); ++i)
  {
    boolString += peek();
    moveAhead();
  }
  if (boolString == "true" && boolString == "false")
    throw ParserException(std::string("Unexpected token: ") + boolString);

  return boolString;
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Get a string literal from Json data buffer.
 *
 * @return returns the parsed number as string.
 */
std::string JsonReader::getJsonNumber()
{
  std::set<char> numericChars = boost::assign::list_of('0')('1')('2')('3')('4')('5')('6')('7')('8')('9')('.')('e')('E')('-')('+');
  std::string number;
  while (eos() == false && numericChars.count(peek()) == 1)
  {
    number += peek();
    moveAhead();
  }
  return number;
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Check the specified token in current buffer position
 *
 * @param token Token to check.
 * @param skip Skip this token.
 * @param mustMach True if specified thoken must macht, otherweise exception is thrown.
 */
bool JsonReader::processToken(JsonToken::JsonTokenType type, bool skip /*= false*/, bool mustMatch/* = true*/)
{
  bool ret = _tokenIterator != _tokenEnd && _tokenIterator->getType() == type;
  if (!ret && mustMatch)
  {
    std::string message;
    if (_tokenIterator != _tokenEnd)
      message = std::string("Unexpected token: ") + _tokenIterator->getValue();
    else
    message = std::string("Not compleated json data");
    throw ParserException(message);
  }
  if (skip && ret)
  {
    ++_tokenIterator;
    ret = _tokenIterator != _tokenEnd;
  }
  return ret;
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Parse a JsonObject from Json data buffer.
 *
 * @param value JsonValue reference where to store parsed JsonObject.
 */
void JsonReader::parse(JsonObject &obj)
{
  bool go = processToken(JsonToken::JsonTokenObjectStart, true) && _tokenIterator->getType() != JsonToken::JsonTokenObjectStart;
  while (go)
  {
    // the member name
    processToken(JsonToken::JsonTokenString);
    std::string name = _tokenIterator->getValue();
    ++_tokenIterator;

    // assign separator
    processToken(JsonToken::JsonTokenAssign, true);

    JsonValue value;
    // json value
    parse(value);
    if (obj.find(name) != obj.end())
      throw ParserException(std::string("Duplicate member: ") + name);

    obj.insert(name, value);

    go = processToken(JsonToken::JsonTokenNext, true, false);
  }
  processToken(JsonToken::JsonTokenObjectEnd, true);
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Parses a string, and returns a floating point number or integer.
 *
 * @param value JsonValue reference where to store parsed number.
 */
void JsonReader::parseNumber(JsonValue &value)
{
   std::stringstream buffer;
   buffer << _tokenIterator->getValue();
   double number = 0;
   buffer >> number;
   double intpart = 0;
   if (modf(number, &intpart) == 0.0)
      value.setType(VInt);
   else
      value.setType(VDouble);
   value.setNumber(number);
   ++_tokenIterator;
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Parses a string, and returns a bool.
 *
 * @param value JsonValue reference where to store parsed bool value.
 */
void JsonReader::parseBoolean(JsonValue &value)
{
  bool isBool = (_tokenIterator->getValue() == "true" ? true : false);
  value.setBool(isBool);
  value.setType(VBoolean);
  ++_tokenIterator;
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Parse a string literal from Json data buffer.
 *
 * @param value JsonValue reference where to store parsed string.
 */
void JsonReader::parseString(JsonValue &value)
{
  value.setString(_tokenIterator->getValue());
  value.setType(VString);
  ++_tokenIterator;
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Parse a empty string literal from Json data buffer.
 *
 * @param value JsonValue reference where to store parsed string.
 */
void JsonReader::parseEmpty(JsonValue &value)
{
  value.setType(VEmpty);
  ++_tokenIterator;
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Parse a JsonObject from Json data buffer.
 *
 * @param value JsonValue reference where to store parsed JsonObject.
 */
void JsonReader::parseObject(JsonValue &value)
{
  value.setType(VObject);
  JsonObject &object = value.getObject();
  parse(object);
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Parse a JsonArray from Json data buffer.
 *
 * @param value JsonValue reference where to store parsed JsonArray.
 */
void JsonReader::parseArray(JsonValue &value)
{
  value.setType(VArray);
  JsonArray &array = value.getArray();
  bool go = processToken(JsonToken::JsonTokenArrayStart, true) && _tokenIterator->getType() != JsonToken::JsonTokenArrayStart;
  while (go)
  {
    JsonValue value;
    parse(value);
    array.pushBack(value);
    go = processToken(JsonToken::JsonTokenNext, true, false);
  }
  processToken(JsonToken::JsonTokenArrayEnd, true);
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief parse
 *
 * @param reference to json value to be parsed
 */
void JsonReader::parse(JsonValue &value)
{
  if (_tokenIterator == _tokenEnd)
     throw ParserException("Unexpected json data end.");
  JsonToken::JsonTokenType type = _tokenIterator->getType();
  switch (type)
  {
  case JsonToken::JsonTokenString:
    parseString(value);
    break;
  case JsonToken::JsonTokenNumber:
    parseNumber(value);
    break;
  case JsonToken::JsonTokenBoolean:
    parseBoolean(value);
    break;
  case JsonToken::JsonTokenEmpty:
    parseEmpty(value);
    break;
  case JsonToken::JsonTokenObjectStart:
    parseObject(value);
    break;
  case JsonToken::JsonTokenArrayStart:
    parseArray(value);
    break;
  default:
     throw ParserException(std::string("Unexpected token: ") + _tokenIterator->getValue());
  }
}

//--------------------------------------------------------------------------------------------------

// JSON writer implementation

/**
 * @brief Construtor
 *        Construct JsonWriter from JsonValue
 *
 * @param value JsonValue reference
 */
JsonWriter::JsonWriter(const JsonValue &value)
  : _jsonValue(value), _depth(0)
{
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Write JsonValue into string.
 *
 * @param text String reference to store json text data.
 * @param value JsonValue to be stored into text.
 */
void JsonWriter::write(std::string &text, const JsonValue &value)
{
  JsonWriter writer(value);
  writer.toString(text);
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Generate text representation of JsonObject.
 *
 * @param output String reference to store json text data.
 */
void JsonWriter::toString(std::string &output)
{
  generate(output);
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Generate text representation of JsonObject.
 *
 * @param output String reference to store json text data.
 */
void JsonWriter::generate(std::string &output)
{
  write(_jsonValue);
  output = _output;
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Write JsonValue into string.
 *
 * @param value JsonValue to store in json text data.
 */
void JsonWriter::write(const JsonValue &value)
{
  switch(value.getType())
  {
  case VInt:
    _output += base::to_string(value.getInt());
    break;
  case VBoolean:
    _output += value.getBool() ? "true" : "false";
    break;
  case VString:
    write(value.getString());
    break;
  case VDouble:
    _output += base::to_string(value.getDouble());
    break;
  case VInt64:
    _output += base::to_string(value.getInt64());
    break;
  case VUint64:
    _output += base::to_string(value.getUint64());
    break;
  case VObject:
    write(value.getObject());
    break;
  case VArray:
    write(value.getArray());
    break;
  case VEmpty:
    _output += "null";
    break;
  default: break;
  }
}


//--------------------------------------------------------------------------------------------------

/**
 * @brief Write JsonObject value.
 *
 * @param value JsonObject to store in json text data.
 */
void JsonWriter::write(const JsonObject &value)
{
  _output += "{";
  ++_depth;
  JsonObject::ConstIterator end = value.end();
  JsonObject::ConstIterator finalIter = end;
  if (!value.empty())
  {
    _output += "\n";
    --finalIter;
  }
  for (JsonObject::ConstIterator it = value.begin();  it != end; ++it)
  {
    _output += std::string(_depth, '\t');
    write(it->first);
    _output += " : ";
    write(it->second);
    if (it != finalIter)
      _output += ",";
    _output += "\n";
  }
  --_depth;
  _output += std::string(_depth, '\t');
  _output += "}";
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Write JsonArray value.
 *
 * @param value JsonArray to store in json text data.
 */
void JsonWriter::write(const JsonArray &value)
{
  _output += "[";
  ++_depth;
  JsonArray::ConstIterator end = value.end();
  JsonArray::ConstIterator finalIter = end;
  if (!value.empty())
  {
    _output += "\n";
    --finalIter;
  }
  for (JsonArray::ConstIterator it = value.cbegin(); it != end; ++it)
  {
    _output += std::string(_depth, '\t');
    write(*it);
    if (it != finalIter)
      _output += ",";
    _output += "\n";
  }
  --_depth;
  _output += std::string(_depth, '\t');
  _output += "]";
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Write string value.
 *
 * @param value String to store in json text.
 */
void JsonWriter::write(const std::string &value)
{
  _output += '"';
  _output += base::escape_json_string(value);
  _output += '"';
}

//--------------------------------------------------------------------------------------------------

// JSON Control Implementation

/**
 * @brief Find node in tree recursively.
 *
 * parent Parent node reference
 * text Text to find.
 * founded Map reference to save results.
 */
static void findNode(TreeNodeRef parent, const std::string &text, JsonTreeBaseView::TreeNodeVectorMap &found)
{
  if (parent.is_valid())
  {
    TreeNodeRef node = parent;
    if (base::contains_string(node->get_string(1), text, false))
      found[text].push_back(node);
    int count = node->count();
    for (int i = 0; i < count; ++i)
    {
      TreeNodeRef child(node->get_child(i));
      if (child)
        findNode(child, text, found);
    }
  }
}


//--------------------------------------------------------------------------------------------------

/**
 * @brief default constructor.
 *
 */
JsonBaseView::JsonBaseView() : Panel(TransparentPanel)
{
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief default destructor.
 *
 */
JsonBaseView::~JsonBaseView()
{
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief
 *
 * @return
 */
bool JsonBaseView::getNeedRepaint() const
{
  return _needRepaint;
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief
 *
 * @return
 */
void JsonBaseView::setNeedRepaint(bool value)
{
  _needRepaint = value;
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Clear control.
 *
 */
void JsonBaseView::clear()
{
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief default constructor.
 *
 */
JsonTreeBaseView::JsonTreeBaseView()
  : _useFilter(false), _searchIdx(0)
{
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief default destructor.
 *
 */
JsonTreeBaseView::~JsonTreeBaseView()
{
}

/**
 * @brief Insert object value to the tree.
 *
 * @param value JsonValue to put in tree.
 * @param node Tree node reference.
 * @param addNew If true add as child node.
 */
void JsonTreeBaseView::generateObjectInTree(JsonParser::JsonValue &/*value*/, TreeNodeRef /*node*/, bool /*addNew*/)
{
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Insert array value to the tree.
 *
 * @param value JsonValue to put in tree.
 * @param node Tree node reference.
 * @param addNew If true add as child node.
 */
void JsonTreeBaseView::generateArrayInTree(JsonParser::JsonValue &/*value*/, TreeNodeRef /*node*/, bool /*addNew*/)
{
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Insert string value to the tree.
 *
 * @param value JsonValue to put in tree.
 * @param node Tree node reference.
 */
void JsonTreeBaseView::generateStringInTree(JsonParser::JsonValue &/*value*/, TreeNodeRef /*node*/)
{
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Insert bool value to the tree.
 *
 * @param value JsonValue to put in tree.
 * @param node Tree node reference.
 */
void JsonTreeBaseView::generateBoolInTree(JsonParser::JsonValue &/*value*/, TreeNodeRef /*node*/)
{
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Insert number value to the tree.
 *
 * @param value JsonValue to put in tree.
 * @param node Tree node reference.
 */
void JsonTreeBaseView::generateNumberInTree(JsonParser::JsonValue &/*value*/, TreeNodeRef /*node*/)
{
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Insert null to tree.
 *
 * @param node Tree node reference.
 */
void JsonTreeBaseView::generateNullInTree(JsonParser::JsonValue &/*value*/, TreeNodeRef /*node*/)
{
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Highlight matches in tree view.
 *
 * @param text Text to find.
 * @param backward Search backward.
 */
void JsonTreeBaseView::highlightMatchNode(const std::string &text, bool backward)
{
  if (_textToFind != text)
  {
    _textToFind = text;
    _searchIdx = 0;
  }
  bool needSearch = false;
  TreeNodeVectorMap::iterator it = _viewFindResult.find(text);
  if (it != _viewFindResult.end())
  {
    if (_searchIdx >= it->second.size())
      _searchIdx = 0;
    TreeNodeRef node = it->second[_searchIdx];
    if (base::contains_string(node->get_string(1), text, false))
    {
      _treeView->select_node(node);
      //_treeView->scrollToNode(node);
      _searchIdx++;
    }
    else
    {
      _viewFindResult.erase(text);
      needSearch = true;
    }
  }
  else
    needSearch = true;
  if (needSearch)
  {
    _searchIdx = 0;
    TreeNodeRef node = _treeView->get_selected_node();
    if (!node.is_valid())
      node = _treeView->root_node();

    findNode(node, text, _viewFindResult);
    TreeNodeVectorMap::iterator it = _viewFindResult.find(text);
    if (it != _viewFindResult.end())
    {
      TreeNodeRef node = it->second[_searchIdx];
      _treeView->select_node(node);
      //_treeView->scrollToNode(node);
      _treeView->focus();
    }
  }
}


//--------------------------------------------------------------------------------------------------

/**
 * @brief Find parents.
 *
 * @param node Tree node reference.
 * @param parents List of returned parents.
 */
void JsonTreeBaseView::collectParents(TreeNodeRef node, std::list<TreeNodeRef> &parents)
{
  TreeNodeRef parent = node->get_parent();
  if (parent->is_valid())
  {
    parents.push_back(parent);
    collectParents(parent, parents);
  }
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Restore oryginal result.
 *
 * @param value Json value reference.
 */
void JsonTreeBaseView::restoreOrygilanResult(JsonParser::JsonValue &value)
{
  _useFilter = false;
  _treeView->clear();
  generateTree(value, _treeView->root_node());
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Filter tree view.
 *
 * @param text Text to find.
 * @param value Json value reference.
 */
bool JsonTreeBaseView::filterView(const std::string &text, JsonParser::JsonValue &value)
{
  TreeNodeRef selectedNode = _treeView->get_selected_node();
  if (!selectedNode.is_valid())
    selectedNode = _treeView->root_node();
  TreeNodeVectorMap viewFilterResult;
  findNode(selectedNode, text, viewFilterResult);
  TreeNodeVectorMap::iterator it = viewFilterResult.find(text);
  if (it != viewFilterResult.end())
  {
    boost::shared_ptr<TreeNodeList> branch(new TreeNodeList);
    TreeNodeVactor::iterator end = it->second.end();
    for(TreeNodeVactor::iterator nodeIter = it->second.begin(); nodeIter != end; ++nodeIter)
    {
      branch->push_back(*nodeIter);
      collectParents(*nodeIter, *branch);
    }
    _filterGuard.clear();
    TreeNodeRef actualNode = _treeView->root_node();
    while (!branch->empty())
    {
      TreeNodeRef node = branch->back();
      branch->pop_back();
      JsonValueNodeData *data = dynamic_cast<JsonValueNodeData*>(node->get_data());
      if (data != NULL)
      {
        JsonParser::JsonValue &jv = data->getData();
        if (_filterGuard.count(&jv))
          continue;
        _filterGuard.insert(&jv);
      }
    }
    _useFilter = true;
    _treeView->clear();
    generateTree(value, _treeView->root_node());
  }
  return _useFilter;
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Fill tree control.
 *
 * @param value JsonValue to show in tree.
 * @param node Tree node reference.
 * @param addNew True if child node should be created.
 */
void JsonTreeBaseView::generateTree(JsonParser::JsonValue &value, TreeNodeRef node, bool addNew)
{
  switch (value.getType())
  {
  case VInt:
  case VDouble:
  case VInt64:
  case VUint64:
    generateNumberInTree(value, node);
    break;
  case VBoolean:
    generateBoolInTree(value, node);
    break;
  case VString:
    generateStringInTree(value, node);
    break;
  case VObject:
    generateObjectInTree(value, node, addNew);
    break;
  case VArray:
    generateArrayInTree(value, node, addNew);
    break;
  case VEmpty:
    generateNullInTree(value, node);
    break;
  default:
    break;
  }
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief callback to handle changed made by user to tree cells.
 *
 * @param node Tree node reference, which was edited.
 * @param column Column number which was edited.
 * @param value New string value to set.
 */
void JsonTreeBaseView::setCellValue(mforms::TreeNodeRef node, int column, const std::string &value)
{
  JsonValueNodeData* data = dynamic_cast<JsonValueNodeData*>(node->get_data());
  bool setData = false;
  if (data != NULL)
  {
    std::stringstream buffer;
    double number = 0;
    int64_t number2 = 0;
    uint64_t number3 = 0;
    bool retBool = false;
    JsonParser::JsonValue &storedValue = data->getData();
    switch (storedValue.getType())
    {
    case VDouble:
    case VInt:
      if (!base::is_number(value))
        break;
      buffer << value;
      buffer >> number;
      storedValue.setNumber(number);
      setData = true;
      break;
    case VInt64:
      if (!base::is_number(value))
        break;
      buffer << value;
      buffer >> number2;
      storedValue.setInt64(number2);
      setData = true;
      break;
    case VUint64:
      if (!base::is_number(value))
        break;
      buffer << value;
      buffer >> number3;
      storedValue.setUint64(number3);
      setData = true;
      break;
    case VBoolean:
      if (!base::isBool(value))
        break;
      buffer << value;
      buffer >> std::boolalpha >> retBool;
      storedValue.setBool(retBool);
      setData = true;
      break;
    case VString:
      storedValue.setString(value);
      setData = true;
      break;
    default:
      break;
    }
  }
  if (setData)
  {
    node->set_string(column, value);
    node->set_attributes(column, mforms::TextAttributes("#c6c6c6", true, true));
    //_needRepaint = true;
  }
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Default constructor
 *
 */
JsonTextView::JsonTextView() : _textEditor(boost::make_shared<CodeEditor>())
{
  init();
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Fill text in control
 *
 * @param jsonTExt A string that contains the json text data to set..
 */
void JsonTextView::setText(const std::string &jsonText)
{
  _textEditor->set_value(jsonText.c_str());
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Destructor.
 *
 */
JsonTextView::~JsonTextView()
{
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Clear control.
 *
 */
void JsonTextView::clear()
{
  _textEditor->set_value("");
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Init controls in text tab control.
 *
 */
void JsonTextView::init()
{
  assert(_textEditor.get() != NULL);
  _textEditor->set_language(mforms::LanguageJson);
  _textEditor->set_features(mforms::FeatureWrapText, false);
  _textEditor->set_features(mforms::FeatureReadOnly, false);
  add(_textEditor.get());
}

void JsonTextView::findAndHighlightText(const std::string &text, bool backward /*= false*/)
{
  _textEditor->find_and_highlight_text(text, mforms::FindDefault, true, backward);
}


//--------------------------------------------------------------------------------------------------

/**
 * @brief Constructor
 *
 */
JsonTreeView::JsonTreeView()
{
  _treeView.reset(new mforms::TreeNodeView(TreeNoBorder | TreeShowColumnLines));
  _treeView->add_column(IconStringColumnType, "", 150, false, true);
  _treeView->add_column(StringColumnType, "Value", 200, false, true);
  _treeView->end_columns();
  _treeView->set_cell_edit_handler(boost::bind(&JsonTreeBaseView::setCellValue, this, _1, _2, _3));
  init();
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Destructor
 *
 */
JsonTreeView::~JsonTreeView()
{
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Init tree view
 *
 * Based of readed json data control function initialize mforms control TreNodeView
 */
void JsonTreeView::init()
{
  assert(_treeView.get() != NULL);
  add(_treeView.get());
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Add Json data to the control.
 *
 * @param value A JsonValue object to show in control.
 */
void JsonTreeView::setJson(JsonParser::JsonValue &value)
{
  clear();
  TreeNodeRef node = _treeView->root_node();
  node->set_data(new JsonTreeBaseView::JsonValueNodeData(value));
  generateTree(value, node);
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Append Json data to the control.
 *
 * @param value A JsonValue object to show in control.
 */
void JsonTreeView::appendJson(JsonParser::JsonValue &value)
{
  _viewFindResult.clear();
  _textToFind = "";
  _searchIdx = 0;
  TreeNodeRef node = _treeView->root_node();
  generateTree(value, node);
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Clear control.
 *
 */
void JsonTreeView::clear()
{
  _treeView->clear();
  _viewFindResult.clear();
  _textToFind = "";
  _searchIdx = 0;
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Insert object value to the tree.
 *
 * @param value JsonValue to put in tree.
 * @param node Tree node reference.
 * @param addNew If true add as child node.
 */
void JsonTreeView::generateObjectInTree(JsonParser::JsonValue &value, TreeNodeRef node, bool addNew)
{
  if (_useFilter && _filterGuard.count(&value) == 0)
    return;
  JsonObject &object = value.getObject();
  size_t size = 0;
  std::stringstream textSize;
  JsonObject::Iterator end = object.end();
  for (JsonObject::Iterator it = object.begin(); it != end; ++it)
  {
    std::string text = it->first;
    switch (it->second.getType())
    {
      case VArray:
      {
        JsonArray &arrayVal = it->second.getArray();
        size = arrayVal.size();
        textSize << size;
        text += "[";
        text += textSize.str();
        text += "]";
        break;
      }
      case VObject:
      {
        JsonObject &objectVal = it->second.getObject();
        size = objectVal.size();
        textSize << size;
        text += "{";
        text += textSize.str();
        text += "}";
        break;
      }

      default: // Nothing else by intention.
        break;
    }

    mforms::TreeNodeRef node2 = (addNew) ? node->add_child() : node;
    node->set_icon_path(0, "JS_Datatype_Object.png");
    node->set_data(new JsonTreeBaseView::JsonValueNodeData(value));
    node2->set_string(0, text);
    node2->set_string(1, "");
    generateTree(it->second, node2);
    node2->expand();
  }
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Insert array value to the tree.
 *
 * @param value JsonValue to put in tree.
 * @param node Tree node reference.
 * @param addNew If true add as child node.
 */
void JsonTreeView::generateArrayInTree(JsonParser::JsonValue &value, TreeNodeRef node, bool addNew)
{
  if (_useFilter && _filterGuard.count(&value) == 0)
    return;
  JsonArray &arrayType = value.getArray();
  JsonArray::SizeType size = arrayType.size();
  std::stringstream textSize;
  textSize << size;
  std::string text = "array [" + textSize.str() + "]";
  mforms::TreeNodeRef node2 = node->add_child();
  node2->set_icon_path(0, "JS_Datatype_Array.png");
  node2->set_string(0, text);
  node2->set_string(1, "");
  node2->set_data(new JsonTreeBaseView::JsonValueNodeData(value));
  JsonArray::Iterator end = arrayType.end();
  int idx = 0;
  for (JsonArray::Iterator it = arrayType.begin(); it != end; ++it, ++idx)
  {
    if (_useFilter && _filterGuard.count(&*it) == 0)
      continue;
    mforms::TreeNodeRef arrrayNode = node2->add_child();
    bool addNew = false;
    if (it->getType() == VArray || it->getType() == VObject)
      addNew = true;
    arrrayNode->set_string(0, base::strfmt("[%d]", idx));
    arrrayNode->set_string(1, "");
    generateTree(*it, arrrayNode, addNew);
  }
  node2->expand();
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Insert bool value to the tree.
 *
 * @param value JsonValue to put in tree.
 * @param node Tree node reference.
 */
void JsonTreeView::generateBoolInTree(JsonParser::JsonValue &value, TreeNodeRef node)
{
  node->set_icon_path(0, "JS_Datatype_Bool.png");
  node->set_attributes(1, mforms::TextAttributes("#0099ff", true, true));
  node->set_bool(1, value.getBool());
  node->set_data(new JsonTreeBaseView::JsonValueNodeData(value));
  node->expand();
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Insert string value to the tree.
 *
 * @param value JsonValue to put in tree.
 * @param node Tree node reference.
 */
void JsonTreeView::generateStringInTree(JsonParser::JsonValue &value, TreeNodeRef node)
{
  node->set_icon_path(0, "JS_Datatype_String.png");
  node->set_attributes(1, mforms::TextAttributes("#cc9966", false, false));
  node->set_string(1, value.getString());
  node->set_data(new JsonTreeBaseView::JsonValueNodeData(value));
  node->expand();
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Insert number value to the tree.
 *
 * @param value JsonValue to put in tree.
 * @param node Tree node reference.
 */
void JsonTreeView::generateNumberInTree(JsonParser::JsonValue &value, TreeNodeRef node)
{
  node->set_icon_path(0, "JS_Datatype_Number.png");
  node->set_attributes(1, mforms::TextAttributes("#99cc66", false, true));
  switch (value.getType())
  {
  case VInt :
    node->set_int(1, (int)value.getDouble());
    break;
  case VDouble:
    node->set_float(1, value.getDouble());
    break;
  case VInt64:
    node->set_long(1, value.getInt64());
    break;
  case VUint64:
    node->set_float(1, (float)value.getUint64());
    break;
  default:
    break;
  }
  node->set_data(new JsonTreeBaseView::JsonValueNodeData(value));
  node->expand();
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Insert null to tree.
 *
 * @param node Tree node reference.
 */
void JsonTreeView::generateNullInTree(JsonParser::JsonValue &value, TreeNodeRef node)
{
  node->set_icon_path(0, "JS_Datatype_Null.png");
  node->set_string(0, "<<null>>");
  node->set_string(1, "");
  node->set_data(new JsonTreeBaseView::JsonValueNodeData(value));
  node->expand();
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Constructor
 *
 */
JsonGridView::JsonGridView()
{
  _treeView.reset(new mforms::TreeNodeView(mforms::TreeAltRowColors | mforms::TreeShowRowLines | mforms::TreeShowColumnLines | mforms::TreeNoBorder));
  _treeView->add_column(IconStringColumnType, "Key", 150, false, true);
  _treeView->add_column(StringLTColumnType, "Value", 200, true, true);
  _treeView->add_column(StringLTColumnType, "Type", 200, false, true);
  _treeView->end_columns();
  _treeView->set_cell_edit_handler(boost::bind(&JsonTreeBaseView::setCellValue, this, _1, _2, _3));
  init();
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Init tree/grid view
 *
 * Based of readed json data control function initialize mforms control TreNodeView
 */
void JsonGridView::init()
{
  assert(_treeView.get() != NULL);
  add(_treeView.get());
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Destructor
 *
 */
JsonGridView::~JsonGridView()
{
  _treeView->clear();
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Clear control.
 *
 */
void JsonGridView::clear()
{
  _treeView->clear();
  _viewFindResult.clear();
  _textToFind = "";
  _searchIdx = 0;
  _useFilter = false;
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Add the Json data to the control.
 *
 * @param value A JsonValue object to show in control.
 */
void JsonGridView::setJson(JsonParser::JsonValue &value)
{
  clear();
  TreeNodeRef node = _treeView->root_node()->add_child();
  generateTree(value, node);
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Append Json data to the control.
 *
 * @param value A JsonValue object to show in control.
 */
void JsonGridView::appendJson(JsonParser::JsonValue &value)
{
  TreeNodeRef node = _treeView->root_node();
  _viewFindResult.clear();
  _textToFind = "";
  _searchIdx = 0;
  generateTree(value, node);
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Insert object value to the tree
 *
 * @param value JsonValue to put in tree
 * @param node Tree node reference
 * @param addNew If true add as child node
 */
void JsonGridView::generateObjectInTree(JsonParser::JsonValue &value, TreeNodeRef node, bool addNew)
{
  if (_useFilter && _filterGuard.count(&value) == 0)
    return;
  JsonObject &object = value.getObject();
  size_t size = 0;
  std::stringstream textSize;
  JsonObject::Iterator end = object.end();
  for (JsonObject::Iterator it = object.begin(); it != end; ++it)
  {
    std::string text = it->first;
    switch (it->second.getType())
    {
    case VArray:
    {
      JsonArray &arrayVal = it->second.getArray();
      size = arrayVal.size();
      textSize << size;
      text += "[";
      text += textSize.str();
      text += "]";
      break;
    }
    case VObject:
    {
      JsonObject &objectVal = it->second.getObject();
      size = objectVal.size();
      textSize << size;
      text += "{";
      text += textSize.str();
      text += "}";
      break;
    }
    default:
      break;
    }
    mforms::TreeNodeRef node2 = (addNew) ? node->add_child() : node;
    node->set_icon_path(0, "JS_Datatype_Object.png");
    node->set_string(1, "");
    node->set_string(2, "Object");
    node->set_data(new JsonTreeBaseView::JsonValueNodeData(value));
    node2->set_string(0, text);
    generateTree(it->second, node2);
    node2->expand();
  }
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Insert array value to the tree
 *
 * @param value JsonValue to put in tree
 * @param node Tree node reference
 * @param addNew If true add as child node
 */
void JsonGridView::generateArrayInTree(JsonParser::JsonValue &value, TreeNodeRef node, bool addNew)
{
  if (_useFilter && _filterGuard.count(&value) == 0)
    return;
  JsonParser::JsonArray &arrayType = value.getArray();
  JsonArray::SizeType size = arrayType.size();
  std::stringstream textSize;
  textSize << size;
  std::string text = "array [" + textSize.str() + "]";
  mforms::TreeNodeRef node2 = node->add_child();
  node2->set_icon_path(0, "JS_Datatype_Array.png");
  node2->set_string(0, text);
  node2->set_string(1, "");
  node2->set_string(2, "Array");
  node2->set_data(new JsonTreeBaseView::JsonValueNodeData(value));
  JsonArray::Iterator end = arrayType.end();
  int idx = 0;
  for (JsonArray::Iterator it = arrayType.begin(); it != end; ++it, ++idx)
  {
    if (_useFilter && _filterGuard.count(&*it) == 0)
      continue;
    mforms::TreeNodeRef arrrayNode = node2->add_child();
    bool addNew = false;
    if (it->getType() == VArray || it->getType() == VObject)
      addNew = true;
    arrrayNode->set_string(0, base::strfmt("[%d]", idx));
    arrrayNode->set_string(1, "");
    generateTree(*it, arrrayNode, addNew);
  }
  node2->expand();
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Insert bool value to the tree
 *
 * @param value JsonValue to put in tree
 * @param node Tree node reference
 */
void JsonGridView::generateBoolInTree(JsonParser::JsonValue &value, TreeNodeRef node)
{
  node->set_icon_path(0, "JS_Datatype_Bool.png");
  node->set_attributes(1, mforms::TextAttributes("#0099ff", true, true));
  node->set_bool(1, value.getBool());
  node->set_string(2, "Boolean");
  node->set_data(new JsonTreeBaseView::JsonValueNodeData(value));
  node->expand();
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Insert string value to the tree
 *
 * @param value JsonValue to put in tree
 * @param node Tree node reference
 */
void JsonGridView::generateStringInTree(JsonParser::JsonValue &value, TreeNodeRef node)
{
  node->set_icon_path(0, "JS_Datatype_String.png");
  node->set_attributes(1, mforms::TextAttributes("#cc9966", false, false));
  node->set_string(1, value.getString());
  node->set_string(2, "String");
  node->set_data(new JsonTreeBaseView::JsonValueNodeData(value));
  node->expand();
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Insert double value to the tree
 *
 * @param value JsonValue to put in tree
 * @param node Tree node reference
 */
void JsonGridView::generateNumberInTree(JsonParser::JsonValue &value, TreeNodeRef node)
{
  node->set_icon_path(0, "JS_Datatype_Number.png");
  node->set_attributes(1, mforms::TextAttributes("#99cc66", false, true));
  switch (value.getType())
  {
  case VInt:
    node->set_int(1, (int)value.getDouble());
    node->set_string(2, "Integer");
    break;
  case VDouble:
    node->set_float(1, value.getDouble());
    node->set_string(2, "Double");
    break;
  case VInt64:
    node->set_long(1, value.getInt64());
    node->set_string(2, "Long Integer");
    break;
  case VUint64:
    node->set_float(1, (float)value.getUint64());
    node->set_string(2, "Unsigned Long Integer");
    break;
  default:
    break;
  }
  node->set_data(new JsonTreeBaseView::JsonValueNodeData(value));
  node->expand();
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Insert null value to the tree
 *
 * @param node Tree node reference
 */
void JsonGridView::generateNullInTree(JsonParser::JsonValue &value, TreeNodeRef node)
{
  node->set_icon_path(0, "JS_Datatype_Null.png");
  node->set_string(0, "<<null>>");
  node->set_string(1, "");
  node->set_string(2, "null");
  node->set_data(new JsonTreeBaseView::JsonValueNodeData(value));
  node->expand();
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief
 *
 * @param
 * @return
 */
void JsonTabView::Setup()
{
  assert(_tabView.get() != NULL);
  _tabView->set_name("json_editor:tab");
  boost::get<0>(_tabId) = _tabView->add_page(_textView.get(), "Text");
  boost::get<1>(_tabId) = _tabView->add_page(_treeView.get(), "Tree");
  boost::get<2>(_tabId) = _tabView->add_page(_gridView.get(), "Grid");
  add(_tabView.get());
  scoped_connect(_tabView->signal_tab_changed(), boost::bind(&JsonTabView::tabChanged, this));
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Constructor
 *
 */
JsonTabView::JsonTabView() : Panel(TransparentPanel), _textView(boost::make_shared<JsonTextView>()),
  _treeView(boost::make_shared<JsonTreeView>()), _gridView(boost::make_shared<JsonGridView>()),
  _tabView(boost::make_shared<TabView>(TabViewPalette))
{
  Setup();
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Destructor
 *
 */
JsonTabView::~JsonTabView()
{
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Add the Json data to the control.
 *
 * @param value A JsonValue object that contains the json text data to set.
 */
void JsonTabView::setJson(const JsonParser::JsonValue &value)
{
  _json = boost::make_shared<JsonParser::JsonValue>(value);
  _ident = 0;
  JsonWriter::write(_jsonText, value);
  _textView->setText(_jsonText);
  _treeView->setJson(*_json);
  _gridView->setJson(*_json);
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Set json text. 
 *
 * @param text String to set in control.
 */
void JsonTabView::setText(const std::string &text)
{
  _jsonText = text;
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Append text to JSON textview control
 *
 * @param value JSON data to append
 */
void JsonTabView::append(const std::string &text)
{
  _jsonText += text;
  _textView->setText(_jsonText);

  JsonParser::JsonValue value;
  JsonParser::JsonReader::read(text, value);
  _json = boost::make_shared<JsonParser::JsonValue>(value);
  _treeView->appendJson(*_json);
  _gridView->appendJson(*_json);
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Signal emitted when the tab is switched by user.
 *
 */
void JsonTabView::tabChanged()
{
  if(_gridView->getNeedRepaint())
  {
    _gridView->setNeedRepaint(false);
  }
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Clear control
 *
 */
void JsonTabView::clear()
{

  _jsonText.clear();
  _textView->clear();
  _treeView->clear();
  _gridView->clear();
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Highlight match in control.
 *
 * text Text to find.
 */
void JsonTabView::highlightMatch(const std::string &text)
{
  _matchText = text;
  int tabId = _tabView->get_active_tab();
  if (tabId == boost::get<0>(_tabId))
  {
    _textView->findAndHighlightText(text);
  }
  else if (tabId == boost::get<1>(_tabId))
  {
    _treeView->highlightMatchNode(text);
  }
  else if (tabId == boost::get<2>(_tabId))
  {
    _gridView->highlightMatchNode(text);
  }

}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Highlight next matches in JSON view.
 *
 */
void JsonTabView::highlightNextMatch()
{
  int tabId = _tabView->get_active_tab();
  if (tabId == boost::get<0>(_tabId) && !_matchText.empty())
  {
    _textView->findAndHighlightText(_matchText);
  }
  else if (tabId == boost::get<1>(_tabId) && !_matchText.empty())
  {
    _treeView->highlightMatchNode(_matchText);
  }
  else if (tabId == boost::get<2>(_tabId) && !_matchText.empty())
  {
    _gridView->highlightMatchNode(_matchText);
  }
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Highlight next match in JSON view.
 *
 */
void JsonTabView::highlightPreviousMatch()
{
  int tabId = _tabView->get_active_tab();
  if (tabId == boost::get<0>(_tabId) && !_matchText.empty())
  {
    _textView->findAndHighlightText(_matchText, true);
  }
  else if (tabId == boost::get<1>(_tabId) && !_matchText.empty())
  {
    _treeView->highlightMatchNode(_matchText, true);
  }
  else if (tabId == boost::get<2>(_tabId) && !_matchText.empty())
  {
    _gridView->highlightMatchNode(_matchText, true);
  }
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Highlight match in control.
 *
 * text Text to find.
 */
bool JsonTabView::filterView(const std::string &text)
{
  int tabId = _tabView->get_active_tab();
  bool ret = false;
  if (tabId == boost::get<0>(_tabId))
  {
    return false; //no filtering for text view
  }
  else if (tabId == boost::get<1>(_tabId))
  {
    ret = _treeView->filterView(text, *_json);
  }
  else if (tabId == boost::get<2>(_tabId))
  {
    ret = _gridView->filterView(text, *_json);
  }
  return ret;
}

//--------------------------------------------------------------------------------------------------

/**
 * @brief Disable filtering.
 *
 * text Text to find.
 */
void JsonTabView::restoreOrginalResult()
{
  int tabId = _tabView->get_active_tab();
  if (tabId == boost::get<0>(_tabId))
  {
    return;
  }
  else if (tabId == boost::get<1>(_tabId))
  {
    _treeView->restoreOrygilanResult(*_json);
  }
  else if (tabId == boost::get<2>(_tabId))
  {
    _gridView->restoreOrygilanResult(*_json);
  }
}

//
// Element.h
//
// $Id$
//
// Library: MongoDB
// Package: MongoDB
// Module:  Element
//
// Definition of the Element class.
//
// Copyright (c) 2012, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
//
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//

#ifndef _MongoDB_Element_included
#define _MongoDB_Element_included

#include <string>
#include <set>

#include "Poco/BinaryReader.h"
#include "Poco/BinaryWriter.h"
#include "Poco/SharedPtr.h"
#include "Poco/Timestamp.h"
#include "Poco/RegularExpression.h"
#include "Poco/Nullable.h"
#include "Poco/NumberFormatter.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/MongoDB/MongoDB.h"
#include "Poco/MongoDB/BSONReader.h"
#include "Poco/MongoDB/BSONWriter.h"

namespace Poco
{
namespace MongoDB
{


class MongoDB_API Element
{
public:

	Element(const std::string& name);


	virtual ~Element();


	virtual std::string toString() const = 0;


	virtual int type() const = 0;


	typedef Poco::SharedPtr<Element> Ptr;

	std::string name() const;

private:

	virtual void read(BinaryReader& reader) = 0;

	virtual void write(BinaryWriter& writer) = 0;

	friend class Document;

	std::string _name;
};


inline std::string Element::name() const
{
	return _name;
}

class ElementComparator
{
public:
	bool operator()(const Element::Ptr& s1, const Element::Ptr& s2)
	{
		return s1->name() < s2->name();
	}
};


typedef std::set<Element::Ptr, ElementComparator> ElementSet;


template<typename T> 
struct ElementTraits
{
};

// BSON Floating point
// spec: double
template<>
struct ElementTraits<double>
{
	enum { TypeId = 0x01 };

	static std::string toString(const double& value)
	{
		return Poco::NumberFormatter::format(value);
	}
};

// BSON UTF-8 string
// spec: int32 (byte*) "\x00"
// int32 is the number bytes in byte* + 1 (for trailing "\x00"
template<>
struct ElementTraits<std::string>
{
	enum { TypeId = 0x02 };

	static std::string toString(const std::string& value)
	{
		return value;
	}
};

template<>
inline void BSONReader::read<std::string>(std::string& to)
{
	Poco::Int32 size;
	_reader >> size;
	_reader.readRaw(size, to);
	to.erase(to.end() - 1); // remove terminating 0
}

template<>
inline void BSONWriter::write<std::string>(std::string& from)
{
	_writer << (Poco::Int32) (from.length() + 1);
	writeCString(from);
}



// BSON bool
// spec: "\x00" "\x01"
template<>
struct ElementTraits<bool>
{
	enum { TypeId = 0x08 };

	static std::string toString(const bool& value)
	{
		return value ? "true" : "false";
	}
};

template<>
inline void BSONReader::read<bool>(bool& to)
{
	Int32 b;
	_reader >> b;
	to = b != 0;
}

template<>
inline void BSONWriter::write<bool>(bool& from)
{
	_writer << (from ? 0x01 : 0x00);
}

// BSON 32-bit integer
// spec: int32
template<>
struct ElementTraits<Int32>
{
	enum { TypeId = 0x10 };


	static std::string toString(const Int32& value)
	{
		return Poco::NumberFormatter::format(value);
	}
};

// BSON UTC datetime
// spec: int64
template<>
struct ElementTraits<Timestamp>
{
	enum { TypeId = 0x09 };

	static std::string toString(const Timestamp& value)
	{
		return DateTimeFormatter::format(value, "%Y-%m-%dT%H:%M:%s%z");
	}
};

template<>
inline void BSONReader::read<Timestamp>(Timestamp& to)
{
	Poco::Int64 value;
	_reader >> value;
	to = Timestamp::fromEpochTime(value / 1000);
	to += (value % 1000 * 1000);
}

template<>
inline void BSONWriter::write<Timestamp>(Timestamp& from)
{
	_writer << (from.epochMicroseconds() / 1000);
}

typedef Nullable<unsigned char> NullValue;

// BSON Null Value
// spec:
template<>
struct ElementTraits<NullValue>
{
	enum { TypeId = 0x0A };

	static std::string toString(const NullValue& value)
	{
		return "null";
	}
};

template<>
inline void BSONReader::read<NullValue>(NullValue& to)
{
}

template<>
inline void BSONWriter::write<NullValue>(NullValue& from)
{
}


class RegularExpression
{
public:

	typedef SharedPtr<RegularExpression> Ptr;


	RegularExpression()
	{
	}
	
	
	RegularExpression(const std::string& pattern, const std::string& options) : _pattern(pattern), _options(options) {}

	
	virtual ~RegularExpression()
	{
	}

	
	std::string getPattern() const;

	
	void setPattern(const std::string& pattern);


	std::string getOptions() const;


	void setOptions(const std::string& options);


	SharedPtr<Poco::RegularExpression> createRE()
	{
		int options = 0;
		for(std::string::iterator optIt = _options.begin(); optIt != _options.end(); ++optIt)
		{
			switch(*optIt)
			{
			case 'i': // Case Insensitive
				options |= Poco::RegularExpression::RE_CASELESS;
				break;
			case 'm': // Multiline matching
				options |= Poco::RegularExpression::RE_MULTILINE;
				break;
			case 'x': // Verbose mode
				//No equivalent in Poco
				break;
			case 'l': // \w \W Locale dependent
				//No equivalent in Poco
				break;
			case 's': // Dotall mode
				options |= Poco::RegularExpression::RE_DOTALL;
				break;
			case 'u': // \w \W Unicode
				//No equivalent in Poco
				break;
			}
		}
		return new Poco::RegularExpression(_pattern, options);
	}


private:

	std::string _pattern;
	std::string _options;
};


inline std::string RegularExpression::getPattern() const
{
	return _pattern;
}


inline void RegularExpression::setPattern(const std::string& pattern)
{
	_pattern = pattern;
}


inline std::string RegularExpression::getOptions() const
{
	return _options;
}


inline void RegularExpression::setOptions(const std::string& options)
{
	_options = options;
}

// BSON Regex
// spec: cstring cstring
template<>
struct ElementTraits<RegularExpression::Ptr>
{
	enum { TypeId = 0x0B };

	static std::string toString(const RegularExpression::Ptr& value)
	{
		//TODO
		return "RE: not implemented yet";
	}
};

template<>
inline void BSONReader::read<RegularExpression::Ptr>(RegularExpression::Ptr& to)
{
	std::string pattern = readCString();
	std::string options = readCString();

	to = new RegularExpression(pattern, options);
}

template<>
inline void BSONWriter::write<RegularExpression::Ptr>(RegularExpression::Ptr& from)
{
	writeCString(from->getPattern());
	writeCString(from->getOptions());
}


class JavaScriptCode
{
public:
	typedef SharedPtr<JavaScriptCode> Ptr;


	JavaScriptCode()
	{
	}


	virtual ~JavaScriptCode()
	{
	}


	void code(const std::string& s);


	std::string code() const;

private:

	std::string _code;
};


inline void JavaScriptCode::code(const std::string& s)
{
	_code = s;
}


inline std::string JavaScriptCode::code() const
{
	return _code;
}

// BSON JavaScript code
// spec: string
template<>
struct ElementTraits<JavaScriptCode::Ptr>
{
	enum { TypeId = 0x0D };

	static std::string toString(const JavaScriptCode::Ptr& value)
	{
		return value.isNull() ? "" : value->code();
	}
};

template<>
inline void BSONReader::read<JavaScriptCode::Ptr>(JavaScriptCode::Ptr& to)
{
	std::string code;
	BSONReader(_reader).read(code);
	to = new JavaScriptCode();
	to->code(code);
}

template<>
inline void BSONWriter::write<JavaScriptCode::Ptr>(JavaScriptCode::Ptr& from)
{
	std::string code = from->code();
	BSONWriter(_writer).write(code);
}

// BSON 64-bit integer
// spec: int64
template<>
struct ElementTraits<Int64>
{
	enum { TypeId = 0x12 };

	static std::string toString(const Int64& value)
	{
		return NumberFormatter::format(value);
	}
};


template<typename T>
class ConcreteElement : public Element
{
public:
	ConcreteElement(const std::string& name, const T& init) : Element(name), _value(init)
	{
	}

	virtual ~ConcreteElement()
	{
	}

	
	T value() const { return _value; }


	std::string toString() const { return ElementTraits<T>::toString(_value); }

	
	int type() const { return ElementTraits<T>::TypeId; }


	void read(BinaryReader& reader)
	{
		BSONReader(reader).read(_value);
	}

	void write(BinaryWriter& writer)
	{
		BSONWriter(writer).write(_value);
	}

private:

	T _value;
};

}} // Namespace Poco::MongoDB

#endif //  _MongoDB_Element_included

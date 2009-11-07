//
// JSONEntity.h
//
// $Id: //poco/Main/Web/include/Poco/Web/JSONEntity.h#2 $
//
// Library: Web
// Package: Configuration
// Module:  JSONEntity
//
// Definition of the JSONEntity class.
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
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


#ifndef Web_JSONEntity_INCLUDED
#define Web_JSONEntity_INCLUDED


#include "Poco/Web/Web.h"
#include "Poco/Dynamic/Var.h"


namespace Poco {
namespace Web {


class Web_API JSONEntity
{
public:
	enum Type
	{
		JSON_T_NONE = 0,
		JSON_T_ARRAY_BEGIN,
		JSON_T_ARRAY_END,
		JSON_T_OBJECT_BEGIN,
		JSON_T_OBJECT_END,
		JSON_T_INTEGER,
		JSON_T_FLOAT,
		JSON_T_NULL,
		JSON_T_TRUE,
		JSON_T_FALSE,
		JSON_T_STRING,
		JSON_T_KEY,
		JSON_T_VALUE_SEPARATOR,
		JSON_T_MAX
	};
#ifdef POCO_HAVE_INT64
	typedef Poco::Int64 Integer;
#else
	typedef Poco::Int32 Integer;
#endif
	typedef double Float;
	typedef std::string String;
	
	typedef std::size_t Length;

	JSONEntity();
		/// Creates empty JSONEntity.

	JSONEntity(Type type, const Poco::Dynamic::Var& value = Poco::Dynamic::Var());
		/// Creates JSONEntity.

	~JSONEntity();
		/// Destroys JSONEntity.

	Type type() const;

	void setFloat(Float val);
	void setString(const String& val);

	Integer toInteger() const;
	Float   toFloat() const;
	String  toString() const;

	static std::string encode(const String& str);

private:
	void swap(JSONEntity& other);

	Type               _type;
	Poco::Dynamic::Var _value;
};


Web_API std::ostream& operator << (std::ostream &os, const JSONEntity& ent);

//
// inlines
//

inline JSONEntity::Integer JSONEntity::toInteger() const
{
	if (JSON_T_INTEGER != _type)
		throw InvalidAccessException("Not an integer value.");

	return _value.extract<Integer>();
}


inline JSONEntity::Float JSONEntity::toFloat() const
{
	if (JSON_T_FLOAT != _type)
		throw InvalidAccessException("Not a float value.");

	return _value.extract<Float>();
}


inline JSONEntity::String JSONEntity::toString() const
{
	if (JSON_T_STRING != _type && JSON_T_KEY != _type)
		throw InvalidAccessException("Not a string or key.");

	return encode(_value.extract<String>());
}


inline JSONEntity::Type JSONEntity::type() const
{
	return _type;
}


} } // namespace Poco::Web


#endif // Web_JSONEntity_INCLUDED

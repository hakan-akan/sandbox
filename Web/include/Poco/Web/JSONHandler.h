//
// JSONHandler.h
//
// $Id: //poco/Main/Web/include/Poco/Web/JSONHandler.h#2 $
//
// Library: Web
// Package: Configuration
// Module:  JSONHandler
//
// Definition of the JSONHandler class.
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


#ifndef Web_JSONHandler_INCLUDED
#define Web_JSONHandler_INCLUDED


#include "Poco/Web/Web.h"
#include "Poco/Web/JSONEntity.h"
#include "Poco/SharedPtr.h"


namespace Poco {
namespace Web {


class Web_API JSONHandler
	/// JSON event handler class. Serves as a base class for user-defined handlers.
	/// The default event handling implementations do nothing. To do the desired work,
	/// an implementation should override the events of interest.
{
public:
	typedef Poco::SharedPtr<JSONHandler> Ptr;

	JSONHandler();
		/// Creates JSONHandler.

	JSONHandler(std::ostream& out);
		/// Creates JSONHandler.

	virtual ~JSONHandler();
		/// Destroys JSONHandler.

	virtual void handleBegin();
		/// Does nothing. Should be implemented in inheriting class 
		/// to handle the begin event.

	virtual void handleArrayBegin();
		/// Does nothing. Should be implemented in inheriting class 
		/// to handle the array begin event.

	virtual void handleArrayEnd();
		/// Does nothing. Should be implemented in inheriting class 
		/// to handle the array end event.

	virtual void handleObjectBegin();
		/// Does nothing. Should be implemented in inheriting class 
		/// to handle the object begin event.

	virtual void handleObjectEnd();
		/// Does nothing. Should be implemented in inheriting class 
		/// to handle the object end event.

	virtual void handleValueSeparator();
		/// Does nothing. Should be implemented in inheriting class 
		/// to handle the value separator (",").

	virtual void handleInteger(const JSONEntity&);
		/// Does nothing. Should be implemented in inheriting class 
		/// to handle the integer event.

	virtual void handleFloat(const JSONEntity&);
		/// Does nothing. Should be implemented in inheriting class 
		/// to handle the float event.

	virtual void handleNull();
		/// Does nothing. Should be implemented in inheriting class 
		/// to handle the null event.

	virtual void handleTrue();
		/// Does nothing. Should be implemented in inheriting class 
		/// to handle the true event.

	virtual void handleFalse();
		/// Does nothing. Should be implemented in inheriting class 
		/// to handle the false event.

	virtual void handleKey(const JSONEntity&);
		/// Does nothing. Should be implemented in inheriting class 
		/// to handle the key event.

	virtual void handleString(const JSONEntity&);
		/// Does nothing. Should be implemented in inheriting class 
		/// to handle the string event.

	virtual void handleEnd();
		/// Does nothing. Should be implemented in inheriting class 
		/// to handle the end event.

	void handle(const JSONEntity& entity);
		/// Dispatcher. Calls apropriate handler for the entity.

protected:
	std::ostream& stream();
		/// Returns the stream.

	bool isKey() const;
	void setKey(bool key);

	std::size_t level() const;
	void incrementLevel(std::size_t incVal = 1);
	void decrementLevel(std::size_t decVal = 1);

private:

	std::size_t   _level;
	bool          _isKey;
	std::ostream* _pOut;
};


//
// inlines
//
inline void JSONHandler::handleBegin()
{
}


inline void JSONHandler::handleArrayBegin()
{
}


inline void JSONHandler::handleArrayEnd()
{
}


inline void JSONHandler::handleObjectBegin()
{
}


inline void JSONHandler::handleObjectEnd()
{
}


inline void JSONHandler::handleValueSeparator()
{
}


inline void JSONHandler::handleInteger(const JSONEntity&)
{
}


inline void JSONHandler::handleFloat(const JSONEntity&)
{
}


inline void JSONHandler::handleNull()
{
}


inline void JSONHandler::handleTrue()
{
}


inline void JSONHandler::handleFalse()
{
}


inline void JSONHandler::handleKey(const JSONEntity&)
{
}


inline void JSONHandler::handleString(const JSONEntity&)
{
}


inline void JSONHandler::handleEnd()
{
}


inline std::ostream& JSONHandler::stream()
{
	poco_check_ptr (_pOut);
	return *_pOut;
}


inline bool JSONHandler::isKey() const
{
	return _isKey;
}


inline void JSONHandler::setKey(bool isKey)
{
	_isKey = isKey;
}


inline std::size_t JSONHandler::level() const
{
	return _level;
}


inline void JSONHandler::incrementLevel(std::size_t incVal)
{
	_level += incVal;
}


inline void JSONHandler::decrementLevel(std::size_t decVal)
{
	_level -= decVal;
}


} } // namespace Poco::Web


#endif // Web_JSONHandler_INCLUDED

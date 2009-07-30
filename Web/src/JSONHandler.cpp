//
// JSONHandler.cpp
//
// $Id: //poco/Main/Web/src/JSONHandler.cpp#7 $
//
// Library: Web
// Package: Configuration
// Module:  JSONHandler
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


#include "Poco/Web/JSONHandler.h"
#include "Poco/Web/JSONParser.h"
#include "Poco/Web/JSONEntity.h"


namespace Poco {
namespace Web {


JSONHandler::JSONHandler(): _level(0), _isKey(false)
{
}


JSONHandler::~JSONHandler()
{
}


void JSONHandler::handle(const JSONEntity& value)
{
	switch(value.type())
	{
	case JSONEntity::JSON_T_ARRAY_BEGIN:    
		handleArrayBegin();
		setKey(false);
		incrementLevel();
		break;

	case JSONEntity::JSON_T_ARRAY_END:
		poco_assert(!isKey());
		if (level() > 0)
			decrementLevel();
		handleArrayEnd();
		break;

	case JSONEntity::JSON_T_OBJECT_BEGIN:
		handleObjectBegin();
		setKey(false);
		incrementLevel();
		break;
		
	case JSONEntity::JSON_T_OBJECT_END:
		poco_assert(!isKey());
		if (level() > 0)
			decrementLevel();
		handleObjectEnd();
		break;

	case JSONEntity::JSON_T_INTEGER:
		{
		handleInteger(value);
		setKey(false);
		break;
		}

	case JSONEntity::JSON_T_FLOAT:
		{
		handleFloat(value);
		setKey(false);
		break;
		}

	case JSONEntity::JSON_T_NULL:
		handleNull();
		setKey(false);
		break;

	case JSONEntity::JSON_T_TRUE:
		handleTrue();
		setKey(false);
		break;

	case JSONEntity::JSON_T_FALSE:
		handleFalse();
		setKey(false);
		break;

	case JSONEntity::JSON_T_KEY:
		{
		setKey(true);
		handleKey(value);
		break;   
		}

	case JSONEntity::JSON_T_STRING:
		{
		handleString(value);
		setKey(false);
		break;
		}

	default:
		poco_assert (false);
		break;
	}
}


} } // namespace Poco::Web
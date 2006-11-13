//
// SerialConfig_POSIX.cpp
//
// $Id: //poco/Main/IO/src/SerialConfig_POSIX.cpp#1 $
//
// Library: IO
// Package: Serial
// Module:  SerialConfig
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
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


#include "Poco/IO/SerialConfig_POSIX.h"
#include "Poco/Exception.h"
#include <sstream>


using Poco::InvalidArgumentException;


namespace Poco {
namespace IO {


const int SerialConfigImpl::MSEC = 1000;


SerialConfigImpl::SerialConfigImpl(SerialConfigImpl::BaudRateImpl baudRate,
	int dataBits,
	char parity,
	StartBitsImpl startBits,
	StopBitsImpl stopBits,
	FlowControlImpl flowControl,
	unsigned char xOnChar,
	unsigned char xOffChar,
	bool useEOF,
	unsigned char eofChar,
	int bufferSize,
	int timeout):  
	_useEOF(useEOF), 
	_bufferSize(bufferSize)
{
	//TODO

	setFlowControlImpl(flowControl, xOnChar, xOffChar);
	setParityCharImpl(parity);	
	setTimeoutImpl(timeout);
}


void SerialConfigImpl::setFlowControlImpl(SerialConfigImpl::FlowControlImpl flowControl,
		unsigned char xOnChar,
		unsigned char xOffChar)
{
	if (FLOW_CTRL_HARDWARE_IMPL == flowControl)
	{
		poco_assert(xOnChar == xOffChar);

		//TODO
	}
	else if (FLOW_CTRL_SOFTWARE_IMPL == flowControl)
	{
		//TODO

		setUseXonXoffImpl(xOnChar, xOffChar);
	}
	else
		throw InvalidArgumentException("Invalid argument supplied. Flow control not set.");

	_flowControl = flowControl;
}


void SerialConfigImpl::setUseXonXoffImpl(unsigned char xOnChar,
		unsigned char xOffChar)
{
	if (xOnChar != xOffChar)
	{
		//TODO
	}
	else
		throw InvalidAccessException("XON == XOFF - not set.");
}


void SerialConfigImpl::setXonCharImpl(unsigned char xOn)
{
	poco_assert(FLOW_CTRL_SOFTWARE_IMPL == _flowControl);
	//TODO
}


void SerialConfigImpl::setXoffCharImpl(unsigned char xOff)
{
	poco_assert(FLOW_CTRL_SOFTWARE_IMPL == _flowControl);
	//TODO
}


char SerialConfigImpl::getParityCharImpl() const
{
	//TODO
	/*
	switch (_dcb.Parity)
	{
	case PARITY_NONE_IMPL:
		return 'N';
	case PARITY_ODD_IMPL:
		return 'O';
	case PARITY_EVEN_IMPL:
		return 'E';
	case PARITY_MARK_IMPL:
		return 'M';
	case PARITY_SPACE_IMPL:
		return 'S';
	default:
		return 'N';
	}*/
}


void SerialConfigImpl::setParityCharImpl(char parityChar)
{
	switch (parityChar)
	{
	case 'n': case 'N':
		break;//TODO

	case 'o': case 'O':
		break;//TODO

	case 'e': case 'E':
		break;//TODO

	case 'm': case 'M':
		break;//TODO

	case 's': case 'S':
		break;//TODO

	default:
		{
			std::ostringstream os;
			os << "SerialConfigImpl::setParityCharImpl(" << parityChar << ')';
			throw InvalidArgumentException(os.str());
		}
	}
}


} } // namespace Poco::IO
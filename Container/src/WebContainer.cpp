//
// WebContainer.cpp
//
// Library: Container
// Package: ContainerCore
// Module:  WebContainer
//
// Copyright (c) 2006, Aleksandar Fabijanic and Contributors.
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


#include "Poco/Servlet/Container/WebContainer.h"
#include "Poco/Servlet/Container/WebApplicationTask.h"
#include "Poco/Servlet/Container/WebServerTask.h"
#include "Poco/Servlet/Ex/SystemFiles.h"
#include "Poco/AutoPtr.h"
#include "Poco/DirectoryIterator.h"
#include "Poco/Path.h"
#include "Poco/Thread.h"
#include "Poco/Task.h"
#include "Poco/Logger.h"
#include "Poco/Exception.h"
#include "Poco/Util/XMLConfiguration.h"


using Poco::Util::XMLConfiguration;
using Poco::Servlet::Ex::SystemFiles;


namespace Poco {
namespace Servlet {
namespace Container {


WebContainer::WebContainer(const std::string& rootDir,
	const std::string& webAppDir,
	const std::string& webSrvDir,
	Logger* pLogger):
	_rootDir(rootDir), 
	_webAppDir(webAppDir), 
	_webSrvDir(webSrvDir),
	_servletDispatcher(&_filterDispatcher),
	_pLogger(pLogger),
	_stop(false), 
	_running(false)
{
	init();
}


WebContainer::~WebContainer()
{
}


void WebContainer::init()
{
	std::ostringstream ss("");
	ss << _rootDir 
		<< Path::separator()
		<< SystemFiles::WEB_INF_DIR
		<< Path::separator()
		<< SystemFiles::WEB_XML_FILE;
	std::string conf = ss.str();
	std::ifstream fstr(conf.c_str());	

	if(!fstr) 
	{
		std::string text = "Could not open file: " + conf;
		if(_pLogger) _pLogger->error(text);
		throw InvalidArgumentException(text);
	}
	
	try
	{
		AutoPtr<XMLConfiguration> pConf = new XMLConfiguration(fstr);
		std::string extension;
		int cnt = 0;
		do
		{
			ss.str("");
			ss << "mime-mapping[" << cnt << "].extension";
			extension = pConf->getString(ss.str(), "");
			if("" == extension) break;
			ss.str("");
			ss << "mime-mapping[" << cnt << "].mime-type";
			_servletDispatcher.addMediaType(extension, pConf->getString(ss.str(), ""));
			++cnt;
		}while(true);
	}
	catch(std::exception& ex)
	{
		if(_pLogger) _pLogger->error(ex.what());
		fstr.close();
		throw;
	}

	fstr.close();
}


void WebContainer::run()
{
	typedef std::vector<std::string> ServerVec;
	ServerVec sv;

	DirectoryIterator di0(_rootDir);
	while("" != di0.name())
	{
	 if(di0->isDirectory())
	 {
		DirectoryIterator di1(di0.path());
		while("" != di1.name())
		{
			if(di1->isDirectory())
			{
				DirectoryIterator di2(di1.path());
				while("" != di2.name())
				{
					if((SystemFiles::WEB_INF_DIR == di2.name()) && (di2->isDirectory()))
					{
						DirectoryIterator di3(di2.path());
						while("" != di3.name())
						{
							if((SystemFiles::WEB_XML_FILE == di3.name()) && !(di3->isDirectory()))
							{
								try
								{
									std::string type = di0.name();//contained entity type (server or app)
									std::stringstream base;//contained entity base directory
									base << _rootDir << di0.name() << Path::separator() << di1.name() << Path::separator();

									if(_webAppDir == type)
									{
										std::ostringstream os;
										os << "Loading from " << type << ' ' << di1.name() << " based in " << base.str();
										if(_pLogger) _pLogger->information(os.str());
										_taskManager.start(new WebApplicationTask(base.str(), _servletDispatcher, &_filterDispatcher));
									}
									else
									if(_webSrvDir == type)
									{
										//Servers are loaded after all the applications have been succesfully 
										//loaded and configured. The servers are only memorized here and 
										//loaded later, after all the servlets have been loaded.
										sv.push_back(base.str());
									}
								}
								catch (Poco::Exception& e)
								{
									if(_pLogger) _pLogger->error(e.displayText());
								}
							}
							++di3;
						 }
					 }
					++di2;
				 }
			 }
			 ++di1;
		 }
	  }
	 ++di0;
  }
	
	//now load the servers
	ServerVec::iterator it = sv.begin();
	for(; it != sv.end(); ++it)
	{
		std::ostringstream os;
		os << "Starting server " << *it;
		if(_pLogger) _pLogger->information(os.str());
		_taskManager.start(new WebServerTask(*it, _servletDispatcher));
	}

	_running = true;

	//TODO: 
	//none of the server tasks should ever die, so add an observer
	//to be able to restart any task that dies (fails, is cancelled or finished)
	while(!_stop) Thread::sleep(5000);
	 
	_running = false;

	_taskManager.cancelAll();
	_taskManager.joinAll();
}


void WebContainer::stop()
{
	_stop = true;
}


bool WebContainer::isRunning()
{
	return _running;
}


} } } // namespace Poco::Servlet::Container'
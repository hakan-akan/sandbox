--
-- build_foundation.lua
--
--Copyright (c) 2012, Applied Informatics Software Engineering GmbH.
--and Contributors.

--Permission is hereby granted, free of charge, to any person or organization
--obtaining a copy of the software and accompanying documentation covered by
--this license (the "Software") to use, reproduce, display, distribute,
--execute, and transmit the Software, and to prepare derivative works of the
--Software, and to permit third-parties to whom the Software is furnished to
--do so, all subject to the following:

--The copyright notices in the Software and this entire statement, including
--the above license grant, this restriction and the following disclaimer,
--must be included in all copies of the Software, in whole or in part, and
--all derivative works of the Software, unless such copies or derivative
--works are solely in the form of machine-executable object code generated by
--a source language processor.

--THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
--IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
--FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
--SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
--FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
--ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
--DEALINGS IN THE SOFTWARE.


-- first we build all the dependencies ... 

function build_foundation (project_name)

    project (project_name)

    language "C++"

    flags       { "No64BitChecks"}	

    
    files {
        "../Foundation/include/**.h",
        "../Foundation/src/**.h",
        "../Foundation/src/**.cpp",
        "../Foundation/src/**.c",
        "../Foundation/**.rc",
        "../Foundation/**.mc",
--        "../**.rc",
    }

    includedirs { 
        "../Foundation/include",
    }

    excludes { 
        "../Foundation/src/*_*.cpp",
    }

    configuration "vs*"
		excludes     { 
            "../Foundation/src/SyslogChannel.cpp" ,
            "../Foundation/src/OpcomChannel.cpp" ,
        }

    --------------------------------------------------------------
    --    create filters
    --
    vpaths 
    { 
        --  Cache
        ["Cache/Header Files"] = { 
                                 "**/AbstractCache.h",
                                 "**/AbstractStrategy.h",
                                 "**/AccessExpirationDecorator.h",
                                 "**/AccessExpireCache.h",
                                 "**/AccessExpireLRUCache.h",
                                 "**/AccessExpireStrategy.h",
                                 "**/ExpirationDecorator.h",
                                 "**/ExpireCache.h",
                                 "**/ExpireLRUCache.h",
                                 "**/ExpireStrategy.h",
                                 "**/KeyValueArgs.h",
                                 "**/LRUCache.h",
                                 "**/LRUStrategy.h",
                                 "**/StrategyCollection.h",
                                 "**/UniqueAccessExpireCache.h",
                                 "**/UniqueAccessExpireLRUCache.h",
                                 "**/UniqueAccessExpireStrategy.h",
                                 "**/UniqueExpireCache.h",
                                 "**/UniqueExpireLRUCache.h",
                                 "**/UniqueExpireStrategy.h",
                                 "**/ValidArgs.h"},

        ["Cache/Source Files"] = {},

        -- Core
        ["Core/Header Files"] = { 
                                 "**/Any.h",
                                 "**/Array.h",
                                 "**/Ascii.h",
                                 "**/AtomicCounter.h",
                                 "**/AutoPtr.h",
                                 "**/AutoReleasePool.h",
                                 "**/Buffer.h",
                                 "**/Bugcheck.h",
                                 "**/ByteOrder.h",
                                 "**/Checksum.h",
                                 "**/Config.h",
                                 "**/Debugger.h",
                                 "**/DynamicAny.h",
                                 "**/DynamicAnyHolder.h",
                                 "**/DynamicFactory.h",
                                 "**/Environment.h",
                                 "**/Environment_UNIX.h",
                                 "**/Environment_VMS.h",
                                 "**/Environment_WIN32.h",
                                 "**/Environment_WIN32U.h",
                                 "**/Exception.h",
                                 "**/FIFOBuffer.h",
                                 "**/Format.h",
                                 "**/Foundation.h",
                                 "**/FPEnvironment.h",
                                 "**/FPEnvironment_C99.h",
                                 "**/FPEnvironment_DEC.h",
                                 "**/FPEnvironment_DUMMY.h",
                                 "**/FPEnvironment_SUN.h",
                                 "**/FPEnvironment_WIN32.h",
                                 "**/Instantiator.h",
                                 "**/MemoryPool.h",
                                 "**/MetaProgramming.h",
                                 "**/NamedTuple.h",
                                 "**/NestedDiagnosticContext.h",
                                 "**/Nullable.h",
                                 "**/NumberFormatter.h",
                                 "**/NumberParser.h",
                                 "**/Platform.h",
                                 "**/Platform_POSIX.h",
                                 "**/Platform_VMS.h",
                                 "**/Platform_WIN32.h",
                                 "**/Poco.h",
                                 "**/RefCountedObject.h",
                                 "**/SharedPtr.h",
                                 "**/SingletonHolder.h",
                                 "**/String.h",
                                 "**/StringTokenizer.h",
                                 "**/Tuple.h",
                                 "**/TypeList.h",
                                 "**/Types.h",
                                 "**/UnWindows.h",
                                 "**/Version.h",
                                 "**/Void.h"},

        ["Core/Source Files"] = {"**/Ascii.cpp",
                                 "**/AtomicCounter.cpp",
                                 "**/Bugcheck.cpp",
                                 "**/ByteOrder.cpp",
                                 "**/Checksum.cpp",
                                 "**/Debugger.cpp",
                                 "**/Environment.cpp",
                                 "**/Exception.cpp",
                                 "**/Format.cpp",
                                 "**/Foundation.h",
                                 "**/FPEnvironment.cpp",
                                 "**/MemoryPool.cpp",
                                 "**/NestedDiagnosticContext.cpp",
                                 "**/NumberFormatter.cpp",
                                 "**/NumberParser.cpp",
                                 "**/RefCountedObject.cpp",
                                 "**/String.cpp",
                                 "**/StringTokenizer.cpp",
                                 "**/Void.cpp"},
        -- Crypt
        ["Crypt/Header Files"] = {"**/DigestEngine.h", 
                                  "**/DigestStream.h", 
                                  "**/HMACEngine.h", 
                                  "**/MD4Engine.h", 
                                  "**/MD5Engine.h", 
                                  "**/Random.h", 
                                  "**/RandomStream.h", 
                                  "**/SHA1Engine.h",},

        ["Crypt/Source Files"] = {"**/DigestEngine.cpp", 
                                  "**/DigestStream.cpp", 
                                  "**/MD4Engine.cpp", 
                                  "**/MD5Engine.cpp", 
                                  "**/Random.cpp", 
                                  "**/RandomStream.cpp", 
                                  "**/SHA1Engine.cpp",},

        -- DateTime
        ["DateTime/Header Files"] = {"**/DateTime.h", 
                                     "**/DateTimeFormat.h",
                                     "**/DateTimeFormatter.h",
                                     "**/DateTimeParser.h",
                                     "**/LocalDateTime.h",
                                     "**/Stopwatch.h",
                                     "**/Timespan.h",
                                     "**/Timestamp.h",
                                     "**/Timezone.h",},

        ["DateTime/Source Files"] = {"**/DateTime.cpp", 
                                     "**/DateTimeFormat.cpp",
                                     "**/DateTimeFormatter.cpp",
                                     "**/DateTimeParser.cpp",
                                     "**/LocalDateTime.cpp",
                                     "**/Stopwatch.cpp",
                                     "**/Timespan.cpp",
                                     "**/Timestamp.cpp",
                                     "**/Timezone.cpp",},

        -- Dynamic
        ["Dynamic/Header Files"] = {"**/Pair.h", 
                                    "**/Struct.h", 
                                    "**/Var.h", 
                                    "**/VarHolder.h",},

        ["Dynamic/Source Files"] = {"**/Var.cpp", 
                                    "**/VarHolder.cpp",},

        -- Event
        ["Event/Header Files"] = {"**/AbstractDelegate.h", 
                                 "**/AbstractEvent.h", 
                                 "**/AbstractPriorityDelegate.h", 
                                 "**/BasicEvent.h", 
                                 "**/DefaultStrategy.h", 
                                 "**/Delegate.h", 
                                 "**/EventArgs.h", 
                                 "**/Expire.h", 
                                 "**/FIFOEvent.h", 
                                 "**/FIFOStrategy.h", 
                                 "**/FunctionDelegate.h", 
                                 "**/NotificationStrategy.h", 
                                 "**/PriorityDelegate.h", 
                                 "**/PriorityEvent.h", 
                                 "**/PriorityExpire.h", 
                                 "**/PriorityStrategy.h",},

        ["Event/Source Files"] = {"**/EventArgs.cpp",},

        -- Filesystem
        ["Filesystem/Header Files"] = {"**/DirectoryIterator.h", 
                                       "**/DirectoryIterator_UNIX.h", 
                                       "**/DirectoryIterator_VMS.h", 
                                       "**/DirectoryIterator_WIN32.h", 
                                       "**/DirectoryIterator_WIN32U.h", 
                                       "**/File.h", 
                                       "**/File_UNIX.h", 
                                       "**/File_VMS.h", 
                                       "**/File_WIN32.h", 
                                       "**/File_WIN32U.h", 
                                       "**/Glob.h", 
                                       "**/Path.h", 
                                       "**/Path_UNIX.h", 
                                       "**/Path_VMS.h", 
                                       "**/Path_WIN32.h", 
                                       "**/Path_WIN32U.h", 
                                       "**/TemporaryFile.h",},

        ["Filesystem/Source Files"] = {"**/DirectoryIterator.cpp",
                                       "**/File.cpp",
                                       "**/Glob.cpp",
                                       "**/Path.cpp",
                                       "**/TemporaryFile.cpp", },

        -- Hasing
        ["Hashing/Header Files"] = {"**/Hash.h", 
                                    "**/HashFunction.h", 
                                    "**/HashMap.h", 
                                    "**/HashSet.h", 
                                    "**/HashStatistic.h", 
                                    "**/HashTable.h", 
                                    "**/LinearHashTable.h", 
                                    "**/SimpleHashTable.h",},

        ["Hashing/Source Files"] = {"**/Hash.cpp",
                                    "**/HashStatistic.cpp", },

        -- Logging
        ["Logging/Header Files"] = {"**/ArchiveStrategy.h", 
                                    "**/AsyncChannel.h", 
                                    "**/Channel.h", 
                                    "**/Configurable.h", 
                                    "**/ConsoleChannel.h", 
                                    "**/EventLogChannel.h", 
                                    "**/FileChannel.h", 
                                    "**/Formatter.h", 
                                    "**/FormattingChannel.h",
                                    "**/LogFile.h", 
                                    "**/LogFile_STD.h", 
                                    "**/LogFile_VMS.h", 
                                    "**/LogFile_WIN32.h", 
                                    "**/LogFile_WIN32U.h", 
                                    "**/Logger.h", 
                                    "**/LoggingFactory.h", 
                                    "**/LoggingRegistry.h", 
                                    "**/LogStream.h", 
                                    "**/Message.h", 
                                    "**/NullChannel.h", 
                                    "**/OpcomChannel.h", 
                                    "**/PatternFormatter.h", 
                                    "**/pocomsg.h", 
                                    "**/PurgeStrategy.h", 
                                    "**/RotateStrategy.h", 
                                    "**/SimpleFileChannel.h", 
                                    "**/SplitterChannel.h", 
                                    "**/StreamChannel.h", 
                                    "**/SyslogChannel.h",
                                    "**/WindowsConsoleChannel.h",},

        ["Logging/Message Files"] = {"**/pocomsg.mc",},
        ["Logging/Resource Files"] = {"**/pocomsg.rc",},
        ["Logging/Source Files"] = {"**/ArchiveStrategy.cpp",
                                    "**/AsyncChannel.cpp",
                                    "**/Channel.cpp",
                                    "**/Configurable.cpp",
                                    "**/ConsoleChannel.cpp",
                                    "**/EventLogChannel.cpp",
                                    "**/FileChannel.cpp",
                                    "**/Formatter.cpp",
                                    "**/FormattingChannel.cpp",
                                    "**/LogFile.cpp",
                                    "**/Logger.cpp",
                                    "**/LoggingFactory.cpp",
                                    "**/LoggingRegistry.cpp",
                                    "**/LogStream.cpp",
                                    "**/Message.cpp",
                                    "**/NullChannel.cpp",
                                    "**/PatternFormatter.cpp",
                                    "**/PurgeStrategy.cpp",
                                    "**/RotateStrategy.cpp",
                                    "**/SimpleFileChannel.cpp",
                                    "**/SplitterChannel.cpp",
                                    "**/StreamChannel.cpp",
                                    "**/WindowsConsoleChannel.cpp",},

        -- Notification
        ["Notification/Header Files"] = {"**/AbstractObserver.h", 
                                         "**/NObserver.h", 
                                         "**/Notification.h", 
                                         "**/NotificationCenter.h", 
                                         "**/NotificationQueue.h", 
                                         "**/Observer.h", 
                                         "**/PriorityNotificationQueue.h", 
                                         "**/TimedNotificationQueue.h",},

        ["Notification/Source Files"] = {"**/AbstractObserver.cpp",
                                         "**/Notification.cpp",
                                         "**/NotificationCenter.cpp",
                                         "**/NotificationQueue.cpp",
                                         "**/PriorityNotificationQueue.cpp",
                                         "**/TimedNotificationQueue.cpp", },

        -- Processes
        ["Processes/Header Files"] = {"**/NamedEvent.h", 
                                      "**/NamedEvent_UNIX.h", 
                                      "**/NamedEvent_VMS.h", 
                                      "**/NamedEvent_WIN32.h", 
                                      "**/NamedEvent_WIN32U.h", 
                                      "**/NamedMutex.h", 
                                      "**/NamedMutex_UNIX.h", 
                                      "**/NamedMutex_VMS.h", 
                                      "**/NamedMutex_WIN32.h", 
                                      "**/NamedMutex_WIN32U.h", 
                                      "**/Pipe.h", 
                                      "**/PipeImpl.h", 
                                      "**/PipeImpl_DUMMY.h", 
                                      "**/PipeImpl_POSIX.h", 
                                      "**/PipeImpl_WIN32.h", 
                                      "**/PipeStream.h", 
                                      "**/Process.h", 
                                      "**/Process_UNIX.h", 
                                      "**/Process_VMS.h", 
                                      "**/Process_WIN32.h", 
                                      "**/Process_WIN32U.h", 
                                      "**/SharedMemory.h", 
                                      "**/SharedMemory_DUMMY.h", 
                                      "**/SharedMemory_POSIX.h", 
                                      "**/SharedMemory_WIN32.h", },

        ["Processes/Source Files"] = {"**/NamedEvent.cpp",
                                      "**/NamedMutex.cpp",
                                      "**/Pipe.cpp",
                                      "**/PipeImpl.cpp",
                                      "**/PipeStream.cpp",
                                      "**/Process.cpp",
                                      "**/SharedMemory.cpp", },

        -- RegularExpression
        ["RegularExpression/Header Files"] = { "**/RegularExpression.h", },

        ["RegularExpression/PCRE Header Files"] = {
                                 "**/pcre.h",
                                 "**/pcre_config.h",
                                 "**/pcre_internal.h",
                                 "**/ucp.h"},

        ["RegularExpression/PCRE Source Files"] = {
                                 "**/pcre_chartables.c",
                                 "**/pcre_compile.c",
                                 "**/pcre_exec.c",
                                 "**/pcre_fullinfo.c",
                                 "**/pcre_globals.c",
                                 "**/pcre_maketables.c",
                                 "**/pcre_newline.c",
                                 "**/pcre_ord2utf8.c",
                                 "**/pcre_study.c",
                                 "**/pcre_tables.c",
                                 "**/pcre_try_flipped.c",
                                 "**/pcre_ucd.c",
                                 "**/pcre_valid_utf8.c",
                                 "**/pcre_xclass.c" },

        ["RegularExpression/Source Files"] = { "**/RegularExpression.cpp" },

        -- SharedLibrary
        ["SharedLibrary/Header Files"] = { "**/ClassLibrary.h", 
                                           "**/ClassLoader.h",
                                           "**/Manifest.h",
                                           "**/MetaObject.h",
                                           "**/SharedLibrary.h",
                                           "**/SharedLibrary_HPUX.h",
                                           "**/SharedLibrary_UNIX.h",
                                           "**/SharedLibrary_VMS.h",
                                           "**/SharedLibrary_WIN32.h",
                                           "**/SharedLibrary_WIN32U.h", },

        ["SharedLibrary/Source Files"] = { "**/Manifest.cpp", 
                                           "**/SharedLibrary.cpp", },

        -- Stream
        ["Stream/Header Files"] = { "**/Base64Decoder.h", 
                                    "**/Base64Encoder.h",
                                    "**/BinaryReader.h",
                                    "**/BinaryWriter.h",
                                    "**/BufferAllocator.h",
                                    "**/BufferedBidirectionalStreamBuf.h",
                                    "**/BufferedStreamBuf.h",
                                    "**/CountingStream.h",
                                    "**/DeflatingStream.h",
                                    "**/FileStream.h",
                                    "**/FileStream_POSIX.h",
                                    "**/FileStream_WIN32.h",
                                    "**/HexBinaryDecoder.h",
                                    "**/HexBinaryEncoder.h",
                                    "**/InflatingStream.h",
                                    "**/LineEndingConverter.h",
                                    "**/MemoryStream.h",
                                    "**/NullStream.h",
                                    "**/StreamCopier.h",
                                    "**/StreamTokenizer.h",
                                    "**/StreamUtil.h",
                                    "**/TeeStream.h",
                                    "**/Token.h",
                                    "**/UnbufferedStream.h", },

        ["Stream/Source Files"] = { "**/Base64Decoder.cpp", 
                                    "**/Base64Encoder.cpp", 
                                    "**/BinaryReader.cpp", 
                                    "**/BinaryWriter.cpp", 
                                    "**/CountingStream.cpp", 
                                    "**/DeflatingStream.cpp", 
                                    "**/FileStream.cpp", 
                                    "**/HexBinaryDecoder.cpp", 
                                    "**/HexBinaryEncoder.cpp", 
                                    "**/InflatingStream.cpp", 
                                    "**/LineEndingConverter.cpp", 
                                    "**/MemoryStream.cpp", 
                                    "**/NullStream.cpp", 
                                    "**/StreamCopier.cpp", 
                                    "**/StreamTokenizer.cpp", 
                                    "**/TeeStream.cpp", 
                                    "**/Token.cpp", },
        ["Stream/zlib"] = { "**/adler32.c", 
                            "**/compress.c", 
                            "**/crc32.c", 
                            "**/crc32.h", 
                            "**/deflate.c", 
                            "**/deflate.h", 
                            "**/infback.c", 
                            "**/infback.h", 
                            "**/inffast.c", 
                            "**/inffast.h", 
                            "**/inffixed.h", 
                            "**/inflate.c", 
                            "**/inflate.h", 
                            "**/inftrees.c", 
                            "**/inftrees.h", 
                            "**/trees.c", 
                            "**/trees.h", 
                            "**/zconf.h", 
                            "**/zconf.c", 
                            "**/zlib.h", 
                            "**/zutil.h", 
                            "**/zutil.c", },


        -- Task
        ["Task/Header Files"] = { "**/Task.h", 
                                  "**/TaskManager.h", 
                                  "**/TaskNotification.h", },

        ["Task/Source Files"] = { "**/Task.cpp", 
                                  "**/TaskManager.cpp", 
                                  "**/TaskNotification.cpp", },

        -- Text
        ["Text/Header Files"] = { "**/ASCIIEncoding.h", 
                                  "**/Latin1Encoding.h", 
                                  "**/Latin9Encoding.h", 
                                  "**/StreamConverter.h", 
                                  "**/TextBufferIterator.h", 
                                  "**/TextConverter.h", 
                                  "**/TextEncoding.h", 
                                  "**/TextIterator.h", 
                                  "**/Unicode.h", 
                                  "**/UnicodeConverter.h", 
                                  "**/UTF16Encoding.h", 
                                  "**/UTF8Encoding.h", 
                                  "**/UTF8String.h", 
                                  "**/Windows1250Encoding.h", 
                                  "**/Windows1251Encoding.h", 
                                  "**/Windows1252Encoding.h", },

        ["Text/Source Files"] = { "**/ASCIIEncoding.cpp", 
                                  "**/Latin1Encoding.cpp", 
                                  "**/Latin2Encoding.cpp", 
                                  "**/Latin9Encoding.cpp", 
                                  "**/StreamConverter.cpp", 
                                  "**/TextBufferIterator.cpp", 
                                  "**/TextConverter.cpp", 
                                  "**/TextEncoding.cpp", 
                                  "**/TextIterator.cpp", 
                                  "**/Unicode.cpp", 
                                  "**/UnicodeConverter.cpp", 
                                  "**/UTF16Encoding.cpp", 
                                  "**/UTF8Encoding.cpp", 
                                  "**/UTF8String.cpp", 
                                  "**/Windows1250Encoding.cpp", 
                                  "**/Windows1251Encoding.cpp", 
                                  "**/Windows1252Encoding.cpp", },

        -- Threading
        ["Threading/Header Files"] = { "**/ActiveDispatcher.h", 
                                       "**/ActiveMethod.h", 
                                       "**/ActiveResult.h", 
                                       "**/ActiveRunnable.h", 
                                       "**/ActiveStarter.h", 
                                       "**/Activity.h", 
                                       "**/Condition.h", 
                                       "**/ErrorHandler.h", 
                                       "**/Event.h", 
                                       "**/Event_POSIX.h", 
                                       "**/Event_WIN32.h", 
                                       "**/Mutex.h", 
                                       "**/Mutex_POSIX.h", 
                                       "**/Mutex_WIN32.h", 
                                       "**/Runnable.h", 
                                       "**/RunnableAdapter.h", 
                                       "**/RWLock.h", 
                                       "**/RWLock_POSIX.h", 
                                       "**/RWLock_WIN32.h", 
                                       "**/ScopedLock.h", 
                                       "**/ScopedUnlock.h", 
                                       "**/Semaphore.h", 
                                       "**/Semaphore_POSIX.h", 
                                       "**/Semaphore_WIN32.h", 
                                       "**/SignalHandler.h", 
                                       "**/SynchronizedObject.h", 
                                       "**/Thread.h", 
                                       "**/Thread_POSIX.h", 
                                       "**/Thread_WIN32.h", 
                                       "**/ThreadLocal.h", 
                                       "**/ThreadPool.h", 
                                       "**/ThreadTarget.h", 
                                       "**/Timer.h",},

        ["Threading/Source Files"] = { "**/ActiveDispatcher.cpp", 
                                       "**/Condition.cpp", 
                                       "**/ErrorHandler.cpp", 
                                       "**/Event.cpp", 
                                       "**/Mutex.cpp", 
                                       "**/Runnable.cpp", 
                                       "**/RWLock.cpp", 
                                       "**/Semaphore.cpp", 
                                       "**/SignalHandler.cpp", 
                                       "**/SynchronizedObject.cpp", 
                                       "**/Thread.cpp", 
                                       "**/ThreadLocal.cpp", 
                                       "**/ThreadPool.cpp", 
                                       "**/ThreadTarget.cpp", 
                                       "**/Timer.cpp",}, 

        -- URI
        ["URI/Header Files"] = { "**/FileStreamFactory.h", 
                                 "**/URI.h", 
                                 "**/URIStreamFactory.h", 
                                 "**/URIStreamOpener.h",},

        ["URI/Source Files"] = { "**/FileStreamFactory.cpp", 
                                 "**/URI.cpp", 
                                 "**/URIStreamFactory.cpp", 
                                 "**/URIStreamOpener.cpp",},

        -- UUID
        ["UUID/Header Files"] = { "**/UUID.h", 
                                  "**/UUIDGenerator.h", },

        ["UUID/Source Files"] = { "**/UUID.cpp", 
                                  "**/UUIDGenerator.cpp",},
    
    }

    --------------------------------------------------------------

    -- generate difference lib dir for x32 and x64
    configuration { "x32" }
        targetdir ("../lib/".._ACTION)

    configuration { "x64" }
        targetdir ("../lib64/".._ACTION)

    -- build config 
    configuration "*static_mt"
        kind "StaticLib"
        defines { "POCO_STATIC", "PCRE_STATIC", "Foundation_EXPORTS"}
        flags { "StaticRuntime" }

    configuration "*static_md"
        kind "StaticLib"
        defines { "POCO_STATIC", "PCRE_STATIC", "Foundation_EXPORTS"}

    configuration "*shared"
        kind "SharedLib"
        defines { "_USRDLL", "PCRE_STATIC", "Foundation_EXPORTS"}

    configuration "debug*"
        defines     "_DEBUG"
        flags       { "Symbols", "ExtraWarnings" }

    configuration "release*"
        defines     "NDEBUG"
        flags       { "OptimizeSpeed"}

    -- library prefix&postfix 
	configuration "debug_static_mt"
        targetname ("Poco"..project_name.."mtd")
	configuration "release_static_mt"
        targetname ("Poco"..project_name.."mt")
	configuration "debug_static_md"
        targetname ("Poco"..project_name.."mdd")
	configuration "release_static_md"
        targetname ("Poco"..project_name.."md")
	configuration "debug_shared"
        targetname ("Poco"..project_name.."d")
	configuration "release_shared"
        targetname ("Poco"..project_name)

    -- visual studio specified options
    configuration "vs*"
		defines     { "_CRT_SECURE_NO_WARNINGS" }
        prebuildcommands { "mc -A \"../../Foundation/src/pocomsg.mc\" -r \"../../Foundation/src\" -h \"../../Foundation/src\"" }

    -- codelite
    configuration "code*"
		defines     { "__GNUWIN32__",}

    -- windows specified
	configuration {"windows"}
        links {
            "ws2_32",
            "iphlpapi",
        }
		defines {
			"WIN32",
			"_WINDOWS",
		}

    -- linux specified
	configuration { "linux" }
        links {
            "pthread"
        }

end

-- now we build it
build_foundation("Foundation")

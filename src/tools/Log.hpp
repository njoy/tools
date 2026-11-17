#ifndef NJOY_TOOLS_LOG
#define NJOY_TOOLS_LOG

// system includes

// other includes
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

namespace njoy {
namespace tools {

/**
 *  @brief A singleton logger for njoy components
 */
class Log {

  static std::shared_ptr<spdlog::logger> initialize_logger() {

    std::shared_ptr<spdlog::logger> instance = spdlog::stdout_color_st( "njoy" );
    instance->set_pattern( "[%^%l%$] %v" );
    #ifndef NDEBUG
    instance->set_level( spdlog::level::debug );
    #endif
    return instance;
  }

  static std::shared_ptr<spdlog::logger>& logger() {

    static std::shared_ptr<spdlog::logger> instance = initialize_logger();
    return instance;
  }

  /* constructors */
  Log() {}; // private to avoid creation of Log instances

public:

  Log( const Log& ) = delete;
  void operator=( const Log& ) = delete;

  /**
   *  @brief Direct the logger output to the given file
   */
  static void add_sink( const std::string& filename ) {

    auto sink_ptr = std::make_shared< spdlog::sinks::basic_file_sink_st >( filename );
    sink_ptr->set_pattern( "[%^%l%$] %v" );
    logger()->sinks().push_back( sink_ptr );
  }

  /**
   *  @brief Flush the logger
   */
  static void flush() {

    logger()->flush();
  }

  /**
   *  @brief Print a message at the info level
   *
   *  For example:
   *
   *  int value = 10;
   *  utility::Log::info( "Some message with a value {}", value );
   */
  template <typename... Args>
  static void info(fmt::format_string<Args...> format_str, Args&&... args) {
      logger()->info(format_str, std::forward<Args>(args)...);
  }

  static void info(std::string_view v) {
      logger()->info(v);
  }

  /**
   *  @brief Print a message at the warning level
   *
   *  For example:
   *
   *  int value = 10;
   *  utility::Log::warning( "Some message with a value {}", value );
   */
  template< typename... Args >
  static void warning( Args... args ) {

    logger()->warn( std::forward< Args >( args )... );
  }

  /**
   *  @brief Print a message at the error level
   *
   *  For example:
   *
   *  int value = 10;
   *  utility::Log::info( "Some message with a value {}", value );
   */
  template <typename... Args>
  static void error(fmt::format_string<Args...> format_str, Args&&... args) {
      logger()->error(format_str, std::forward<Args>(args)...);
  }

  /**
   *  @brief Print a message at the debug level
   *
   *  This only prints when NDEBUG is defined when compiling this code.
   *
   *  For example:
   *
   *  int value = 10;
   *  utility::Log::debug( "Some message with a value {}", value );
   */
  #ifdef NDEBUG
    template< typename... Args >
    static void debug( Args... ) {}
  #else
    template< typename... Args >
    static void debug( Args... args ) {

      logger()->debug( std::forward< Args >( args )... );
    }
  #endif
};

} // tools namespace

/* type alias - for backwards compatibility reasons */
using Log = tools::Log;

} // njoy namespace

#include <string>
#include <iostream>

#include <cstdio>
#include <cstdarg>

#define MAX_LOG_STRING_LENGTH 4096
inline std::string format_string(const char* fmt, ...)
{
    char buf[MAX_LOG_STRING_LENGTH];
    va_list args;
    va_start(args, fmt);
    std::vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);

       buf[MAX_LOG_STRING_LENGTH - 1] = '\0';
    return std::string(buf);
}

#ifndef _WIN32
#   define SET_RED "\x1b[31m"
#   define SET_YELLOW "\x1b[33m"
#   define SET_GREEN "\x1b[32m"
#   define SET_CLEAR "\x1b[0m"
#else
#   define SET_RED
#   define SET_YELLOW
#   define SET_GREEN
#   define SET_CLEAR
#endif //_WIN32

/*** Throwing errors ****************************************************/
#define NJOY_THROW_EXCEPTION_MESSAGE(msg, ...) \
    format_string(msg, ##__VA_ARGS__) + " (" + __FILE__ + ":" + std::to_string(__LINE__) + ")\n"

#define NJOY_THROW_RUNTIME_ERROR(msg, ...) \
    throw std::runtime_error( SET_RED "Runtime error: " SET_CLEAR  + NJOY_THROW_EXCEPTION_MESSAGE(msg, ##__VA_ARGS__ ));

#define NJOY_THROW_OUT_OF_RANGE(msg, ...) \
    throw std::out_of_range(  SET_RED "Out of range error: " SET_CLEAR + NJOY_THROW_EXCEPTION_MESSAGE(msg, ##__VA_ARGS__ ));

#define NJOY_RETHROW_ERROR(e, msg, ...) \
    throw std::runtime_error( e.what() + std::string( SET_RED "Runtime error: " SET_CLEAR ) + NJOY_THROW_EXCEPTION_MESSAGE(msg, ##__VA_ARGS__ ) );

/*** Warning messages ***************************************************/
#define NJOY_LOG_WARNING_MESSAGE(msg, ...) \
    std::string( SET_YELLOW "WARNING: " SET_CLEAR) + format_string(msg, ##__VA_ARGS__) + \
    " (" + __FILE__ + ":" + std::to_string(__LINE__) + ")"

#define NJOY_LOG_WARNING(msg, ...) \
    std::cout << NJOY_LOG_WARNING_MESSAGE(msg, ##__VA_ARGS__ ) << "\n";

/*** Info messages ******************************************************/
#define NJOY_LOG_INFO_MESSAGE(msg, ...) \
    std::string("INFO: " SET_CLEAR) + format_string(msg, ##__VA_ARGS__) + " (" + __FILE__ + ":" + std::to_string(__LINE__) + ")"

#define NJOY_LOG_INFO(msg, ...) \
    std::cout << NJOY_LOG_INFO_MESSAGE(msg, ##__VA_ARGS__ ) << "\n";

/*** Check that expected exception is thrown and print it if it is ******/
#define NJOY_PRINT_CHECK_THROWS( MY_FUNCTION_TO_LOG ) \
    do {\
        try { \
            ( MY_FUNCTION_TO_LOG ); \
            FAIL("Expected exception but none was thrown");\
        } \
        catch ( const std::exception& e ) { \
            std::cout << e.what(); \
            SUCCEED();\
        }\
    } while (0)

#endif //NJOY_TOOLS_LOG

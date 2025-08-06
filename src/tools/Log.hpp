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

#endif

#ifndef NJOY_TOOLS_CONFIGURATION
#define NJOY_TOOLS_CONFIGURATION

// system includes
#include <fstream>
#include <map>
#include <string>

// other includes

namespace njoy {
namespace tools {

  /**
   *  @class
   *  @brief Configuration file reader
   *
   *  Configuration values are stored as key-value string pairs.
   *
   *  The configuration file format is simple key=value pairs, one per line.
   *  Lines starting with '#' are treated as comments.
   */
  class Configuration {

    /* fields */

    std::map< std::string, std::string > properties_;
    std::string filename_;

    /* auxiliary functions */

    /**
     *  @brief Trim whitespace from both ends of a string
     *
     *  @param[in] string   the string to trim
     */
    static std::string trim( const std::string& string ) {

      const auto start = string.find_first_not_of( " \t\r\n" );
      if ( start == std::string::npos ) {

        return "";
      }
      const auto end = string.find_last_not_of( " \t\r\n" );
      return string.substr( start, end - start + 1 );
    }

    /**
     *  @brief Load configuration from a file
     *
     *  @param[in] filename   the full filename of the configuration file to load
     */
    void load( const std::string& filename ) {

      std::ifstream file( filename );
      if ( ! file.is_open() ) {

        throw std::runtime_error( "Failed to open configuration file: " + filename );
      }

      this->properties_.clear();
      this->filename_ = filename;

      std::string line;
      std::size_t number = 0;

      while ( std::getline( file, line ) ) {

        ++number;
        line = trim( line );

        if ( line.empty() || line.front() == '#' ) {

          continue;
        }

        const auto pos = line.find( '=' );
        if ( pos == std::string::npos ) {

          throw std::runtime_error( "Invalid configuration format at line " +
                                    std::to_string( number ) + ": " + line );
        }

        const std::string key = trim( line.substr( 0, pos ) );
        const std::string value = trim( line.substr( pos + 1 ) );

        if ( key.empty() ) {

          throw std::runtime_error( "Empty key at line " + std::to_string( number ) );
        }

        this->properties_[key] = value;
      }
    }

    /* private functions */

    /**
     *  @brief Private constructor
     */
    Configuration() : properties_(), filename_() {}

    /**
     *  @brief Private destructor
     */
    ~Configuration() = default;

  public:

    /* constructor */

    Configuration( const Configuration& ) = delete;
    Configuration( Configuration&& ) = delete;

    Configuration& operator=( const Configuration& ) = delete;
    Configuration& operator=( Configuration&& ) = delete;

    /* methods */

    /**
     *  @brief Get the configuration instance
     *
     *  @param[in] filename   the full filename of the configuration file to load
     */
    static Configuration& getInstance( const std::string& filename ) {

      static Configuration instance;
      if ( instance.filename() != filename ) {

        instance.load( filename );
      }
      return instance;
    }

    /**
     *  @brief Get filename of the configuration file that has been loaded
     */
    const std::string& filename() const {

      return this->filename_;
    }

    /**
     *  @brief Get a value from the configuration
     *
     *  @param[in] key             the configuration key
     */
    const std::string& get( const std::string& key ) const {

      return this->properties_.at( key );
    }

    /**
     *  @brief Check if a key exists in the configuration
     *
     *  @param[in] key   the configuration key
     */
    bool hasKey( const std::string& key ) const {

      return this->properties_.find( key ) != this->properties_.end();
    }
  };

} // tools namespace
} // njoy namespace

#endif
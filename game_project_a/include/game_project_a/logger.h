#ifndef QSLIBRARY_GAME_PROJECT_A_LOGGER_H
#define QSLIBRARY_GAME_PROJECT_A_LOGGER_H 1

#include <iostream>
#include <sstream>
#include <string>

/**
 * A simple Logger
 *
 * Logs to console... can be derived and overridden for other behavior
 */
class Logger
{
public:
    /** constructor */
    Logger()=default;

    /** virtual destructor for derivation */
    virtual ~Logger()=default;

    /**
     * Write Critical Errors to log
     * @param stream error message
     */
    void WriteCritical(std::stringstream& stream)
    {
        std::cerr << stream.str();
    }

    /**
     * Write Errors to log
     * @param stream error message
     */
    void WriteError(std::stringstream& stream)
    {
        std::cerr << stream.str();
    }

    /**
     * Write debugging information to log
     * @param stream error message
     */
    void WriteDebug(std::stringstream& stream)
    {
        std::cerr << stream.str();
    }
};


#endif // QSLIBRARY_GAME_PROJECT_A_LOGGER_H
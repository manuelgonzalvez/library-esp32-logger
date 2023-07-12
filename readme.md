# MyLogging Library

Esta libreria es un complemento simple al Serial.x(Arduino) o log_x(ESP) para habilitar dinamicamente niveles de logging en el codigo.

> **Warning** Documentacion en desarrollo

## Caracteristicas

- Five log levels: NONE, ERROR, WARN, INFO, DEBUG, and VERBOSE.
- Flexible configuration to control the log level for each logger individually.
- Optional mutex support for thread safety in multithreaded applications.
- Easy integration into Arduino projects.
- Logger list creation as map , to change logging levels dynamically.

## Instalacion

### PlatformIO

1. añadir a platformio.ini:

        lib_deps = https://github.com/manuelgonzalvez/library-esp32-logger.git


## Usage

### Creating Loggers

Si se van a crear varias instancias del objeto, es conveniente declararlas previamente como externas en una clase en comun que permita realizar operaciones sobre las mismas.

Para crear un objeto "logger", añadir el header de la libreria

>+-- [helpers.h]

```cpp

#include "ESP32LoggingHelper.h"

extern logger myLoggerA;
extern logger myLoggerB;

```

> classA.cpp
```cpp

#include "helpers.h"

// Create a logger with a specific log level and name, and add it to the loggerList array
logger myLoggerA(LOGGER_DEBUG, "myLoggerA",true);
```

> classB.cpp

```cpp

#include "helpers.h"

// Create a logger with a specific log level and name, logger not added to the list.
logger myLoggerB(LOGGER_DEBUG, "myLoggerB");
```




### Logging Messages

Once you have created a logger, you can use it to log messages at different log levels. The library provides five log levels: `ERROR`, `WARN`, `INFO`, `DEBUG`, and `VERBOSE`. The log level of each logger determines which messages will be printed.

```cpp
if(myLogger.printD()) // Log an error message
{
log_d("Uptime: %zu", ScaleData.uptime);
}
```
resultara en:
```js
[nodos] [D][myNodes.cpp:932] checkNodeUptime(): Uptime: 9172 
```

### Setting Log Levels

You can change the log level of a logger at any time using the `setLevel()` method. This allows you to adjust the verbosity of your output dynamically.

```cpp
myLogger.setLevel(LOGGER_WARN); // Set the log level to WARN
```

### Thread Safety (Mutex)

> **Warning**
> If you are working in a multithreaded environment, you can enable the mutex option to ensure thread safety. When the mutex is enabled, a lock will be acquired before printing each log message, preventing multiple threads from interfering with each other.

To enable the mutex, uncomment the `#define USE_MUTEX` line in the `mylogging.h` file.

```cpp
#define USE_MUTEX // Enable mutex for thread safety
```

**Note:** Enabling the mutex may introduce additional execution overhead, so use it only if necessary in your specific application.

### Accessing Loggers

The `loggerList` class provides methods to access the created loggers. You can retrieve loggers by their tag name or by their index in the list of loggers.

```cpp
// Retrieve a logger by tag name
logger* myLogger = loggerList::getLogger("myLogger");

// Retrieve a logger by index
logger* myLogger = loggerList::getLoggerByIndex(0);
```

### Obtaining Logger Information

The `loggerList` class also allows you to get information about the loggers, such as the number of loggers and the log level of a specific logger.

```cpp
int count = loggerList::getLoggersCount();       // Get the number of loggers
const char* tagName = loggerList::getLoggerTagByIndex(0);  // Get the tag name of the first logger
uint8_t level = loggerList::getLoggerLevelByIndex(0);     // Get the log level of the first logger
```

<!-- ## Examples

The library includes example sketches that demonstrate its usage. You can find them in the Arduino IDE under **File > Examples > MyLogging**. -->

## License

This library is released under the [MIT License](https://opensource.org/licenses/MIT).

## Credits

The MyLogging library was developed by Manuel Gonzalvez. If you have any questions or suggestions, please feel free to contact me at __manuelgonzalvez@gmail.com__.


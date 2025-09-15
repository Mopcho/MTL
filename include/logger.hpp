#ifndef LOGGER_HPP
#define LOGGER_HPP

#ifdef MTL_DEBUG
#define LOG(fmt, ...) printf(fmt, __VA_ARGS__)
#else
#define LOG(fmt, ...) do {} while (0)
#endif

#endif //LOGGER_HPP

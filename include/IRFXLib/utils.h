//
// Created by suhasghorp on 5/13/2021.
//

#ifndef IRFXLIB_INCLUDE_IRFXLIB_UTILS_H_
#define IRFXLIB_INCLUDE_IRFXLIB_UTILS_H_

//American or European
enum class ExerciseType { American, European};

enum class OptionType { Call, Put};

enum PayoffType { Vanilla, Digital};

struct Result { double price; double delta; double gamma ;};

#endif //IRFXLIB_INCLUDE_IRFXLIB_UTILS_H_

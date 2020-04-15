#include "magic_wand_model_data.h"

// We need to keep the data array aligned on some architectures.
#ifdef __has_attribute
#define HAVE_ATTRIBUTE(x) __has_attribute(x)
#else
#define HAVE_ATTRIBUTE(x) 0
#endif
#if HAVE_ATTRIBUTE(aligned) || (defined(__GNUC__) && !defined(__clang__))
#define DATA_ALIGN_ATTRIBUTE __attribute__((aligned(4)))
#else
#define DATA_ALIGN_ATTRIBUTE
#endif

const unsigned char g_magic_wand_model_data[] DATA_ALIGN_ATTRIBUTE = {
  // Paste the data of the char array in `src/model.cc` here
};

unsigned int model_tflite_len = ;// Fill the int in `src/model.cc` here
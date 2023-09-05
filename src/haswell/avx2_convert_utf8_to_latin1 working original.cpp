// depends on "tables/utf8_to_utf16_tables.h"

// for reference, this is the previous version:

// scalar:
/* convert_utf8_to_latin1+haswell, input size: 440052, iterations: 3000, dataset: unicode_lipsum/wikipedia_mars/french.utflatin8.txt   
  5.281 ins/byte,    1.872 cycle/byte,    1.706 GB/s (50.2 %),     3.193 GHz,    2.821 ins/cycle 
   5.376 ins/char,    1.906 cycle/char,    1.676 Gc/s (50.2 %)     1.02 byte/char  */

// SSE
/* convert_utf8_to_latin1+haswell, input size: 440052, iterations: 30000, dataset: /home/leorio/unicode_lipsum/wikipedia_mars/french.utflatin8.txt
   1.760 ins/byte,    0.970 cycle/byte,    3.292 GB/s (2.2 %),     3.194 GHz,    1.814 ins/cycle 
   1.792 ins/char,    0.988 cycle/char,    3.234 Gc/s (2.2 %)     1.02 byte/char  */

// par (added 32-bit fast path)
/* convert_utf8_to_latin1+haswell, input size: 440052, iterations: 30000, dataset: /home/leorio/unicode_lipsum/wikipedia_mars/french.utflatin8.txt
   1.760 ins/byte,    0.968 cycle/byte,    3.300 GB/s (2.3 %),     3.194 GHz,    1.819 ins/cycle 
   1.792 ins/char,    0.985 cycle/char,    3.242 Gc/s (2.3 %)     1.02 byte/char  */


// depends on "tables/utf8_to_utf16_tables.h"


// Convert up to 12 bytes from utf8 to latin1 using a mask indicating the
// end of the code points. Only the least significant 12 bits of the mask
// are accessed.
// It returns how many bytes were consumed (up to 12).
size_t convert_masked_utf8_to_latin1(const char *input,
                           uint64_t utf8_end_of_code_point_mask,
                           char *&latin1_output) {
  // we use an approach where we try to process up to 12 input bytes.
  // Why 12 input bytes and not 16? Because we are concerned with the size of
  // the lookup tables. Also 12 is nicely divisible by two and three.
  //
  //
  // Optimization note: our main path below is load-latency dependent. Thus it is maybe
  // beneficial to have fast paths that depend on branch prediction but have less latency.
  // This results in more instructions but, potentially, also higher speeds.
  //
  const __m128i in = _mm_loadu_si128((__m128i *)input);
  const __m128i in_second_half = _mm_loadu_si128((__m128i *)(input + 16));

  const uint16_t input_utf8_end_of_code_point_mask =
      utf8_end_of_code_point_mask & 0xfff; //we're only processing 12 bytes in case it`s not all ASCII

  if((input_utf8_end_of_code_point_mask & 0xffffffff) == 0xffffffff) {
    // Load the next 128 bits.

    // Combine the two 128-bit registers into a single 256-bit register.
    __m256i in_combined = _mm256_set_m128i(in_second_half, in);

    // We process the data in chunks of 32 bytes.
    _mm256_storeu_si256(reinterpret_cast<__m256i *>(latin1_output), in_combined);

    latin1_output += 32; // We wrote 32 characters.
    return 32; // We consumed 32 bytes.
  }


  if(((utf8_end_of_code_point_mask & 0xffff) == 0xffff)) {
    // We process the data in chunks of 16 bytes.
    _mm_storeu_si128(reinterpret_cast<__m128i *>(latin1_output), in);
    latin1_output += 16; // We wrote 16 characters.
    return 16; // We consumed 16 bytes.
  }
  /// We do not have a fast path available, so we fallback.
  const uint8_t idx =
      tables::utf8_to_utf16::utf8bigindex[input_utf8_end_of_code_point_mask][0];
  const uint8_t consumed =
      tables::utf8_to_utf16::utf8bigindex[input_utf8_end_of_code_point_mask][1];
  // this indicates an invalid input:
  if(idx >= 64) { return consumed; }
  // Here we should have (idx < 64), if not, there is a bug in the validation or elsewhere.
  // SIX (6) input code-words
  // this is a relatively easy scenario
  // we process SIX (6) input code-words. The max length in bytes of six code
  // words spanning between 1 and 2 bytes each is 12 bytes. On processors
  // where pdep/pext is fast, we might be able to use a small lookup table.
  const __m128i sh =
        _mm_loadu_si128((const __m128i *)tables::utf8_to_utf16::shufutf8[idx]);
  const __m128i perm = _mm_shuffle_epi8(in, sh);
  const __m128i ascii = _mm_and_si128(perm, _mm_set1_epi16(0x7f));
  const __m128i highbyte = _mm_and_si128(perm, _mm_set1_epi16(0x1f00));
  __m128i composed = _mm_or_si128(ascii, _mm_srli_epi16(highbyte, 2));
  const __m128i latin1_packed = _mm_packus_epi16(composed,composed);
  // writing 8 bytes even though we only care about the first 6 bytes.
  // performance note: it would be faster to use _mm_storeu_si128, we should investigate.
  _mm_storel_epi64((__m128i *)latin1_output, latin1_packed);
  latin1_output += 6; // We wrote 6 bytes.
  return consumed;
}
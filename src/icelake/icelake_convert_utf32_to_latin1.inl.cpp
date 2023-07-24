// file included directly

std::pair<const char32_t*, char*> avx512_valid_convert_utf32_to_latin1(const char32_t* buf, size_t len, char* latin1_output) {
  const char32_t* end = buf + len;

  while (buf + 16 < end) {
    // Load 16 UTF-32 characters
    __m512i chunk = _mm512_loadu_si512((__m512i*)buf);
    // Truncate to Latin1
    __m128i latin1_chunk = _mm512_cvtepi32_epi8(chunk);
    // Store in the output buffer
    _mm_storeu_si128((__m128i*)latin1_output, latin1_chunk);

    buf += 16;
    latin1_output += 16;
  }

  return std::make_pair(buf, latin1_output);
}

static inline void spin(volatile uint32_t count) {
  while (count--) asm("nop");
}

bool my_strcmp(volatile const char* str1, const char* str2) {
    // Loop through both strings
    while (*str1 && *str2) {
        // Compare characters one by one
        if (*str1 != *str2) {
            return false;  // Return 1 if they are different
        }
        str1++;
        str2++;
    }

    return true;
}

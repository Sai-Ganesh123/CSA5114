#include <stdio.h> 
 #include <stdint.h> 
 #include <string.h> 
 #include <stdlib.h> 
 #define LEFTROTATE(x, c) (((x) << (c)) | ((x) >> (32 - (c)))) 
 void sha1(uint8_t *input, size_t length, uint8_t *output) { 
 
 }  
 int main() { 
     char input[1024]; 
     printf("Enter a string to hash: "); 
     fgets(input, sizeof(input), stdin);
     input[strcspn(input, "\n")] = '\0'; // Remove newline if present 
     uint8_t output[20]; 
     sha1((uint8_t *)input, strlen(input), output); 
     printf("SHA-1 Hash: "); 
     for (int i = 0; i < 20; i++) { 
         printf("%02x", output[i]); 
     } 
     printf("\n"); 
     return 0; 
 }
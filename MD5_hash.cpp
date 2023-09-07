#include <stdio.h>
#include <math.h>
#include <string.h>

// ??nh ngh?a hàm d?ch trái
unsigned int leftrotate(unsigned int x, int c) {
    return (x << c) | (x >> (32 - c));
}

void MD5(const unsigned char *message, unsigned int messageLen, unsigned char *digest) {
    unsigned int r[64];
    unsigned int k[64];
    
    // r xác ??nh s? d?ch chuy?n m?i vòng
    unsigned int r1[16] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22};
    unsigned int r2[16] = {5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20};
    unsigned int r3[16] = {4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23};
    unsigned int r4[16] = {6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};
    
    // S? d?ng ph?n nguyên nh? phân c?a sin c?a s? nguyên làm h?ng s?
    for (int i = 0; i < 64; i++) {
        if (i < 16)
            r[i] = r1[i];
        else if (i < 32)
            r[i] = r2[i - 16];
        else if (i < 48)
            r[i] = r3[i - 32];
        else
            r[i] = r4[i - 48];
        
        k[i] = floor(fabs(sin(i + 1)) * pow(2, 32));
    }
    
    // Kh?i t?o bi?n
    unsigned int h0 = 0x67452301;
    unsigned int h1 = 0xEFCDAB89;
    unsigned int h2 = 0x98BADCFE;
    unsigned int h3 = 0x10325476;
    
    // Ti?n x? lý
    
    unsigned int paddedLen = (messageLen * 8) + 1 + 64;
    unsigned int paddedLenInBits = paddedLen % 512;
    unsigned int appendLen;
    
    if (paddedLenInBits <= 448)
        appendLen = 448 - paddedLenInBits;
    else
        appendLen = 448 + (512 - paddedLenInBits);
    
    unsigned int totalLen = messageLen * 8;
    
    unsigned char paddedMessage[paddedLen / 8];
    memcpy(paddedMessage, message, messageLen);
    
    paddedMessage[messageLen] = 0x80;
    
    // Thêm các bit '0' ?? ??t ???c ?? dài thích h?p
    for (int i = messageLen + 1; i < paddedLen / 8; i++) {
        paddedMessage[i] = 0x00;
    }
    
    // Thêm ?? dài c?a message ban ??u vào padded message (64-bit little-endian)
    unsigned int *lengthPtr = (unsigned int *)(paddedMessage + (paddedLen / 8) - 8);
    *lengthPtr = totalLen;
    
    // X? lý m?u tin trong ?o?n 512-bit ti?p theo
    
    unsigned int chunkCount = paddedLen / (512 / 8);
    
    for (unsigned int chunk = 0; chunk < chunkCount; chunk++) {
        unsigned int *w = (unsigned int *)(paddedMessage + (chunk * (512 / 8)));
        
        // Kh?i t?o giá tr? b?m cho ?o?n này
        unsigned int a = h0;
        unsigned int b = h1;
        unsigned int c = h2;
        unsigned int d = h3;
        
        // Vòng l?p chính
        for (int i = 0; i < 64; i++) {
            unsigned int f, g;
            
            if (i < 16) {
                f = (b & c) | ((~b) & d);
                g = i;
            } else if (i < 32) {
                f = (d & b) | ((~d) & c);
                g = (5 * i + 1) % 16;
            } else if (i < 48) {
                f = b ^ c ^ d;
                g = (3 * i + 5) % 16;
            } else {
                f = c ^ (b | (~d));
                g = (7 * i) % 16;
            }
            
            unsigned int temp = d;
            d = c;
            c = b;
            b = b + leftrotate((a + f + k[i] + w[g]), r[i]);
            a = temp;
        }
        
        // Thêm b?ng b?m c?a ?o?n vào k?t qu?
        h0 = h0 + a;
        h1 = h1 + b;
        h2 = h2 + c;
        h3 = h3 + d;
    }
    
    // L?u tr? k?t qu? vào digest (little-endian)
    digest[0] = h0 & 0xFF;
    digest[1] = (h0 >> 8) & 0xFF;
    digest[2] = (h0 >> 16) & 0xFF;
    digest[3] = (h0 >> 24) & 0xFF;
    digest[4] = h1 & 0xFF;
    digest[5] = (h1 >> 8) & 0xFF;
    digest[6] = (h1 >> 16) & 0xFF;
    digest[7] = (h1 >> 24) & 0xFF;
    digest[8] = h2 & 0xFF;
    digest[9] = (h2 >> 8) & 0xFF;
    digest[10] = (h2 >> 16) & 0xFF;
    digest[11] = (h2 >> 24) & 0xFF;
    digest[12] = h3 & 0xFF;
    digest[13] = (h3 >> 8) & 0xFF;
    digest[14] = (h3 >> 16) & 0xFF;
    digest[15] = (h3 >> 24) & 0xFF;
}

int main() {
    // Chu?i thông ?i?p ??u vào
    unsigned char message[] = "The quick brown fox jumps over the lazy dog";
    unsigned int messageLen = strlen((const char *)message);
    
    // Kích th??c b?ng b?m (16 byte = 128 bit)
    unsigned char digest[16];
    
    // G?i hàm MD5 ?? tính toán b?ng b?m
    MD5(message, messageLen, digest);
    
    // In k?t qu?
    printf("Digest: ");
    for (int i = 0; i < 16; i++) {
        printf("%02x ", digest[i]);
    }
    printf("\n");
    
    return 0;
}



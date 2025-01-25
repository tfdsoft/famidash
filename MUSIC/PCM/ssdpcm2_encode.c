#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>

#define clamp(x,y,z) ((x)>(z)?(z):((x)<(y)?(y):(x)))

uint8_t byte_thing[8] = {128,64,32,16,8,4,2,1};
int dpcm_vals[4] = {-1,0,1,2};

int main(int argc, char *argv[]) {
  int N = 128; // Size of input sequence (should be a power of 2)
  uint8_t int_buffer[N * 2];
  size_t bytesRead;
  int buffer_len = N;
  uint16_t delta_size = 8;
  FILE *file = fopen(argv[1], "rb");
  FILE *wfile = fopen("audio.bin", "wb");
  if (file != NULL) {
    uint8_t dpcm = 128;
    uint8_t dpcm2 = 128;
    uint8_t dpcm3;
    bool I = false;
    while ((bytesRead = fread(int_buffer, 1, buffer_len, file)) > 0) {
      uint8_t x[N];  // Input sequence (real part)
      long dist[64]; // Input sequence (real part)
      for (int i = 0; i < N; i++) {
        x[i] = int_buffer[i];
      }
      if (!I) {
        uint8_t dpcm = x[0];
        uint8_t dpcm2 = x[0];
        I = true;
      }
      uint8_t dpcm_old = dpcm;
      uint8_t dpcm_old2 = dpcm;
      for (int delta = 0; delta < 64; delta++) {
        dpcm = dpcm_old;
        dpcm2 = dpcm_old2;
        dist[delta] = 0;
        for (int i = 0; i < N; i++) {
          int min_dist = INT_MAX;
          int min_pos = 0;
          for (int k = 0; k < 4; k++) {
            for (int j = 0; j < 4; j++) {
              int dist = abs(x[i] - (dpcm + (delta * dpcm_vals[j])));
              if (dist < min_dist) {
                min_pos = j;
                min_dist = dist;
              }
            }
          }
          uint16_t d = dpcm;
          dpcm += delta * dpcm_vals[min_pos];
          d += delta * dpcm_vals[min_pos];
          if (d != dpcm) {
            dist[delta] = INT_MAX;
            continue;
          }
          // dpcm = clamp(dpcm,0,255);
          dpcm3 = dpcm;
          dpcm2 = dpcm;
          dist[delta] += (long)abs(((int)x[i]) - ((int)dpcm3));
        }
      }
      dpcm = dpcm_old;
      dpcm2 = dpcm_old2;
      int min_dist = INT_MAX;
      int min_pos = 0;
      for (int j = 0; j < 256; j++) {
        for (int i = 0; i < 64; i++) {
          if (dist[i] < min_dist) {
            min_dist = dist[i];
            min_pos = i;
          }
        }
      }
      delta_size = min_pos;
      fwrite(&delta_size, 1, 1, wfile);
      uint8_t byte = 0;
      uint8_t byte_count = 0;
      for (int i = 0; i < N; i++) {
        int min_dist = INT_MAX;
        int min_pos = 0;
        for (int k = 0; k < 4; k++) {
          for (int j = 0; j < 4; j++) {
            int dist = abs(x[i] - (dpcm + (delta_size * dpcm_vals[j])));
            if (dist < min_dist) {
              min_pos = j;
              min_dist = dist;
            }
          }
        }
        dpcm += delta_size * dpcm_vals[min_pos];
        // dpcm = clamp(dpcm,0,255);
        dpcm3 = dpcm;
        byte = (byte << 2) | min_pos;
        byte_count++;
        if (byte_count == 4) {
          fwrite(&byte, 1, 1, wfile);
          byte_count = 0;
        }
        dpcm2 = dpcm;
      }
    }
  } else {
    printf("Cannot read file\n");
    return 1;
  }
  delta_size = 0xff;
  fwrite(&delta_size, 1, 1, wfile);
  fclose(file);
  fclose(wfile);

  return 0;
}

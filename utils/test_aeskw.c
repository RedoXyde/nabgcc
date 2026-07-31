/**
 * @file test_aeskw.c
 * @brief Host-side vectors for the real AES-128 decrypt + RFC 3394 unwrap
 *
 * Never debug a cipher on the device: run this on the development machine
 * before any of it is wired into eapol.c.
 *
 *   cc -Iinc -o /tmp/test_aeskw utils/test_aeskw.c src/net/aes128.c
 *   /tmp/test_aeskw
 *
 * Exits 0 with "ALL PASS" only if every vector holds.
 */
#include <stdio.h>
#include <string.h>

#include "net/aes128.h"

static int failures;

static void check(const char *name, int ok)
{
  printf("%-40s %s\n", name, ok ? "PASS" : "FAIL");
  if(!ok) failures++;
}

int main(void)
{
  /* FIPS-197 Appendix C.1: AES-128 */
  static const uint8_t key[16] = {
    0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,
    0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f
  };
  static const uint8_t plain[16] = {
    0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,
    0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff
  };
  static const uint8_t cipher[16] = {
    0x69,0xc4,0xe0,0xd8,0x6a,0x7b,0x04,0x30,
    0xd8,0xcd,0xb7,0x80,0x70,0xb4,0xc5,0x5a
  };

  /* RFC 3394 section 4.1: wrap 128 bits of key data with a 128-bit KEK */
  static const uint8_t kek[16] = {
    0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,
    0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f
  };
  static const uint8_t wrapped[24] = {
    0x1f,0xa6,0x8b,0x0a,0x81,0x12,0xb4,0x47,
    0xae,0xf3,0x4b,0xd8,0xfb,0x5a,0x7b,0x82,
    0x9d,0x3e,0x86,0x23,0x71,0xd2,0xcf,0xe5
  };
  static const uint8_t keydata[16] = {
    0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,
    0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff
  };

  struct aes128_dec ctx;
  uint8_t buf[32];
  uint8_t corrupt[24];

  aes128_dec_init(&ctx, key);
  aes128_dec_block(&ctx, buf, cipher);
  check("FIPS-197 C.1 decrypt", memcmp(buf, plain, 16) == 0);

  aes128_dec_block(&ctx, buf, buf);
  check("in-place aliasing differs from input", memcmp(buf, plain, 16) != 0);

  check("RFC 3394 4.1 unwrap accepts",
        aes_key_unwrap(kek, wrapped, sizeof(wrapped), buf) == 1);
  check("RFC 3394 4.1 unwrap key data", memcmp(buf, keydata, 16) == 0);

  memcpy(corrupt, wrapped, sizeof(corrupt));
  corrupt[9] ^= 0x01;
  check("corrupted wrap rejected",
        aes_key_unwrap(kek, corrupt, sizeof(corrupt), buf) == 0);

  check("short input rejected", aes_key_unwrap(kek, wrapped, 16, buf) == 0);
  check("ragged length rejected", aes_key_unwrap(kek, wrapped, 23, buf) == 0);

  /* GTK KDE surrounded by an RSN IE (type 0x30) and a pad KDE, as APs
   * actually lay out msg3 key data. GTK = 16 bytes of 0xAA, key id 2.
   * KDE length = OUI(3) + data type(1) + keyid/reserved(2) + GTK(16)
   * = 22 = 0x16 (802.11-2016 figure 12-34). */
  {
    static const uint8_t keydata_kde[] = {
      0x30, 0x04, 0x01, 0x00, 0x00, 0x0f,             /* RSN IE, skipped */
      0xdd, 0x16, 0x00, 0x0f, 0xac, 0x01,             /* GTK KDE */
      0x02, 0x00,                                     /* key id 2, tx=0 */
      0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,
      0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,
      0xdd, 0x00                                      /* pad KDE */
    };
    uint8_t g[32];
    uint32_t glen = 0;
    uint8_t kid = 0;
    int ok = rsn_find_gtk(keydata_kde, sizeof(keydata_kde), g, sizeof(g),
                          &glen, &kid);
    check("GTK KDE found", ok == 1);
    check("GTK KDE length", glen == 16);
    check("GTK KDE key id", kid == 2);
    check("GTK KDE key bytes", ok && g[0] == 0xaa && g[15] == 0xaa);

    check("no GTK in plain RSN IE",
          rsn_find_gtk(keydata_kde, 6, g, sizeof(g), &glen, &kid) == 0);
    check("GTK too big for caller rejected",
          rsn_find_gtk(keydata_kde, sizeof(keydata_kde), g, 8,
                       &glen, &kid) == 0);
    check("truncated KDE rejected",
          rsn_find_gtk(keydata_kde, 12, g, sizeof(g), &glen, &kid) == 0);
  }

  if(failures) {
    printf("%d FAILURE(S)\n", failures);
    return 1;
  }
  printf("ALL PASS\n");
  return 0;
}

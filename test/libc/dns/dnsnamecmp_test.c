/*-*- mode:c;indent-tabs-mode:nil;c-basic-offset:2;tab-width:8;coding:utf-8 -*-│
│vi: set net ft=c ts=2 sts=2 sw=2 fenc=utf-8                                :vi│
╞══════════════════════════════════════════════════════════════════════════════╡
│ Copyright 2020 Justine Alexandra Roberts Tunney                              │
│                                                                              │
│ This program is free software; you can redistribute it and/or modify         │
│ it under the terms of the GNU General Public License as published by         │
│ the Free Software Foundation; version 2 of the License.                      │
│                                                                              │
│ This program is distributed in the hope that it will be useful, but          │
│ WITHOUT ANY WARRANTY; without even the implied warranty of                   │
│ MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU             │
│ General Public License for more details.                                     │
│                                                                              │
│ You should have received a copy of the GNU General Public License            │
│ along with this program; if not, write to the Free Software                  │
│ Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA                │
│ 02110-1301 USA                                                               │
╚─────────────────────────────────────────────────────────────────────────────*/
#include "libc/dns/dns.h"
#include "libc/str/str.h"
#include "libc/testlib/testlib.h"

TEST(dnsnamecmp, testEmpty) {
  char *A = strcpy(tmalloc(1), "");
  char *B = strcpy(tmalloc(1), "");
  EXPECT_EQ(dnsnamecmp(A, B), 0);
  EXPECT_EQ(dnsnamecmp(A, A), 0);
  tfree(B);
  tfree(A);
}

TEST(dnsnamecmp, testDotless_caseInsensitiveBehavior) {
  char *A = tmalloc(2);
  char *B = tmalloc(2);
  EXPECT_EQ(dnsnamecmp(strcpy(A, "a"), strcpy(B, "a")), 0);
  EXPECT_EQ(dnsnamecmp(A, A), 0);
  EXPECT_EQ(dnsnamecmp(strcpy(A, "a"), strcpy(B, "A")), 0);
  EXPECT_EQ(dnsnamecmp(strcpy(A, "A"), strcpy(B, "a")), 0);
  EXPECT_LT(dnsnamecmp(strcpy(A, "a"), strcpy(B, "b")), 0);
  EXPECT_LT(dnsnamecmp(strcpy(A, "a"), strcpy(B, "B")), 0);
  EXPECT_GT(dnsnamecmp(strcpy(A, "d"), strcpy(B, "a")), 0);
  tfree(B);
  tfree(A);
}

TEST(dnsnamecmp, testMultiLabel_lexiReverse) {
  char *A = tmalloc(16);
  char *B = tmalloc(16);
  EXPECT_EQ(dnsnamecmp(strcpy(A, "a.example"), strcpy(B, "a.example")), 0);
  EXPECT_GT(dnsnamecmp(strcpy(A, "b.example"), strcpy(B, "a.example")), 0);
  EXPECT_LT(dnsnamecmp(strcpy(A, "b.example"), strcpy(B, "a.examplz")), 0);
  EXPECT_GT(dnsnamecmp(strcpy(A, "a.zxample"), strcpy(B, "a.examplz")), 0);
  EXPECT_EQ(dnsnamecmp(strcpy(A, "c.a.example"), strcpy(B, "c.a.example")), 0);
  EXPECT_GT(dnsnamecmp(strcpy(A, "d.a.example"), strcpy(B, "c.a.example")), 0);
  EXPECT_LT(dnsnamecmp(strcpy(A, "cat.example"), strcpy(B, "lol.example")), 0);
  tfree(B);
  tfree(A);
}

TEST(dnsnamecmp, testTldDotQualifier_canBeEqualToDottedNames) {
  char *A = tmalloc(16);
  char *B = tmalloc(16);
  EXPECT_EQ(dnsnamecmp(strcpy(B, "aaa.example."), strcpy(A, "aaa.example")), 0);
  tfree(B);
  tfree(A);
}

TEST(dnsnamecmp, testFullyQualified_alwaysComesFirst) {
  char *A = tmalloc(16);
  char *B = tmalloc(16);
  EXPECT_LT(dnsnamecmp(strcpy(B, "aaa.example."), strcpy(A, "zzz")), 0);
  EXPECT_LT(dnsnamecmp(strcpy(B, "zzz.example."), strcpy(A, "aaa")), 0);
  EXPECT_GT(dnsnamecmp(strcpy(A, "zzz"), strcpy(B, "aaa.example.")), 0);
  EXPECT_GT(dnsnamecmp(strcpy(A, "aaa"), strcpy(B, "zzz.example.")), 0);
  tfree(B);
  tfree(A);
}

TEST(dnsnamecmp, testLikelySld_alwaysComesBeforeLocalName) {
  char *A = tmalloc(16);
  char *B = tmalloc(16);
  EXPECT_LT(dnsnamecmp(strcpy(B, "z.e"), strcpy(A, "a")), 0);
  EXPECT_LT(dnsnamecmp(strcpy(B, "aaa.example"), strcpy(A, "zzz")), 0);
  EXPECT_LT(dnsnamecmp(strcpy(B, "zzz.example"), strcpy(A, "aaa")), 0);
  EXPECT_GT(dnsnamecmp(strcpy(A, "zzz"), strcpy(B, "aaa.example")), 0);
  EXPECT_GT(dnsnamecmp(strcpy(A, "aaa"), strcpy(B, "zzz.example")), 0);
  tfree(B);
  tfree(A);
}

TEST(dnsnamecmp, testLikelySubdomain_alwaysComesAfterSld) {
  char *A = tmalloc(16);
  char *B = tmalloc(16);
  EXPECT_LT(dnsnamecmp(strcpy(B, "a.e"), strcpy(A, "z.a.e")), 0);
  EXPECT_GT(dnsnamecmp(strcpy(A, "z.a.e"), strcpy(B, "a.e")), 0);
  EXPECT_LT(dnsnamecmp(strcpy(B, "b.e"), strcpy(A, "a.b.e")), 0);
  EXPECT_GT(dnsnamecmp(strcpy(A, "a.b.e"), strcpy(B, "b.e")), 0);
  tfree(B);
  tfree(A);
}
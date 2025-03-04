/*-*- mode:c;indent-tabs-mode:nil;c-basic-offset:2;tab-width:8;coding:utf-8 -*-│
│vi: set net ft=c ts=2 sts=2 sw=2 fenc=utf-8                                :vi│
╞══════════════════════════════════════════════════════════════════════════════╡
│ Copyright 2022 Justine Alexandra Roberts Tunney                              │
│                                                                              │
│ Permission to use, copy, modify, and/or distribute this software for         │
│ any purpose with or without fee is hereby granted, provided that the         │
│ above copyright notice and this permission notice appear in all copies.      │
│                                                                              │
│ THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL                │
│ WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED                │
│ WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE             │
│ AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL         │
│ DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR        │
│ PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER               │
│ TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR             │
│ PERFORMANCE OF THIS SOFTWARE.                                                │
╚─────────────────────────────────────────────────────────────────────────────*/
#include "libc/intrin/describeflags.internal.h"
#include "libc/macros.internal.h"
#include "libc/nt/enum/consolemodeflags.h"
#include "libc/sysv/consts/map.h"
#include "libc/sysv/consts/prot.h"

#ifdef DescribeMapFlags
#undef DescribeMapFlags
#endif

const char *DescribeMapFlags(char buf[64], int x) {
  const struct DescribeFlags kMapFlags[] = {
      {MAP_STACK, "STACK"},                      // order matters
      {MAP_PRIVATE, "PRIVATE"},                  //
      {MAP_ANONYMOUS, "ANONYMOUS"},              //
      {MAP_SHARED, "SHARED"},                    //
      {MAP_FIXED, "FIXED"},                      //
      {MAP_FIXED_NOREPLACE, "FIXED_NOREPLACE"},  //
      {MAP_CONCEAL, "CONCEAL"},                  //
      {MAP_HUGETLB, "HUGETLB"},                  //
      {MAP_LOCKED, "LOCKED"},                    //
      {MAP_NORESERVE, "NORESERVE"},              //
      {MAP_NONBLOCK, "NONBLOCK"},                //
      {MAP_POPULATE, "POPULATE"},                //
  };
  return DescribeFlags(buf, 64, kMapFlags, ARRAYLEN(kMapFlags), "MAP_", x);
}

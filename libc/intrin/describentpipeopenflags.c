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
#include "libc/nt/enum/filemapflags.h"
#include "libc/nt/ipc.h"

#ifdef DescribeNtPipeOpenFlags
#undef DescribeNtPipeOpenFlags
#endif

static const struct DescribeFlags kPipeOpenFlags[] = {
    {kNtPipeAccessDuplex, "Duplex"},      // 0x00000003
    {kNtPipeAccessOutbound, "Outbound"},  // 0x00000002
    {kNtPipeAccessInbound, "Inbound"},    // 0x00000001
};

const char *DescribeNtPipeOpenFlags(char buf[64], uint32_t x) {
  return DescribeFlags(buf, 64, kPipeOpenFlags, ARRAYLEN(kPipeOpenFlags),
                       "kNtPipeAccess", x);
}

/*-*- mode:c;indent-tabs-mode:nil;c-basic-offset:2;tab-width:8;coding:utf-8 -*-│
│vi: set net ft=c ts=2 sts=2 sw=2 fenc=utf-8                                :vi│
╞══════════════════════════════════════════════════════════════════════════════╡
│ Copyright 2020 Justine Alexandra Roberts Tunney                              │
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
#include "libc/calls/struct/metastat.internal.h"
#include "libc/calls/syscall-sysv.internal.h"
#include "libc/dce.h"
#include "libc/intrin/asan.internal.h"
#include "libc/sysv/errfuns.h"

/**
 * Performs fstatat() on System Five.
 * @asyncsignalsafe
 */
int32_t sys_fstatat(int32_t dirfd, const char *path, struct stat *st,
                    int32_t flags) {
  int rc;
  void *p;
  union metastat ms;
  if (IsAsan() && !__asan_is_valid_str(path)) return efault();
  if (IsLinux()) {
    _Static_assert(sizeof(*st) == sizeof(ms.linux), "assumption broken");
    if (IsAsan() && (st && !__asan_is_valid(st, sizeof(*st)))) return efault();
    p = st;
  } else if (st) {
    p = &ms;
  } else {
    p = 0;
  }
  if (__sys_fstatat(dirfd, path, p, flags) != -1) {
    __stat2cosmo(st, &ms);
    return 0;
  } else {
    return -1;
  }
}

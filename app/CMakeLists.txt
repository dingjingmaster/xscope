file(GLOB X_SCOPE_SRC
        bigreqscope.h  config.h      fd.h      glxscope.h  nas.h    randrscope.h   scope.h     wcpscope.h
        common.h       extensions.h  global.h  lbxscope.h  proto.h  renderscope.h  shmscope.h  x11.h

        audio.c          decode_glx.c    decode_render.c  fd.c            print_glx.c    print_render.c  scope.c            tablenas.c
        common.c         decode_lbx.c    decode_shm.c     print_lbx.c    print_shm.c     scope-transport.c  xstats.c
        decode11.c       decodenas.c     decode_wcp.c     print11.c       printnas.c     print_wcp.c     server.c
        decode_bigreq.c  decode_randr.c  extensions.c     print_bigreq.c  print_randr.c  prtype.c        table11.c
        )

add_executable(xscope ${X_SCOPE_SRC})
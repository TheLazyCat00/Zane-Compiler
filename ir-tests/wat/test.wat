(module
  (import "wasi_snapshot_preview1" "fd_write"
    (func $fd_write (param i32 i32 i32 i32) (result i32)))

  (memory $mem 1)
  (export "memory" (memory $mem))

  (data (i32.const 0) "Hello, World!\n")

  (func $_start
    i32.const 1      ;; stdout
    i32.const 0      ;; pointer to string
    i32.const 1      ;; iovec count
    i32.const 20     ;; result pointer
    call $fd_write
    drop              ;; remove returned i32
  )
  (export "_start" (func $_start))
)

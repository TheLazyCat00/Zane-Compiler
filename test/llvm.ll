; ModuleID = 'zane'
source_filename = "zane"

@0 = private unnamed_addr constant [8 x i8] c"\22Hello\22\00", align 1
@1 = private unnamed_addr constant [6 x i8] c"\22Bye\22\00", align 1
@2 = private unnamed_addr constant [5 x i8] c"\22Hi\22\00", align 1

declare i32 @puts(ptr)

define void @main() {
entry:
  %0 = call i32 @puts(ptr @0)
  %1 = call i32 @puts(ptr @1)
  ret void
}

define void @greet() {
entry:
  %0 = call i32 @puts(ptr @2)
  ret void
}

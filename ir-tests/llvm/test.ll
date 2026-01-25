declare i32 @printf(i8*, ...)

@hi = private unnamed_addr global [3 x i8] c"hi\00"
@bchar = private unnamed_addr constant [2 x i8] c"b\00"

define void @sayHi() {
entry:
	%0 = getelementptr [3 x i8], [3 x i8]* @hi, i32 0, i32 0
	call i32 (i8*, ...) @printf(i8* %0)

	ret void
}

define i32 @main() {
entry:
	%bptr = getelementptr [2 x i8], [2 x i8]* @bchar, i32 0, i32 0
	%b = load i8, i8* %bptr

	%ptr0 = getelementptr [3 x i8], [3 x i8]* @hi, i32 0, i32 0
	store i8 %b, i8* %ptr0

	call void @sayHi()
	ret i32 0
}

package instructions

type Variable struct {
	Name string
	Type string
	IsConst bool
}

type Parameter struct {
	Name string
	Type string
}

type FunctionType int
const (
	OpenFunction FunctionType = iota
	RealTimeFunction
	PureFunction
)

type Function struct {
	Name string
	ReturnType string
	Parameters []Parameter
	Type FunctionType
}

type Visibility int
const (
	Public Visibility = iota
	Private
)

type Field struct {
	Variable Variable
	Visibility Visibility
}

type Object struct {
	Name string
	Fields []Field
}

type Method struct {
	Receiver Object
	Function Function
}

func DeclareVariable(name string, value Object) {

}

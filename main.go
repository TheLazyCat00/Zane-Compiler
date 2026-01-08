package main

import (
	"encoding/json"
	"fmt"
	"os"
	// "reflect"
	"zane/parsergen"
	"zane/preprocessor"
)

func main() {
	if len(os.Args) < 2 {
		fmt.Println("Usage: zane <filepath>")
		os.Exit(1)
	}

	// Preprocessor
	file, err := preprocessor.NewFile(os.Args[1])
	if err != nil {
		fmt.Println("Error:", err)
		os.Exit(1)
	}

	ast := parsergen.Process(file.Buffer)

	encoder := json.NewEncoder(os.Stdout)
	encoder.SetEscapeHTML(false)
	encoder.SetIndent("", "  ")
	
	if err := encoder.Encode(ast); err != nil {
		fmt.Println("Error marshaling AST:", err)
		os.Exit(1)
	}
}

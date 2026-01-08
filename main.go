package main

import (
	"encoding/json"
	"fmt"
	"os"
	"reflect"
	"zane/parsergen"
	"zane/preprocessor"
)

func removeNulls(data interface{}) interface{} {
	v := reflect.ValueOf(data)
	if !v.IsValid() {
		return nil
	}

	switch v.Kind() {
	case reflect.Ptr:
		if v.IsNil() {
			return nil
		}
		return removeNulls(v.Elem().Interface())
	case reflect.Struct:
		result := make(map[string]interface{})
		t := v.Type()
		for i := 0; i < v.NumField(); i++ {
			field := v.Field(i)
			fieldName := t.Field(i).Name
			cleanedValue := removeNulls(field.Interface())
			if cleanedValue != nil {
				result[fieldName] = cleanedValue
			}
		}
		if len(result) == 0 {
			return nil
		}
		return result
	case reflect.Slice:
		if v.IsNil() || v.Len() == 0 {
			return nil
		}
		result := make([]interface{}, 0, v.Len())
		for i := 0; i < v.Len(); i++ {
			cleanedValue := removeNulls(v.Index(i).Interface())
			if cleanedValue != nil {
				result = append(result, cleanedValue)
			}
		}
		if len(result) == 0 {
			return nil
		}
		return result
	case reflect.Map:
		if v.IsNil() || v.Len() == 0 {
			return nil
		}
		result := make(map[string]interface{})
		for _, key := range v.MapKeys() {
			cleanedValue := removeNulls(v.MapIndex(key).Interface())
			if cleanedValue != nil {
				result[key.String()] = cleanedValue
			}
		}
		if len(result) == 0 {
			return nil
		}
		return result
	default:
		// For basic types (string, int, bool, float64, etc.)
		// Check for zero values
		if v.IsZero() {
			return nil
		}
		return data
	}
}

func main() {
	if len(os.Args) < 2 {
		fmt. Println("Usage: zane <filepath>")
		os.Exit(1)
	}

	// Preprocessor
	file, err := preprocessor.NewFile(os.Args[1])
	if err != nil {
		fmt.Println("Error:", err)
		os.Exit(1)
	}

	ast := parsergen.Process(file.Buffer)

	// Pretty print the AST (remove nulls)
	cleanedAST := removeNulls(ast)
	jsonData, err := json.MarshalIndent(cleanedAST, "", "  ")
	if err != nil {
		fmt.Println("Error marshaling AST:", err)
		os.Exit(1)
	}
	fmt.Println(string(jsonData))
}

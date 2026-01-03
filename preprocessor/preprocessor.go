package preprocessor

import (
	"os"
	"zane/types"
)

func NewFile(filename string) (* types.File, error) {
	content, err := os.ReadFile(filename)
	if err != nil {
		return nil, err
	}

	return &types.File {
		Name:   filename,
		Buffer: string(content),
	}, nil
}


func Process(f * types.File) {
	f.StripComments()
}

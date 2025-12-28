package preprocessor

import (
	"os"
	"strings"
	"zane/types"
)

func NewFile(filename string) (* types.File, error) {
	content, err := os.ReadFile(filename)
	if err != nil {
		return nil, err
	}

	return &types.File {
		Name:   filename,
		Buffer: strings.Split(string(content), "\n"),
	}, nil
}


func Process(f * types.File) {
	f.StripComments()
}

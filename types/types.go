package types

import (
	"strings"
)

type Buffer = []string
type File struct {
	Name   string
	Buffer Buffer
}

func (f * File) StripComments() {
	for i, line := range f.Buffer {
		f.Buffer[i], _, _ = strings.Cut(line, "//")
	}
}

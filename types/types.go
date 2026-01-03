package types

import (
	"strings"
)

type File struct {
	Name   string
	Buffer string
}

func (f *File) StripComments() {
	lines := strings.Split(f.Buffer, "\n")

	for i, line := range lines {
		lines[i], _, _ = strings.Cut(line, "//")
	}

	f.Buffer = strings.Join(lines, "\n")
}

#!/bin/bash

watchfiles --ignore-paths ./generated_parser 'bash -c "clear && go generate ./... && go run main.go test.txt"' .
